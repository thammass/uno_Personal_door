/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
char iMENU=0;
int Aout1=0;
int Aout2=1;
int Aout3=2;
int Aout4=3;
int R=4;
char * buff;
char string[10];
char CH;


void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  printMENU(0);
  pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
 // buff = Serial.read();
 // buff = Serial.read();
 // buff = Serial.read();
}

void printMENU(int i){
  // out
  analogWrite(3, Aout1);
  analogWrite(5, Aout2);
  iMENU=i;
  switch(i){
     case 0:
       Serial.println("Program monitor V1.0 \r\n");
       Serial.write("\r\n\r\n---- Main -----\r\n");
       Serial.write("1. Aout \r\n");
       Serial.write("2. R out\r\n");

       break;
     case 1:
      Serial.write("\r\n\r\n-----config 1-----\r\n");
      Serial.write("1. Aout1 out [ "); Serial.print(Aout1); Serial.write(" ]\r\n");
      Serial.write("2. Aout2 out [ "); Serial.print(Aout2); Serial.write(" ]\r\n");
      Serial.write("3. Aout3 out [ "); Serial.print(Aout3); Serial.write(" ]\r\n");
      Serial.write("4. Aout4 out [ "); Serial.print(Aout4); Serial.write(" ]\r\n");
      Serial.write("------------------------\r\n");
      Serial.write("Q. Quit \r\n\r\n");          
      break;
    case 2: 
        Serial.write("\r\n\r\n-----config 2-----\r\n");
        Serial.write("1. R [ "); Serial.print(R); Serial.write(" ]\r\n\r\n");
        Serial.write("------------------------\r\n");
        Serial.write("Q. Quit \r\n\r\n");
      break;
    }
  
}
//------------------------------------------------------------------------
char* GetSerialString(){
   int index = 0;
   char byteBuffer;
   int EXIT=1;
   while(EXIT){
      if(Serial.available()>0){
         byteBuffer = Serial.read();
        // Serial.print(byteBuffer, DEC);
         if(byteBuffer==13){
             string[index] ='\0';
             EXIT=0;
         }
         string[index]=byteBuffer;
         index++;
      }
   }
   return string;
  }
//------------------------------------------------------------------------

void loop() // run over and over
{

//   char* serialInput = GetSerialString();
//   interval = atoi(serialInput);
//   Serial.print("LED interval is now ");
//   Serial.println(interval,DEC);

  
  if (Serial.available() > 0){
        switch(iMENU){
          //---------------------------------------
          case 0:  //menu 0
             switch(Serial.read()){
              case '1':
                 printMENU(1);
                 break;
              case '2':
                printMENU(2); 
                break;
             }
           break;
          //----------------------------------------
          case 1:   // menu 1
             switch(Serial.read()){
              case '1':
                   Serial.write("input Aout1 [0-100]: ");
                   buff=GetSerialString();
                   Aout1=atoi(buff);
                    printMENU(1);
                   break;
              case '2':
                   Serial.write("input Aout2 [0-100]: ");
                   buff=GetSerialString();
                   Aout2=atoi(buff);
                    printMENU(1);
                   break;
              case 'Q':
              case 'q':
                iMENU=0;
                printMENU(0);
                break;
             }
            
           break;
          //----------------------------------------
          case 2:   // menu 2 
             switch(Serial.read()){
              case '1':
                  Serial.write("input R [50-100]: ");
                    buff=GetSerialString();
                   R=atoi(buff);
                   printMENU(2);
                break;
              
              case 'Q':
              case 'q':
                iMENU=0;
                printMENU(0);
                break;
             }
           break;
        }//swiitch(iMENU)
  }//if (Serial.available() > 0)
}
