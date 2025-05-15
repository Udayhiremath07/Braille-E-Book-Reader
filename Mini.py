import pyautogui
import time
import pymsgbox
import pytesseract
from PIL import Image
import pdfplumber
import os   

# Set path to Tesseract-OCR (Modify this based on your installation path)
pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

# Function to extract text from an image
def extract_text_from_image(image_path):
    image = Image.open(image_path)
    return pytesseract.image_to_string(image, config="--psm 6").strip()

# Function to extract text from a PDF
def extract_text_from_pdf(pdf_path):
    extracted_text = ""
    with pdfplumber.open(pdf_path) as pdf:
        for page in pdf.pages:
            extracted_text += page.extract_text() + " "  # Append text with space to keep words together
    return extracted_text.strip()

# Function to get the full file path based on the script's location
def get_file_path(file_name):
    script_directory = os.path.dirname(os.path.abspath(__file__))  # Folder where Mini.py is located
    file_path = os.path.join(script_directory, file_name)
    return file_path

# Get the file name from the user
file_name = pymsgbox.prompt("Enter the file name (e.g., simpletext.pdf):", "File Selection")

# Generate the full file path
file_path = get_file_path(file_name)

if not file_path or not os.path.exists(file_path):
    pymsgbox.alert("Invalid file path! Exiting.", "Error")
    exit()

# Determine file type and extract text accordingly
extracted_text = ""
if file_path.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.tiff')):
    extracted_text = extract_text_from_image(file_path)
elif file_path.lower().endswith('.pdf'):
    extracted_text = extract_text_from_pdf(file_path)
else:
    pymsgbox.alert("Unsupported file type! Please use an image or a PDF.", "Error")
    exit()

if not extracted_text:
    pymsgbox.alert("No text found in the file!", "Warning")
    exit()

print(f"Extracted Text: {extracted_text}")

# Alert the user to switch to Wokwi's Serial Monitor
pymsgbox.alert("Switch to Wokwi Serial Monitor now!\nClick inside the Serial Monitor and wait for text input.", "Wokwi Input Alert")

time.sleep(2)  # Reduced delay for faster execution

# Type and send characters without newline
pyautogui.typewrite(extracted_text, interval=0.02)  # Faster typing speed
pyautogui.press("enter")  # Send the entire text at once

print("Text sent to Wokwi automatically!")
