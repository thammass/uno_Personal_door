/*-----------------------------------------
Project Personal Door
Door Unit ( v1.1)
 ----------------------------------------
Develop by Mr.Thammasak Sa-nguansatwaja
Test date: 2015/10/08
Windows: Windows8 64Bit Professional
-----------------------------------------
Software Tools:
-----------------------------------------
- Arduino 1.0.6
- library Stepper.h (standard arduino library)
-----------------------------------------
Embedded Device
-----------------------------------------
MPU:	UNO
Board:	UNO
IN:	3 Analog IN  (Max:5Vdc)
        - A4 ,Proxymit Feedback Position Zone
        - A3 ,Door Open
        - A2 ,Door 0:Forward  ,1: Reverse
        - A1 ,Safety
        - A0 ,Set Direction
OUT:	4 Digital Out (Max: 5Vdc)
        - Stepping Motor(STEPS, pin 11, pin 10, pin 9, pin 8);

        1 Analog OUT (Max:5Vdc)
        - pin 9  (0 - 5 V : 0 - 180 degree)
-----------------------------------------  */
//---library Stepper.h (standard arduino library) ----------
#include <Stepper.h>
#include <EEPROM.h>

#define STEPS 200
#define MaxSTEP
#define RampSTEP 1
Stepper stepper(STEPS, 4, 5, 6, 7);
//----- prototype -----------------
void closeDOOR(void);
//void motorMOVE(void);
void stepMOVE(int  DIR);
//---------- proten ----------------
const int ProxPin = A5; // analog pin used to connect the potentiometer
const int AoutPosition = 9;
//int ProxValue; // variable to read the value from the analog pin

//---------- motor Control ---------
// เปลี่ยนค่า DOOR เพื่อใช้ในการอัดโปรแกรม แต่ละประตู
#define DOOR 1   
#define vON 300
#define usePROX 1

const int CenterPin = A0;
const int Finger = A1;
const int DirectPin = A4;

const int OpenPin = A3;
const int FeedBackPin = A2;

//const int SafetyPin = A5;


unsigned int SetPointValue = 0;
unsigned int FeedBackValue = 0;
unsigned int CenterValue = 0;
unsigned int OpenValue = 0;
unsigned int DirectValue = 0;
//unsigned int SafetyValue=0;
unsigned int countRead = 0;

unsigned long sampSetPointValue = 0;
unsigned long sampFeedBackValue = 0;
unsigned long sampOpenValue = 0;
unsigned long sampDirectValue = 0;

#define loopSensor 10
#define loopAVGSensor (loopSensor*3)
#define loopPrint 1500
#define loopMotor loopAVGSensor

unsigned int countloopSensor = 0;
unsigned int countloopAVGSensor = 0;
unsigned int countloopMotor = 0;
unsigned int countloopPrint = loopPrint;
unsigned char OPEN = 0;
unsigned char DIR = 0;
unsigned char tempDIR = 0;
#define Ready 0
#define Stop 1
#define DoorOpen 2
#define DoorClose 3
#define Safety 4
#define Wait 5
#define DoorCenter 6

unsigned char STM = Stop;
int MAXSPEED = 0;
unsigned int TIMEOUT = 0;
//--------- positioning ----------
int proportional = 0;
char stepPOS0;
char POS90;
char stepPOS180;
//---------------------------------
int loopMOTORoff = 0;
void motorOFF(void) {

  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);

  digitalWrite(9, LOW);
  /*

  if(loopMOTORoff++  >4){
    loopMOTORoff=0;
  }
  if( loopMOTORoff >4){
     //  digitalWrite(7, HIGH);
       //digitalWrite(6, HIGH);
       digitalWrite(5, HIGH);
       //digitalWrite(4, HIGH);
  }
   */
}
//-------------------------------------------------------------------------------------
void setup() {

  // initialize serial communications at 9600 bps:
  Serial.begin(19200);
  // stepper.setSpeed(30);

  switch (DOOR) {   //โอ๋ request update  2021/07/19
    case 1: //door1
    
      POS90 = -60;
      stepPOS0 = 70;
      stepPOS180 = 67;
      MAXSPEED = 65;
      break;
    case 2:  //door 2
    case 3:  //door 3
      POS90 = -90;
      stepPOS0 = 92;
      stepPOS180 = 92;
      MAXSPEED = 150;
      break;
   case 4: //door4
      POS90 = -60;
      stepPOS0 = 67;
      stepPOS180 = 67;
      MAXSPEED = 60;
      break;
  }
//  EEPROM.write(1, POS90);
//  EEPROM.write(2, stepPOS0);
//  EEPROM.write(3, stepPOS180);
 // EEPROM.write(4, MAXSPEED);

//  POS90 = EEPROM.read(1);
 // stepPOS0 = EEPROM.read(2);
 // stepPOS180 = EEPROM.read(3);
 // MAXSPEED = EEPROM.read(4);

  Serial.print("\r\n ------ start ------- \r\n" );
  Serial.print("POS90:"); Serial.println(int(POS90));
  Serial.print(" POS0:"); Serial.println(int(stepPOS0));
  Serial.print(" POS180:"); Serial.println(int(stepPOS180));

  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);

  //while(1);

}
//-------------------------------------------------------------------------------------
void loop() {

  //----------Read Input ---------------
  if (countloopSensor++ >= loopSensor) {
    // Serial.print("Read sensor.\r\n");
    countloopSensor = 0;
    countRead++;
    //   sampSetPointValue += analogRead(SetPointPin);
    sampFeedBackValue += analogRead(ProxPin); // reads the value of the potentiometer (value // between 0 and 1023)
    sampOpenValue += analogRead(OpenPin);
    sampDirectValue += analogRead(DirectPin);
  }//if(countloopSensor++ > loopSensor)
  //----------Calculate sensor -----------------
  if (countloopAVGSensor++ >= loopAVGSensor) {
    // Serial.print("AVGSensor.\r\n");
    countloopAVGSensor = 0;

    FeedBackValue = (sampFeedBackValue / countRead);
    //analogWrite(AoutPosition, FeedBackValue);

    //  FeedBackValue = map(FeedBackValue,0,930 , 0, 180);

    //---- Avg ------
    OpenValue = (sampOpenValue / countRead);
    if (OpenValue > vON) {
      OPEN = 0;
      // digitalWrite(9, LOW);
    } else {
      OPEN = 1;
      //digitalWrite(9, HIGH);
    }

    DirectValue = (sampDirectValue / countRead);
    if (DirectValue > vON) {
      DIR = 0;
    } else {
      DIR = 1;
    }

    sampFeedBackValue = 0;
    sampOpenValue = 0;
    sampDirectValue = 0;
    countRead = 0;
  }//if(countloopAVGSensor++ >= loopAVGSensor)
  //---------- Print out  ---------------------

  if (countloopPrint++ >= loopPrint) {
    countloopPrint = 0;
    Serial.print("STM:");
    switch (STM) {
      case Ready: Serial.print("Ready"); break;
      case Stop: Serial.print("Stop"); break;
      case DoorOpen: Serial.print("DoorClose"); break;
      case DoorClose: Serial.print("DoorClose"); break;
      case Safety: Serial.print("Safety"); break;
      case Wait: Serial.print("Wait"); break;
      case DoorCenter: Serial.print("DoorCenter"); break;

      default: Serial.print("default");
    }
    //      Serial.print("  SetPointValue=" );Serial.print(SetPointValue);
    Serial.print(" FeedBackValue=" ); Serial.print(FeedBackValue);
    Serial.print(" OpenValue="); Serial.print(OpenValue);
    // Serial.print(" DirectValue=" );Serial.print(DirectValue);
    Serial.print(" OPEN="); Serial.print(OPEN);
    Serial.print(" DIR=" ); Serial.print(DIR);
    Serial.print(" tempDIR=" ); Serial.print(tempDIR);

    Serial.print("\r\n");

    switch (STM) {
      case Wait:
        motorOFF();
        if (OPEN == 1) {
          STM = Ready;
        }
        break;
      case Ready: //0
        if (OPEN == 1) {
          digitalWrite(9, HIGH);
          delay(50);
          Serial.println(" DoorOpen " );
          if (DIR == 1) {
            // goto 180 degree
            tempDIR = 3;
            //close:3
          } else {
            // goto 0 degree
            tempDIR = 1;
            //close:1
          }
          //Home on open
          if (usePROX) {
            if (tempDIR == 1) {
              FeedBackValue = analogRead(ProxPin);
              TIMEOUT = 0;
              while ( FeedBackValue < 50 && TIMEOUT++ < 95) {
                FeedBackValue = analogRead(ProxPin);
                stepper.setSpeed(8);
                stepper.step(1);
                delay(5);
              }
            } else {
              FeedBackValue = analogRead(ProxPin);
              TIMEOUT = 0;
              while ( FeedBackValue > 50 && TIMEOUT++ < 95) {
                FeedBackValue = analogRead(ProxPin);
                stepper.setSpeed(8);
                stepper.step(-1);
                delay(5);
              }
            }
          }
          //-----------------------
          if (DIR == 1) {
            stepMOVE(2);
          } else {
            stepMOVE(0);
          }
          /*
              Serial.println(" DoorOPEN check " );
              if (tempDIR == 1) {
                FeedBackValue = analogRead(ProxPin);
                TIMEOUT = 0;
                while ( FeedBackValue > 50  && TIMEOUT++ < 95) {
                  FeedBackValue = analogRead(ProxPin);
                  stepper.setSpeed(8);
                  stepper.step(1);
                }
              } else if (tempDIR == 3) {
                FeedBackValue = analogRead(ProxPin);
                TIMEOUT = 0;
                while ( FeedBackValue < 50 && TIMEOUT++ < 95) {
                  FeedBackValue = analogRead(ProxPin);
                  stepper.setSpeed(8);
                  stepper.step(-1);
                }
              }
              //delay(150);
           */
          STM = DoorOpen;
        } else {
          STM = DoorClose;
        }
        break;
      case Stop: //1
        if (OPEN == 1) {
          STM = Ready;
        } else {
          motorOFF();
          CenterValue = analogRead(CenterPin);
          Serial.print("CEN:");
          Serial.println(CenterValue);
          if (!(CenterValue > 50)) {
            //is center
            Serial.println("is CEN:");
          } else {
            // หาอาศา
            //0  step-
            FeedBackValue = analogRead(ProxPin);
            if (FeedBackValue > 50) {
              //while( CenterValue >50  && TIMEOUT++<150){
              //delay(1000);
              Serial.println("Auto CEN:");
              digitalWrite(9, HIGH);
              delay(50);
              while ((CenterValue > 50)) {
                CenterValue = analogRead(CenterPin);
                stepper.setSpeed(5);
                stepper.step(-1);
                delay(5);
              }
              //}
            } else {
              //180 step+
              Serial.println("Auto CEN:");
              digitalWrite(9, HIGH);
              delay(50);
              while ((CenterValue > 50)) {
                CenterValue = analogRead(CenterPin);
                stepper.setSpeed(5);
                stepper.step(1);
                delay(5);
              }
            }//if (FeedBackValue > 50)
          }//if (CenterValue > 50)
        }
        break;
      case DoorOpen: //2
        if (OPEN == 0) {
          STM = DoorClose;
          //digitalWrite(9,HIGH);

        } else {
          //delay(100);
          motorOFF();
        }
        break;
      case DoorClose:  //3
        digitalWrite(9, HIGH);
        stepMOVE(tempDIR);
        //delay(500);
        STM = DoorCenter;
        // change state to "STOP" on Close door complete
        break;
      case DoorCenter:
        Serial.println(" DoorCenter " );
        if (usePROX) {
          if (tempDIR == 1) {
            FeedBackValue = analogRead(ProxPin);
            TIMEOUT = 0;
            digitalWrite(9, HIGH);
            delay(50);
            while ( FeedBackValue > 50  && TIMEOUT++ < 95) {
              FeedBackValue = analogRead(ProxPin);
              stepper.setSpeed(5);
              stepper.step(-1);
              delay(5);
            }
          } else if (tempDIR == 3) {
            FeedBackValue = analogRead(ProxPin);
            TIMEOUT = 0;
            digitalWrite(9, HIGH);
            delay(50);
            while ( FeedBackValue < 50 && TIMEOUT++ < 95) {
              FeedBackValue = analogRead(ProxPin);
              stepper.setSpeed(5);
              stepper.step(1);
              delay(5);
            }
          }
          //delay(150);
        }
        STM = Stop;
        break;
      default:   // else
        STM = Stop;
    }
  }

  //--------check sfetySwitch ------------
  //SafetyValue=analogRead(SafetyPin);
  //if(SafetyValue>vON){STM=Safety;}
  //----------state machine-----------------------------------------
}
//-------------------------------------------------------------------------------------
void stepMOVE(int DIR) {
  int tragetSTEP;
  int stepCount = 0;
  int L = 0;
  int FWD = 0;
  int MaxSP = MAXSPEED;
  if (DIR == 0) {
    //forward
    tragetSTEP = (stepPOS0); //10;
  } else if (DIR == 1) {
    // back forward
    tragetSTEP = (POS90); //10;
  } else if (DIR == 2) {
    //Rev
    tragetSTEP = (-stepPOS0); //10;
  } else if (DIR == 3) {
    // back Rev
    tragetSTEP = (-POS90); //10;
  }
  if (tragetSTEP > 0) {
    FWD = 1;
  } else {
    FWD = 0;
  }
  //stepper.setSpeed(MaxSP);
  //stepper.step(tragetSTEP);
  /*
  for (L = 1; L <= abs(tragetSTEP); L++) {
    //-------------------------
    if (L <= 10)stepper.setSpeed(MaxSP/2);
    else if (L <= 20)stepper.setSpeed(MaxSP);
    else if (L <= 30)stepper.setSpeed(MaxSP);
    else if (L <= 40)stepper.setSpeed(MaxSP);
    else if (L <= 50)stepper.setSpeed(MaxSP);
    else if (L <= 60)stepper.setSpeed(MaxSP);
    else if (L <= 65)stepper.setSpeed(MaxSP);
    else if (L <= 70)stepper.setSpeed(MaxSP);
    else if (L <= 75)stepper.setSpeed(MaxSP);
    else if (L <= 80)stepper.setSpeed(MaxSP);
    else if (L <= 90)stepper.setSpeed(MaxSP);
    else if (L <= 100)stepper.setSpeed(MaxSP);
    else stepper.setSpeed(15);
    //-------------------------
    if (FWD == 1) {
      stepper.step(1);
    } else {
      stepper.step(-1);
    }
  }//for
  */
  /*
  if (FWD == 1) {
    //open
      stepper.setSpeed(MaxSP/2);
      stepper.step(tragetSTEP/10);
      stepper.setSpeed(MaxSP/2);
      stepper.step(tragetSTEP/10);

      stepper.setSpeed(MaxSP);
      stepper.step((tragetSTEP/10)*8);

  }else{
    //center
      stepper.setSpeed(MaxSP/4);
      stepper.step(tragetSTEP/10);
      stepper.setSpeed(MaxSP/2);
      stepper.step(tragetSTEP/10);

      stepper.setSpeed(MaxSP);
      stepper.step((tragetSTEP/10)*7);

      stepper.setSpeed(MaxSP/2);
      stepper.step(tragetSTEP/10);

  }
  */
  if (FWD == 1) {
    //open
    stepper.setSpeed(MaxSP / 2);
    stepper.step(10);
    stepper.setSpeed(MaxSP / 2);
    stepper.step(10);

    stepper.setSpeed(MaxSP);
    stepper.step(tragetSTEP - 35);


    stepper.setSpeed(MaxSP / 2);
    stepper.step(15);
  } else {
    //center
    stepper.setSpeed(MaxSP / 2);
    stepper.step(-10);
    stepper.setSpeed(MaxSP / 2);
    stepper.step(-10);

    stepper.setSpeed(MaxSP);
    stepper.step(tragetSTEP + 30);

    stepper.setSpeed(MaxSP / 2);
    stepper.step(-10);

  }
  delay(50);
}
//-------------------------------------------------------------------------------------


