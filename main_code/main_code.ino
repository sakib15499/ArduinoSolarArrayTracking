
#include <Adafruit_MotorShield.h>
#include <ezButton.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 32 steps per revolution (11.25 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *stepper = AFMS.getStepper(32, 2);

// Select port M1 for DC motor
Adafruit_DCMotor *DCmotor = AFMS.getMotor(1);

// the top two will read from one analog input
int commonpinTOP = 0; // common analog pin used for top is 0

int pr_TR = 2;  // top right photocell is connected to digital pin 2
int tr;     

int pr_TL = 4;  // top left photocell is connected to digital pin 4
int tl;     

// the bottom two will read from one analog input
int commonpinBOTTOM = 2; // common analog pin used for bottom is 2

int pr_BR = 6;  // bottom right photocell is connected to digital pin 6
int br;     

int pr_BL = 8;  // bottom left photocell is connected to digital pin 8
int bl;     

ezButton limS1(11);  // create ezButton object that attach to pin 11;
ezButton limS2(12);  // create ezButton object that attach to pin 12;

// initialize potVal variable, where we will map potentiometer readings 
// farthest from the wood is the analog pin
int potVal = 0;

void setup() {
  Serial.begin(9600);     // set up Serial library at 9600 bps
  
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // initialize the digital pins
  pinMode(pr_TR, OUTPUT);
  pinMode(pr_TL, OUTPUT);
  pinMode(pr_BR, OUTPUT);
  pinMode(pr_BL, OUTPUT);

  // set the stepper speed
  stepper->setSpeed(10);  // 10 rpm
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  DCmotor->setSpeed(0);

  limS1.setDebounceTime(50); // set debounce time to 50 milliseconds
  limS2.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  digitalWrite(pr_TR, HIGH);
  digitalWrite(pr_TL, LOW);
  digitalWrite(pr_BR, HIGH);
  digitalWrite(pr_BL, LOW);
  
  tr = analogRead(commonpinTOP);
  br = analogRead(commonpinBOTTOM);
  
  Serial.print("Photocell TR: ");
  Serial.print("\t");
  Serial.print(tr);
  Serial.println();
  
  Serial.print("Photocell BR: ");
  Serial.print("\t");
  Serial.print(br);
  Serial.println();
  
  delay(100);
  
  digitalWrite(pr_TR, LOW);
  digitalWrite(pr_TL, LOW);
  digitalWrite(pr_BR, LOW);
  digitalWrite(pr_BL, LOW);
  
  delay(100);
  
  digitalWrite(pr_TR, LOW);
  digitalWrite(pr_TL, HIGH);
  digitalWrite(pr_BR, LOW);
  digitalWrite(pr_BL, HIGH);

  tl = analogRead(commonpinTOP);
  bl = analogRead(commonpinBOTTOM);
 
  
  Serial.print("Photocell TL: ");
  Serial.print("\t");
  Serial.print(tl);
  Serial.println();

  Serial.print("Photocell BL: ");
  Serial.print("\t");
  Serial.print(bl);
  Serial.println();
  
  delay(100);

  potVal = map(analogRead(A3),0,1024,0,500);
  Serial.print(potVal);

  int tol = 50; // tolerance for reading, may need to play with flashlight and adjust this

  int avg_t = (tl + tr) / 2; // average value top
  int avg_b = (bl + br) / 2; // average value bottom
  int avg_l = (tl + bl) / 2; // average value left
  int avg_r = (tr + br) / 2; // average value right

  int diff_vert = avg_t - avg_b;  // check the difference of up and down
  int diff_horiz = avg_l - avg_r; // check the difference of left and right

  // the potentiometer decides the allowable range of motion of the stepper motor
  if ((potVal > 100) && (potVal < 500)) {
    // check if the difference is in the tolerance else change vertical angle
    if (-1 * tol > diff_vert || diff_vert > tol) {
      if (avg_t > avg_b) {
        stepper->step(50, BACKWARD, SINGLE);
      }
      
      else if (avg_t < avg_b) {
        stepper->step(50, FORWARD, SINGLE);
  
      }
    } 

  // check if the difference is in the tolerance else change horizontal angle
  DCmotor->setSpeed(0);
  int switch1 = limS2.getState();
  int switch2 = limS2.getState();

  while((switch1 == LOW) && (switch2 == LOW)){
    if (-1 * tol > diff_horiz || diff_horiz > tol) {
      if (avg_l > avg_r) {
        // write another if BEFORE movemement (here) that says "as long as button is not pressed you can move this way, else, switch direction"
         DCmotor->setSpeed(150);
         DCmotor->run(FORWARD);
         delay(100);
         DCmotor->setSpeed(0);
      }
      
      else if (avg_l < avg_r) {
        // write another if BEFORE movemement (here) that says "as long as button is not pressed you can move this way, else, switch direction"
        DCmotor->setSpeed(150);
        DCmotor->run(BACKWARD);
        delay(100);
        DCmotor->setSpeed(0);
      }
      
      else if (avg_l = avg_r) {
        // do not move (I think that is what RELEASE is)
        DCmotor->setSpeed(0);
      }
    }
  }
      
  DCmotor->setSpeed(0);
  }
  delay(10);
  
}
