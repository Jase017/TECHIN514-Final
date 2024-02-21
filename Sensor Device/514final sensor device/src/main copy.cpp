#include <Encoder.h>
#include <Arduino.h>
// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(7, 8);
int fsrPin = A0;     // A0 接口
int fsrReading;
int ledPin = A5;
bool hasPrintedStart = false; // Flag to check if "Start" has been printed

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  if (!hasPrintedStart) { // Check if "Start" has not been printed
    fsrReading = analogRead(fsrPin); // Read the value from the FSR
    Serial.print("Analog reading = ");
    Serial.print(fsrReading); // Print the reading to the Serial Monitor

    if (fsrReading < 100) {
      Serial.println(" - No pressure"); // Print "No pressure" if reading is below 100
    } else {
      Serial.println(" Start"); // Print "Start" when pressure is detected
      hasPrintedStart = true; // Set the flag to true to avoid printing readings in future
      digitalWrite(ledPin, HIGH);
    }
  }

  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition/100);
  }
}

