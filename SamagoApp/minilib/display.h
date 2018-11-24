/*
 * display.h
 *
 * Created: 11/1/2018 5:50:42 PM
 *  Author: drender
 */ 
#include <stdarg.h>

#ifndef DISPLAY_H_
#define DISPLAY_H_

void display_putc(int c);
void display_gotoxy(uint32_t, uint32_t);
void display_cls(void);

void display_puts(uint8_t* string)
{
	uint8_t c;
	
	while(c = *string++) display_putc(c);
}

int log_10(int num)
{
	int i = 0;
	
	while(num > 9)
	{
		num /= 10;
		i++;
	}
	
	return i;
}

void display_printn(int val)
{
	int lim = log_10(val);
	
	char string[lim+1];
	int power = 1;
	int digit;
	
	for(int i = lim; i >= 0; i--)
	{
		digit = val%(power*10);
		digit /= power;
		digit += 48;
		
		string[i] = digit;
		
		power *= 10;
	}
	
	for(int i=0; i < lim+1; i++) display_putc(string[i]);
}

/* Adapted from vishal's example: https://stackoverflow.com/questions/1735236/how-to-write-my-own-printf-in-c on November 8, 2018, 2:13 P.M. */
void display_printf(const char *format, ...)
{
	char *ind;
	
	va_list valist;
	
	va_start(valist, format);
	
	for(ind = format; *ind != '\0'; ind++)
	{
		while(*ind != '%' && *ind != '\0')
		{
			display_putc(*ind);
			ind++;
		}
		
		if(*ind == '\0') break;
		
		ind++;
		
		switch(*ind)
		{
			case 'c' : display_putc(va_arg(valist, char)); break;
			case 'd' : display_printn(va_arg(valist, int)); break;
			case 's' : display_puts(va_arg(valist, uint8_t*)); break;
		}
	}
	
	va_end(valist);
}

#endif /* DISPLAY_H_ */