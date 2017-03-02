/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/
byte serialIn;
int ledPin = 9;
String grabber;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledPin, OUTPUT);
  
  Serial.begin(115200);
  while(!Serial){
    //Waiting for serial connection
  }
}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()){
    

    // read the most recent byte (which will be from 0 to 255):
    serialIn = Serial.read();
    //grabber = serialIn.remove(0, 1);
    // set the brightness of the LED:
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  /*
    if (serialIn < 2000){
      digitalWrite(LED_BUILTIN, HIGH);
    }else{
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(1000);
  */



  
  /*commandLetter = Serial.readStringUntil(' ');
  char firstChar = commandLetter.charAt(0);
  if(firstChar == 'T'){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if(firstChar == 'F'){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("I'm reading an F!");
  }
  delay(2000);*/
}
