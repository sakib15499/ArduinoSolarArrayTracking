#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 32 steps per revolution (11.25 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *stepper = AFMS.getStepper(32, 2);


// farthest from the wood is the analog pin
// initialize value from the potentiometer
int potVal = 0;


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper with pot!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  stepper->setSpeed(10);  // 10 rpm
   
} 

void loop() {
  
  potVal = map(analogRead(A3),0,1024,0,1000);
  Serial.println(potVal);

  // forward rotates away 
  while (potVal < 520 && potVal > 0){
    stepper->step(100, FORWARD, SINGLE);
    potVal = map(analogRead(A3),0,1024,0,1000);
    Serial.println(potVal);
  }
 

  potVal = map(analogRead(A3),0,1024,0,1000);
  while (potVal > 520 && potVal < 995){
    stepper->step(100, BACKWARD, SINGLE);
    potVal = map(analogRead(A3),0,1024,0,1000);
    Serial.println(potVal);
  }

}
