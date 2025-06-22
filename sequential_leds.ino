/*
  sequential_leds.ino
  --------------------------
  This sketch sequentially turns on 5 LEDs one after another 
  with a delay between each. After the last LED, the sequence restarts.

  Pins used: 4, 5, 6, 7, 8

  Circuit diagram:
    (Each LED should be connected with a 220–330 Ohm resistor)

    Arduino pin ─── Resistor ───►|─── GND
                                 LED

    Example:
      Pin 4 ─── Resistor ───►|─── GND
      Pin 5 ─── Resistor ───►|─── GND
      Pin 6 ─── Resistor ───►|─── GND
      Pin 7 ─── Resistor ───►|─── GND
      Pin 8 ─── Resistor ───►|─── GND

*/
bool prevButton = false;
int currentLED = 0;

const int buttonPin = A4;
const int ledPins[] = {4, 5, 6, 7, 8};
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  bool button = !digitalRead(buttonPin); 

  if (button && !prevButton) {
    currentLED++;
    if (currentLED > numLEDs) {
      currentLED = 0; 
    }

    for (int i = 0; i < numLEDs; i++) {
      digitalWrite(ledPins[i], i < currentLED ? HIGH : LOW);
    }

    Serial.print("Enable: ");
    Serial.println(currentLED);
  }

  prevButton = button;
  delay(100);
}
