from MNISTNeuralNetwork import MNISTNeuralNetwork

data_path = r'C:\Users\Stefan\Desktop\mnistData' 
network_architecture = [784, 100, 10]

# Create an instance of the MNISTNeuralNetwork class
mnist_nn = MNISTNeuralNetwork(network_architecture, data_path)

# Load data
mnist_nn.load_data()

# Train the network
mnist_nn.train(epochs=150, mini_batch_size=128, learning_rate=0.1)

# Save the network data and weights and biases
mnist_nn.save_all('mnist_data.h5')

# Print the test accuracy
accuracy = mnist_nn.evaluate()
n_test = len(mnist_nn.test_data)  # Get the number of test samples
final_accuracy = accuracy / n_test * 100  # Calculate percentage
print(f"Test accuracy: {accuracy} out of {n_test}")
print(f"Final accuracy: {final_accuracy:.2f}%")
