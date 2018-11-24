/*
 * clock.h
 *
 * Created: 11/1/2018 5:50:21 PM
 *  Author: drender
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

typedef struct{
	uint32_t seconds; /**< seconds */
	uint32_t minutes; /**< minutes */
	uint32_t hours;   /**< hours */
	uint32_t day;     /**< day */
	uint32_t month;   /**< month */
	uint32_t year;    /**< year */
}tTime;

void clock_read(tTime*);

void clock_write(tTime*);

#endif /* CLOCK_H_ */