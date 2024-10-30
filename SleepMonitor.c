#include <Wire.h> // I2C communication

// Define sensor pins
const int lightsensorPin = A3; // Light sensor connected to A3
const int soundSensorPin = A1; // Sound sensor connected to A1
const int co2SensorPin = A0; // CO2 sensor connected to A0
const int buzzerPin = 8; // Buzzer connected to D8

// Threshold settings
const int threshold = 250; // Light threshold, adjustable as needed
const int soundThreshold = 200; // Sound threshold
const int lightThreshold = 10; // Assume light threshold is LOW
const int co2Threshold = 233; // CO2 threshold

// Initialization
void setup() {
    // Set up serial port
    Serial.begin(9600);
    pinMode(lightsensorPin, INPUT); // Set sensor pin to input mode
    // Set buzzer to output
    pinMode(buzzerPin, OUTPUT);
}

void loop() {
    int lightState = analogRead(lightsensorPin); // Read value from light sensor
    if (lightState < threshold) {
        // Enter monitoring mode
        monitorbackground();
        monitorSleep();
    }
    // Small delay
    delay(1000);
}

void monitorSleep() {
    Serial.println("Now monitoring");
    // Read sound sensor data
    int lightState = analogRead(lightsensorPin); // Read value from light sensor
    int soundLevel = analogRead(soundSensorPin);

    if (soundLevel > soundThreshold) {
        // Sound too loud, trigger buzzer
        digitalWrite(buzzerPin, HIGH);
        Serial.println("Sound too loud! Alarm triggered.");
        delay(1000);
        digitalWrite(buzzerPin, LOW);
    } else {
        digitalWrite(buzzerPin, LOW);
    }

    // Read CO2 sensor data
    int co2Level = analogRead(co2SensorPin);
    if (co2Level > co2Threshold) {
        // CO2 level too high, trigger buzzer
        digitalWrite(buzzerPin, HIGH);
        Serial.println("CO2 level too high! Alarm triggered.");
        delay(1000);
        digitalWrite(buzzerPin, LOW);
    }

    Serial.print("Sensor1:");
    Serial.println(soundLevel);
    Serial.print("Sensor2:");
    Serial.println(co2Level);
    Serial.print("Sensor3:");
    Serial.println(lightState);

    // Small delay
    delay(300);
}
