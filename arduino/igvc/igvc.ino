ir_left_pin#include <Servo.h>

//sensors
//photo
int light_value;
int roomlight_value;
int lightPin = 0;         //Pin assignment
int roomlightPin = 1;     //Pin assignment
//ir
int lval = 0;  //variable to store the values from sensor(initially zero)
int rval = 0;
//servos
int ping_front=0;
int ping_left=0;
int ping_right=0;
//servos
Servo right_servo;  // create servo object to control a servo
Servo left_servo;

void forward();
void reverse();
void left();
void right();
void halt();
void sensors();
void set_flags();

//sensors

int light_sensor_handler();
int ir_left_handler();
int ir_right_handler();

uint8_t obstacle_front;
uint8_t obstacle_left;
uint8_t obstacle_right;
uint8_t inv_wall_left;
uint8_t inv_wall_right;
uint8_t in_room;
uint8_t state;


const int dark = 309;
const int light = 310;
const int ir_left_pin = 13;
const int ir_right_pin = 12; //analog pin used to connect the sharp sensor
const int threshold = 250;  //value when vehicle should can direction
const int ping_right_pin = 2;
const int ping_left_pin = 1;
const int ping_front_pin = 0;
const int ping_front_min=10;
const int ping_left_min=10;
const int ping_right_min=10;

void setup() {
  Serial.begin(9600);

  DDRB=0xFF;
  PORTB=0x00;

  right_servo.attach(11);  // attaches the servo on pin 10&12 to the servo object
  left_servo.attach(10);
  halt();
  delay(1000);
}

void loop() {

  sensors();
  set_flags();

  state_machine();


  delay(1);
}

void set_flags(){
  inv_wall_left = 0x00;
  inv_wall_right = 0x00;
  in_room = 0x00;
  obstacle_front = 0x00;
  obstacle_left = 0x00;
  obstacle_right = 0x00;

  if (light_value <= dark)
    in_room = 0b00100000;   //If robot does not detect light (i.e. room is dark) set flag to 1
  else if (light_value >= light)
    in_room = 0b00000000;  //If the robot detects light, set the flag to 0
  if(lval < threshold)
		inv_wall_left = 0b00010000;
	if(rval < threshold)
		inv_wall_right = 0b00001000;
  if(ping_front < ping_front_min)
		obstacle_front = 0b00000001;
  if(ping_left < ping_left_min)
		obstacle_front = 0b00000010;
  if(ping_right < ping_right_min)
		obstacle_front = 0b00000100;
}



void sensors(){

  light_sensor();
  ir_left_handler();
  ir_right_handler();
  ping_front_handler();
  ping_left_handler();
  ping_right_handler();

}

void state_machine(){
  PORTB=0x00;
  state = obstacle_front | obstacle_left | obstacle_right | inv_wall_left | inv_wall_right | in_room;
  PORTB=state;


  if(state >= 0x20)

    state = 0x20;



  switch (state) {
    case 0x00: //00000000 open path
      forward();
    break;
    case 0x01: // 00000001 obstacle_front
      right();
      delay(100);
    break;
    case 0x02: // 00000010 obstacle_left
      right();
      delay(10);
    break;
    case 0x03: // 00000011 obstacles front and left
      right();
      delay(10);
    break;
    case 0x04: // 00000100 obstacle right
      left();
      delay(10);
    break;
    case 0x05: // 00000101 obstacle right and front
      left();
      delay(10);
    break;
    case 0x06: // 00000110 obstacle left and right
      forward();
      delay(10);
    break;
    case 0x07: // 00000111 obstacle front, left, and right_
      reverse();
      delay(10);
    break;
    case 0x08: // 00001000 inv wall left
      right();
      delay(10);
    break;
    case 0x09: // 00001001 inv wall left and obstacle front
      right();
      delay(10);
    break;
    case 0x0A: // 00001010 inv wall left and obstacle left
      right();
      delay(10);
    break;
    case 0x0B: // 00001011 inv wall left and obstacle left and obstacle front
      reverse();
      delay(10);
    break;
    case 0x0C: // 00001100 inv wall left and obstacle right
      forward();
      delay(10);
    break;
    case 0x0D: // 00001101 inv wall left and obstacle right and obstacle front
      reverse();
      delay(10);
    break;
    case 0x0E: // 00001110 inv wall left and obstacle left and right
      forward();
      delay(10);
    break;
    case 0x0F: // 00001111 inv wall left and obstacle front left and right
      reverse();
      delay(10);
    break;
    case 0x10:// 00010000 inv wall right
      left();
      delay(10);
    break;
    case 0x11: // 00010001 inv wall right and front
      left();
      delay(10);
    break;
    case 0x12: // 00010010 inv wall right and obstacle left
      forward();
      delay(10);
    break;
    case 0x13: // 00010011 inv wall right and obstacles left and front
      reverse();
      delay(10);
    break;
    case 0x14: // 00010100 inv wall right and obstacle right
      left();
      delay(10);
    break;
    case 0x15: // 00010101 inv wall right and obstacle front and right
      left();
      delay(10);
    break;
    case 0x16: // 00010110 inv wall right and obstacle left and right
      forward();
      delay(10);
    break;
    case 0x17: // 00010111 inv wall right and obstacle front left and right
      reverse();
      delay(10);
    break;
    case 0x18: //00011000 inv wall right and inv_wall_left
      forward();
      delay(10);
    break;
    case 0x19: // 00011001 inv wall right and left and obstacle front
      reverse();
      delay(10);
    break;
    case 0x1A: // 00011010 inv wall right and left and obstacle left
      forward();
      delay(10);
    break;
    case 0x1B: //  00011011 inv wall right and left and obstacle front and left
      reverse();
      delay(10);
    break;
    case 0x1C: // 00011100 in wall right and left and obstacle right
      forward();
      delay(10);
    break;
    case 0x1D: // 00011101 inv wall right and left and obstacle front and right
      reverse();
      delay(10);
    break;
    case 0x1E: // 00011110 inv left and right and obstacle left and right
      forward();
      delay(10);
    break;
    case 0x1F: // 00011111 inv wall left and right and obstacle front left and right.
      reverse();
      delay(10);
    break;
    case 0x20:
      in_room_algorithm();
      delay(10);
    break;
  }
}

//sensors

int light_sensor_handler(){

  roomlight_value = (analogRead(roomlightPin)); //Write the value of the photoresistor to the room light variable.
  light_value = (analogRead(lightPin)); //Write the value of the photoresistor to the light variable
}

int ir_left_handler(){
	lval = analogRead(ir_left_pin); //reads the value of the sharp sensor
	return lval;
}

int ir_right_handler(){
	rval = analogRead(lsensorpin);
}

int ping_left_handler(){
  long duration, cm;
  pinMode(ping_left_pin, OUTPUT);
  digitalWrite(ping_left_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_left_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_left_pin, LOW);
  pinMode(ping_left_pin, INPUT);
  duration = pulseIn(ping_left_pin, HIGH);
  cm = duration/29/2;
  return cm;
}

int ping_right_handler(){
  long duration, cm;
  pinMode(ping_right_pin, OUTPUT);
  digitalWrite(ping_right_pin, LOW);
  delayMicroseconds(ping_right_pin);
  digitalWrite(ping_right_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_right_pin, LOW);
  pinMode(ping_right_pin, INPUT);
  duration = pulseIn(ping_right_pin, HIGH);
  cm = duration/29/2;
  return cm;
}

int ping_front_handler(){
  long duration, cm;
  pinMode(ping_front_pin, OUTPUT);
  digitalWrite(ping_front_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_front_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_front_pin, LOW);
  pinMode(ping_front_pin, INPUT);
  duration = pulseIn(ping_front_pin, HIGH);
  cm = duration/29/2;
  return cm;
}


//LIGHT sensor
void light_sensor(){

  roomlight_value = (analogRead(roomlightPin)); //Write the value of the photoresistor to the room light variable.
  light_value = (analogRead(lightPin)); //Write the value of the photoresistor to the light variable

}

//SERVOS

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

//In Room Algorithm

void in_room_algorithm(){
  ;
}
