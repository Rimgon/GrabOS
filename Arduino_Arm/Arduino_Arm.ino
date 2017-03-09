 /*
  testBraccio90.ino

 testBraccio90 is a setup sketch to check the alignment of all the servo motors
 This is the first sketch you need to run on Braccio
 When you start this sketch Braccio will be positioned perpendicular to the base
 If you can't see the Braccio in this exact position you need to reallign the servo motors position

 Created on 18 Nov 2015
 by Andrea Martino

 This example is in the public domain.
 */

#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
long serialInSpeed, serialInBase, serialInShoulder, serialInElbow, serialInWristVertical, serialInWristRotation, serialInGripper;
String commandLetter;
int commandValue;
int basePos = 90;
int shoulderPos = 45;
int elbowPos = 180;
int wristVerticalPos = 180;
int wristRotationPos = 90;
int gripperPos = 10;

void setup() {  
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Serial.begin(9600);
  while(!Serial){
    //Wait for the serial bus to connect over USB
  }
  Serial.println("Setup Running...");
  Braccio.begin();
  Serial.println("Braccio Setup Complete...");
  
}

void loop() {



  /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  
  // the arm is aligned upwards  and the gripper is closed
                     //(step delay, M1, M2, M3, M4, M5, M6);
  Serial.println("GrabOS Version 0.6 by Alex King. Name subject to change.\nIn case of emergency, text at 740-549-1070.");
  Serial.println("Initializing main loop...");
  Serial.println(">>>>>COMMAND SYNTAX<<<<<\n Specify servo to move\n \tb - base\n \ts - shoulder\n \te - elbow\n \tv - wrist vertical\n \tr - wrist rotation\n \tg - gripper\n then degree value. Limits are as follows:\n \tBase: 0-180\n\tShoulder: 15-165\n\tElbow: 0-180\n\tWrist Vertical: 0-180\n\tWrist Rotation: 0-180\n\tGripper: 10-73 (Open to closed)\nInclude a space between the letter and the numerical value.\n Good luck!");
  while (true){
    
    if(Serial.available() != 0){
      commandLetter = Serial.readStringUntil(' ');
      char firstChar = commandLetter.charAt(0);
      Serial.print((String)firstChar + " ");

      commandValue = Serial.parseInt();
      Serial.println(commandValue);
      
      
      switch (firstChar) {
        case 'b':
          moveBase(commandValue);
          break;
  
        case 's':
          moveShoulder(commandValue);
          break;
  
        case 'e':
          moveElbow(commandValue);
          break;
  
        case 'v':
          moveWristVertical(commandValue);
          break;
  
        case 'r':
          moveWristRotation(commandValue);
          break;
  
        case 'g':
          moveGripper(commandValue);
          break;
  
        default:
          Serial.println("Invalid command: First character not recognized.\n \tb - base\n \ts - shoulder\n \te - elbow\n \tv - wrist vertical\n \tr - wrist rotation\n \tg - gripper");
        break;  
      }
    }
    

  }
}

//Homemade functions to do stuff that the arm won't do for us, namely relative movement

void moveBase(int localBasePos){
  Serial.println("Setting base position to: " + (String)localBasePos);
  basePos = localBasePos;
  Braccio.ServoMovement(20, basePos, shoulderPos, elbowPos, wristVerticalPos, wristRotationPos, gripperPos);
  Serial.println("Done!");
}

void moveShoulder(int localShoulderPos){
  Serial.println("Setting shoulder position to: " + (String)localShoulderPos);
  shoulderPos = localShoulderPos;
  Braccio.ServoMovement(20, basePos, shoulderPos, elbowPos, wristVerticalPos, wristRotationPos, gripperPos);
  Serial.println("Done!");
}

void moveElbow(int localElbowPos){
  Serial.println("Setting elbow position to: " + (String)localElbowPos);
  elbowPos = localElbowPos;
  Braccio.ServoMovement(20, basePos, shoulderPos, elbowPos, wristVerticalPos, wristRotationPos, gripperPos);
  Serial.println("Done!");
}

void moveWristVertical(int localWristVerticalPos){
  Serial.println("Setting wristVertical position to: " + (String)localWristVerticalPos);
  wristVerticalPos = localWristVerticalPos;
  Braccio.ServoMovement(20, basePos, shoulderPos, elbowPos, wristVerticalPos, wristRotationPos, gripperPos);
  Serial.println("Done!");
}

void moveWristRotation(int localWristRotationPos){
  Serial.println("Setting wristRotation position to: " + (String)localWristRotationPos);
  wristRotationPos = localWristRotationPos;
  Braccio.ServoMovement(20, basePos, shoulderPos, elbowPos, wristVerticalPos, wristRotationPos, gripperPos);
  Serial.println("Done!");
}

void moveGripper(int localGripperPos){
  Serial.println("Setting Gripper position to: " + (String)localGripperPos);
  gripperPos = localGripperPos;
  Braccio.ServoMovement(20, basePos, shoulderPos, elbowPos, wristVerticalPos, wristRotationPos, gripperPos);
  Serial.println("Done!");
}

void changeArmPos(int localArmSpeed, int localBasePos, int localShoulderPos, int localElbowPos, int localWristVerticalPos, int localWristRotationPos, int localGripperPos){
  Serial.println("Moving to: " + (String)serialInSpeed + (String)serialInShoulder + (String)serialInElbow + (String)serialInWristVertical + (String)serialInWristRotation + (String)serialInGripper);
  Braccio.ServoMovement(localArmSpeed, basePos + localBasePos, shoulderPos + localShoulderPos, elbowPos + localElbowPos, wristVerticalPos + localWristVerticalPos, wristVerticalPos + localWristRotationPos, gripperPos + localGripperPos);
}

void setArmPos(int localArmSpeed, int localBasePos, int localShoulderPos, int localElbowPos, int localWristVerticalPos, int localWristRotationPos, int localGripperPos){
  basePos = localBasePos;
  shoulderPos = localShoulderPos;
  elbowPos = localElbowPos;
  wristVerticalPos = localWristVerticalPos;
  wristRotationPos = localWristRotationPos;
  gripperPos = localGripperPos;
  Braccio.ServoMovement(localArmSpeed, localBasePos, localShoulderPos, localElbowPos, localWristVerticalPos, localWristRotationPos, localGripperPos);
}
