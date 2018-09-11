#DEFINE DARK 309
#DEFINE LIGHT 310


int light_value;
int roomlight_value;
int lightPin = 0;         //Pin assignment
int roomlightPin = 1;     //Pin assignment

void setup() {

  Serial.begin(9600);

}

void loop() {

  light_sensor();
  set_flags();

}

int light_sensor(){

  roomlight_value = (analogRead(roomlightPin)); //Write the value of the photoresistor to the room light variable.
  light_value = (analogRead(lightPin)); //Write the value of the photoresistor to the light variable

}

int set_flags(){

  if (light_value =< DARK)
    inroom = 0b00100000;   //If robot does not detect light (i.e. room is dark) set flag to 1
  if (light_value => LIGHT)
    inroom = 0b00000000;  //If the robot detects light, set the flag to 0

}
