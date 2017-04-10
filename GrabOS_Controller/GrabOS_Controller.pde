//Processing code for this example
 // Dimmer - sends bytes over a serial port
 // by David A. Mellis
 //This example code is in the public domain.

 import processing.serial.*;
 import org.gamecontrolplus.*;
 import org.gamecontrolplus.gui.*;
 
 PFont f;
 
Serial port;
ControlIO control;
ControlDevice stick;
float px, py, stickX, stickY;
boolean Grabber, Base, Shoulder, Elbow, Wrist;
int retCol[] = {255, 0};
byte activeMotor;
byte GrabberState;
boolean hasWritten = false;


 void setup() {
 size(400, 400);
 
 f = createFont("Arial", 16, true);
 textFont(f,36);

 println("Available serial ports:");
 // if using Processing 2.1 or later, use Serial.printArray()
 println(Serial.list());

if(Serial.list().length < 1){
  println("No arduino attached. Plug it in and try again.");
  System.exit(-1);
}

 // Uses the first port in this list (number 0).  Change this to
 // select the port corresponding to your Arduino board.  The last
 // parameter (e.g. 9600) is the speed of the communication.  It
 // has to correspond to the value passed to Serial.begin() in your
 // Arduino sketch.
 port = new Serial(this, Serial.list()[0], 9600);

 // If you know the name of the port used by the Arduino board, you
 // can specify it directly like this.
 //port = new Serial(this, "COM1", 9600);
 
 
 control = ControlIO.getInstance(this);
 stick = control.getMatchedDevice("joystick");
 if(stick == null){
     println("No suitable device configured");
     System.exit(-1);
 }
 }
 
 
 // Poll for user input called from the draw() method.
public void getUserInput() {
  px = map(stick.getSlider("X").getValue(), -1, 1, 0, 400);
  py = map(stick.getSlider("Y").getValue(), -1, 1, 0, 400);
  stickX = stick.getSlider("X").getValue();
  stickY = stick.getSlider("Y").getValue();
  Grabber = stick.getButton("GRAB").pressed();
  Base = stick.getButton("BASE").pressed();      //1
  Shoulder = stick.getButton("SHLD").pressed();  //2
  Elbow = stick.getButton("ELB").pressed();      //3
  Wrist = stick.getButton("WRST").pressed();     //4
}
 

 void draw() {
 getUserInput();
 // draw a gradient from black to white

 
 background(128, 128, 128);
 
 fill(255);


 
 if(Wrist){
   activeMotor = 4;
 }else if(Elbow){
   activeMotor = 3;
 }else if(Shoulder){
   activeMotor = 2;
 }else if(Base){
   activeMotor = 1;
 }else {
   activeMotor = 0;
 }
 
 
  if(Grabber){
    retCol[0] = 0;
    retCol[1] = 255;
    GrabberState = 1;
  }else{
    retCol[0] = 255;
    retCol[1] = 0;
    GrabberState = 0;
  }
 
 
   //Draw axes
  stroke(0);
  line(200, 0, 200, 400);
  line(0, 200, 400, 200);

//Show position
  noStroke();
  fill(retCol[0], retCol[1], 0, 64);
  ellipse(px, py, 20, 20);
  
 // write the current X-position of the mouse to the serial port as
 // a single byte
 byte out[] = new byte[3];
 out[0] = activeMotor;
 out[1] = (byte)abs(map(stickX, -1, 1, 0, 127)+0);
 out[2] = (byte)(127-abs(map(stickY, -1, 1, 0, 127)+0));
 //out[3] = GrabberState;
 
 text(out[0]+" "+out[1]+" "+out[2]+" "+map(out[out.length-2], 0, 127, 0, 180), 10, 100);
 
 if((activeMotor != 0 && hasWritten == false)/* || Grabber && hasWritten == false*/){
   port.write(out);
   hasWritten = true;
 }
 if(activeMotor == 0){
   hasWritten = false;
 }
 if(port.available()>0){
   print(port.readString());
 }
 }
 