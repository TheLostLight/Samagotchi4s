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
#include "main.h"

#define MINIOSAPP __attribute__ ((section(".entry_point"))) uint32_t
#define STACKINFO __attribute__ ((section(".stack_info"))) uint32_t

extern uint32_t _estack;
STACKINFO sp  = &_estack;

tButtonNum volatile selection = NoButton;
pet user_pet = {0, 0, 0, 0, 0, 0};

MINIOSAPP main(void){
	
	update_stats(&user_pet);
	
	bool new;
	
	is_new_file(&new);
	
	if(new) //If no file was present before beginning application, and SamagOS created a new one do this.
	{
		 display_gotoxy(0, 0);
		 display_puts("A new pet has been born!");
		 display_gotoxy(0, 2);
		 display_puts("Please enter a name");
		 display_gotoxy(0, 3);
		 display_puts("for your new pet:");
		 
		 delay_ms(3000); //Delay so that user has time to read information. Could be substituted for a "button listener".
		 display_cls();
		 
		 while(!make_name()) display_cls(); //Loop until user has confirmed a name for their pet.
		 
		 display_cls();
		 set_name(&user_pet.name); //Probably an unnecessary step. Currently does nothing in kernel.
		 
		 display_gotoxy(0, 0);
		 display_printf("Congratulations!");
		 display_gotoxy(0, 1);
		 display_printf("have named your pet:");
		 display_gotoxy(0, 2);
		 display_printf("%s", user_pet.name);
		 delay_ms(2500);
		 display_cls();
		 display_gotoxy(0, 0);
		 display_printf("What breed is %s", user_pet.name);
		 display_gotoxy(0, 3);
		 
		 button_read(&selection); //clear buffer
		 selection = NoButton;
		 int pos = 0;
		 display_puts(breed_choices[pos]);
		 
		 while(selection != Button2) //Loop for selecting breed. Only two right now, but written in an easily expandable way.
		 {
			 button_read(&selection);
			 
			 switch(selection)
			 {
				case Button1: if(pos > 0) pos--; else pos = BREED_NUM; display_clr_line(3); display_puts(breed_choices[pos]);
				case Button3: pos = (pos+1)%BREED_NUM; display_clr_line(3); display_puts(breed_choices[pos]);
				default: break; 
			 }
		 }
		 
		 user_pet.breed = pos;
		 display_clr_line(3);
		 display_printf("%s is a %s.", user_pet.name, breed_choices[pos]);
		 delay_ms(2500);
		 display_cls();
		 draw(user_pet.breed, 100);
	}
	else //If an old file was loaded before starting application, do this
	{
		read_name(&user_pet);
		display_gotoxy(0, 0);
		display_printf("Welcome back!");
		display_gotoxy(0, 3);
		display_printf("%s missed you.", user_pet.name);
		delay_ms(3000);
		
		display_cls();
		draw(user_pet.breed, 100);
	}
	
	int menuc = 0;
	button_read(&selection); //Clear buffer
	print_menu_header();
	start_time();

	while(true) //Loop for main menu
	{
		display_puts(main_menu[menuc]);
		button_read(&selection);
		
		while(selection == NoButton) button_read(&selection);
		
		switch(selection)
		{
			case NoButton: /* error */ break;
			case Button0 : show_stats(); //Shortcut for viewing pet stats
			case Button1 : if(menuc > 0) --menuc; else menuc = MENU_NUM-1; break; //Scroll down options in menu
			case Button2 : open_menu(menuc); break; //Perform currently selected option
			case Button3 : menuc = (menuc+1)%MENU_NUM; break; //Scroll up options in menu
			default      : break;
		}
		
		display_clr_line(3);
		update_stats(&user_pet);
		
	}

	return 0;	
}

/* Routine for setting the name of the user pet */
bool make_name(void)
{
	display_gotoxy(0, 0);
	display_puts("Buttons 1 & 3: scroll");
	display_gotoxy(0, 1);
	display_puts("Button 2: enter");
	display_gotoxy(0, 2);
	display_puts("Button 0: confirm");
	
	uint8_t pos = 0;
	char buffer[8] = {0};
	
	for(int count = 0; pos < 7; count++)
	{
		count = count%1000;
		
		display_gotoxy(0, 3);
		
		for(int i=0; i<pos; i++) display_putc(buffer[i]);
		
		display_putc(cursor[count/500]);
		
		button_read(&selection);
		
		if(selection != NoButton)
		{
			switch(selection)
			{
				case Button1 : decrement_cursor(); break;
				case Button2 : display_putc(cursor[0]); buffer[pos++] = cursor[0]; break;
				case Button3 : increment_cursor(); break;
				default		 : break;
			}
		}
		if(selection == Button0) {display_putc(cursor[0]); break;}
	}
	
	for(int i=0; i<8; i++) user_pet.name[i] = buffer[i];
	display_cls();
	display_gotoxy(0, 0);
	display_printf("Name: %s", user_pet.name);
	display_gotoxy(0, 1);
	display_puts("Is this ok?");
	display_gotoxy(0, 3);
	display_puts("Button 1: ok Else: cancel");
	button_read(&selection);
	
	while(selection == NoButton) button_read(&selection);
	
	if(selection == Button1) return true;
	return false;
}

void decrement_cursor(void)
{
	if(cursor[0] == ' ') cursor[0] = 'z'; //Switch to lower case
	
	else
	{
		cursor[0]--;
		
		if(cursor[0] < 'A') cursor[0] = ' '; //inserts empty space if user decrements below 'A'
	}
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

/* Performs an event based on the number of button pressed by user */
void open_menu(int op)
{
	switch(op)
	{
		case 0: display_cls(); 
			display_gotoxy(0, 0); 
			display_printf("You give %s some pet food", user_pet.name);
			delay_ms(2000);
			draw(user_pet.breed, 100);
			feed( &user_pet );
			display_cls();
			display_gotoxy(0, 0);
			display_printf("%s's hunger is now %d", user_pet.name, MAX_STAT-user_pet.satiety); //Hunger is the inverse of satiety.
			break;

		case 1: display_cls(); 
			display_gotoxy(0, 0); 
			display_printf("You play with %s for a while", user_pet.name);
			delay_ms(2000);
			draw(user_pet.breed, 100);
			play( &user_pet );
			display_cls();
			display_gotoxy(0, 0);
			display_printf("%s's happiness is now %d", user_pet.name, user_pet.happiness);
			break;

		case 2: display_cls(); 
			display_gotoxy(0, 0); 
			display_printf("%s takes a nap...", user_pet.name);
			delay_ms(2000);
			draw(user_pet.breed, 100);
			rest( &user_pet );
			display_cls();
			display_gotoxy(0, 0);
			display_printf("%s's energy is now %d", user_pet.name, user_pet.energy);
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
	//stop_time();
	update_stats(&user_pet);

	display_cls();
	display_gotoxy(0, 0);
	display_printf("Once finished viewing,");
	display_gotoxy(0, 1);
	display_puts("press any button to continue");
	delay_ms(2500);
	button_read(&selection); //clear input in case user accidentally presses button here
	
	display_cls();
	//Display all main stats
	display_gotoxy(0, 0);
	display_printf("Hunger:    %d", MAX_STAT-user_pet.satiety);
	display_gotoxy(0, 1);
	display_printf("Energy:    %d", user_pet.energy);
	display_gotoxy(0, 2);
	display_printf("Happiness: %d", user_pet.happiness);
	display_gotoxy(0, 3);
	display_printf("Age :      %d", user_pet.age);

	button_read(&selection); //clear once more

	do button_read(&selection); //Wait for user to press button before proceeding
	while (selection == NoButton);

	start_time();
	print_menu_header();
}

/* Used as a prologue to the Main menu */
void print_menu_header()
{
	display_cls();
	display_gotoxy(0, 0);
	display_printf("What would you and"); 
	display_gotoxy(0, 1);
	display_printf("%s like to do?", user_pet.name);
	display_gotoxy(0, 3);
	button_read(&selection);
}

/* Clears current line of the display */
void display_clr_line(int line)
{
	display_gotoxy(0, line);
	display_puts("                              ");
	display_gotoxy(0, line);
}

