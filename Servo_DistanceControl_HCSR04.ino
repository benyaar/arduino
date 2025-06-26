/*
  Project: Servo Control with Ultrasonic Distance Sensor (HC-SR04)

  Description:
  This sketch controls a servo motor using an ultrasonic distance sensor.
  When an object is detected within a defined distance threshold (e.g. 10 cm),
  the servo rotates to 180°. If the object is further away, the servo returns to 0°.

  Components Used:
  - Arduino Uno/Nano
  - HC-SR04 Ultrasonic Sensor
  - SG90 Servo Motor
  - Jumper wires
  - (Optional) External power source for servo

  Wiring:
  HC-SR04:
    VCC  -> 5V
    GND  -> GND
    TRIG -> D8
    ECHO -> D7

  Servo:
    Signal (Orange) -> D9
    VCC (Red)       -> 5V (or external 5V with common GND)
    GND (Brown)     -> GND
*/

#include <Servo.h>

#define TRIG_PIN 8             // Trigger pin of HC-SR04
#define ECHO_PIN 7             // Echo pin of HC-SR04
#define DISTANCE_THRESHOLD 10  // Distance in cm to trigger the servo

Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(9);          
  myservo.write(0);           
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  float distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control servo based on distance
  if (distance < DISTANCE_THRESHOLD) {
    myservo.write(180);
  } else {
    myservo.write(0);   
  }

  delay(300);  
}
