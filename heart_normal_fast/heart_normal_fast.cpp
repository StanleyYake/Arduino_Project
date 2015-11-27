#include <TimerOne.h>
#include "animation_normal_fast_heart.h"

//Pin connected to ST_CP of 74HC595(Pin 12)
int latchPin = 8;
//Pin connected to SH_CP of 74HC595(Pin 11)
int clockPin = 12;
////Pin connected to DS of 74HC595(Pin 14)
int dataPin = 11;

const int ultra_redPin = 3; 

int ledState = HIGH;         // the current state of the output pin
int ledState2 = HIGH;

int buttonState;             // the current reading from the input pin 
int ultra_redState;

int lastButtonState = LOW;   // the previous reading from the input pin
int lastultra_redState = LOW;

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 45;    // the debounce time; increase if the output flickers

// A number indicating when to advance to the next frame
unsigned long nextImage = 0;
// A counter to know what frame we're showing
int animationIndex = 0;

int animationIndex_l = 4;

int animationIndex_2 = 8;

int animationIndex_3 = 12;
// 8x8 Point temporary array
byte brightnesses[64];
// Matrix image frame for 8x8 LED
int M[8];

bool Scene1_flag = true;
bool Scene2_flag = false;

//------------------------------------------------------------------------
void  init_Interrupter1()
{
  Timer1.initialize(50000);
  Timer1.attachInterrupt(Interrupter1);  // every 50ms
  //Timer1.detachInterrupt();
}

void Interrupter1()
{
  //
  //---------------------------------------------
  int reading1 = digitalRead(ultra_redPin);

  if (reading1 != lastultra_redState) {

    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading1 != ultra_redState) 
    {
        ultra_redState = reading1;
  
        if (ultra_redState == HIGH) 
        {
          ledState2 = !ledState2;
        }
    }
  }
  lastultra_redState = reading1;
}


void setup() 
{
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
  
  pinMode(ultra_redPin, INPUT);

//  Serial.begin(9600);
   init_Interrupter1();  
}

void loop() 
{
  if (ledState2)
  {
       if(animationIndex >= 4) // Frame0, 1, 2, 3.
      {
        //restart animation index
        animationIndex = 0;
      }
      else
      {
          //load Delay time for Image
          nextImage = animationDelays[animationIndex];

          //load image(converted)
          for(int i=0; i<64; i++) 
          {
             brightnesses[i] = (animation[animationIndex][i/4] >> (i%4*2)) & B00000001; 
             M[i/8] |= (brightnesses[i] << (i%8)) ;
          }


        //Update Image
        screenUpdate(nextImage);
        animationIndex ++;
    
        //clear M[]
        for(int i=0; i<(8); ++i) 
        {
          M[i]=0;
        }
      }
    
  }else // switch another state.
  {
// display latter two frame,
  if(animationIndex_l >= 8) // Frame 4, 5, 6, 7
  {
    //restart animation index
    animationIndex_l = 4;
  }
  else
    {
    //load Delay time for Image
    nextImage = animationDelays[animationIndex_l];

    //load image(converted)
      for(int i=0; i<64; i++) 
      {
        brightnesses[i] = (animation[animationIndex_l][i/4] >> (i%4*2)) & B00000001; 
        M[i/8] |= (brightnesses[i] << (i%8)) ;
      }


    //Update Image
    screenUpdate(nextImage);
    animationIndex_l ++;
//
    //clear M[]
    for(int i=0; i<(8); ++i) {
      M[i]=0;
    }

  }// End for second pattern.
  
} // End if Scene1_flag


}// End loop.


void screenUpdate(unsigned long frametime) 
{ // function to display image

    unsigned long startime=millis();
  while(millis()-startime<frametime)
  {
    byte row = B10000000; // row 1  
    for (byte k = 0; k < 8; k++) 
    {
      digitalWrite(latchPin, LOW); // open latch ready to receive data
      shiftIt(~row); // row binary number
      shiftIt(M[k]); // LED array (inverted) 

      // Close the latch, sending the data in the registers out to the matrix
      digitalWrite(latchPin, HIGH);
      row = row>> 1; // bitshift right
    }
  } 
}



void shiftIt(byte dataOut) {
  // Shift out 8 bits LSB first, on rising edge of clock
  boolean pinState;

  //clear shift register read for sending data
  digitalWrite(dataPin, LOW);
  // for each bit in dataOut send out a bit
//  for (int i=0; i<8; i++) {
  for (int i=7; i>=0; i--)  {
    //set clockPin to LOW prior to sending bit
    digitalWrite(clockPin, LOW);
    // if the value of DataOut and (logical AND) a bitmask
    // are true, set pinState to 1 (HIGH)
    if ( dataOut & (1<<i) ) {
      pinState = HIGH;
    }
    else {
      pinState = LOW;
    }
    //sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(dataPin, pinState);
    //send bit out on rising edge of clock
    digitalWrite(clockPin, HIGH);
    digitalWrite(dataPin, LOW);
  }
  digitalWrite(clockPin, LOW); //stop shifting
}

