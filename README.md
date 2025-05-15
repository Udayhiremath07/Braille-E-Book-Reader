#  Braille E-Book Reader

An affordable, low-power, and accessible **Braille E-Book Reader** project designed to assist visually impaired individuals in reading digital text. This system extracts text using OCR and converts it into Braille patterns using actuators or LEDs controlled by an ESP32 microcontroller.

##  Features

-  Extracts text from images using OCR (Tesseract)
-  Converts text to Braille code
-  Displays Braille characters using 6-dot LED or actuator matrix
-  LCD display shows readable character output alongside Braille
-  Ultra low-cost implementation, ideal for students and medical accessibility projects
-  Simulated on [Wokwi](https://wokwi.com/), no hardware required

##  Project Structure

| File / Folder     | Description                                  |
|-------------------|----------------------------------------------|
| `Mini.py`         | Python script that extracts text from images using OCR and sends it to ESP32 |
| `sketch.ino`      | Arduino code for ESP32 to control Braille LEDs and LCD |
| `diagram.json`    | Wokwi circuit setup file for simulation      |

## 📷 Workflow

1.  User uploads an image with text (e.g. e-book page).
2.  Python script uses Tesseract OCR to extract text.
3.  Text is sent to ESP32 via Serial.
4.  ESP32 maps each character to a Braille dot pattern.
5.  LEDs/Actuators display the Braille character.
6.  LCD displays the corresponding character in plain text.

##  Components Used

- ESP32 Microcontroller
- 6 LEDs (Braille dots)
- LCD1602 I2C Display
- Jumper wires
- Python with OCR (Tesseract)
- Optional: Actuators (for tactile Braille)

##  Future Enhancements

- Multi-line Braille display
- Refreshable actuator-based interface
- Full e-book to Braille parsing
- Text-to-Speech + Braille hybrid support
