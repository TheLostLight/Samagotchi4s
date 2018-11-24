/*
 * buttons.c
 *
 * Created: 11/14/2018 3:12:14 PM
 *  Author: drender
 */ 
#include <stdint-gcc.h>
#include <stdbool.h>
#include "minilib/buttons.h"
#include "minilib/display.h"
#include <stdio.h>

#define NUM_BUTTONS 4

void button_count(tButtonNum);
uint32_t count[NUM_BUTTONS];
tButtonNum volatile last_pressed = NoButton;

static void buttons_main(void){
	
	for(int i=0; i<NUM_BUTTONS; i++) count[i] = 0;
	
	display_gotoxy(0, 0);
	display_puts("Button 0 presses: 0");
	display_gotoxy(0, 1);
	display_puts("Button 1 presses: 0");
	display_gotoxy(0, 2);
	display_puts("Button 2 presses: 0");
	display_gotoxy(0, 3);
	display_puts("Button 3 presses: 0");
	
		
	//Just loop on nothing and wait for button interrupts.
	while( true )
	{
		button_read(&last_pressed);
		
		if(last_pressed != NoButton) button_count(last_pressed);
	}
	
	return 0;
}

void button_count(tButtonNum b)
{
	display_gotoxy(0, b);
	display_printf( "Button %d presses: %d", b, ++count[b] );
}
