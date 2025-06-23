#include <LiquidCrystal.h>
#include <DHT.h>

// ======================================================
// Project: DHT11 + LCD1602 Display with Arduino
// Description:
// This sketch reads temperature and humidity from a DHT11 sensor
// and displays them on a 16x2 LCD using the LiquidCrystal library.
// ======================================================

// ===================
// Wiring Instructions:
// -------------------
// DHT11 Sensor:
//   DATA -> Digital pin 7 (S)
//   VCC  -> 5V on Arduino ()
//   GND  -> GND (-)
//
// LCD 1602 (using 6 digital pins):
//   RS   -> Pin 12
//   E    -> Pin 11
//   D4   -> Pin 5
//   D5   -> Pin 4
//   D6   -> Pin 3
//   D7   -> Pin 2
//   VSS  -> GND
//   VDD  -> 5V
//   VO   -> Center pin of 10k potentiometer (contrast)
//   RW   -> GND
//   A (LED+) -> 5V (via resistor, e.g., 220Ω)
//   K (LED-) -> GND
// ======================================================

#define DHTPIN 7         // DHT11 data pin
#define DHTTYPE DHT11    // Define sensor type

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);  // Initialize 16x2 LCD
  lcd.print("Читання DHT11...");
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error!");
    lcd.clear();
    lcd.print("Error!");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);  // ° symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");

  delay(2000);
}
