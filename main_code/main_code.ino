
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 32 steps per revolution (11.25 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *stepper = AFMS.getStepper(32, 2);

// Select port M1 for DC motor
Adafruit_DCMotor *DCmotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

// LDR pin connections
int pr_TR = 0; // LDR top right
int pr_TL = 1; // LDR top left
int pr_BR = 2; // LDR bottom right
int pr_BL = 3; // LDR bottom left


void setup() {
  Serial.begin(9600);     // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper with photocell!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  stepper->setSpeed(10);  // 10 rpm
}

void loop() {

  int tr = analogRead(pr_TR); // top right
  int tl = analogRead(pr_TL); // top left
  int br = analogRead(pr_BR); // bottom right
  int bl = analogRead(pr_BL); // bottom left

  int tol = 50; // tolerance for reading, may need to play with flashlight and adjust this

  int avg_t = (tl + tr) / 2; // average value top
  int avg_b = (bl + br) / 2; // average value bottom
  int avg_l = (tl + bl) / 2; // average value left
  int avg_r = (tr + br) / 2; // average value right

  int diff_vert = avg_t - avg_b;  // check the difference of up and down
  int diff_horiz = avg_l - avg_r; // check the difference of left and right

  // check if the difference is in the tolerance else change vertical angle
  // need to add in set amounts of steps, right now it is generic; also need to figure out if forward means up or down
  if (-1 * tol > diff_vert || diff_vert > tol) {
    if (avg_t > avg_b) {
      stepper->step(100, FORWARD, SINGLE);
    }
    
    else if (avg_t < avg_b) {
      stepper->step(100, BACKWARD, SINGLE);

    }
  } 

 // check if the difference is in the tolerance else change horizontal angle
 // need to make sure DC motor does not run continuously, will probably need that release / whatever stop is after every single one
  if (-1 * tol > diff_horiz || diff_horiz > tol) {     
    if (avg_l > avg_r) {
      // write another if BEFORE movemement (here) that says "as long as button is not pressed you can move this way, else, switch direction"
       DCmotor->setSpeed(150);
       DCmotor->run(FORWARD);

    }
    else if (avg_l < avg_r) {
      // write another if BEFORE movemement (here) that says "as long as button is not pressed you can move this way, else, switch direction"
      DCmotor->setSpeed(150);
      DCmotor->run(FORWARD);

    }
    else if (avg_l = avg_r) {
      // do not move (I think that is what RELEASE is)
      DCmotor->run(RELEASE)
    }

  }
  
  delay(0);
  
}
