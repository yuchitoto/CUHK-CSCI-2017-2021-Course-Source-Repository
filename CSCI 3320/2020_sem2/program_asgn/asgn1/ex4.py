from __future__ import print_function

import os
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from scipy import misc
from struct import unpack

from sklearn import metrics
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix

def plot_mean_image(X, log):
    meanrow = X.mean(0)
    # present the row vector as an image
    plt.figure(figsize=(3,3))
    plt.imshow(np.reshape(meanrow,(28,28)), cmap=plt.cm.binary)
    plt.title('Mean image of ' + log)
    plt.show()

def get_labeled_data(imagefile, labelfile):
    """
    Read input-vector (image) and target class (label, 0-9) and return it as list of tuples.
    Adapted from: https://martin-thoma.com/classify-mnist-with-pybrain/
    """
    # Open the images with gzip in read binary mode
    images = open(imagefile, 'rb')
    labels = open(labelfile, 'rb')

    # Read the binary data
    # We have to get big endian unsigned int. So we need '>I'

    # Get metadata for images
    images.read(4)  # skip the magic_number
    number_of_images = images.read(4)
    number_of_images = unpack('>I', number_of_images)[0]
    rows = images.read(4)
    rows = unpack('>I', rows)[0]
    cols = images.read(4)
    cols = unpack('>I', cols)[0]

    # Get metadata for labels
    labels.read(4)  # skip the magic_number
    N = labels.read(4)
    N = unpack('>I', N)[0]

    if number_of_images != N:
        raise Exception('number of labels did not match the number of images')

    # Get the data
    X = np.zeros((N, rows * cols), dtype=np.uint8)  # Initialize numpy array
    y = np.zeros(N, dtype=np.uint8)  # Initialize numpy array
    for i in range(N):
        for id in range(rows * cols):
            tmp_pixel = images.read(1)  # Just a single byte
            tmp_pixel = unpack('>B', tmp_pixel)[0]
            X[i][id] = tmp_pixel
        tmp_label = labels.read(1)
        y[i] = unpack('>B', tmp_label)[0]
    return (X, y)


def my_clustering_mnist(X, y, n_clusters):
    # =======================================
    # Complete the code here.
    # you need to
    #   1. Cluster images into n_clusters clusters using the k-means implemented by yourself or the one provided in scikit-learn.
    #
    #   2. Plot centers of clusters as images and combine these images in a single figure.
    #
    #   3. Return scores like this: return [score, score, score, score]
    # =======================================
    kmeans = KMeans(n_clusters=n_clusters, random_state=0, n_jobs=-1).fit(X)
    fig, ax = plt.subplots(1, n_clusters, figsize=(16, 2))
    for n in range(n_clusters):
        ax[n].imshow(kmeans.cluster_centers_[n].reshape(28,28), cmap=plt.cm.gray_r)
    plt.show()
    #plt.savefig('meanimages.jpg')
    
    #find the ground truth ls
    return [metrics.adjusted_rand_score(y,kmeans.labels_),
            metrics.mutual_info_score(y,kmeans.labels_),
            metrics.v_measure_score(y,kmeans.labels_),
            metrics.silhouette_score(X,kmeans.labels_),]  

def main():
    # Load the dataset
    fname_img = 't10k-images.idx3-ubyte'
    fname_lbl = 't10k-labels.idx1-ubyte'
    [X, y]=get_labeled_data(fname_img, fname_lbl)

    # Plot the mean image
    plot_mean_image(X, 'all images')

    # =======================================
    # Complete the code here.
    # Use PCA to reduce the dimension here.
    # You may want to use the following codes. Feel free to write in your own way.
    # - pca = PCA(n_components=...)
    # - pca.fit(X)
    # - print('We need', pca.n_components_, 'dimensions to preserve 0.9 POV')
    # =======================================

    pca = PCA(n_components = 28*28)
    pca.fit(X)
    
    POV = []
    add, reduced_d = 0, 0
    for i in pca.explained_variance_:
        add += i
        POV.append(add/pca.explained_variance_.sum())
    plt.plot(POV)
    plt.xlabel('order of eigenvalues')
    plt.ylabel('POV')
    plt.title('POV Against Order of Eigenvalues')
    plt.show()

    
    for i,val in enumerate(POV):
        if val > 0.90:
            reduced_d = i
            print(i,"dimensions are needed to preserve 0.90 POV.")
            print("At",i,",it attained",val,"POV.")
            break 
    print("shape:",pca.components_.shape)
            
    #pca = PCA(n_components = reduced_d)
    #X = pca.fit(X).transform(X)
    
    # Clustering 
    #I have actually plot more to see whether 8 is highest in the metric evaluation
    range_n_clusters = [8, 9, 10, 11, 12]
    ari_score = [None] * len(range_n_clusters)
    mri_score = [None] * len(range_n_clusters)
    v_measure_score = [None] * len(range_n_clusters)
    silhouette_avg = [None] * len(range_n_clusters)

    for n_clusters in range_n_clusters:
        i = n_clusters - range_n_clusters[0]
        print("Number of clusters is: ", n_clusters)
        [ari_score[i], mri_score[i], v_measure_score[i], silhouette_avg[i]] = my_clustering_mnist(X, y, n_clusters)
        print('The ARI score is: ', ari_score[i])
        print('The MRI score is: ', mri_score[i])
        print('The v-measure score is: ', v_measure_score[i])
        print('The average silhouette score is: ', silhouette_avg[i])

    # =======================================
    # Complete the code here.
    # Plot scores of all four evaluation metrics as functions of n_clusters in a single figure.
    # =======================================
    plt.plot(range_n_clusters, ari_score, label="ari score", marker='o')
    plt.plot(range_n_clusters, mri_score, label="mri score", marker='o')
    plt.plot(range_n_clusters, v_measure_score, label="v measure score", marker='o')
    plt.plot(range_n_clusters, silhouette_avg, label="silhouette score", marker='o')
    plt.title('Evalutation Metrics')
    plt.ylabel('metrics score')
    plt.xlabel('number of clusters')
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
    plt.tight_layout()  
    plt.show()
#     print(ari_score)
#     print(mri_score)
#     print(v_measure_score)
#     print(silhouette_avg)
    
if __name__ == '__main__':
    main()
