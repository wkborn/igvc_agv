
//#define F_CPU 1600000
#define blink_rate 1

#include<stdint.h>
#include<stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setup();
void loop();
void sensor_data();
uint8_t ping_front();

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
uint32_t ms;


ISR(TIMER1_OVF_vect)
{
  TCNT1 = 0x10000 - (F_CPU/1100000/blink_rate);
  ms++;
}

unsigned long int millis(void)
{
    return ms;
}

void Timer0_Init(void)
{
  /* Set up Timer 1 control and status registers */
  TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0);	// OC1A/B disconnected, no PWM
  TCCR1B = (1<<CS12)   | (0<<CS11)   | (1<<CS10);					// Prescaler is 1024

  /* Preset Timer1 */
  TCNT1 = 0x10000 - (F_CPU/110000/blink_rate);

  /* Clear any interrupt flags */
  TIFR1 = (1<<TOV1);

  /* Enable local interrupt */
  /* Enable Timer1 overflow interrupt */
  TIMSK1 = (1<<TOIE1);

  TCNT0 = 0xF0;

  /* Enable interrupts */
  sei();
}

uint32_t millisToCentimeters(uint32_t millis) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return (millis) / 29 / 2;
}

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
  Timer0_Init();

  DDRB = 0b00011111;
  DDRD &= ~(1 << PD0);
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
  PORTB=0x00;
  _delay_ms(1000);
  PORTB=0xFF;
  _delay_ms(1000);
  PORTB=0x00;
  _delay_ms(10000);
  PORTB=0x00;
  _delay_ms(1000);
  PORTB=0xFF;
  _delay_ms(1000);
  PORTB=0x00;
}

void loop(){

  sensor_data();
	PORTB = 0x00;
  PORTB = state;
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


  //_delay_ms(1);
}


void sensor_data(){
  obstacle_front = ping_front();
  //obstacle_left = 0b00000010;
  //obstacle_right = 0b00000100;
  //inv_wall_left = 0b00001000;
  //inv_wall_right = 0b00010000;
  //in_room=0b00100000;
}

uint8_t ping_front(){
  //PIN PD1
  /*
  PORTB=0x00;
  _delay_ms(1000);
  PORTB=0xFF;
  _delay_ms(1000);
  PORTB=0x00;
  */
  _delay_ms(100);
  PORTD=0x00;

  DDRD= 0b00000001; //pinMode(pingPin, OUTPUT);
  PORTD= 0x00; //digitalWrite(pingPin, LOW);
  _delay_us(2);
  PORTD= 0b00000001; //digitalWrite(pingPin, HIGH);
  _delay_us(5);
  PORTD= 0x00; //digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  DDRD= 0x00;//pinMode(pingPin, INPUT);
  uint16_t init_millis= millis();

  while((PIND&0b00000001)!=0x01){
    ;
  }

  while((PIND&0b00000001)!=0x00){
    if ((millis()-init_millis)>200)
    {
      break;
    }
  }


  uint32_t duration = millis()-init_millis; //pulseIn(pingPin, HIGH);
  uint32_t dist = millisToCentimeters(duration);
  if(dist<10)
  {
    return 0b00010000;
  }

  return 0b00011111;
}


/*
if (init_millis>=10000)
{
  while (1){
    PORTB=0x00;
    _delay_ms(1000);
    PORTB=0xFF;
    _delay_ms(1000);
    PORTB=0x00;
  }
}

*/
