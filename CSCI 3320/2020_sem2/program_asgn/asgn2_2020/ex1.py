import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split

def logistic_func(x):

    L = 1/(1+np.e**(-x))
    
    return L

def train(X_train, y_train, tol = 10 ** -4):

    LearningRate = 0.05
    
    weights, wp = [],[]
    # w0 is the last element of weights
    for i in range(len(X_train[0])+1): 
        weights.append(np.random.random_sample())
        wp.append(2)

    weights = np.asarray(weights)
    wp = np.asarray(wp)
    while(np.linalg.norm(wp-weights) > tol):
        wp = weights.copy()
        y_pred = logistic_func(np.matmul(X_train,weights[:-1])+weights[-1])
        
        ##update
        diff = 0
        for i in range(len(X_train[0])): #update wi
            weights[i] += LearningRate * sum((y_train - y_pred) * X_train.T[i])
            
        weights[-1] += LearningRate * sum(y_train - y_pred) #update w0
        #print(np.linalg.norm(wp-weights))
    return weights

def train_matrix(X_train, y_train, tol = 10 ** -4):

    LearningRate = 0.05
    
    weights = []
    for i in range(len(X_train[0])+1): 
        weights.append(np.random.random_sample())
    weights = np.asarray(weights).reshape(len(X_train[0])+1,1)
    
    ones = np.ones(len(X_train)).reshape(len(X_train),1)
    X_form = np.concatenate((ones,X_train),axis=1)
    
    wp = weights.copy()+1
    while(np.linalg.norm(wp-weights) > tol):
        wp = weights.copy()
        loss = (y_train - logistic_func(np.matmul(X_form,weights)).T)
        weights += LearningRate * np.matmul(loss ,X_form).T
    weights = weights.reshape(len(weights),)
    weights = np.roll(weights,-1)
    return weights

def predict(X_test, weights):

    predictions = logistic_func(np.matmul(X_test,weights[:-1]) + weights[-1])
    predictions[predictions >= 0.5] = 1
    predictions[predictions < 0.5] = 0
    
    return predictions

def plot_prediction(X_test, X_test_prediction):
    X_test1 = X_test[X_test_prediction == 0, :]
    X_test2 = X_test[X_test_prediction == 1, :]
    plt.scatter(X_test1[:, 0], X_test1[:, 1], color='red')
    plt.scatter(X_test2[:, 0], X_test2[:, 1], color='blue')
    plt.show()


#Data Generation
n_samples = 1000

centers = [(-1, -1), (5, 10)]
X, y = make_blobs(n_samples=n_samples, n_features=2, cluster_std=1.8,
                  centers=centers, shuffle=False, random_state=42)

X_train, X_test, y_train, y_test = train_test_split(X, y,random_state=42)

# Experiments
w = train_matrix(X_train, y_train)
X_test_prediction = predict(X_test, w)
plot_prediction(X_test, X_test_prediction)
plot_prediction(X_test, y_test)

wrong = np.count_nonzero(y_test - X_test_prediction)
print ('Number of wrong predictions is: ' + str(wrong))
