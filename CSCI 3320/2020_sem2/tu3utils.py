__author__ = "kccai"
from numpy import *


def error_function(theta_0, theta_1, points):
    totalError = 0
    for i in range(0, len(points)):
        x = points[i, 0]
        r = points[i, 1]
        totalError += (r - (theta_1 * x + theta_0)) ** 2
    return totalError / float(len(points))


def step_gradient(theta_0_current, theta_1_current, points, learningRate):
    theta_0_gradient = 0
    theta_1_gradient = 0
    N = float(len(points))
    for i in range(0, len(points)):
        x = points[i, 0]
        r = points[i, 1]
        theta_0_gradient += (-1.0) * (r - ((theta_1_current * x) + theta_0_current))
        theta_1_gradient += (-1.0) * x * (r - ((theta_1_current * x) + theta_0_current))
    theta_0_gradient = theta_0_gradient * 2 / N
    theta_1_gradient = theta_1_gradient * 2 / N
    new_theta_0 = theta_0_current - (learningRate * theta_0_gradient)
    new_theta_1 = theta_1_current - (learningRate * theta_1_gradient)
    return [new_theta_0, new_theta_1]


def gradient_descent_method(points, starting_theta_0, starting_theta_1, learning_rate, num_iterations):
    theta_0 = starting_theta_0
    theta_1 = starting_theta_1
    theta_0_track = zeros(num_iterations)
    theta_1_track = zeros(num_iterations)
    error_track = zeros(num_iterations)
    for i in range(num_iterations):
        theta_0, theta_1 = step_gradient(theta_0, theta_1, array(points), learning_rate)
        theta_0_track[i] = theta_0
        theta_1_track[i] = theta_1
        error_track[i] = error_function(theta_0, theta_1, points)
    return [theta_0, theta_1, theta_0_track, theta_1_track, error_track]


def normalize_feature(A):
    A = (A - mean(A)) / std(A)
    return A
