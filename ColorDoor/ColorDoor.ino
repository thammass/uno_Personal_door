/*-----------------------------------------
Project Personal Door - LED Unit ( v1.0)
 ----------------------------------------
Develop by Mr.Thammasak Sa-nguansatwaja
Test date: 2015/07/30
Windows: Windows8 64Bit Professional

-----------------------------------------
Software Tools:
-----------------------------------------
- Arduino 1.0.6
- library   Adafruit_GFX.h , Colorduino_GFX.h

-----------------------------------------
Embedded Device
-----------------------------------------
MPU:	UNO 
Board:	UNO
IN:
OUT:
--------------------------------------  */

// Include required libraries
#include <Adafruit_GFX.h>
#include <Colorduino_GFX.h>

// Create new Colorduino instance
ColorduinoPanel Colorduino;

// some vars required for timing
long previousMillis = 0;
long interval = 50;
int DIR;
int ANA;

int sensorPin = A15; 

void setup() {
  // Initialize random generator
  randomSeed(255);
  DIR=0;
  
  // Set port mode, load data structures and start the timer
  Colorduino.init();
  // Set white balance
  Colorduino.setWhiteBalance(36, 63, 63);
    
}

void loop() {
  int x,y;
  ANA = analogRead(sensorPin);
  // some timing stuff
  if(ANA>500){DIR=1;}else{DIR=0;}
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    
    // draw pixel on the back-buffer
    GFX_Color_t G = Colorduino.color(0, 255, 0);
    GFX_Color_t B = Colorduino.color(0,0,0);
    
    if(DIR==0){ // pass
        for(y=0;y<8;y++)
          for(x=0;x<8;x++){
            // create new color
            GFX_Color_t color=B;
            if((y==0) && ( (x==6)) )color=G;
            if((y==1) && ( (x==1)||(x==5)||(x==6)||(x==7)) )color=G;
            if((y==2) && ( (x==0)||(x==1)||(x==4)||(x==5)||(x==6)) )color=G;
            if((y==3) && ( (x==0)||(x==1)||(x==3)||(x==4)||(x==5)) )color=G;
            if((y==4) && ( (x==0)||(x==1)||(x==2)||(x==3)||(x==4)) )color=G;
            if((y==5) && ( (x==0)||(x==1)||(x==2)||(x==3)) )color=G;
            if((y==6) && ( (x!=7) ))color=G;
            if((y==7) && ( (x < 6)))color=G;
            
            
            Colorduino.drawPixel(x, y, color);
            Colorduino.swapBuffers(true);  
        }
        delay(300); 
        for(y=0;y<8;y++)
          for(x=0;x<8;x++){
            // create new color
            GFX_Color_t color=B;            
            //if((y==0) && ( (x==6)||(x==7)) )color=G;
            if((y==0) && ( (x==2)||(x==6)||(x==7)) )color=G;
            if((y==1) && ( (x==2)||(x==1)||(x==7)||(x==5)||(x==6)) )color=G;
            if((y==2) && ( (x==2)||(x==1)||(x==6)||(x==4)||(x==5)) )color=G;
            if((y==3) && ( (x==2)||(x==1)||(x==5)||(x==3)||(x==4)) )color=G;
            if((y==4) && ( (x==2)||(x==1)||(x==4)||(x==3)) )color=G;
            if((y==5) && ( (x!=0) ))color=G;
            if((y==6) && ( (x==1)||(x==2)||(x==3)||(x==4)||(x==5)||(x==6)) )color=G;
            Colorduino.drawPixel(x, y, color);
            Colorduino.swapBuffers(true);    
        }
        delay(1200);
    }else{  // dot entry
          GFX_Color_t R = Colorduino.color(255, 0, 0);
          for(y=0;y<8;y++)
          for(x=0;x<8;x++){
            // create new color
            GFX_Color_t color=B;
            if((y==0) && ( (x==0)||(x==1)||(x==6)||(x==7) ) )color=R;
            if((y==1) && ( (x==0)||(x==1)||(x==2)||(x==5)||(x==6)||(x==7)) )color=R;
            if((y==2) && ( (x==1)||(x==2)||(x==3)||(x==4)||(x==5)||(x==6)) )color=R;
            if((y==3) && ( (x==2)||(x==3)||(x==4)||(x==5)) )color=R;
            if((y==4) && ( (x==2)||(x==3)||(x==4)||(x==5)) )color=R;
            if((y==5) && ( (x==1)||(x==2)||(x==3)||(x==4)||(x==5)||(x==6)) )color=R;
            if((y==6) && ( (x==0)||(x==1)||(x==2)||(x==5)||(x==6)||(x==7)) )color=R;
            if((y==7) && ( (x==0)||(x==1)||(x==6)||(x==7) ) )color=R;
            
            Colorduino.drawPixel(x, y, color);
            Colorduino.swapBuffers(true);  
        }       
        delay(400);
        for(y=0;y<8;y++)
          for(x=0;x<8;x++){
            // create new color

            GFX_Color_t color=B;

            if((y==0) && ( (x==0)||(x==1)||(x==6)||(x==7) ) )color=R;
            if((y==1) && ( (x==0)||(x==1)||(x==2)||(x==5)||(x==6)||(x==7)) )color=R;
            if((y==2) && ( (x==1)||(x==2)||(x==3)||(x==4)||(x==5)||(x==6)) )color=R;
            if((y==3) && ( (x==2)||(x==3)||(x==4)||(x==5)) )color=R;
            if((y==4) && ( (x==2)||(x==3)||(x==4)||(x==5)) )color=R;
            if((y==5) && ( (x==1)||(x==2)||(x==3)||(x==4)||(x==5)||(x==6)) )color=R;
            if((y==6) && ( (x==0)||(x==1)||(x==2)||(x==5)||(x==6)||(x==7)) )color=R;
            if((y==7) && ( (x==0)||(x==1)||(x==6)||(x==7) ) )color=R;

            Colorduino.drawPixel(x, y, color);
            Colorduino.swapBuffers(true);    
        }
        delay(800);
      
    }
  }
}
