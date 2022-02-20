/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */
 
int photocellPin0 = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading0;     // the analog reading from the analog resistor divider

int photocellPin1 = 1;     // the cell and 10K pulldown are connected to a1
int photocellReading1;     // the analog reading from the analog resistor divider

int photocellPin2 = 2;     // the cell and 10K pulldown are connected to a2
int photocellReading2;     // the analog reading from the analog resistor divider

int photocellPin3 = 3;     // the cell and 10K pulldown are connected to a3
int photocellReading3;     // the analog reading from the analog resistor divider
 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading0 = analogRead(photocellPin0);  
 
  Serial.print("Analog reading 0= ");
  Serial.print(photocellReading0);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading0 < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading0 < 
00) {
    Serial.println(" - Dim");
  } else if (photocellReading0 < 500) {
    Serial.println(" - Light");
  } else if (photocellReading0 < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(1000);

  photocellReading1 = analogRead(photocellPin1);  

  Serial.print("Analog reading 1= ");
  Serial.print(photocellReading1);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading1 < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading1 < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading1 < 500) {
    Serial.println(" - Light");
  } else if (photocellReading1 < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(1000);

  photocellReading2 = analogRead(photocellPin2);  

  Serial.print("Analog reading 2= ");
  Serial.print(photocellReading2);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading2 < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading2 < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading2 < 500) {
    Serial.println(" - Light");
  } else if (photocellReading2 < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(1000);

  photocellReading3 = analogRead(photocellPin3);  

  Serial.print("Analog reading 3= ");
  Serial.print(photocellReading3);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading3 < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading3 < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading3 < 500) {
    Serial.println(" - Light");
  } else if (photocellReading3 < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(1000);
}
