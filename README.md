# BAE-305-Final-Project
This repository contains all of the files associated with the BAE 305 final project.
## Project Summary

This report outlines the design, creation, and testing of a remote-control (RC) car intended for both the use of children and RC enthusiasts. In the original design concept, the user was intended to use radio connections to wirelessly control a four-wheel-drive, four-wheel-steer RC car programmed and powered by an Arduino Uno microcontroller. Additional features originally included a speedometer, a visual display, and car noises corresponding with the acceleration of the car. In the final product, the car was two-wheel-drive and two-wheel-steer and included features such as a handheld Bluetooth controller (as opposed to radio), an ultrasonic sensor serving as a safety feature, and a horn that plays the UK fight song. Through various testing phases, such as testing motor control via Bluetooth and iterating steering control to improve alignment, the RC car was completed and fully functional. 

## Design Description

### Bluetooth Wireless Connection

#### Materials


- HC-05 Bluetooth Module  
- Breadboard  
- Jumper wires  
- Raspberry Pi 3  
- Arduino Uno  
- 8BitDo Zero 2 Controller  

#### Assembly Procedures

First, the communication between the Raspberry Pi 3 and Arduino Uno was created. Once the HC-05 Bluetooth module was acquired, it was plugged into a breadboard and wired to the Arduino via jumper wires. It was connected to the 5V power rail and ground, the RX pin was connected to the software TX port, and the TX pin was connected to the software RX port. On the Raspberry Pi, no additional hardware was needed, as it has native Bluetooth capabilities. Serial communication and Bluetooth pairing were enabled by modifying the /boot/config.txt and disabling the serial console via raspi-config and using the bluetoothctl menu. The HC-05 was put in pairing mode by pressing and holding its button while powering it, which caused the onboard LED to blink rapidly. The Raspberry Pi then scanned for devices, paired with the HC-05, and trusted the connection. Once paired, the HC-05 was assigned a virtual serial port (e.g., /dev/rfcomm0), which is called in the main Python script. 

Once this connection was made, the 8BitDo Zero 2 gamepad was integrated via a wired USB connection to the Raspberry Pi. The controller was initialized in D-Input mode by holding the Start + Y buttons before connection, allowing it to register as a standard USB gamepad. Once connected, the Raspberry Pi automatically recognized the controller as /dev/input/js0. Functionality was verified using the jstest utility. Python was used to display button inputs to map button and directional inputs to specific vehicle actions, such as motor direction and auxiliary functions (playing the UK fight song).  

<img width="479" alt="Screenshot 2025-04-30 at 2 15 17 PM" src="https://github.com/user-attachments/assets/ef632437-6112-4380-be69-5a888d180a2a" />

Figure 1: HC-05 Wiring Diagram

### Ultrasonic Sensor 

#### Materials
•	HC-sr04 ultrasonic distance sensor
•	4 male-female jumper cables

#### Assembly Procedures
Connect all four jumper cables to the HC-sr04, ensuring to note which wires connect to certain pins (Ideally using color coding to distinguish functions, such as red for power and black for ground). Connect the VCC pin of the Ultrasonic distance sensor to the 5V source of the Arduino. Connect the GND pin of the Ultrasonic distance sensor to any of the ground pins on the Arduino. Connect the Trig pin on the ultrasonic distance sensor to pin 6 on the Arduino, and the Echo pin to pin 7 on the Arduino. Ensure that each of the pins are connected to the correct pin on the Arduino before powering on.
![image](https://github.com/user-attachments/assets/ab00fed3-09b2-42f4-a935-6a70b7adbbbd)

### Steering

#### Materials
  •	¼” – 20 tpi Hardware

  •	3D printed Steering Components

    -	Steering Knuckles
    
    -	Drag Links
    
    -	Front Carriage
    
  •	SG90 Servo and Included Lever (Pitman arm)

  •	1/8” Cotter Pins

#### Assembly Procedures
The steering system is simple to assemble, creating an intuitive assembly and maintenance process. 

Step 1: Bolt the front carriage under the base of the car using three ¼” bolts

![image](https://github.com/user-attachments/assets/08a6f2a9-ff0a-4d6a-b5ac-0010a96d6840)

Figure X: Steering System Assembly Step 1

Step 2: Install steering knuckle on each side of the front carriage using two ¼” bolts

![image](https://github.com/user-attachments/assets/339a3a2a-9231-463b-99c6-5513c82f32aa)

Figure X: Steering System Assembly Step 2

Step 3: Bolt Servo mount to base of car using two ¼” bolts and install the servo

![image](https://github.com/user-attachments/assets/3eb1e185-1fda-4cd7-b99e-526b81092372)

Figure X: Steering System Assembly Step 3

Step 4: Connect the servo to each steering knuckle with respected drag links, cotter pin each connection

![image](https://github.com/user-attachments/assets/58e12c10-ae57-48ac-aff8-da3e45756ed1)

Figure X: Steering System Assembly Step 4

Step 5: Bolt wheels to the outside face of each steering knuckle using a ¼” bolt

![image](https://github.com/user-attachments/assets/a2e4a77f-6bc3-4ebd-810c-9c81bceaf158)

Figure X: Steering System Assembly Step 5

Step 6: The servo is then wired using 5V for power, one power signal from a PWM pin, and a ground. The Arduino is coded to send an output for left and right turns at 45° based on the input from the controller. 

![image](https://github.com/user-attachments/assets/9d0cadc0-ba3e-405b-9068-16020f9461e4)

Figure X: Steering Servo Wiring Schematic

### Body

#### Materials
•	3d Printer
•	3d printing filament
#### Assembly Procedures
Download the 3d files "TruckBed","Truck cover" and "CarFront". These files can be printed by slicing them in any 3D printing slicing program, and then printing them on an appropriately sized 3D printer. The files will result in 3 files that will appear as seen below:
![image](https://github.com/user-attachments/assets/ebaafa90-f2fd-43e7-a646-50aba946723d)
![image](https://github.com/user-attachments/assets/ccc51285-e8b9-4306-a54b-73516ae395e0)
![image](https://github.com/user-attachments/assets/084f6ad2-f7d5-48e5-b837-543897263b38)
These pieces are designed to slide onto a 1.5mm thick aluminium plate that is 30cm x 15.5cm. to assemble simply slide the truck bed and the truck front onto the aluminum platform. the truck cover is designed to sit flush with the top of the truck bed, and can either be temporarily placed to access the electronics for maintenance, or glued closed for more permanent stability

### Speakers

#### Materials

Arduino 
DFPlayer Mini 
1W 8 Ohm speaker 
680 Ohm resistor 
1K Ohm resistor 
9V battery 
8705 Voltage Regulator 

#### Assembly Procedures

The Speaker assembly consisted of multiple interconnected pieces. The wiring can be found in Figure X. First, the Arduino was connected to the RX and TX pins of the DFPlayer mini. The RX of the player was connected through a parallel circuit that had two paths starting from the Arduino digital pin. The first path ran through a 680 resistor then split to the player. The second path after running through the 680 resistor, ran through a 1K resistor and to ground. This allowed the Arduino to control when the player functioned. The player controlled the sound, sourcing it to a 1W speaker to amplify the sound. The speaker connected to the SPK1 and SPK2 pins in the player. To power the speaker, a 9V battery was wired as the power source. The battery ran through a voltage regulator to set 5V and 1.5A to the DFPlayer. The voltage regulator output pin connected to the Vin of the player, supplying the necessary power to run the speaker. 

The Arduino IDE code used a downloadable DFPlayer library. After a few set up functions, the DFPlayer Mini could play a specific file from the command “MP3player.play(#)” where # corresponds to the desired sound file number. Sound functions within the system at three separate points. The player functions from the second Arduino. First, an engine sound plays resulting from changes in acceleration. The DFPlayer command was integrated into an if statement for when the accelerometer reads a value above a threshold. The other two sounds, the UK fight song and the reverse sound, function in the same way—however the logic set to run them are found on the first Arduino. The Arduino 1 code sends a signal to Arduino 2 when a specific button is pressed for the fight song and the car is reversing for the reversing sound. Each sound plays through the audio file. The full code can be found in Results. 

![ChatGPT Image Apr 24, 2025, 07_51_10 PM](https://github.com/user-attachments/assets/49e78c2a-422a-499e-becc-d9fc334d4564)
Figure X: Circuit Diagram for the sound components of the RC car. This wiring diagram was generated by ChatGPT 4o Ai

### Lights

#### Materials

LED x2 
1K Ohm resistor x2 

#### Assembly Procedures

Two LEDs were added to the car in the same way. The circuit for these LED’s are simple and direct, with few components. Fed power from the Arduino, the circuit path flows from a digital pin to the 1K resistor in the breadboard, to the LED, to ground. The LED’s did not share a digital pin, as to allow them to be controlled separately. For the circuit diagram, see Figure X.

![LED circuit diagram image](https://github.com/user-attachments/assets/1fa10b14-06f0-4c6f-aa4c-e830933da2d8)
Figure X: Circuit Diagram for the LED circuit. This is repeated for the second LED circuit

## Design Discussion

### Bluetooth

Bluetooth was chosen as the means for communication rather than traditional radio. While traditional radio does not require pairing or draw the amount of power that Bluetooth does, Bluetooth was chosen for its ease of integration with both of the microcontrollers being used in the project. The Pi is natively compatible with Bluetooth devices, and the Arduino merely needed an inexpensive Bluetooth module (HC-05). Apart from the occasional disconnection due to the power demands of the module, this made connection seamless after the initial connection to the Pi was made.  

Future designs may employ Bluetooth for additional features to the car. Supplemental power sources may be needed to prevent the disconnection of the module from the Pi. 

### Distance Sensing
Mounted on the front of the WildCar is an ultrasonic distance sensor. This sensor works by pulsing out an ultrasonic sound wave with known properties, and then waiting until the sound wave returns to the sensor, after being reflected off the immediate surroundings. By monitoring the duration that the wave takes to return, the distance from the sensor to an obstacle can be determined. We used this as a way to prevent the user from accidentally crashing into an obstacle, by defining a minimum distance that the car should be from something before it stops.
### Steering
To create a more realistically functioning car, we decided to model the steering after a two-wheel bell crank. The bell crank method uses a two-link system connected to each wheel that allows both wheels to turn from a single servo, similar to actual automobiles. This is done through a series of steering components, which includes a pitman arm, steering knuckles, and drag links. The goal with this system was to create what is known as Ackermann geometry. A steering system is considered to be Ackermann steering if the inside wheel is at a sharper angle than the outside wheel while turning. This is the case with the bell crank system, as seen below.

![image](https://github.com/user-attachments/assets/ec759c19-a169-40f3-bb2a-fdf99235ec02)

Figure X: Ackermann Steering Angle Phenomenon

With the pitman arm at a center-point, equal length drag links, and mirrored geometry for the steering knuckles, this creates a sharper angle for the side that the servo is turning away from. If not for this phenomenon, the inside wheel would be fighting the ground during turns due to travelling on a smaller turning radii than the outside wheel, as shown below. Ackermann steering allows for less wear on tires, steering components, and axle gearing if applicable. 

![image](https://github.com/user-attachments/assets/5186bd61-a32d-4c9a-b299-12ec5034290e)

Figure X: Inside wheel vs. Outside wheel Turning Radius 
### Sound

The car contains a sound component that functions as a final output for multiple logic systems. The sound for the car functions through a DFPlayer Mini. The DFPlayer is an MP3 module for the Arduino. The DFPlayer Mini was chosen as the sound playing device because of its easy integration with the Arduino system. Arduino IDE has a downloadable library for the DFplayer that allows audio to be integrated into the code with a few simple commands. For this application, the DFPlayer Mini connects to a 1W speaker that projects the sound. Housing a micro-SD card, the player runs MP3 audio files when directed by the Arduino microcontroller.  A voltage regulator and 9V battery were used to ensure the system received adequate power. The 9V supplied the voltage, and the regulator ensured adequate current flowed through the DFPlayer and to the speaker.  

### Lights

Lights were an added design feature of the car. These lights were to signal as the car turned. LED’s were chosen because they are often used in Arduino projects, and the bright colors add an additional sensory element for users. Individual LED’s were chosen over a strip of lights due to the high demand for current needed to sustain brightness in a longer string of LED’s. The entire car already had 9V batteries and 5V power packs, so it was determined unnecessary to add additional power sources for just the lights. Additionally, the singular LED’s mimicked the turn signals of a car, fitting well with the theme for the project. 

## Testing Procedures

The testing of the car took place in several phases as each feature was completed, as well as a final “sprint” to integrate all features.  


The first feature to be completed was the establishment of the wireless connection. A series of tests were completed for each leg of communication previously mentioned. First, the communication between the Raspberry Pi 3 and Arduino Uno was tested. Once the HC-05 Bluetooth module was running on the Arduino, serial communications were opened on both the Arduino and Pi. The HC-05, acting as the slave, was sent serial messages via the assigned serial port from the Pi to confirm its connection. Once the connection between the Pi and Arduino was secured, attention was turned to connecting the 8BitDo controller to the Pi. The controller was wired to the Pi via USB—similar to how a keyboard would work with the Pi. To determine what messages each button of the controller was sending upon being pressed, a short python script was created and used to read the button press events. These outputs were recorded and used in the development of the primary code. 

Another feature that needed to be completed and tested was sound. Initially, based on the DFPlayer specifications a 3W speaker was chosen. This speaker was the top of the power output range for the player. When in a system that ran solely the DFPlayer and the speaker, the sound worked without issues. When integrating with the system however, the speaker size proved to be an issue. Given the power demand of the 3W speaker, the addition of the sound system was creating a power need that exceeded the output capabilities of the Arduino. Consequently, the sound quality decreased, and other components of the car would not run when the speaker was playing. The necessary solution was switching to a different speaker that could use a smaller amount of power. Therefore, a 1W speaker was selected to replace the 3W speaker. This speaker was wired in the same way as the original speaker. This set up worked the first day it was implemented, however the following day had additional issues: giving loud low pitch feedback and not playing the desired mp3 files. A 9V battery was added to be the power source for the player and speaker. Wired through the Arduino however, this did not fix the issue as the Arduino limited the current flow of the circuit. To resolve this issue, a voltage regulator was incorporated. The voltage regulator connected to the 9V rather than the Arduino, supplying a 5V and 1.5 A to the DFPlayer and speaker. This resolved the sound issues. 

Lights were another feature that needed to be tested and integrated. Initially, it was planned to use an LED strip to maximize the appeal of the LED. In the inital testing of the LEDs it was determined that 5V from the Arduino was not sufficient to run the strip. This LED strip would require an additional power source to supply enough current to maintain light for many LEDs. Once additional power sources were acquired for the motors, the LEDs were revisited to see if they could be powered. During this testing, a 9V battery was wired through the 5V pin of the Arduino rather than the necessary Vin pin. This issue caused the computer connected to the Arduino to receive 9V of back voltage and stop working. Individual LEDs were chosen to be used over the strip due to the lack of need for additional power. These LEDs wired directly to the Arduino and were controlled from HIGH and LOW commands through a digital pin. 

The steering system also proposed a few challenges. The code was simple, just a few lines taken from online sources and tailored to the needs of this project. The CAD modeling resulted in relatively smooth implementation of the moving parts. However, the first iteration of the steering knuckles did not have clearance for the “lug nuts” and required more drop to allow for them. Connection methods for the drag links were also a point of testing. The holes were too small to reasonably use bolts and screws would’ve inhibited the rotation during turning. 

## Results

![IMG_6337](https://github.com/user-attachments/assets/fdd1002d-88ab-4f99-a785-212e5844289f)
Figure X: Complete car assembly

## Discussion

Throughout the project, there were multiple challenges and complications that needed to be overcome to complete the deliverables. These challenges molded the final project into what is presented in this report. The WildCar completed each deliverable it set out to do: two-wheel drive, two-wheel steering, wireless Bluetooth control, Lights synced to turning, revving sound from acceleration, beeping upon reversing, playing a song from a controlled input, and stop when too close to an object-- all integrated into a covered complete car design. 

Bluetooth control of the car proved to be both one of the most prominent features and drawbacks of the car. Proving difficult to set up and maintain manually, Bluetooth through a Raspberry Pi was an effective means of remote communication when connected. The system communicated with little delay and the signal transmitted without error. Bluetooth as incorporated in this system, however, had many drawbacks that would limit how well the project could be extrapolated to other projects. First, the connection needed to be manually established. The connection would often get lost, and the connection process repeated. Additionally, using the Pi as a relay from the controller and communicator to the Arduino proved to be an added layer of complexity. Navigating the Pi system was not user friendly and minimally added to the effectiveness of the project. While it did increase the range of connection when compared to the controller and Arduino alone, it was still limited by the inherent limitations of Bluetooth (about 30ft). Higher quality controllers or radio controllers are available for purchase that have greater range, and can cut out the Pi as an intermediate, effectively communicating directly with the Arduino. 

Another limitation with the WildCar design is in regard to power. The Ardunos are only capable of 5V power output with a power pack. Many parts of the design required greater power to run sufficiently when integrated. The final design required two 5V power packs and two 9V batteries. The design was limited by these sources because the batteries would quickly drain and require replacement. The power sources, whilst rechargeable, faced similar issues. The system did supply power effectively, and each component functioned properly with the power supplied. Multiple sources also allowed for each component to receive the specific power needed independently. Performance would decrease as the power drained. A higher quality single power supply would allow for a more integrated design, would last longer, and clean up the wiring. As seen in the use of a voltage regulator to meet the specific needs of the speaker, power output could be modified as needed to meet individual needs of components. A better power supply would also allow the car to run longer at full performance.  

The code for the steering system worked as expected with the lines given online. Integration was easy, as the controller was already connected via Bluetooth to send input to the servo. Another easy fix came through the implementation of cotter pins for the linkage connections; the pins are small enough and allow for rotation during turning. The last step was to add clearance for the lug nuts, which was done through a second iteration of 3D printed steering knuckles. This allowed for tightening of the entire steering system, and brought the car closer to having true Ackermann steering geometry.
