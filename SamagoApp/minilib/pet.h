/*
 * pet.h
 *
 * Created: 11/23/2018 3:10:56 PM
 *  Author: drender
 */ 


#ifndef PET_H_
#define PET_H_

typedef uint32_t tBreed;

enum tBreed{Crab=0, Unicorn};

typedef struct{
	uint32_t satiety;
	uint32_t energy;
	uint32_t happiness;
	uint32_t age;
	char name[8];
	tBreed   breed;
	
}pet;

/* Pet related system calls */
void update_stats(pet*);

void set_name(uint8_t*); //Probably unnecessary. Does nothing in Kernel currently.

void read_name(pet*);

void save_file(pet*);

void is_new_file( bool* );

void feed( pet* );
void rest( pet* );
void play( pet* );

void draw(tBreed, uint32_t);

void start_time(void); //starts timer for ticking down pet stats
void stop_time(void); //pauses timer
void delay_ms(uint32_t); //Delay for making pauses in program flow

const uint32_t MAX_STAT = 100; //Max value for pet stats. Should be the same as the kernel value. "Or is this value even necessary?"

#endif /* PET_H_ */
