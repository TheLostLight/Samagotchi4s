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

void open_menu( int );
void show_stats( void );

char cursor[2] = {' ', '_'};

const uint8_t MENU_NUM = 5;
uint8_t* main_menu[menu_options] = {"Feed", "Play", "Put to sleep", "Check Status", "Save"};

#endif /* MAIN_H_ */
