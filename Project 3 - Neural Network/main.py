# James Helm
# Program 3 - Neural Network
# CS461 Fall 2021
#
# Sources used:
# https://towardsdatascience.com/multi-output-model-with-tensorflow-keras-functional-api-875dd89aa7c6
# https://www.tensorflow.org/tutorials/load_data/csv
# https://www.tensorflow.org/tutorials/keras/regression#get_the_data
# https://keras.io/api/optimizers/
# https://machinelearningmastery.com/deep-learning-models-for-multi-output-regression/

import tensorflow as tf
import numpy as np
import pandas as pd
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense, Input


# Below was kept for convenience of testing. Uncomment this for the commented out code below
# import seaborn as sns
# from matplotlib import pyplot as plt


# Function to build the model.
# Calculation of number of layers to minimize chance of overfitting below
# num_layers = (Number of samples in training) / (α * (Number of input neurons + number of output neurons))
# α = 2 chosen from testing
def build_model():
    input_layer = Input(shape=(len(train.columns),))
    first_dense = Dense(units='32', activation='relu', name='first_dense')(input_layer)
    second_dense = Dense(units='32', activation='relu', name='second_dense')(first_dense)
    math = Dense(units='1', name='math_output')(second_dense)
    reading = Dense(units='1', name='read_output')(second_dense)
    writing = Dense(units='1', name='write_output')(second_dense)

    model = Model(inputs=input_layer, outputs=[math, reading, writing])

    return model


# Helper function for formatting the output and returning 3 arrays of edited data
def format_output(data):
    y1 = data.pop('Math Score')
    y1 = np.array(y1)
    y2 = data.pop('Reading Score')
    y2 = np.array(y2)
    y3 = data.pop('Writing Score')
    y3 = np.array(y3)
    return y1, y2, y3


# Initial columns creation and data import
columns = ['Gender', 'Race/Ethnicity', 'Parental Level of Education', 'Lunch', 'Test Preparation Course', 'Math Score',
           'Reading Score', 'Writing Score']
rawDataSet = pd.read_csv('resources/StudentsPerformance.csv', names=columns,
                         na_values='?', comment='\t', sep=',', skipinitialspace=True, skiprows=1)
dataSet = rawDataSet.copy()
dataSet.tail()
np.set_printoptions(precision=0, suppress=True)

# Dataset dummy creation for non-numeric data
dataSet['Gender'] = dataSet['Gender'].map({'male': 'Male', 'female': 'Female'})
dataSet['Race/Ethnicity'] = dataSet['Race/Ethnicity'].map({'group A': 'Group A', 'group B': ' Group B',
                                                           'group C': 'Group C', 'group D': 'Group D',
                                                           'group E': 'Group E'})
dataSet['Parental Level of Education'] = \
    dataSet['Parental Level of Education'].map({'high school': 'HS', 'some college': 'SC', 'associate\'s degree': 'AD',
                                                'bachelor\'s degree': 'BD', 'master\'s degree': 'MD'})
dataSet['Lunch'] = dataSet['Lunch'].map({'standard': 'Standard', 'free/reduced': 'Free/Reduced'})
dataSet['Test Preparation Course'] = dataSet['Test Preparation Course'].map({'none': 'No Prep',
                                                                             'completed': 'Prep'})
dataSet = pd.get_dummies(dataSet, columns=['Gender', 'Race/Ethnicity', 'Parental Level of Education', 'Lunch',
                                           'Test Preparation Course'], prefix='', prefix_sep='')
dataSet.tail()

# Data set sample separation
# noinspection PyTypeChecker
train, validate, test = np.split(dataSet.sample(frac=1), [int(0.70 * len(dataSet)), int(0.85 * len(dataSet))])
print(len(train), 'training sample')
print(len(validate), 'validation samples')
print(len(test), 'test samples')

# Data set distribution display. Purely for testing and curiosity.
# Uncomment imports above for functionality
'''
sns.pairplot(train[['Math Score', 'Reading Score', 'Writing Score']])
plt.show()
print(dataSet.to_string())
'''

# Formatting of np arrays
train_Y = format_output(train)
test_Y = format_output(test)
val_Y = format_output(validate)
training_x = np.array(train)
test_x = np.array(test)
validate_x = np.array(validate)

model = build_model()

# Learning rate decay function
lr_schedule = tf.keras.optimizers.schedules.ExponentialDecay(
    initial_learning_rate=.001,
    decay_steps=100000,
    decay_rate=0.9,
    staircase=True)

# Optimizer implementing Gradient Descent factoring in learning rate decay function
optimizer = tf.keras.optimizers.SGD(learning_rate=lr_schedule)

# Compiling of the model with loss for all three outputs
model.compile(optimizer=optimizer, loss={'math_output': 'mae', 'read_output': 'mae', 'write_output': 'mae'},
              metrics={'math_output': tf.keras.metrics.MeanAbsoluteError(),
                       'read_output': tf.keras.metrics.MeanAbsoluteError(),
                       'write_output': tf.keras.metrics.MeanAbsoluteError()})

# Training montage!
# From trial and error, batch size of 10 with 50 epochs seems to give the best results.
# Console does a little dance while this runs on my computer
model.fit(training_x, train_Y, epochs=50, batch_size=10,
          validation_data=(validate_x, val_Y))

print("Testing the model:")
# Tests the model and outputs the return results to specific variables to be displayed below
loss, math_loss, reading_loss, writing_loss, math_mae, reading_mae, writing_mae = \
    model.evaluate(x=test_x, y=test_Y)

# Displaying loss values after full training and testing
# Rounded to two decimal places for readability
print()
print("Final loss output")
print(f'Total loss: {loss:.2f}')
print(f'Math loss: {math_loss:.2f}')
print(f'Reading loss: {reading_loss:.2f}')
print(f'Writing loss: {writing_loss:.2f}')
print(f'Math Accuracy: {(100 - math_mae):.2f}%')
print(f'Reading Accuracy: {(100 - reading_mae):.2f}%')
print(f'Writing Accuracy: {(100 - writing_mae):.2f}%')
print()

# Just to see the model's layers
# print("Training model summary")
# model.summary()

# For outputting the model into a base flowchart png
# Warning: Running this is finicky. Requires installing a couple special packages outside of the virtual environment:
# Install Graphviz and Pydot to see this
#tf.keras.utils.plot_model(model, "test_model.png", show_shapes=True)
