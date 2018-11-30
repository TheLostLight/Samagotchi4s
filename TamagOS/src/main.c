//
//	------------     MiniOS entry point     -------------
//

#include "minios/system.h"
#include "minios/hal/hal.h"
#include "minios/console/console.h"
#include "minios/loader.h"
#include "minios/scheduler.h"
#include "pet.h"

//Make sure either the console or default app is selected for init
#if (!defined(SYS_INIT_FROM_CONSOLE) && !defined(SYS_INIT_FROM_DEFAPP)) || (defined(SYS_INIT_FROM_CONSOLE) && defined(SYS_INIT_FROM_DEFAPP))
#error "Define either SYS_INIT_FROM_CONSOLE or SYS_INIT_FROM_DEFAPP. Not both or none. See system.h"
#endif

int main(void)
{
	//Initializes the system
	system_init();
	hal_io_button_startall_int();
	
	
#ifdef SYS_INIT_FROM_CONSOLE
	//Execute the console
	console_begin();	
#else

	//Set up app values
	isNewFile = true;
	pet user_pet = { 100, 100, 100, 0, "", 0 };
	
	//Create process with default app	
	uint32_t loader_rval;
	uint32_t sched_rval;
	
	sched_rval = scheduler_process_create( SYS_APP_DEFAULT_NAME, "Samago", &loader_rval );
	
	if(  sched_rval == SCHEDULER_PROCESS_CREATE_FAILED ){
		if( loader_rval ==  LOADER_NO_APP_FOUND )		system_panic( "Default App not found" );	
		else if( loader_rval ==  LOADER_APP_TOO_LARGE ) system_panic( "Not enough mem 4 default App" );	
	}
#endif
	
	//Wait here until the timer's first tick
	//TODO: Maybe go to sleep here?
	while(1);
}
