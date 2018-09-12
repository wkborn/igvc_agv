#DEFINE DARK 309
#DEFINE LIGHT 310
#DEFINE LSENSORPIN 0
#DEFINE RSENSORPIN 0 //analog pin used to connect the sharp sensor
#DEFINE THRESHOLD 250  //value when vehicle should can direction

#include <Servo.h>

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
  inroom = 0x00;
  obstacle_front = 0x00;
  obstacle_left = 0x00;
  obstacle_right = 0x00;

  if (light_value =< DARK)
    inroom = 0b00100000;   //If robot does not detect light (i.e. room is dark) set flag to 1
  else if (light_value >= LIGHT)
    inroom = 0b00000000;  //If the robot detects light, set the flag to 0
  if(lval < THRESHOLD)
		inv_wall_left = 0b00010000;
	if(rval < THRESHOLD)
		inv_wall_right = 0b00001000;
  if(ping_front < PINGFRONTVAL)
		obstacle_front = 0b00000001;
  if(ping_left < PINGLEFTVAL)
		obstacle_front = 0b00000010;
  if(ping_right < PINGRIGHTVAL)
		obstacle_front = 0b00000100;
}



void sensors(){
  light_sensor();
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
      reverse()
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
      left()
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
	lval = analogRead(lsensorpin); //reads the value of the sharp sensor
	return lval;
}

int ir_right_handler(){
	rval = analogRead(lsensorpin);
}

int ping_left_handler(){
  long duration, cm
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);
  pinMode(3, INPUT);
  duration = pulseIn(3, HIGH);
  cm = duration/29/2;
  return cm;
}

int ping_right_handler(){
  long duration, cm
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(5);
  digitalWrite(2, LOW);
  pinMode(2, INPUT);
  duration = pulseIn(2, HIGH);
  cm = duration/29/2;
  return cm;
}

int ping_front_handler(){
  long duration, cm
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  delayMicroseconds(2);
  digitalWrite(0, HIGH);
  delayMicroseconds(5);
  digitalWrite(0, LOW);
  pinMode(0, INPUT);
  duration = pulseIn(0, HIGH);
  cm = duration/29/2;
  return cm;
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
