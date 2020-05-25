import numpy as np
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

def create_data(x1, x2, x3):
    x4 = np.multiply(x2, x2)
    x5 = 10 * x1 + 10
    x6 = -1 * x2 / 2
    X = np.hstack((x1, x2, x3, x4, x5, x6))
    return X

def pca(X):
    '''
    # PCA step by step
    #   1. normalize matrix X
    #   2. compute the covariance matrix of the normalized matrix X
    #   3. do the eigenvalue decomposition on the covariance matrix
    # If you do not remember Eigenvalue Decomposition, please review the linear
    # algebra
    # In this assignment, we use the ``unbiased estimator'' of covariance. You
    # can refer to this website for more information
    # http://docs.scipy.org/doc/numpy-1.10.1/reference/generated/numpy.cov.html
    # Actually, Singular Value Decomposition (SVD) is another way to do the
    # PCA, if you are interested, you can google SVD.
    # YOUR CODE HERE!
    '''

    ####################################################################
    # here V is the matrix containing all the eigenvectors, D is the
    # column vector containing all the corresponding eigenvalues.
    mean, sd = np.zeros((1,6)), np.zeros((1,6))
    for i in X:
        mean += i
    mean = mean / X.shape[0]
    X = X - mean
    pca = PCA()
    pca.fit(X)
    #print(pca.explained_variance_,"\n\n")
    cov = np.cov(X.T)
    #D, V = np.linalg.eig(cov)
    Td, Tv = np.linalg.eigh(cov) 
    #print("D:",D)
    #print("V:",V)
    Tv = Tv.T
    idx = np.argsort(Td)[::-1]
    V = Tv[idx]
    D = Td[idx]
    return [V, D]

def main():
    N = 1000
    shape = (N, 1)
    x1 = np.random.normal(0, 1, shape) # samples from normal distribution
    x2 = np.random.exponential(10.0, shape) # samples from exponential distribution
    x3 = np.random.uniform(-100, 100, shape) # uniformly sampled data points
    X = create_data(x1, x2, x3)
    
    V,D = pca(X)
    plt.plot(D)
    plt.xlabel('order of eigenvalues')
    plt.ylabel('eigenvalues')
    plt.title('Eigenvalues Against Order of Eigenvalues')
    plt.show()
    POV = []
    add = 0
    for i in D:
        add += i
        POV.append(add/sum(D))
    plt.plot(POV)
    plt.xlabel('order of eigenvalues')
    plt.ylabel('POV')
    plt.title('POV Against Order of Eigenvalues')
    plt.show()
    ####################################################################
    # Use the definition in the lecture notes,
    #   1. perform PCA on matrix X
    #   2. plot the eigenvalues against the order of eigenvalues,
    #   3. plot POV v.s. the order of eigenvalues
    # YOUR CODE HERE!

    ####################################################################


if __name__ == '__main__':
    main()
