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
const int ir_left_pin = 3;
const int ir_right_pin = 4; //analog pin used to connect the sharp sensor
const int threshold = 250;  //value when vehicle should can direction
const int ping_right_pin = 2;
const int ping_left_pin = 3;
const int ping_front_pin = 4;
const int ping_front_min=10;
const int ping_left_min=10;
const int ping_right_min=10;

void setup() {
  Serial.begin(9600);
}

void loop() {

  sensors();
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
  Serial.print("Ping front (cm): ");
  Serial.print(ping_front);
  Serial.println(" cm.");
  Serial.print("Ping left (cm): ");
  Serial.print(ping_left);
  Serial.println(" cm.");
  Serial.print("Ping right (cm): ");
  Serial.print(ping_right);
  Serial.println(" cm.");
  Serial.print("IR left: ");
  Serial.println(lval);
  Serial.print("IR right: ");
  Serial.println(rval);
  

  delay(1000);
}

void sensors(){

  light_sensor();
  ir_left_handler();
  ir_right_handler();
  delay(10);
  ping_front = ping_front_handler();
  delay(10);
  ping_left = ping_left_handler();
  delay(10);
  ping_right = ping_right_handler();

}

//sensors

int light_sensor_handler(){

  roomlight_value = (analogRead(roomlightPin)); //Write the value of the photoresistor to the room light variable.
  light_value = (analogRead(lightPin)); //Write the value of the photoresistor to the light variable
}

int ir_left_handler(){
  lval =  analogRead(ir_left_pin); //reads the value of the sharp sensor
}

int ir_right_handler(){
  rval = analogRead(ir_right_pin);
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
  delayMicroseconds(ping_front_pin);
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


