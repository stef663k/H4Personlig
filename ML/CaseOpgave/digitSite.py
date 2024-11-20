# app.py
import numpy as np
import streamlit as st
import cv2
from PIL import Image
from MNISTNeuralNetwork import MNISTNeuralNetwork
import os
import tempfile
import matplotlib.pyplot as plt


def load_model():
    data_path = r'C:\Users\Stefan\Desktop\mnistData'
    network_architecture = [784, 100, 10]
    mnist_nn = MNISTNeuralNetwork(network_architecture, data_path)
    mnist_nn.load_data()
    mnist_nn.load_all('mnist_data.h5')
    return mnist_nn.network

def classify_digit(model, image):
    img = cv2.imread(image, cv2.IMREAD_GRAYSCALE)
    img = cv2.resize(img, (28, 28))  # Resize to 28x28 for MNIST

    img = 255 - img  # Invert image color

    img = img.reshape(784, 1)  # Flatten the image
    img = img / 255.0  # Normalize

    print("Preprocessed image values (first 5):", img[:5])

    output = model.feedforward(img)
    print("Raw output:", output)  

    prediction = np.argmax(output)  
    print("Predicted class index:", prediction)

    return prediction



def resize_image(image, target_size):
    img = Image.open(image)
    resized_img = img.resize(target_size)
    return resized_img

def run_app():
    st.set_page_config(page_title='Digit Recognition 🔢', page_icon='🔢')
    st.title('Handwritten Digit Recognition 🔢')
    st.caption('by Stefan Lynge Hvilsom')

    st.markdown(r'''This is a simple handwritten digit recognition model. It is trained on the MNIST dataset and uses a simple neural network with two hidden layers.''')
    st.subheader('Lets go!!!')

    uploaded_img = st.file_uploader('Upload an image', type=['png'])

    if uploaded_img is not None:
        image_np = np.array(Image.open(uploaded_img).convert('L'))

        temp_image_path = os.path.join(tempfile.gettempdir(), 'temp_image.png')
        cv2.imwrite(temp_image_path, image_np)

        resized_image = resize_image(temp_image_path, (300, 300))

        col1, col2, col3 = st.columns(3)

        with col1:
            st.image(resized_image)

        submit = st.button('Predict')

        if submit:
            model = load_model()
            prediction = classify_digit(model, temp_image_path)
            st.subheader('Prediction Results')
            st.success(f'The digit is: {prediction}')  # No need for np.argmax here


        os.remove(temp_image_path)


if __name__ == '__main__':
    run_app()
