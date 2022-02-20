#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 32 steps per revolution (11.25 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *stepper = AFMS.getStepper(32, 2);

int Pval = 0;
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

  stepper->setSpeed(10);  // 20 rpm
}

void loop() {

  potVal = map(analogRead(A0),0,1024,0,500);
  if (potVal>Pval)
  stepper->step(100, FORWARD, SINGLE);
  if (potVal<Pval)
  stepper->step(100, BACKWARD, SINGLE);

  Pval = potVal;

Serial.println(Pval); //for debugging
}

//  Serial.println("Single coil steps");
//  myMotor->step(100, FORWARD, SINGLE);
//  myMotor->step(100, BACKWARD, SINGLE);
//
//}
