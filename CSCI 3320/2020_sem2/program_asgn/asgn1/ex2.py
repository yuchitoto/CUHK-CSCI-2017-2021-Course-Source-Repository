import os.path
import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

def load_data(digits = [0], num = 200):
    '''
    Loads all of the images into a data-array.

    The training data has 5000 images per digit,
    but loading that many images from the disk may take a while.  So, you can
    just use a subset of them, say 200 for training (otherwise it will take a
    long time to complete.

    Note that each image as a 28x28 grayscale image, loaded as an array and
    then reshaped into a single row-vector.

    Use the function display(row-vector) to visualize an image.

    '''
    totalsize = 0
    for digit in digits:
        totalsize += min([len(next(os.walk('train%d' % digit))[2]), num])
    print('We will load %d images' % totalsize)
    X = np.zeros((totalsize, 784), dtype = np.uint8)   #784=28*28
    for index in range(0, len(digits)):
        digit = digits[index]
        print('\nReading images of digit %d' % digit)
        for i in range(num):
            pth = os.path.join('train%d' % digit,'%05d.pgm' % i)
            image = plt.imread(pth).reshape((1, 784))
            X[i + index * num, :] = image
        print('\n')
    return X

def plot_mean_image(X, digits = [0]):
    ''' example on presenting vector as an image
    '''
    plt.close('all')
    meanrow = X.mean(0)
    # present the row vector as an image
    plt.imshow(np.reshape(meanrow,(28,28)))
    plt.title('Mean image of digit ' + str(digits))
    plt.gray(), plt.xticks(()), plt.yticks(()), plt.show()

def main():
    digits = [0, 1, 2]
    # load handwritten images of digit 0, 1, 2 into a matrix X
    # for each digit, we just use 500 images
    # each row of matrix X represents an image
    X = load_data(digits, 500)
    # plot the mean image of these images!
    # you will learn how to represent a row vector as an image in this function
    
    plot_mean_image(X, digits)
    ####################################################################
    # plot the eigen images, eigenvalue v.s. the order of eigenvalue, POV
    # v.s. the order of eigenvalue
    # you need to
    #   1. do the PCA on matrix X;
    #
    #   2. plot the eigenimages (reshape the vector to 28*28 matrix then use
    #   the function ``imshow'' in pyplot), save the images of eigenvectors
    #   which correspond to largest 9 eigenvalues. Save them in a single file
    #   ``eigenimages.jpg''.
    #
    #   3. plot the POV (the Portion of variance explained v.s. the number of
    #   components we retain), save the figure in file ``digit_pov.jpg''
    #
    #   4. report how many dimensions are need to preserve 0.95 POV, describe
    #   your answers and your undestanding of the results in the plain text
    #   file ``description.txt''
    #
    #   5. remember to submit file ``eigenimages.jpg'', ``digit_pov.jpg'',
    #   ``description.txt'' and ``ex2.py''.
    # YOUR CODE HERE!

    ####################################################################
    pca = PCA(n_components = 28*28)
    pca.fit(X)
    

    fig, ax = plt.subplots(3, 3, figsize=(6, 6))
    fig.suptitle("Eigens Images")
    for n in range(3):
        for k in range(3):
            ax[n,k].imshow(pca.components_[n].reshape(28,28), cmap=plt.cm.gray_r)
    plt.savefig('eigens_fig.png')
    plt.show()
    plt.plot(pca.explained_variance_)
    plt.xlabel('order of eigenvalues')
    plt.ylabel('eigenvalues')
    plt.title('Eigenvalues Against Order of Eigenvalues')
    plt.show()
    
    POV = []
    add = 0
    for i in pca.explained_variance_ratio_:
        add += i
        POV.append(add)
    plt.plot(POV)
    plt.xlabel('order of eigenvalues')
    plt.ylabel('POV')
    plt.title('POV Against Order of Eigenvalues')
    plt.savefig('digit_pov.png')
    plt.show()
    
    for i,val in enumerate(POV):
        if val > 0.95:
            print(i,"dimensions are needed to preserve 0.95 POV.")
            print("At",i,",it attained",val,"POV.")
            break
    

if __name__ == '__main__':
    main()
