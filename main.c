
#include<stdint.h>
#include<stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

void setup();
void loop();
void sensor_data();

uint16_t ping_1;
uint16_t ping_2;
uint16_t ping_3;
float pr_1;
float pr_2;
uint16_t ir_1;
uint16_t ir_2;
uint8_t obstacle_front;
uint8_t obstacle_left;
uint8_t obstacle_right;
uint8_t inv_wall_left;
uint8_t inv_wall_right;
uint8_t in_room;
uint8_t state;
uint8_t prev_direction;

int main()
{
  setup();

  while(1)
  {
    loop();
  }

  return 0;
}


void setup(){
  DDRB = 0x0F;
  ping_1 = 0;
  ping_2 = 0;
  ping_3 = 0;
  pr_1 = 0.0f;
  pr_2 = 0.0f;
  ir_1 = 0;
  ir_2 = 0;
  obstacle_left = 0;
  obstacle_front = 0;
  obstacle_right = 0;
  inv_wall_left = 0;
  inv_wall_right = 0;
  in_room = 0;
  state = 0;
  prev_direction = 0;
}

void loop(){

  sensor_data();
	PORTB = 0x00;

	if((state & 0x10)==0x10)
		state = state | 0x0F;
	else
		state=0x00;
	state = obstacle_front | obstacle_left | obstacle_right | inv_wall_left | inv_wall_right | in_room;
	PORTB = state;

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


  _delay_ms(1000);
}


void sensor_data(){
  //obstacle_front = 0b00000001;
  //obstacle_left = 0b00000010;
  //obstacle_right = 0b00000100;
  //inv_wall_left = 0b00001000;
  //inv_wall_right = 0b00010000;
  //in_room=0b00100000;
}
