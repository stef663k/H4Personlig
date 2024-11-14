import os
import MNISTNeuralNetwork

# Example usage
data_path = r'C:\Users\Stefan\Desktop\mnistData' 
network_architecture = [784, 100, 10]

# Create an instance of the MNISTNeuralNetwork class
mnist_nn = MNISTNeuralNetwork(network_architecture, data_path)

# Load data
mnist_nn.load_data()

# Train the network
mnist_nn.train(epochs=150, mini_batch_size=128, learning_rate=1.0)

# Save the network data and weights
mnist_nn.save_all('mnist_data.h5')

# Print the test accuracy
print("Test accuracy:", mnist_nn.evaluate())
final_accuracy = mnist_nn.evaluate() / 10000 * 100
print(f"Final accuracy: {final_accuracy}%")
