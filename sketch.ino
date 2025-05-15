#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ledPins[6] = {2, 4, 5, 18, 19, 21};  // Braille LED pins
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address 0x27, 16 columns, 2 rows

void setup() {
  Serial.begin(115200);
  Wire.begin(25, 26);  // SDA = GPIO 21, SCL = GPIO 22

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Braille E-Book Reader");

  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    char receivedChar = Serial.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Char: ");
    lcd.print(receivedChar);

    displayBraille(receivedChar);
  }
}

void displayBraille(char character) {
  int braillePatterns[][6] = {
    {1, 0, 0, 0, 0, 0}, // A
    {1, 1, 0, 0, 0, 0}, // B
    {1, 0, 0, 1, 0, 0}, // C
    {1, 0, 0, 1, 1, 0}, // D
    {1, 0, 0, 0, 1, 0}, // E
    {1, 1, 0, 1, 0, 0}, // F
    {1, 1, 0, 1, 1, 0}, // G
    {1, 1, 0, 0, 1, 0}, // H
    {0, 1, 0, 1, 0, 0}, // I
    {0, 1, 0, 1, 1, 0}, // J
    {1, 0, 1, 0, 0, 0}, // K
    {1, 1, 1, 0, 0, 0}, // L
    {1, 0, 1, 1, 0, 0}, // M
    {1, 0, 1, 1, 1, 0}, // N
    {1, 0, 1, 0, 1, 0}, // O
    {1, 1, 1, 1, 0, 0}, // P
    {1, 1, 1, 1, 1, 0}, // Q
    {1, 1, 1, 0, 1, 0}, // R
    {0, 1, 1, 1, 0, 0}, // S
    {0, 1, 1, 1, 1, 0}, // T
    {1, 0, 1, 0, 0, 1}, // U
    {1, 1, 1, 0, 0, 1}, // V
    {0, 1, 0, 1, 1, 1}, // W
    {1, 0, 1, 1, 0, 1}, // X
    {1, 0, 1, 1, 1, 1}, // Y
    {1, 0, 1, 0, 1, 1}  // Z
  };

  int numbers[10][6] = {
    {0, 1, 0, 1, 1, 0}, // 0
    {1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 0, 0, 0}, // 2
    {1, 0, 0, 1, 0, 0}, // 3
    {1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 0, 0, 1, 0}, // 5
    {1, 1, 0, 1, 0, 0}, // 6
    {1, 1, 0, 1, 1, 0}, // 7
    {1, 1, 0, 0, 1, 0}, // 8
    {0, 1, 0, 1, 0, 0}  // 9
  };

  int specialChars[2][6] = {
    {0, 1, 0, 1, 0, 1}, // !
    {0, 1, 0, 0, 1, 1}  // ?
  };

  // Convert to uppercase if it's a lowercase letter
  if (character >= 'a' && character <= 'z') {
    character -= 32;
  }

  // Check if it's an uppercase letter (A-Z)
  if (character >= 'A' && character <= 'Z') {
    int index = character - 'A';
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], braillePatterns[index][i]);
    }
  }
  // Check if it's a number (0-9)
  else if (character >= '0' && character <= '9') {
    int index = character - '0';
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], numbers[index][i]);
    }
  }
  // Check if it's a special character (! or ?)
  else if (character == '!') {
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], specialChars[0][i]);
    }
  } else if (character == '?') {
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], specialChars[1][i]);
    }
  }
  // If unknown character, turn off all LEDs
  else {
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(2000); // Delay before turning LEDs off
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
