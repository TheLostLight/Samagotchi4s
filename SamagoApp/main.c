/*
 * main.c
 *
 * Created: 11/8/2018 1:17:30 PM
 *  Author: drender
 */ 
#include <stdint-gcc.h>
#include <stdbool.h>
#include "minilib/buttons.h"
#include "minilib/display.h"
#include "minilib/pet.h"

#define MINIOSAPP __attribute__ ((section(".entry_point"))) uint32_t
#define STACKINFO __attribute__ ((section(".stack_info"))) uint32_t

extern uint32_t _estack;
STACKINFO sp  = &_estack;

tButtonNum volatile selection = NoButton;

MINIOSAPP main(void){
	
	bool new;
	
	is_new_file(&new);
	
	if(new)
	{
		 display_gotoxy(0, 0);
		 display_puts("A new pet has been born!");
		 display_gotoxy(0, 2);
		 display_puts("Please enter a name for your new pet:");
		 
		 //delay
		 display_cls();
		 
		 while(!make_name()) display_cls();
		 
		 display_cls();
		 set_name(&user_pet.name);
		 
		 display_gotoxy(0, 0);
		 display_printf("Congratulations! You have named your pet %s.", user_pet.name);
		 display_gotoxy(0, 2);
		 display_printf("What kind of pet is %s?", user_pet.name);
	}
	else
	{
		update_stats(&user_pet);
		read_name(&user_pet);
		display_gotoxy(0, 0);
		display_printf("Welcome back!");
		display_gotoxy(0, 3);
		display_printf("%s missed you.", user_pet.name);
		
		//delay
	}
	
	start_time();
	
	return 0;	
}

bool make_name(void)
{
	display_gotoxy(0, 0);
	display_puts("Buttons 1 & 2 change the selected character,");
	display_gotoxy(0, 1);
	display_puts("Button 3 Enters the currently selected character,");
	display_gotoxy(0, 2);
	display_puts("Button 0 to enter selected name:");
	
	uint8_t pos = 0;
	char buffer[20] = '\0';
	
	for(int count = 0; pos < 20; count++)
	{
		count = count%100
		
		display_gotoxy(pos, 3);
		
		display_putc(cursor[count/50]);
		
		button_read(&selection);
		
		if(selection != NoButton)
		{
			switch(selection)
			{
				case Button1 : decrement_cursor(); break;
				case Button2 : increment_cursor(); break;
				case Button3 : display_putc(cursor[0]); [pos++] = cursor[0]; break;
				default		 : break;
			}
		}
		if(selection == Button0) {display_putc(cursor[1]); break;}
		
	}
	
	user_pet.name = buffer;
	display_cls();
	display_gotoxy(0, 0);
	display_printf("You have chosen the name, %s", user_pet.name);
	display_gotoxy(0, 1);
	display_puts("Is this what you want to name your pet?");
	display_gotoxy(0, 3);
	display_puts("(Press button 1 to confirm, any other to cancel)");
	button_read(&selection);
	
	while(selection == NoButton) button_read(&selection);
	
	if(selection == Button1) return true;
	return false;
}

void decrement_cursor(void)
{
	if(cursor[0] == ' ') cursor[0] = 'z'; //Switch to lower case
}
	else
	{
		cursor[0]--;
		
		if(cursor[0] < 'A') cursor[0] = ' '; //inserts empty space if user decrements below 'A'
}

void increment_cursor(void)
{
	if(cursor[0] == ' ') cursor[0] = 'A'; //Switch to upper case
	else
	{
		cursor[0]++;
		
		if(cursor[0] > 'z') cursor[0] = ' '; //inserts empty space if user increments above 'z'
	}
}

