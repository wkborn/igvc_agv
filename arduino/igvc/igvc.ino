
#include <Servo.h>

Servo right_servo;  // create servo object to control a servo
Servo left_servo;

void forward();
void reverse();
void left();
void right();
void halt();
void sensors();

uint8_t obstacle_front;
uint8_t obstacle_left;
uint8_t obstacle_right;
uint8_t inv_wall_left;
uint8_t inv_wall_right;
uint8_t in_room;
uint8_t state;

void setup() {
  right_servo.attach(11);  // attaches the servo on pin 10&12 to the servo object
  left_servo.attach(10);
  halt();
  delay(1000);
}

void loop() {

  sensors();

  state_machine();


  delay(1);
}

void forward() {
    right_servo.write(100);
    delay(400);
    left_servo.write(97);
}

void reverse() {
    right_servo.write(80);
    delay(10);
    left_servo.write(80);
    delay(10);
}

void left() {
    right_servo.write(100);
    delay(10);
    left_servo.write(80);
    delay(10);
}

void right() {
    right_servo.write(80);
    delay(10);
    left_servo.write(100);
    delay(10);
}

void halt() {
    right_servo.write(0);
    delay(10);
    left_servo.write(91);
    delay(10);

}


void sensors(){

}

void state_machine(){
  state = obstacle_front | obstacle_left | obstacle_right | inv_wall_left | inv_wall_right | in_room;





  if(state >= 0x20)

    state = 0x20;



  switch (state) {



    case 0x00:



    break;



    case 0x01:



    break;



    case 0x02:



    break;



    case 0x03:



    break;



    case 0x04:



    break;



    case 0x05:



    break;



    case 0x06:



    break;



    case 0x07:



    break;



    case 0x08:



    break;



    case 0x09:



    break;



    case 0x0A:



    break;



    case 0x0B:



    break;



    case 0x0C:



    break;



    case 0x0D:



    break;



    case 0x0E:



    break;



    case 0x0F:



    break;



    case 0x10:



    break;



    case 0x11:



    break;



    case 0x12:



    break;



    case 0x13:



    break;



    case 0x14:



    break;



    case 0x15:



    break;



    case 0x16:



    break;



    case 0x17:



    break;



    case 0x18:



    break;



    case 0x19:



    break;



    case 0x1A:



    break;



    case 0x1B:



    break;



    case 0x1C:



    break;



    case 0x1D:



    break;



    case 0x1E:



    break;



    case 0x1F:



    break;



    case 0x20:



    break;

  }
}
