/*
 * main.h
 *
 * Created: 11/23/2018 3:10:06 PM
 *  Author: drender
 */ 


#ifndef MAIN_H_
#define MAIN_H_


void make_name( void );

char decrement_cursor( void );
char increment_cursor( void );

char cursor[2] = {' ', '_'};

uint8_t menu_options = 5;
uint8_t* main_menu[menu_options] = {"Feed", "Play", "Put to sleep", "Check Status", "Save"};

#endif /* MAIN_H_ */