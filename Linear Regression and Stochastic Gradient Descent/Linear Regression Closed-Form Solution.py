#!/usr/bin/env python
# coding: utf-8

# In[1]:


from sklearn.datasets import load_svmlight_file
X, y = load_svmlight_file(f="housing_scale.txt", n_features=13)
X = X.toarray()


# In[2]:


import numpy
n_samples, n_features = X.shape
#print(X.shape)
X = numpy.column_stack((X, numpy.ones((n_samples, 1))))


# In[3]:


from sklearn.model_selection import train_test_split
X_train, X_validate, y_train, y_validate = train_test_split(X, y, test_size=0.2)


# In[4]:


penalty_factor = 0
learning_rate = 0.01
max_epoch = 2000
losses_train = []
losses_validate = []


# In[5]:


#w = numpy.zeros((n_features + 1, 1))


# In[6]:


from numpy.linalg import inv
w = inv(X_train.transpose().dot(X_train)).dot(X_train.transpose()).dot(y_train)
#print(w)


# In[7]:


from numpy import average, square
#print(X_train.dot(w))

loss_train_closed = 0.5*average(square(y_train-X_train.dot(w)))
loss_validate_closed = 0.5*average(square(y_validate-X_validate.dot(w)))
print("The loss under the training set is ", loss_train_closed)
print("The loss under the validating set is ", loss_validate_closed)

