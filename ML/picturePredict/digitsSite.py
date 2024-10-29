# app.py
import tensorflow as tf
import numpy as np
import streamlit as st
import cv2
from PIL import Image
import os
import tempfile

# Load the trained model
model = tf.keras.models.load_model('numbersRec.model.keras')

def classify_digit(model, image):
    img = cv2.imread(image, cv2.IMREAD_GRAYSCALE)
    img = cv2.resize(img, (28, 28))
    img = np.invert(np.array([img]))  # Invert the image
    prediction = model.predict(img)
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
            prediction = classify_digit(model, temp_image_path)
            st.subheader('Prediction Results')
            st.success(f'The digit is: {np.argmax(prediction)}')

        os.remove(temp_image_path)

if __name__ == '__main__':
    run_app()
