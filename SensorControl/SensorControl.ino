/*-----------------------------------------
  Project Personal Door
  Sensor  Unit ( v1.2)
  ----------------------------------------
  Develop by Mr.Thammasak Sa-nguansatwaja
  Test date: 2015/11/01
  Windows: Windows8 64Bit Professional

  -----------------------------------------
  Software Tools:
  -----------------------------------------
  - Arduino 1.0.6
  - library
    Ultrasonic - Library for HR-SC04 Ultrasonic Ranging Module.
    Rev.4 (06/2012)
    J.Rodrigo ( www.jrodrigo.net )
    more info at www.ardublog.com
  -----------------------------------------
  Embedded Device
  -----------------------------------------
  MPU:	Mega 2560
  Board:	Mega 2560
  IN:	....
  OUT:	....

  V1.0  ออกใช้งานครั้งแรก
  V1.1  แก้ปัญหา auto direct door2
  V1.2  add funtion alert fujiko

  -----------------------------------------  */
//#include <Ultrasonic.h>
//-------------  analog ----------
#define  aClose 80  //80
#define  aOpen 500 //900
//----------------------------
#define  delayDOOR  (100)      //25      // หลังจากเดินผ่าน sensor ขาออก  // ไม่ให้ sensor เห็นเท้าขาออก ใส่ค่าเพิ่มขึ้น//25
#define  delayDOORautoClose (1100)//(250)   // ไม่เดินผ่าน sensor จะ close
#define  delayDOORautoDIR   delayDOORautoClose    // auto direct

#define loopALAM 0
unsigned char Falam = 0;
unsigned int F1read = 0;
int cDoor1 = 0;
unsigned int F2read = 0;
unsigned int F4read = 0;
int cDoor2 = 0;
int cDoor2IN = 0;
int cDoor2OUT = 0;
unsigned int F3read = 0;
int cDoor3 = 0;
unsigned int modeIN = 0;
unsigned int loopCount = 0;
int loopS1Count = 0;
const int Sensor1 = 2;
const int Sensor2 = 4;
const int Sensor3 = 6;
const int Sensor4 = 8;
const int Sensor5 = 10;
const int Sensor6 = 12;
int buttonState = 0;



const int prn = 0;
unsigned int ALAM1 = 0, ALAM2 = 0, ALAM3 = 0, ALAM4 = 0;
//ping 2  F4 contact
//ping 3  Motor Open
//Ultrasonic S1(3, 2); // (Trig PIN Green,Echo PIN RED)
//Ultrasonic S2(5, 4);
//Ultrasonic S3(7, 6);
//Ultrasonic S4(9, 8);
//Ultrasonic S5(11, 10);
//Ultrasonic S6(13, 12);

int v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0, v6 = 0;
char IR1 = 1;
char IR2 = 1;
char IR3 = 1;
char IR4 = 1;
char IR5 = 1;
char IR6 = 1;
int SW_IN = 1, SW_OUT = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  pinMode(22, INPUT);// in
  pinMode(23, INPUT);// out


  pinMode(Sensor1, INPUT); // sensor ir
  pinMode(Sensor2, INPUT); // sensor ir
  pinMode(Sensor3, INPUT); // sensor ir
  pinMode(Sensor4, INPUT); // sensor ir
  pinMode(Sensor5, INPUT); // sensor ir
  pinMode(Sensor6, INPUT); // sensor ir

  pinMode(24, OUTPUT);// out
  pinMode(25, OUTPUT);// out

  pinMode(A4, OUTPUT);  //Door3, F3:A1

  pinMode(A2, OUTPUT);  //ALAM F1
  pinMode(A3, OUTPUT);  //ALAM F2
 // pinMode(A4, OUTPUT);  //ALAM F3
 // pinMode(A5, OUTPUT);  //ALAM F4

  pinMode(A12, OUTPUT);  //Door4, F4:A14
  pinMode(A13, OUTPUT); // Door4 DIR
  pinMode(A15, OUTPUT);  //door4 LED

  pinMode(A8, OUTPUT);  //Door2, F2:A10
  pinMode(A9, OUTPUT); // Door2 DIR
  pinMode(A11, OUTPUT);  //door2 LED

  pinMode(A6, OUTPUT);  //Door1, F1:A7

  digitalWrite(A12, LOW); //door4
  digitalWrite(A4, LOW); //door3

  digitalWrite(A8, LOW); //door2
  digitalWrite(A6, LOW); //door1

  digitalWrite(A13, LOW); //door4 DIR
  digitalWrite(A9, HIGH); //door2 DIR

  digitalWrite(A15, LOW); //door4 LED
  digitalWrite(A11, LOW); //door2 LED


  //  digitalWrite(A15, HIGH);// X  F4
  //  digitalWrite(A11, HIGH); // /  F2

  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
//  digitalWrite(A4, HIGH);
//  digitalWrite(A5, HIGH);

  digitalWrite(24, HIGH); //Door1 DIR
  digitalWrite(25, HIGH); // FUJIKO S1
}

void loop() {
  byte i = 0;
  byte samp = 1;
  // delay(1);
  //Serial.println("  ");
  //----------  read sensor -----------------
  v1 = 0;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  //for (i = 0; i < samp; i++) {
  //v1 = S1.Ranging(CM);//v1 = S1.Ranging(CM);
  IR1 = digitalRead(Sensor1);
  if (IR1 == HIGH) {
    v1 = 50;
  }
  else {
    v1 = 0;
  }
  delay(1);
  //v2 = S2.Ranging(CM);//v2 = S2.Ranging(CM);
  IR2 = digitalRead(Sensor2);
  if (IR2 == HIGH) {
    v2 = 50;
  }
  else {
    v2 = 0;
  }
  //v3 = S3.Ranging(CM);//v3 = S3.Ranging(CM);
  IR3 = digitalRead(Sensor3);
  if (IR3 == HIGH) {
    v3 = 50;
  }
  else {
    v3 = 0;
  }
  //v4 = S4.Ranging(CM);//v4 = S4.Ranging(CM);
  IR4 = digitalRead(Sensor4);
  if (IR4 == HIGH) {
    v4 = 50;
  }
  else {
    v4 = 0;
  }
  delay(1);
  // v5 = S5.Ranging(CM);//v5 = S5.Ranging(CM);
  IR5 = digitalRead(Sensor5);
  if (IR5 == HIGH) {
    v5 = 50;
  }
  else {
    v5 = 0;
  }
  delay(1);
  //v6 = S6.Ranging(CM);//v6 = S6.Ranging(CM);
  IR6 = digitalRead(Sensor6);
  if (IR6 == HIGH) {
    v6 = 50;
  }
  else {
    v2 = 0;
  }
  //}
  // v1 = v1 / samp;
  // v2 = v2 / samp;
  // v3 = v3 / samp;
  // v4 = v4 / samp;
  // v5 = v5 / samp;
  // v6 = v6 / samp;
  //---------------- Gate1 -------------------
  pinMode(22, INPUT);// in
  pinMode(23, INPUT);// out

  SW_IN = digitalRead(23);
  SW_OUT = digitalRead(22);

  F1read = analogRead(A7);

  if (F1read < aClose ) {
    cDoor1 = delayDOORautoClose; //delayDOOR;
    digitalWrite(24, LOW); //Door1 DIR
  }
  if (!SW_IN) {
    cDoor1 = delayDOOR; //delayDOOR;
    digitalWrite(24, LOW); //Door1 DIR
  }
  if (!SW_OUT) {
    cDoor1 = delayDOOR; //delayDOOR;
    digitalWrite(24, HIGH); //Door1 DIR
  }

  if (cDoor1 > 0) {
    cDoor1--;
    if ( v2 < 45) {
      cDoor1 = delayDOOR;
    }
    if (prn) {
      //  Serial.println(cDoor1);
      // Serial.println("*** F1:Pass ***");
    }
    //Serial.print(cDoor1);delay(10);
    digitalWrite(A6, HIGH); //open
  } else {
    digitalWrite(A6, LOW);  //close
  }
  //---------------- Gate2 -------------------
  F4read = analogRead(A14); //IN
  F2read = analogRead(A10); //out

  if (F4read < aClose && cDoor2OUT == 0) {
    //In
    modeIN = 1;
    cDoor2IN = delayDOORautoDIR + delayDOORautoClose; //delayDOOR;
    cDoor2 = delayDOORautoClose;
  } else if ( F2read < aClose && cDoor2IN == 0) {
    //Exit
    modeIN = 0;
    cDoor2OUT = delayDOORautoDIR + delayDOORautoClose; //delayDOOR;
    cDoor2 = delayDOORautoClose;
  } else {

  }
  //-------------  DIR Detect -------------------------------------------------
  if (cDoor2IN > 0) {
    cDoor2IN--;
    if (cDoor2IN <= 0) cDoor2IN = 0; // bug Open ค้าง
    // IN
    //Direct
    if (prn) {
      Serial.println("*** IN:Pass ***");
    } //Serial.println(F4read);}
    digitalWrite(A13, LOW); //door4 DIR
    digitalWrite(A9, HIGH); //door2 DIR

    digitalWrite(A15, LOW);  // /  F4
    digitalWrite(A11, HIGH); // X  F2
    // delay(1);
  } else if (cDoor2OUT > 0) {
    cDoor2OUT--;
    if (cDoor2OUT <= 0) cDoor2OUT = 0; // bug Open ค้าง
    // OUT
    //Direct
    if (prn) {
      Serial.println("*** OUT:Pass ***");
    }//Serial.println(F2read);}
    digitalWrite(A13, HIGH);//door4 DIR
    digitalWrite(A9, LOW);  //door2 DIR

    digitalWrite(A15, HIGH);// X  F4
    digitalWrite(A11, LOW); // /  F2
    // delay(1);
  } else {
    // Free
    digitalWrite(A15, LOW);// /  F4
    digitalWrite(A11, LOW); // /  F2
  }
  //-------------------------------------------------------------------------------

  if (cDoor2 > 0) {
    cDoor2--;
    if (cDoor2OUT > 0) {
      if ( v4 < 45 ) {
        cDoor2 = delayDOOR;
        cDoor2OUT = delayDOORautoDIR;
      }
    } else { //cDoor2IN
      if ( v3 < 45 ) {
        cDoor2 = delayDOOR;
        cDoor2IN = delayDOORautoDIR;
      }
    }
    digitalWrite(A8, HIGH);
    digitalWrite(A12, HIGH);

  } else {
    cDoor2 = 0;
    digitalWrite(A8, LOW);
    digitalWrite(A12, LOW);
  }
  //---------------- Gate3 -------------------
  F3read = analogRead(A5);
  //F3read=100;
  if (F3read < aClose ) {
    cDoor3 = delayDOORautoClose; //delayDOOR;
  }
  if (cDoor3 > 0) {
    cDoor3--;
    if ( v6 < 45 ) {
      cDoor3 = delayDOOR;
    }
    if (prn)Serial.println("*** F3:Pass ***");
    digitalWrite(A4, HIGH);
  } else {
    digitalWrite(A4, LOW);
  }
  //---------------------------------------------------------
  if (prn) {
    Serial.print("S1:");
    Serial.print(v1); // CM or INC
    Serial.print(" S2:");
    Serial.print(v2); // CM or INC
    Serial.print(" S3:");
    Serial.print(v3); // CM or INC
    Serial.print(" S4:");
    Serial.print(v4); // CM or INC
    Serial.print(" S5:");
    Serial.print(v5); // CM or INC
    Serial.print(" S6:");
    Serial.print(v6); // CM or INC
    Serial.print("    ");
    Serial.print(" IN:");
    Serial.print(cDoor2IN); // CM or INC
    Serial.print(" OUT:");
    Serial.print(cDoor2OUT); // CM or INC
    Serial.print(" CLOSE:");
    Serial.print(cDoor2); // CM or INC
    Serial.println(" ");
  } else {
    //Serial.println(".");
  }

  if (loopCount == 0) {
    if (cDoor1 <= 0) {
      if ( v1 < 45 || v2 < 45) {
        ALAM1 = 1;
        loopS1Count = delayDOOR * 5;
      }
    }
    if (cDoor2 <= 0) {
      if (v3 < 45) {
        ALAM2 = 1;
        loopS1Count = delayDOOR * 5;
      }
      if (v4 < 45) {
        ALAM4 = 1;
        loopS1Count = delayDOOR * 5;
      }
    }

    if (cDoor3 <= 0) {
      if ( v5 < 45 || v6 < 45) {
        ALAM3 = 1;
        loopS1Count = delayDOOR * 5;
      }
    }
  }
  if (loopCount == 0) {
    loopCount = loopALAM;
    if (ALAM1 == 1) {
      digitalWrite(A2, LOW);
    }
    if (ALAM2 == 1) {
      digitalWrite(A3, LOW);
    }
    if (ALAM3 == 1) {
      //digitalWrite(A4, LOW);
    }
    if (ALAM4 == 1) {
      //digitalWrite(A5, LOW);
    }
  } else {
    if (loopCount > loopALAM / 2) {
      ALAM1 = 0; ALAM2 = 0; ALAM3 = 0; ALAM4 = 0;
      digitalWrite(A3, HIGH);
      //digitalWrite(A4, HIGH);
      //digitalWrite(A5, HIGH);
    }
  }
  if (loopS1Count > 0) {
    loopS1Count--;
    digitalWrite(25, LOW);
  } else {
    loopS1Count = 0;
    digitalWrite(25, HIGH); //Fujiko off
  }
  if (loopCount > 0) {
    loopCount--;
  }
}
