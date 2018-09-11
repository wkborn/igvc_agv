/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

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

void setup() {
  right_servo.attach(11);  // attaches the servo on pin 10&12 to the servo object
  left_servo.attach(10);
  halt();
  delay(1000);
}

void loop() {
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
}


