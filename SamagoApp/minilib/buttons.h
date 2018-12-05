/*
 * buttons.h
 *
 * Created: 11/14/2018 2:47:17 PM
 *  Author: drender
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

typedef int32_t tButtonNum;

enum tButtonNum{NoButton = -1, Button0, Button1, Button2, Button3, Button4};
	
	
void button_read( tButtonNum* ); //Reads the last pressed button.

#endif /* BUTTONS_H_ */