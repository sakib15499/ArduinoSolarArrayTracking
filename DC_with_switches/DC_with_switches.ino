
#include <Adafruit_MotorShield.h>
#include <ezButton.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *DCmotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

ezButton limS1(11);  // create ezButton object that attach to pin 11;
ezButton limS2(12);  // create ezButton object that attach to pin 12;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  DCmotor->setSpeed(0);

  limS1.setDebounceTime(50); // set debounce time to 50 milliseconds
  limS2.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  limS1.loop(); // MUST call the loop() function first
  limS2.loop(); // MUST call the loop() function first
  
  if(limS2.isPressed())
    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

  if(limS2.isReleased())
    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");
    DCmotor->run(FORWARD);

  int state = limS2.getState();
  if(state == LOW){
    Serial.println("The limit switch: UNTOUCHED");
    DCmotor->setSpeed(150);
    DCmotor->run(FORWARD);
    delay(100);
    DCmotor->setSpeed(0);
  }
  else {
    Serial.println("The limit switch: TOUCHED");
    DCmotor->setSpeed(0);
  }
    
       
}
