#include <SoftwareSerial.h>                 //Imporing of necesarry Libraries
#include <Servo.h>

SoftwareSerial BTSerial(3,2);               // Bluetooth (RX,TX) as arduino sees it

const int trig = 4;                         // Pins for Ultrasonic distance sensor
const int echo = 5;                         //

const int LeftLED = 7;                      //Pins for turning signal LEDs
const int RightLED = 6;

const int AIN1 = 8;                         //Pins for motor Driver
const int AIN2 = 9;
const int PWMA = 10;
const int Servopin = 11;                    //Pin to control Servo motor

const int arduinoConnection1 = 12;          //Pins to connect to second arduino
const int arduinoConnection2 = 13;

Servo myServo;                              //Instantiates a servo object

int motorSpeed = 250;                       //initialization of global variables to be used by program
int centerPos = 90;
int leftPos = centerPos - 45;  
int rightPos = centerPos + 45; 
float duration, distance;
char command;

void setup() {
  pinMode(AIN1, OUTPUT);                    //Set pins associated with motor driver to be outputs
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(trig, OUTPUT);                    //Set pins for the Ultrasonic sensor to be input/output respectively for trigger and echo
  pinMode(echo, INPUT);
  pinMode(LeftLED,OUTPUT);                  //Set pins associated with LED indicators to be outputs
  pinMode(RightLED,OUTPUT);
  pinMode(arduinoConnection1,OUTPUT);       //set connection Pins to be output pins
  pinMode(arduinoConnection2,OUTPUT);

  BTSerial.begin(9600);                     //Begin serial communication with the HC-05
  myServo.attach(Servopin);                 //Tell the servo which pin it is attached to so that its internal methods function correctly 
  myServo.write(centerPos);                 //Write the location of the servo motor to be the center position that we want
  }

void loop() {
  
  digitalWrite(trig, LOW);                  //Trigger the Ultrasonic distance sensor to emit a recoverable signal
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);           //Collect information about the ultrasonic signal and calculate the distance from the car to an obstacle
  distance = (duration*0.0343)/2;
  delay(100);
  
  if (distance <= 10 ){                    //Check if the car is too close to something
    if (BTSerial.available()) {            //Allow the car to check the bluetooth because the user will want to reverse still if they got too close to something

      command = (char)BTSerial.read();

      if (command = 'B'){
         // B = full backward
        spinMotor(-255);
        digitalWrite(arduinoConnection1, LOW);      //Inhibit playing of UK fight song sound
        digitalWrite(arduinoConnection2, HIGH);     //Play reversing sound
      }else{
        spinMotor(0);
        digitalWrite(arduinoConnection1, LOW);      //Inhibit playing of UK fight song sound
        digitalWrite(arduinoConnection2, LOW);      //Inhibit playing of Reversing sound
      }

    }else{
      spinMotor(0);
      digitalWrite(arduinoConnection1, LOW);        //Inhibit playing of UK fight song sound
      digitalWrite(arduinoConnection2, LOW);        //Inhibit playing of Reversing sound
    }
        
  }else{

    if (BTSerial.available()) {
      command = (char)BTSerial.read();                //Read in a character from the HC-05
          
      switch (command){                               //Interperet meaning of recieved character
        case 'F':
          // F = full forward
          spinMotor(255);
          digitalWrite(arduinoConnection1, LOW);      //Inhibit playing of UK fight song sound
          digitalWrite(arduinoConnection2, LOW);      //Inhibit playing of Reversing sound
          break;
        case 'B':
          // B = full backward
          spinMotor(-255);
          digitalWrite(arduinoConnection1, LOW);      //Inhibit playing of UK fight song sound
          digitalWrite(arduinoConnection2, HIGH);     //Play reversing sound
          delay(100);
          digitalWrite(arduinoConnection2, LOW);      //Inhibit constant restarting of reversing sound
          break;
        case 'S':
          // S = Complete Stop
          spinMotor(0);
          digitalWrite(arduinoConnection1, LOW);    //Inhibit playing of UK fight song sound
          digitalWrite(arduinoConnection2, LOW);    //Inhibit playing of reversing sound
          break;
        case 'L':
          //  L = Hard Left
          myServo.write(leftPos);                   //Put servo into left turning position
          digitalWrite(LeftLED, HIGH);              //Turn on Left turning signal
          digitalWrite(RightLED, LOW);              //Inhibit Right turning signal
          break;
        case 'R':
          // R = Hard Right
          myServo.write(rightPos);                  //put servo into right turning position
          digitalWrite(LeftLED, LOW);               //Inhibit Left turning signal
          digitalWrite(RightLED, HIGH);             //Turn on Right turning signal
          break;
        case 'C':
          //Return to center position         
          myServo.write(centerPos);                 //Return servo to center position
          digitalWrite(LeftLED, LOW);               //Inhibit Left turning signal
          digitalWrite(RightLED, LOW);              //Inhibit Right turning signal
          break;
        case 'W':
          //Play UK fight song on command
          digitalWrite(arduinoConnection1, HIGH);   //Play UK fight song  
          digitalWrite(arduinoConnection2, LOW);    //Inhibit playing of reversing sound
          delay(100);
          digitalWrite(arduinoConnection1, HIGH);   //Inhibit constant restarting of fight song
          break;
      }
    }
  }
} 

/********************************************************************************/
void spinMotor(int motorSpeed){ 

  if (motorSpeed > 0){                                //if the motor should drive forward (positive speed)  
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high 
    digitalWrite(AIN2, LOW);                          //set pin 2 to low 
  }
  else if (motorSpeed < 0){ 
    digitalWrite(AIN1, LOW);                          //set pin 1 to low 
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high 
  }else{                                              //if the motor should stop 
    digitalWrite(AIN1, LOW);                          //set pin 1 to low 
    digitalWrite(AIN2, LOW);                          //set pin 2 to low 
  }

  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed 
}
