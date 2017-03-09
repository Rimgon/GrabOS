/*
  Dimmer

 Demonstrates the sending data from the computer to the Arduino board,
 in this case to control the brightness of an LED.  The data is sent
 in individual bytes, each of which ranges from 0 to 255.  Arduino
 reads these bytes and uses them to set the brightness of the LED.

 The circuit:
 LED attached from digital pin 9 to ground.
 Serial connection to Processing, Max/MSP, or another serial application

 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe and Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Dimmer

 */

const int xPin = 9;      // the pin that the LED is attached to
const int yPin = 8;
byte currentValue = 0;
byte values[] = {0,0,0};

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);
}

void loop() {
  byte brightness;

  // check if data has been sent from the computer:  
  if(Serial.available()){
    int incomingValue = Serial.read();
    values[currentValue] = incomingValue;

    currentValue++;
    if(currentValue > 2){
      currentValue = 0;
    }
    
    // after this point values[]
    // has the most recent set of
    // all values sent in from Processing
  }
  analogWrite(yPin, values[sizeof(values)-2]);
  analogWrite(xPin, values[sizeof(values)-1]);
}

