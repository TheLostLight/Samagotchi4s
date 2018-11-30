/*
 * main.h
 *
 * Created: 11/23/2018 3:10:06 PM
 *  Author: drender
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define MENU_NUM 5
#define BREED_NUM 2


bool make_name( void );

void decrement_cursor( void );
void increment_cursor( void );

void open_menu( int );
void show_stats( void );
void display_clr_line( int );

char cursor[2] = {' ', '_'};
	
uint8_t* breed_choices[BREED_NUM] = {"Crab", "Unicorn"};

uint8_t* main_menu[MENU_NUM] = {"Feed", "Play", "Put to sleep", "Check Status", "Save"};

#endif /* MAIN_H_ */
