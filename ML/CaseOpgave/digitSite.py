from flask import Flask, request, jsonify, send_from_directory
import numpy as np
from PIL import Image
import MNISTNeuralNetwork
from io import BytesIO

app = Flask(__name__)

# Path and architecture details
data_path = r'C:\Users\Stefan\Desktop\mnistData'
network_architecture = [784, 100, 10]

# Create an instance and load the pre-trained model
mnist_nn = MNISTNeuralNetwork.MNISTNeuralNetwork(network_architecture, data_path)
mnist_nn.load_all('mnist_data.h5')  # This only loads the pre-trained data, no training here

@app.route('/predict', methods=['POST'])
def index():
    return send_from_directory('.', 'index.html')
def predict():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'}), 400
    
    file = request.files['file']
    image = Image.open(file).convert('L')
    image = image.resize((28, 28))
    image_data = np.array(image).astype('float32').reshape(784, 1) / 255.0

    # Feed the image data to the loaded model
    prediction = mnist_nn.network.feedforward(image_data)
    predict_digit = int(np.argmax(prediction))

    return jsonify({'prediction': predict_digit})

if __name__ == '__main__':
    app.run(debug=True)
