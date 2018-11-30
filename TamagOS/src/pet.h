/*
 * pet.h
 *
 * Created: 2018/11/28 16:19:54
 *  Author: Duncan
 */ 


#ifndef PET_H_
#define PET_H_

#include <stdbool.h>
#include <stdint-gcc.h>

typedef uint32_t tBreed;

enum tBreed{Crab=0, Unicorn};

typedef struct{
	uint32_t satiety;
	uint32_t energy;
	uint32_t happiness;
	uint32_t age;
	uint8_t* name;
	tBreed   breed;
	
}pet;

pet user_pet;
bool isNewFile;

void update_petstats( pet* );

void feed_pet( pet* );

void rest_pet( pet* );

void play_pet( pet* );

#endif /* PET_H_ */