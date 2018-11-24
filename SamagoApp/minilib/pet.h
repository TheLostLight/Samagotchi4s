/*
 * pet.h
 *
 * Created: 11/23/2018 3:10:56 PM
 *  Author: drender
 */ 


#ifndef PET_H_
#define PET_H_

enum tBreed{Dog=0, Cat, Turtle, Dragon};

typedef struct{
	uint32_t satiety;
	uint32_t energy;
	uint32_t happiness;
	uint32_t age;
	uint8_t  name;
	tBreed   breed;
	
}pet;

pet user_pet;

void update_stats(pet*);

void set_name(uint8_t*);

void read_name(pet*);

void save_file(pet*);

void is_new_file( bool* );

void feed( pet* );
void rest( pet* );
void play( pet* );

void draw();

void start_time(void);
void stop_time(void);

#endif /* PET_H_ */