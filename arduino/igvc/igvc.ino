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

  if (light_value =< DARK)
    inroom = 0b00100000;   //If robot does not detect light (i.e. room is dark) set flag to 1
  else if (light_value >= LIGHT)
    inroom = 0b00000000;  //If the robot detects light, set the flag to 0
  if(lval < THRESHOLD)
		inv_wall_left = 0b00010000;
	if(rval < THRESHOLD)
		inv_wall_right = 0b00001000;
}



void sensors(){
  light_sensor();
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
