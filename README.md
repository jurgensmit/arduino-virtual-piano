# Arduino Virtual Piano

An Arduino sketch to play piano without a keyboard. Plays notes relative to the distance measured by an ultrasonic sensor

The application uses an ultrasonic distance sensor (HC-SR04) to measure the distance to your hand (or any other object
for that matter). This distance is then translated in to a note which is played through a piezo buzzer using the Arduino's 
tone function.

## Do it yourself

1. Build the circuit according the Fritzing sketch. 
2. Compile and upload the Arduino sketch. 
3. Start jamming...

## What you need

1. Arduino
2. HC-SR04 Ultrasonic Distance Sensor
3. Piezo Buzzer
4. 100 Ohm Resistor

Optionally

5. Green Led + 1 kOhm Resistor (to show when a note is played)
6. Red Led + 1 kOhm Resitor (to show when no note is played)
7. Grove 2x16 LCD Display (connected via i2c)
