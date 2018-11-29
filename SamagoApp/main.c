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
		 
		 delay(1000);
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
		
		delay_ms(800);
	}
	
	volatile int menuc = 0;
	button_read(&selection); //Clear buffer
	print_menu_header();
	start_time();

	while(true)
	{
		display_puts(main_menu[menuc]);
		button_read(&selection);

		switch(selection)
		{
			case NoButton: break;
			case Button0 : show_stats();
			case Button1 : if(menuc < 1) menuc = MENU_NUM-1; else --menuc; break;
			case Button2 : show_menu(menuc); break;
			case Button3 : menu = (menu+1)%MENU_NUM; break;
			default      : break;
		}

		update_stats(&user_pet);
	}

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

void open_menu(int op)
{
	switch(op)
	{
		case 0: display_cls(); 
			display_gotoxy(0, 0); 
			display_printf("You give %s some pet food");
			delay_ms(800);
			draw(user_pet.breed);
			feed( &user_pet );
			display_cls();
			display_gotoxy(0, 0);
			display_printf("%s's hunger is now %n", user_pet.name, MAX_STAT-user_pet.satiety); //Hunger is the inverse of satiety.
			break;

		case 1: display_cls(); 
			display_gotoxy(0, 0); 
			display_printf("You play with %s for a while");
			delay_ms(800);
			draw(user_pet.breed);
			play( &user_pet );
			display_cls();
			display_gotoxy(0, 0);
			display_printf("%s's happiness is now %n", user_pet.name, user_pet.happiness);
			break;

		case 2: display_cls(); 
			display_gotoxy(0, 0); 
			display_printf("%s takes a nap...");
			delay_ms(800);
			draw(user_pet.breed);
			rest( &user_pet );
			display_cls();
			display_gotoxy(0, 0);
			display_printf("%s's energy is now %n", user_pet.name, user_pet.energy);
			break;

		case 3: show_stats(); 
			return;

		case 4: stop_time();
			display_cls();
			save_file( &user_pet );
			display_gotoxy(0, 0);
			display_puts("Your file has been saved");
			start_time();
			break;

		default: display_cls();
			 display_gotoxy(0, 0);
			 display_puts("Error: menu selection out of bounds");
			 break;
	}

	print_menu_header();
}

void show_stats()
{
	stop_time();
	update_stats(&user_pet);

	display_cls();
	display_gotoxy(0, 0);
	display_printf("Once finished viewing,");
	display_gotoxy(0, 1);
	display_puts("press any button to continue");
	delay_ms(1000);
	read_button(&selection); //clear input in case user accidentally presses button here
	
	display_cls();
	display_gotoxy(0, 0);
	display_printf("Hunger:    %n", MAX_STATS-user_pet.satiety);
	display_gotoxy(0, 1);
	display_printf("Energy:    %n", user_pet.energy);
	display_gotoxy(0, 2);
	display_printf("Happiness: %n", user_pet.happiness);
	display_gotoxy(0, 3);
	display_printf("Age (min): %n", user_pet.age);

	read_button(&selection); //clear once more

	do read_button(&selection);
	while (selection == NoButton);

	start_time();
	print_menu_header();
}

void print_menu_header()
{
	display_cls();
	display_gotoxy(0, 0);
	display_printf("What would you and %s like to do?", user_pet.name);
	display_gotoxy(0, 3);
	button_read(&selection);
}

