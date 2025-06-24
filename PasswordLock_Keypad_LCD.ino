/*
============================================================
Project: Password Lock with 4x4 Keypad and LCD (Arduino)
Author: ChatGPT
Description:
  A simple digital lock using a 4x4 keypad, 16x2 LCD, and an LED.
  The user enters a 4-digit code using the keypad.
  If the code is correct, access is granted (LED turns on).
  '*' resets the input, '#' confirms it.
============================================================

Hardware Connections:

-- LCD 1602 (6-wire connection) --
RS  -> Pin 12
E   -> Pin 11
D4  -> Pin A5
D5  -> Pin A4
D6  -> Pin A3
D7  -> Pin A2
RW  -> GND
VSS -> GND
VDD -> 5V
VO  -> Center of 10k potentiometer (contrast)
A   -> 5V through 220Ω resistor
K   -> GND

-- Keypad 4x4 --
Row pins    -> 9, 8, 7, 6
Column pins -> 5, 4, 3, 2

-- LED (lock indicator) --
Anode (+)   -> A0 through 220Ω resistor
Cathode (-) -> GND
============================================================
*/

#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(12, 11, A5, A4, A3, A2);

const String correctCode = "1234";
String inputCode = "";
const int ledPin = A0;

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  lcd.print("Enter password:");
  lcd.setCursor(0, 1);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '*') {
      inputCode = "";
      lcd.clear();
      lcd.print("Enter password:");
      lcd.setCursor(0, 1);
    } else if (key == '#') {
      lcd.clear();
      if (inputCode == correctCode) {
        lcd.print("Access granted");
        digitalWrite(ledPin, HIGH);
      } else {
        lcd.print("Access denied");
        digitalWrite(ledPin, LOW);
      }
      delay(3000);
      inputCode = "";
      lcd.clear();
      lcd.print("Enter password:");
      lcd.setCursor(0, 1);
    } else if (inputCode.length() < 4 && isDigit(key)) {
      inputCode += key;
      lcd.print("*");
    }
  }
}
