/*
 * pet.c
 *
 * Created: 2018/11/29 22:00:23
 *  Author: Duncan
 */ 
#include "pet.h"

const uint32_t MAXSTAT = 100; //Maximum value for a stat. Defined here for easier adjustment

void update_petstats(pet* p) //Sets application pet stats to the kernel's pet stats
{
	p->age       = user_pet.age;
	p->satiety   = user_pet.satiety;
	p->energy    = user_pet.energy;
	p->happiness = user_pet.happiness;
}

static void increaseS(int i) //Increases Satiety (decreases hunger)
{
	i = user_pet.satiety + i;
	
	if(i >= MAXSTAT) user_pet.satiety = MAXSTAT;
	else if(i <= 0) user_pet.satiety = 0;
	else user_pet.satiety = i;
}

static void increaseE(int i) //Increases Energy
{
	i = user_pet.energy + i;
	
	if(i >= MAXSTAT) user_pet.energy = MAXSTAT;
	else if(i <= 0) user_pet.energy = 0;
	else user_pet.energy = i;
}

static void increaseH(int i) //Increases Happiness
{
	i = user_pet.happiness + i;
	
	if(i >= MAXSTAT) user_pet.happiness = MAXSTAT;
	else if(i <= 0) user_pet.happiness = 0;
	else user_pet.happiness = i;
}

void feed_pet(pet* p) //Used as a systemcall when user goes to feed pet. Changes kernel pet's stats by set amount.
{
	if(user_pet.satiety < MAXSTAT-19)
	{
		increaseE(-3);
		increaseH(5);
	}
	else
	{
		increaseE(-6);
		increaseH(-6);
	}
	
	increaseS(20);
	
	update_petstats(p);
}

void rest_pet(pet* p) //Used as a systemcall when user goes to rest pet. Changes kernel pet's stats by set amount.
{
	
	if(user_pet.energy < MAXSTAT/2 && user_pet.energy > MAXSTAT/4)
	{
		increaseS(-20);
		user_pet.energy = MAXSTAT;
		increaseH(5);
	}
	else
	{
		increaseS(-10);
		user_pet.energy = MAXSTAT-10;
		increaseH(-5);
	}
	
	update_petstats(p);
}

void play_pet(pet* p) //Used as a systemcall when user goes to play with pet. Changes kernel pet's stats by set amount.
{
	if(user_pet.energy < MAXSTAT/3 || user_pet.satiety < MAXSTAT/4)
	{
		increaseS(-5);
		increaseE(-10);
		increaseH(-1);
	}
	else
	{
		increaseS(-10);
		increaseE(-10);
		increaseH(20);
	}
	
	update_petstats(p);
}