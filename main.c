#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include <time.h>

void delay(int t)
{
    int milli_seconds = 1000 * t;
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds){
      ;
    }
}


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

  state = obstacle_front | obstacle_left | obstacle_right | inv_wall_left | inv_wall_right | in_room;

  if(state >= 0x20)
    state = 0x20;

  switch (state) {
    case 0x00:
      printf("no flags\n");
    break;
    case 0x01:
      printf("obstacle front\n");
    break;
    case 0x02:
      printf("obstacle left\n");
    break;
    case 0x03:
      printf("obstacle front and left\n");
    break;
    case 0x04:
      printf("obstacle right\n");
    break;
    case 0x05:
      printf("obstacle front and right\n");
    break;
    case 0x06:
      printf("obstacle left and right\n");
    break;
    case 0x07:
      printf("obstacle front, left, and right\n");
    break;
    case 0x08:
      printf("invisible wall left\n");
    break;
    case 0x09:
      printf("obstacle front and invisible wall left\n");
    break;
    case 0x0A:
      printf("obstacle left and invisible wall left\n");
    break;
    case 0x0B:
      printf("invisible wall left and obstacle front and left\n");
    break;
    case 0x0C:
      printf("invisible wall left and obstacle right\n");
    break;
    case 0x0D:
      printf("invisible wall left and obstacle front and right\n");
    break;
    case 0x0E:
      printf("invisible wall left and obstacle left and right\n");
    break;
    case 0x0F:
      printf("invisible wall left and obstacle front, left and right\n");
    break;
    case 0x10:
      printf("invisible wall right\n");
    break;
    case 0x11:
      printf("invisible wall right and obstacle front\n");
    break;
    case 0x12:
      printf("invisible wall right and obstacle left\n");
    break;
    case 0x13:
      printf("invisible wall right and obstacle front and left\n");
    break;
    case 0x14:
      printf("invisible wall right and obstacle right\n");
    break;
    case 0x15:
      printf("invisible wall right and obstacle front and right\n");
    break;
    case 0x16:
      printf("invisible wall right and obstacle left and right\n");
    break;
    case 0x17:
      printf("invisible wall right and obstacle front, left and right\n");
    break;
    case 0x18:
      printf("invisible wall right and inv_wall_left\n");
    break;
    case 0x19:
      printf("invisible wall right and inv wall left and obstacle front\n");
    break;
    case 0x1A:
      printf("invisible wall right and obstacle left and invisible wall left\n");
    break;
    case 0x1B:
      printf("invisible wall right and invisible wall left and obstacle front and left\n");
    break;
    case 0x1C:
      printf("invisible wall right and invisible wall left and obstacle right\n");
    break;
    case 0x1D:
      printf("invisible wall right and invisible wall left and obstacle front and right\n");
    break;
    case 0x1E:
      printf("invisible wall right and invisible wall left and obstacle left and right\n");
    break;
    case 0x1F:
      printf("invisible wall right and invisible wall left and obstacle front, left, and right\n");
    break;
    case 0x20:
      printf("in room\n");
    break;
  }
  //delay(500);
}


void sensor_data(){
  obstacle_front = 0b00000001;
  //obstacle_left = 0b00000010;
  //obstacle_right = 0b00000100;
  inv_wall_left = 0b00001000;
  //inv_wall_right = 0b00010000;
  //in_room=0b00100000;
}
