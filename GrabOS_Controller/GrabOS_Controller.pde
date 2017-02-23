


/**
 Basic demonstration of using a joystick.
 
 When this sketch runs it will try and find
 a game device that matches the configuration
 file 'joystick' if it can't match this device
 then it will present you with a list of devices
 you might try and use.
 
 The chosen device requires 2 sliders and 2 buttons.
 */

import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;

import processing.serial.*;
import cc.arduino.*;

ControlIO control;
ControlDevice stick;
float px, py;
boolean grabButton;
int retCol;
byte grabber;

Serial serialPort;


public void setup() {
  size(400, 400);
  println(Arduino.list());
  serialPort = new Serial(this, Serial.list()[0], 9600);
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  stick = control.getMatchedDevice("joystick");
  if (stick == null) {
    println("No suitable device configured");
    System.exit(-1); // End the program NOW!
  }
  

  
  
}

// Poll for user input called from the draw() method.
public void getUserInput() {
  px = map(stick.getSlider("X").getValue(), -1, 1, 0, 1);
  py = map(stick.getSlider("Y").getValue(), -1, 1, 0, 1);
  grabButton = stick.getButton("GRAB").pressed();
}

public float filter(float raw){
  if (raw < 0.05){                //Deadzone, to avoid unwanted movements
    return 0;
  }else{
    return raw;                   //Tune movement here
  }
}


public void draw() {
  getUserInput(); // Polling
  background(128, 128, 128);
  
  if(grabButton){
    retCol = 0;
    grabber = 'T';
  }else{
    retCol = 255;
    grabber = 'F';
  }

  
  //Draw axes
  stroke(0);
  line(200, 0, 200, 400);
  line(0, 200, 400, 200);

  //Show position
  noStroke();
  fill(64, retCol, 64, 64);
  ellipse(filter(px)*height, filter(py)*width, 20, 20);
  
  //Talk to the arduino over serial
  serialPort.write(grabber + " " + filter(px)+ " " +filter(py));
}