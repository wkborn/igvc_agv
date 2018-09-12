#DEFINE LSENSORPIN 0
#DEFINE RSENSORPIN 0 //analog pin used to connect the sharp sensor
#DEFINE THRESHOLD 250  //value when vehicle should can direction



int lval = 0;  //variable to store the values from sensor(initially zero)
int rval = 0;

int ir_left_handler(){
	lval = analogRead(lsensorpin); //reads the value of the sharp sensor
	return lval;
}

int ir_right_handler(){
	rval = analogRead(lsensorpin);
	return rval;
}

int set_ir_flags(){
	if(lval < THRESHOLD)
		inv_wall_left = 0b00010000;
	
	if(lval >= THRESHOLD)
		inv_wall_left = 0b00000000;
	
	if(rval < THRESHOLD)
		inv_wall_right = 0b00001000;

	if(rval >= THRESHOLD)
		inv_wall_right = 0b00000000;
}
