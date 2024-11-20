import h5py
import numpy as np
import cv2
import matplotlib.pyplot as plt
from Network import Network  # Assuming you are using the Network class from the previous script
import os
print("Current directory:", os.getcwd())
print("Files in current directory:", os.listdir(os.getcwd()))


def debug_preprocessing(image_path):
    # Load the image in grayscale mode
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    
    # Resize to 28x28 pixels (MNIST standard size)
    img = cv2.resize(img, (28, 28))
    
    # Optional: Invert colors if needed (depends on how the model was trained)
    img = 255 - img
    
    # Flatten the image to a 784x1 vector and normalize to [0, 1] range
    img_flattened = np.reshape(img, (784, 1)) / 255.0
    
    # Debugging information: check the range and shape
    print(f"Min value: {np.min(img_flattened)}, Max value: {np.max(img_flattened)}")
    print(f"Flattened shape: {img_flattened.shape}")
    
    # Visualize the preprocessed image
    plt.imshow(img, cmap='gray')
    plt.title('Debug Image - Preprocessed')
    plt.show()
    
    return img_flattened

def debug_feedforward(model, img):
    # Print out activations for each layer during feedforward
    a = img
    for i, (w, b) in enumerate(zip(model.weights, model.biases)):
        z = np.dot(w, a) + b
        a = model.sigmoid(z)
        
        # Debug information per layer
        print(f"Layer {i + 1}:")
        print(f"  Activation shape = {a.shape}")
        print(f"  Activation mean = {np.mean(a):.4f}, Activation max = {np.max(a):.4f}")
    
    # Final prediction from the output layer
    prediction = np.argmax(a)
    print(f"Final Prediction: {prediction}")
    return prediction

def check_model_parameters(model):
    # Iterate over each layer to verify weights and biases
    for i, (w, b) in enumerate(zip(model.weights, model.biases)):
        print(f"Layer {i + 1}:")
        print(f"  Weight shape: {w.shape}, Weight mean: {np.mean(w):.4f}, Weight max: {np.max(w):.4f}")
        print(f"  Bias shape: {b.shape}, Bias mean: {np.mean(b):.4f}, Bias max: {np.max(b):.4f}")

def load_all(filepath):
    # Load model from an HDF5 file and initialize the network
    with h5py.File(filepath, 'r') as f:
        # Extract architecture, weights, and biases
        architecture = f['architecture'][:]
        weights = [np.array(f[f'weights_layer_{i}']) for i in range(len(architecture)-1)]
        biases = [np.array(f[f'biases_layer_{i}']) for i in range(len(architecture)-1)]
        
        # Debug information: check the loaded data
        print(f"Loaded {len(weights)} weights and {len(biases)} biases.")
        for i, (w, b) in enumerate(zip(weights, biases)):
            print(f"Layer {i + 1}: Weight shape = {w.shape}, Bias shape = {b.shape}")
        
    # Initialize the Network with the loaded architecture and set the weights/biases
    model = Network(architecture.tolist())
    model.set_weights(weights)
    model.set_biases(biases)
    
    return model

# Example Usage
image_path = "4num1.png"  
model_filepath = 'mnist_data.h5'  

# Load the trained model
model = load_all(model_filepath)

# Preprocess and load the image
preprocessed_img = debug_preprocessing(image_path)

# Debugging: Perform feedforward and check activations at each layer
debug_feedforward(model, preprocessed_img)

# Check model parameters (weights and biases)
check_model_parameters(model)
