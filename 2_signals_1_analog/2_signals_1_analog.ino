int commonpin = 0; // common analog pin used is 0
int commonpinReading;

int PCPin2 = 2;  // one photocell is connected to digital pin 2
int PCReading2;     

int PCPin6 = 6;  // another photocell is connected to digital pin 6
int PCReading6;     

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);   
pinMode(PCPin2, OUTPUT);
pinMode(PCPin6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(PCPin2, HIGH);
digitalWrite(PCPin6, LOW);

PCReading2 = analogRead(commonpin);

Serial.print("Photocell 2: ");
Serial.print("\t");
Serial.print(PCReading2);
Serial.println();

delay(100);

digitalWrite(PCPin2, LOW);
digitalWrite(PCPin6, LOW);

delay(100);

digitalWrite(PCPin2, LOW);
digitalWrite(PCPin6, HIGH);


PCReading6 = analogRead(commonpin);

Serial.print("Photocell 6: ");
Serial.print("\t");
Serial.print(PCReading6);
Serial.println();

delay(100);
}
