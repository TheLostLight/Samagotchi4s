//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "minios/console/console.h"
#include "minios/loader.h"
#include "minios/scheduler.h"
#include "minios/status.h"
#include <string.h>
#include <asf.h>

//Make sure either the console or default app is selected for init
//#if (!defined(SYS_INIT_FROM_CONSOLE) && !defined(SYS_INIT_FROM_DEFAPP)) || (defined(SYS_INIT_FROM_CONSOLE) && defined(SYS_INIT_FROM_DEFAPP))
//#error "Define either SYS_INIT_FROM_CONSOLE or SYS_INIT_FROM_DEFAPP. Not both or none. See system.h"
//#endif

// count down function reduce the satiety, energy, and happiness for 1
void count_down();


int main(void)
{
//Initializes the system
	system_init();
	
		
#ifdef SYS_INIT_FROM_CONSOLE
	//Execute the console
	console_begin();	
#else
	//Create process with default app	
	uint32_t loader_rval;
	uint32_t sched_rval;
	
	sched_rval = scheduler_process_create( SYS_APP_DEFAULT_NAME, "SamagoApp.bin", &loader_rval );
	
	if(  sched_rval == SCHEDULER_PROCESS_CREATE_FAILED ){
		if( loader_rval ==  LOADER_NO_APP_FOUND )		system_panic( "Default App not found" );	
		else if( loader_rval ==  LOADER_APP_TOO_LARGE ) system_panic( "Not enough mem 4 default App" );	
	}
	
		
	hal_nvmem_start(1);
	uint8_t file_name[] = "0:SamagotchiStats.txt";
	uint8_t default_stats[] ="100-100-100-0-Dino-0";
	uint8_t return_stats[25];
	uint32_t buffer_size = 25;
	uint32_t result = 0;
	
	result = hal_nvmem_fat_file_read(&file_name, &return_stats, buffer_size);
	
	if (return == 0){
		//Writing pet stats to new file
		hal_nvmem_fat_file_write(&file_name, &default_stats, buffer_size);
		
		//initializing with default values
		kernel_pet.satiety = 100;
		kernel_pet.energy = 100;
		kernel_pet.happiness = 100;
		kernel_pet.age = 0;
		kernel_pet.name = "Dino";
		kernel_pet.breed = 0;
	}
	else{
		
		//initial pet with values read from file
		const char s[2] = "-";
		char *token;
		char *ptr;
		
		token = strtok(return_stats, s);
		kernel_pet.satiety=strtol(token, &ptr, 10);
		
		token = strtok(NULL, s);
		kernel_pet.energy = strtol(token, &ptr, 10);
		
		token = strtok(NULL, s);
		kernel_pet.happiness = strtol(token, &ptr, 10);;
		
		token = strtok(NULL, s);
		kernel_pet.age = strtol(token, &ptr, 10);
		
		token = strtok(NULL, s);
		kernel_pet.name = token;
		
		token = strtok(NULL, s);
		kernel_pet.breed = strtol(token, &ptr, 10);
	}
	
#endif
	
	//Wait here until the timer's first tick
	//TODO: Maybe go to sleep here?
	while(1);
}



// s= satiety, e= energy, h= happiness
/*void count_down(void){
	if (satiety>0)
	{
		satiety-=satiety;
	}else{println("the satiety is 0.")}
		
	if (energy>0)
	{
		energy-=energy;
	}else{println("the energy is 0.")}
	
	if (happiness>0)
	{
		happiness-=happiness;
	}else{println("the happiness is 0.")}
	
	
}
*/
