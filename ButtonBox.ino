#include <Joystick.h>

/* 
 * -------------------------------------------------------------------------
 * Arduino Button Box
 * -------------------------------------------------------------------------
 */

// Array of pins for the columns
int cPins[] = {3, 4, 5};
int cPinsNo = 3;

// Array of pins for the rows
int rPins[] = {11, 12, 13};
int rPinsNo = 3;

// Array for the last known switch states [cPinsNo][rPinsNo]
int colPrev[3][3] = {0};

// Mapping of Buttons to Joystick buttions IDs
uint8_t buttonCodes[3][3] = {
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8}
};

uint8_t HIDId = 0x15;
uint8_t numButtons = 9;
Joystick_ Joystick (HIDId, JOYSTICK_TYPE_JOYSTICK, numButtons, false, false, false, false, false, false, false, false, false, false, false);

void setup()
{
  //Start Serial
  Serial.begin(9600);
  Serial.println("Multiplexed Buttons Test");

  //Set the Column Pin Mode
  for(int cPin = 0; cPin < cPinsNo; cPin++)
  {
    pinMode(cPins[cPin], OUTPUT);
    digitalWrite(cPins[cPin], HIGH);
  }

  //Set the Row Pin Mode
  for(int rPin = 0; rPin < rPinsNo; rPin++)
  {
    pinMode(rPins[rPin], INPUT);
    digitalWrite(rPins[rPin], HIGH);
  }

  // Initialize Joystick Library
  Joystick.begin();
} 

void loop()
{
  // Loop through the columns
  for(int cPin = 0; cPin < cPinsNo; cPin++)
  {
    digitalWrite(cPins[cPin], LOW);

    // Loop through the rows
    for(int rPin = 0; rPin < rPinsNo; rPin++)
    {
      //Check if each switch is pressed
      if(digitalRead(rPins[rPin]) == LOW)
      {
        // Check to see if the state has changed since last time
        if(colPrev[cPin][rPin] == 0)
        {
          // Do action here, switch is on
          Serial.print(cPins[cPin]);
          Serial.print(", ");
          Serial.print(rPins[rPin]);
          Serial.println(" ON");

          Joystick.setButton(buttonCodes[cPin][rPin], true);
          // Keyboard.press(buttonCodes[cPin][rPin]);
          delay(150);
          // Keyboard.release(buttonCodes[cPin][rPin]); 
          Joystick.setButton(buttonCodes[cPin][rPin], false);

          // Update last known state of this switch
          colPrev[cPin][rPin] = 1;
        }
      } 
      else {

        // Check to see if the state has changed since last time
        if(colPrev[cPin][rPin] == 1)
        {
          // Do action here, switch is off
          Serial.print(cPins[cPin]);
          Serial.print(", ");
          Serial.print(rPins[rPin]);
          Serial.println(" OFF");

          // Update last known state of this switch
          colPrev[cPin][rPin] = 0;
        }
      }
    }
    digitalWrite(cPins[cPin], HIGH);
  }
}
