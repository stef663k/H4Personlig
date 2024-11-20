import os
from Network import Network
import h5py
import numpy as np
from mnist import MNIST
from sklearn.utils import shuffle

class MNISTNeuralNetwork:
    def __init__(self, network_architecture, data_path):
        self.network = Network(network_architecture)
        self.data_path = data_path

    def save_all(self, filename):
        architecture = self.network.get_architecture()
        weights = self.network.get_weights()
        biases = self.network.get_biases()
        
        with h5py.File(filename, 'w') as f:
            f.create_dataset('architecture', data=np.array(architecture))
            
            # Save weights and biases
            for i, (weight, bias) in enumerate(zip(weights, biases)):
                f.create_dataset(f'weights_layer_{i}', data=weight)
                f.create_dataset(f'biases_layer_{i}', data=bias)
        
        print(f"All data saved to {filename}")
    
    def load_all(self, filename):
        with h5py.File(filename, 'r') as f:
            # Load architecture
            architecture = f['architecture'][:]
            
            weights = []
            biases = []
            for i in range(len(architecture) - 1):
                weight = f[f'weights_layer_{i}'][:]
                bias = f[f'biases_layer_{i}'][:]
                weights.append(weight)
                biases.append(bias)
            
            # Set weights and biases in the network
            self.network = Network(architecture.tolist())
            self.network.set_weights(weights)
            self.network.set_biases(biases)
        
        print(f"Data and network loaded from {filename}")
    
    def load_data(self):
        print(f"Loading data from: {self.data_path}")
        mndata = MNIST(self.data_path)
        mndata.train_img_fname = 'train-images.idx3-ubyte'
        mndata.train_lbl_fname = 'train-labels.idx1-ubyte'
        mndata.test_img_fname = 't10k-images.idx3-ubyte'
        mndata.test_lbl_fname = 't10k-labels.idx1-ubyte'
        
        # Load training data
        training_data, training_labels = mndata.load_training()
        training_data = [np.array(x) / 255.0 for x in training_data]
        training_data = [np.reshape(x, (784, 1)) for x in training_data]  
        training_labels = [self.vectorized_result(y) for y in training_labels]
        
        self.train_images = np.array([x[0] for x in zip(training_data, training_labels)])
        self.train_labels = np.array([x[1] for x in zip(training_data, training_labels)])
        
        # Convert data into list of tuples for SGD
        self.training_data = list(zip(self.train_images, self.train_labels))
        
        # Shuffle training data
        self.training_data = shuffle(self.training_data)
        
        # Test data (use validation data as test data)
        self.test_data = self.load_testing_data(mndata)

    def load_testing_data(self, mndata):
        validation_data, validation_labels = mndata.load_testing()
        validation_data = [np.array(x) / 255.0 for x in validation_data]
        validation_data = [np.reshape(x, (784, 1)) for x in validation_data]  
        return list(zip(validation_data, validation_labels))
    
    def vectorized_result(self, j):
        e = np.zeros((10, 1))
        e[j] = 1.0
        return e
    
    def train(self, epochs, mini_batch_size, learning_rate):
        self.network.SGD(self.training_data, epochs, mini_batch_size, learning_rate, test_data=self.test_data)
    
    def evaluate(self):
        return self.network.evaluate(self.test_data)



