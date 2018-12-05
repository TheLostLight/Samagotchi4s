/*
 * main.h
 *
 * Created: 11/23/2018 3:10:06 PM
 *  Author: drender
 */ 


#ifndef MAIN_H_
#define MAIN_H_

/* Definitions for setting the max size for 'menu arrays'.*/ 
/*Makes it easier to adjust them if new options are to be added later on. */
#define MENU_NUM 5
#define BREED_NUM 2

/* Prototypes */
bool make_name( void );

void decrement_cursor( void );
void increment_cursor( void );

void open_menu( int );
void show_stats( void );
void display_clr_line( int );

/* When creating a pet name, makes the currently selected position 'blink' */
char cursor[2] = {' ', '_'};

/* Array of strings for the menu where user selects breed */
uint8_t* breed_choices[BREED_NUM] = {"Crab", "Unicorn"};

/* Array of strings for user choices in main menu */
uint8_t* main_menu[MENU_NUM] = {"Feed", "Play", "Put to sleep", "Check Status", "Save"};

#endif /* MAIN_H_ */
