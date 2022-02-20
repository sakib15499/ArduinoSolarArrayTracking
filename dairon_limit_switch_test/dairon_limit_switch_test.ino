/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-limit-switch
 */

#include <ezButton.h>

ezButton limitSwitch(2);  // create ezButton object that attach to pin 2;

void setup() {
  Serial.begin(9600);
  limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  limitSwitch.loop(); // MUST call the loop() function first

// DO NOTE THAT I WIRED IT 'BACKWARDS' AND SO MY LABELS MATCH OUR BUTTON EVEN
// IF THE FUNCTION NAMES ARE OPPOSITE
  if(limitSwitch.isPressed())
    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");

  if(limitSwitch.isReleased())
    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

  int state = limitSwitch.getState();
  if(state == HIGH)
    Serial.println("The limit switch: TOUCHED");
  else
    Serial.println("The limit switch: UNTOUCHED");

}
