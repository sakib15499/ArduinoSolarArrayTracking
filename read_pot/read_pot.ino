


// farthest from the wood is the analog pin
int potVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // set up Serial library at 9600 bps
 

}

void loop() {
  // put your main code here, to run repeatedly:
   potVal = map(analogRead(A3),0,1024,0,1000);
   Serial.println(potVal);
}
