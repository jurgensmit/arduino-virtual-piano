/*
 * Arduino Virtual Piano - Plays notes relative to the distance measured by the ultrasonic sensor
 *
 * Circuit: 
 *
 * - An HC-SR04 ultrasonic sensor connected to pin 13 (trigger) and pin 12 (echo) to measure the distance
 * - A piezo buzzer connected to pin 8 to produce the sound
 * - A Grove 2x16 LCD display connected to I2C to show some information
 * - Optionally a green led connected to pin 10 to indicate a tone being played
 * - Optionally a red led connected to pin 11 to indicate no tone being played
 *
 */

#include <NewPing.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define TRIGGER_PIN    13    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN       12    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE   42    // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define RED_LED_PIN    11    // Arduino pin tied to the anode of the red led
#define GREEN_LED_PIN  10    // Arduino pin tied to the anode of the green led
#define BUZZER_PIN     8     // Arduino pin tied to the buzzer
#define NOTE_DURATION  450   // The duration of 1 note

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.
rgb_lcd lcd;

// Frequency of the noted that can be played (c4..c5)
int notes[] = {
  220, 247, 262, 294, 330, 349, 392, 440
};

void setup() {
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows:

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.clear();
  lcd.print("Virtual Piano");
  
  turnOffLeds();
}

void turnOnRedLed() {
  digitalWrite(RED_LED_PIN, HIGH);
}

void turnOnGreenLed() {
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void turnOffLeds() {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

void printDistance(unsigned int distance) {
  lcd.home();
  if(distance > 0) {
    lcd.print(String("Distance ") + String(distance) + String(" cm                "));
  }
  else {
    lcd.print("Out of Range!   ");
  }
}

unsigned int getDistance() {
  delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int distance = sonar.ping_cm(); // Send ping, get distance in centimeters.
  return distance;
}

void printNote(int noteIndex) {
  lcd.setCursor(0, 1);
  if(noteIndex >= 0) {
    lcd.print(String("Note index ") + String(noteIndex) + String("     "));
  }
  else {
    lcd.print("No note to play!");
  }
}

void playNote(unsigned int frequency, unsigned int duration) {
  if(frequency > 0) {
    tone(BUZZER_PIN, frequency);
  }
  delay(duration);
  noTone(BUZZER_PIN);
}

void loop() {
  turnOffLeds();
  unsigned int distance = getDistance();
  printDistance(distance);
  if(distance >= 10 && distance <= 41) {
    turnOnGreenLed();
    unsigned int noteIndex = (distance - 10) / 4;
    printNote(noteIndex);
    playNote(notes[noteIndex], NOTE_DURATION);
  }
  else {
    turnOnRedLed();
    printNote(-1);
    playNote(0, NOTE_DURATION);  // Not play any note, just wait
  }
}
