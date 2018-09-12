#DEFINE PINGFRONTVAL 50
int ping_front;

int ping_front_handler(){

		//TODO
		//Collect sensor data
	
		return sensor_data;
}

int set_flags(){
	if(ping_front < PINGFRONTVAL)
		obstacle_front = 0b00000001;
}

