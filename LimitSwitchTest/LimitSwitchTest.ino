


// set pin for switch
// pin 6 is ok too
int limSwitch = 0;

const int limSwitchPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(limSwitchPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   limSwitch = digitalRead(limSwitchPin);

  Serial.print("\t");
  Serial.print("limSwitch=");
  Serial.print("\t");
  Serial.println(limSwitch);
}
