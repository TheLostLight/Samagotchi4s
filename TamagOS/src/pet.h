/*
 * pet.h
 *
 * Created: 2018/11/28 16:19:54
 *  Author: Duncan
 */ 


#ifndef PET_H_
#define PET_H_

enum tBreed{Dog=0, Cat, Turtle, Dragon};

typedef struct{
	uint32_t satiety;
	uint32_t energy;
	uint32_t happiness;
	uint32_t age;
	uint8_t*  name;
	tBreed   breed;
	
}pet;



#endif /* PET_H_ */