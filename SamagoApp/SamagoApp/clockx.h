/*
 * clock.c
 *
 * Created: 11/1/2018 6:24:39 PM
 *  Author: drender
 */ 
#include <stdint-gcc.h>
#include <stdbool.h>
#include "minilib/led.h"
#include "minilib/display.h"
#include "minilib/clock.h"

static void clock_main(void){
	
	tTime clock;
	
	uint8_t* day_to_month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
	"Aug", "Sep", "Oct", "Nov", "Dec" };
	
	uint8_t* the_time;
	
	while( true ){
		clock_read( &clock );
		display_gotoxy(0, 0);
		display_printf( " %s %d %d,", day_to_month[clock.month-1], clock.day, clock.year );
		display_gotoxy(0, 1);
		format_time(clock, the_time);
		display_printf(" %s ", the_time);
	}

}