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

//******************DRIVE***********************//
#include <Servo.h>

Servo right_servo;  // create servo object to control a servo
Servo left_servo;
// twelve servo objects can be created on most boards

void forward();
void reverse();
void left();
void right();
void halt();

int pos = 0;    // variable to store the servo position

//*****************DRIVE*********************//

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

const int mpingPin = 7;
const int lpingPin = 8;
const int rpingPin = 9;

//*****************PING*********************//

void setup() {
  right_servo.attach(11);  // attaches the servo on pin 10&12 to the servo object
  left_servo.attach(10);
  halt();
  delay(1000);
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
  pinMode(lpingPin, OUTPUT);
  digitalWrite(lpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(lpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(lpingPin, LOW);
  pinMode(lpingPin, OUTPUT);
  digitalWrite(rpingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rpingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(rpingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(mpingPin, INPUT);
  mduration = pulseIn(mpingPin, HIGH);
  pinMode(lpingPin, INPUT);
  lduration = pulseIn(lpingPin, HIGH);
  pinMode(rpingPin, INPUT);
  rduration = pulseIn(rpingPin, HIGH);

  // convert the time into a distance
  minches = microsecondsToInches(mduration);
  mcm = microsecondsToCentimeters(mduration);
  linches = microsecondsToInches(lduration);
  lcm = microsecondsToCentimeters(lduration);
  rinches = microsecondsToInches(rduration);
  rcm = microsecondsToCentimeters(rduration);
  

 // Serial.print("Middle distance: ");
 // Serial.print(minches);
 // Serial.print("in, ");
 // Serial.print(mcm);
 // Serial.print("cm");
 // Serial.println();
 // Serial.print("Left distance: ");
 // Serial.print(linches);
 // Serial.print("in, ");
 // Serial.print(lcm);
 // Serial.print("cm");
 // Serial.println();
 // Serial.print("Right distance: ");
 // Serial.print(rinches);
 // Serial.print("in, ");
 // Serial.print(rcm);
 // Serial.print("cm");
 // Serial.println();

  delay(100);

//********************PING***************************//

//*****************IR SENSOR******************//

  lval = analogRead(lsensorpin);       // reads the value of the sharp sensor
  rval = analogRead(rsensorpin);

//*****************IR SENSOR******************//

//*******************PHOTODETECTOR******************//

roomlightvalue = (analogRead(roomlightPin)); //Write the value of the photoresistor to the room light variable.
light value = (analogRead(lightPin)); //Write the value of the photoresistor to the light variable 

//Serial.println("Room Light Value: ");
//Serial.print(analogRead(roomlightPin)); //Write the value of the photoresistor to the serial monitor.
//Serial.println("Light Value: ");
//Serial.print(analogRead(lightPin)); //Write the value of the photoresistor to the serial monitor.

//*******************PHOTODETECTOR******************//

//********************DRIVE**************************//
  forward();
  delay(4600);
  while(1)
  {
    halt();
    delay(10);
  }
}

void forward() {
    right_servo.write(100);
    delay(400);
    left_servo.write(97);                      
}

void reverse() {
    right_servo.write(80);// tell servo to go to position in variable 'pos'
    delay(10);
    left_servo.write(80);                      // waits 15ms for the servo to reach the position
    delay(10);
}

void left() {
    right_servo.write(100);// tell servo to go to position in variable 'pos'
    delay(10);
    left_servo.write(80);                      // waits 15ms for the servo to reach the position
    delay(10);
}

void right() {
    right_servo.write(80);// tell servo to go to position in variable 'pos'
    delay(10);
    left_servo.write(100);                      // waits 15ms for the servo to reach the position
    delay(10);
}

void halt() {
    right_servo.write(0);// tell servo to go to position in variable 'pos'
    delay(10);
    left_servo.write(91);                      // waits 15ms for the servo to reach the position
    delay(10);

//**********************DRIVE***************************//

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


