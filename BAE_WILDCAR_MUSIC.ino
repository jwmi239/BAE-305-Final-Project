#include <SoftwareSerial.h>                                   //Import Necesarry Libraries
#include <Wire.h> 
#include <SparkFun_MMA8452Q.h> 
#include <DFRobotDFPlayerMini.h>

static const uint8_t PIN_MP3_TX = 5;                          //Set the Tx and Rx pins of the DFplayer
static const uint8_t PIN_MP3_RX = 4;

const int arduinoConnection1 = 12;                            //set up pins for communication from another arduino
const int arduinoConnection2 = 13;

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);        //Begin a softwareSerial object for the DFPlayer so we can communicate with it
DFRobotDFPlayerMini MP3player;                                //Create a DFPlayer object so we can use its functions
MMA8452Q accel;                                               //create an accelerometer object to get acceleration readings

void setup(){

  Serial.begin(9600);                                         //begin serial communication with a computer (if available) and with DFPlayer
  softwareSerial.begin(9600);

  pinMode(arduinoConnection1, INPUT);                         //prepare arduino connection pins to revcieve signals
  pinMode(arduinoConnection2, INPUT);

  if (MP3player.begin(softwareSerial)){                       //Check is MP3Player is functioning correctly
    Serial.println("MP3 Player ready");
  }else{
    Serial.println("MP3 Player NOT READY");
  }

  Wire.begin();                                               //Begin a wire object that connects the accelerometer to the arduino using the SDA and SGL pins

  if (accel.begin() == false) {                               //Ensure the Accelerometer is connected
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

  MP3player.volume(30);                                      //set the volume of the speaker
  delay(500);
  MP3player.play(1);      //Should play Backing up noise *For troubleshooting*
  delay(5000);
  MP3player.play(2);      //Should play UK Fight song *For troubleshooting*
  delay(5000);
  MP3player.play(3);      //Should play Reving noise *For troubleshooting*
  delay(5000);
}

void loop(){
  Serial.print(digitalRead(arduinoConnection1)); //*For troubleshooting*
  Serial.print(digitalRead(arduinoConnection2)); //*For troubleshooting*

  if (accel.available()) {

    Serial.print(accel.getCalculatedX());//*For troubleshooting*
    Serial.print(accel.getCalculatedY());//*For troubleshooting*
    Serial.println(accel.getCalculatedZ());//*For troubleshooting*

    if(accel.getCalculatedZ()>=1.5){
      MP3player.play(1);
    }else if (digitalRead(arduinoConnection1) == "HIGH"){             //Checks if the DFPlayer should play the UK Fight song
      MP3player.play(2);
    }else if (digitalRead(arduinoConnection2) == "HIGH"){             //Checks if the DFPlayer should play the reversing sound
      MP3player.play(3);
    }
  }
}