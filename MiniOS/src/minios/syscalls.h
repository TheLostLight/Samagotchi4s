/**
 * @file	syscalls.h
 * @author  
 * @version 
 *
 * @brief System Calls Interface header file
 *
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

void syscalls_init(void);

/**
*	System call numbers
*/
enum{
	//LED
	//FIX THIS
	//SVCLedWrite				= 0,
	//SVCLedRead				= 1,

	//Button
	//SVCButtonStartallEv		= 2,
	//SVCButtonStartallPoll	= 3,
	SVCButtonRead			= 2,

	//Clock
	SVCClockRead			= 3,
	SVCClockWrite			= 4,
	
	//Serial
	//SVCSerialStartEv		= 7,
	//SVCSerialStartPoll		= 8,
	//SVCSerialPutc			= 9,
	//SVCSerialGetc			= 10,
	
	//Sensors
	//SVCSensorStartEv		= 11,
	//SVCSensorStartPoll		= 12,
	//SVCSensorRead			= 13,

	//Display
	SVCDisplayCls			= 9,
	SVCDisplayPutc			= 10,
	SVCDisplayGotoxy		= 11,
	SVCDisplayNumLines		= 12,
	//SVCDisplayCurrLine		= 18,

	//Millisecond timer
	//SVCMtimerStartEv		= 19,
	//SVCMtimerStartPoll		= 20,
	//SVCMtimerStop			= 21,
	//SVCMtimerRead			= 22,

	//System
	//SVCSysinfo				= 23,
	
	//Update Pet
	SVCUpdateStats			=13,
	SVCSetName				=14,
	SVCReadName				=15,
	SVCSaveFile				=16,
	SVCIsNewFile			=17,
	SVCFeed					=18,
	SVCRest					=19,
	SVCPlay					=20,
	
	//Scheduler
	SVCProcessCreate		= 27,
	SVCThreadCreate			= 28,
	SVCProcessStop			= 29,
	
	//Parallel IO
	SVCPIOCreatePin			= 31,
	SVCPIOWritePin			= 32,
	SVCPIOReadPin			= 33,
	SVCPIOSetPinDir			= 34,
	
	//PWM
	SVCPWMChannelStart		= 38,
	SVCPWMChannelWrite		= 39,
	SVCPWMChannelStop		= 40,
	
	//ADC
	SVCADCChannelStart		= 45,
	SVCADCChannelEnable		= 46,
	SVCADCChannelDisable	= 47,
	SVCADCChannelStatus		= 48,
	SVCADCChannelRead		= 49,
	
	//SDcard
	SVCSdCardRead			=50,
	SVCSdCardWrite			=51
	
};



#endif /* SYSCALLS_H_ */