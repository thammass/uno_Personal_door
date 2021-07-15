
/* 
 Stepper Motor Control - one revolution
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.  
 
  
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 
 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
                                     // for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution,4,5,6,7);            

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}
int i=0;
void STOP(void){
  digitalWrite(7, LOW);  
  digitalWrite(6, LOW);     
  digitalWrite(5, LOW);  
  digitalWrite(4, LOW);  
 
  
}

void loop() {
  // step one revolution  in one direction:
   Serial.println("clockwise");
  
  while(1){
    myStepper.setSpeed(50);
    myStepper.step(65);
    myStepper.setSpeed(20);
    myStepper.step(10);

    //myStepper.setSpeed(25);
   // myStepper.step(20);
 //   STOP();
    delay(2000);
    myStepper.setSpeed(50;
    myStepper.step(-85);
  //  STOP();
    delay(2000);
    STOP();
    delay(1000);
 
  }
  for(i=0;i<50;i++){
    
    myStepper.step(10);
  //myStepper.setSpeed(200);
  // myStepper.step(1);
  //myStepper.setSpeed(100);
  //for(i=0;i<5;i++) myStepper.step(1);
  //STOP();
  delay(100);
  }
  while(1);
  /*
   // step one revolution in the other direction:
  Serial.println("counterclockwise");
 // myStepper.setSpeed(100);
  for(i=0;i<50;i++)myStepper.step(-1);
 // myStepper.setSpeed(200);
//  myStepper.step(-20);
 // myStepper.setSpeed(100);
//  for(i=0;i<5;i++)myStepper.step(-1);
 STOP();
 delay(1000); 
*/
}

