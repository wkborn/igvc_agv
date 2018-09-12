/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

//STATE VARIABLES
//PING: rcm, lcm, mcm
//IR SENSOR: lval, rval
//PHOTO DETECTOR: lightvalue, roomlightvalue

//*****************IR SENSOR******************//

int lsensorpin = 0;                 // analog pin used to connect the sharp sensor
int lval = 0;                 // variable to store the values from sensor(initially zero)
int rsensorpin = 0;
int rval = 0;

//*****************IR SENSOR******************//

//*******************PHOTODETECTOR******************//

int roomlightPin = 0;  //define a pin for Photo resistor
int lightPin = 1;  //define a pin for Photo Detector
int roomlightvalue = 0; //creates a variable to hold the current light value of the room
int lightvalue = 0; //creates a variable to hold the current light value of the room

//*******************PHOTODETECTOR******************//

//*****************PING**********************//

const int mpingPin = 0;
const int lpingPin = 3;
const int rpingPin = 2;

//*****************PING*********************//

void setup() {
  
  Serial.begin(9600);
  
}

void loop() {

//********************PING***************************//

  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long mduration, minches, mcm;
  long lduration, linches, lcm;
  long rduration, rinches, rcm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(mpingPin, OUTPUT);
  digitalWrite(mpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(mpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(mpingPin, LOW);
  pinMode(mpingPin, INPUT);
  mduration = pulseIn(mpingPin, HIGH);
  minches = microsecondsToInches(mduration);
  mcm = microsecondsToCentimeters(mduration);
  
  pinMode(lpingPin, OUTPUT);
  digitalWrite(lpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(lpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(lpingPin, LOW);
  pinMode(lpingPin, INPUT);
  lduration = pulseIn(lpingPin, HIGH);
  linches = microsecondsToInches(lduration);
  lcm = microsecondsToCentimeters(lduration);

  delay(100);
  
  pinMode(rpingPin, OUTPUT);
  digitalWrite(rpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(rpingPin, LOW);
  pinMode(rpingPin, INPUT);
  rduration = pulseIn(rpingPin, HIGH);
  rinches = microsecondsToInches(rduration);
  rcm = microsecondsToCentimeters(rduration);  

  delay(100);

  Serial.print("Middle distance: ");
  Serial.print(minches);
  Serial.print("in, ");
  Serial.print(mcm);
  Serial.println("cm");
  Serial.print("Left distance: ");
  Serial.print(linches);
  Serial.print("in, ");
  Serial.print(lcm);
  Serial.println("cm");
  Serial.print("Right distance: ");
  Serial.print(rinches);
  Serial.print("in, ");
  Serial.print(rcm);
  Serial.println("cm");

  delay(100);

//********************PING***************************//

//*****************IR SENSOR******************//

  lval = analogRead(lsensorpin);       // reads the value of the sharp sensor
  rval = analogRead(rsensorpin);

  Serial.print("Left IR Value: ");
  Serial.println(lval);
  Serial.print("Right IR Value: ");
  Serial.println(rval);

//*****************IR SENSOR******************//

//*******************PHOTODETECTOR******************//

  roomlightvalue = (analogRead(roomlightPin)); //Write the value of the photoresistor to the room light variable.
  lightvalue = (analogRead(lightPin)); //Write the value of the photoresistor to the light variable 

  Serial.print("Room Light Value: ");
  Serial.println(analogRead(roomlightPin)); //Write the value of the photoresistor to the serial monitor.
  Serial.print("Light Value: ");
  Serial.println(analogRead(lightPin)); //Write the value of the photoresistor to the serial monitor.

//*******************PHOTODETECTOR******************//

  delay(100);

}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}


