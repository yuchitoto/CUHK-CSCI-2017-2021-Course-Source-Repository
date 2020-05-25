from __future__ import print_function
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt

from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans
from sklearn import metrics

def create_dataset():
    # Generate sample points
    centers = [[3,5], [5,1], [8,2], [6,8], [9,7]]
    X, y = make_blobs(n_samples=1000,centers=centers,cluster_std=[0.5, 0.5, 1, 1, 1],random_state=3320)
    # =======================================
    # Complete the code here.
    # Plot the data points in a scatter plot.
    # Use color to represents the clusters.
    # =======================================
    clabel = []
    for i in y:
        if i == 0: clabel.append('r') #red
        elif i == 1: clabel.append('g') #green
        elif i == 2: clabel.append('b') #blue
        elif i == 3: clabel.append('y') #yellow
        elif i == 4: clabel.append('c') #cyan
    plt.scatter(X[:, 0], X[:, 1], c=clabel, edgecolor = 'w')
    plt.title('Groundtruth Graph')
    plt.xlabel('dim1')
    plt.ylabel('dim2')
    plt.show()
    return [X, y]

def my_clustering(X, y, n_clusters):
    # =======================================
    # Complete the code here.
    # you need to
    #   1. Implement the k-means by yourself
    #   and cluster samples into n_clusters clusters using your own k-means
    #
    #   2. Print out all cluster centers.
    #
    #   3. Plot all clusters formed,
    #   and use different colors to represent clusters defined by k-means.
    #   Draw a marker (e.g., a circle or the cluster id) at each cluster center.
    #
    #   4. Return scores like this: return [score, score, score, score]
    # =======================================
    color = ['r','g','b','y','c','m']   
     
    centers = [[],[]]
    for i in range(n_clusters):
        x1 = np.random.uniform(X.T[0].max(),X.T[0].min()) 
        while(x1 in centers[0]): x1 = np.random.uniform(X.T[0].max(),X.T[0].min()) #prevent diff centroid locates at the same pos
        centers[0].append(x1)
        x2 = np.random.uniform(X.T[1].max(),X.T[1].min())
        while(x2 in centers[1]): x2 = np.random.uniform(X.T[1].max(),X.T[1].min()) #..
        centers[1].append(x2)
    centers = np.asarray(centers).T
    ls,predls = [],[]
    old_centers,centers = list(np.zeros(centers.shape)),list(centers)
    itr=0
    while (np.linalg.norm(np.asarray(old_centers)-np.asarray(centers))>0.001 and itr<200):
        #print('itr:',itr)
        itr+=1
        predls.clear()
        #cluster assignment
        ls.clear()
        for i in range(n_clusters): ls.append([])
        for i in X:
            mini = max(X.T[0].max(), X.T[1].max())
            min_class = -1
            for j in range(n_clusters):
                if np.linalg.norm(i-centers[j])<mini: 
                    mini = np.linalg.norm(i-centers[j])
                    min_class = j
            #print(i,"in class",min_class)
            ls[min_class].append(i)
            predls.append(min_class)

        #centroid adjustment
        old_centers = centers.copy()
        centers.clear()
        for i,val in enumerate(ls):
            #actually can have zero pt be clustered in the class -> T have no data
            h = np.asarray(val).T[0].mean() if len(val)>0 else np.random.uniform(X.T[0].max(),X.T[0].min())
            k = np.asarray(val).T[1].mean() if len(val)>0 else np.random.uniform(X.T[1].max(),X.T[1].min())
            centers.append([h,k])
            #print(i,":",'[',h,k,']')
    for i,val in enumerate(centers):
        print('Position of the {} center: [{:.2},{:.2}]'.format(i,val[0],val[1]))
    for i in range(n_clusters):
        ls[i] = np.asarray(ls[i]).T
        plt.scatter(ls[i][0],ls[i][1], color=color[i], edgecolor = 'w')
        plt.scatter(centers[i][0],centers[i][1], color=color[i], edgecolor = 'k', s = 40)
    plt.title('Clustered Data ({} clusters)'.format(n_clusters))
    plt.xlabel('dim1')
    plt.ylabel('dim2')
    plt.show()
    
    #find the ground truth ls
    return [metrics.adjusted_rand_score(y,predls),
            metrics.mutual_info_score(y,predls),
            metrics.v_measure_score(y,predls),
            metrics.silhouette_score(X,predls)]  # You won't need this line when you are done

def main():
    X, y = create_dataset()
    range_n_clusters = [2, 3, 4, 5, 6]
    ari_score = [None] * len(range_n_clusters)
    mri_score = [None] * len(range_n_clusters)
    v_measure_score = [None] * len(range_n_clusters)
    silhouette_avg = [None] * len(range_n_clusters)
    elbow_score = [None] * len(range_n_clusters)

    for n_clusters in range_n_clusters:
        i = n_clusters - range_n_clusters[0]
        print("Number of clusters is: ", n_clusters)
        # Implement the k-means by yourself in the function my_clustering
        [ari_score[i], mri_score[i], v_measure_score[i], silhouette_avg[i]] = my_clustering(X, y, n_clusters)
        print('The ARI score is: ', ari_score[i])
        print('The MRI score is: ', mri_score[i])
        print('The v-measure score is: ', v_measure_score[i])
        print('The average silhouette score is: ', silhouette_avg[i])
    
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
    # =======================================
    # Complete the code here.
    # Plot scores of all four evaluation metrics as functions of n_clusters in a single figure.
    # =======================================

if __name__ == '__main__':
    main()

