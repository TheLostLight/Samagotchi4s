.equ	SVCLedSet,		    0
.equ	SVCLedRead,		    1
.equ	SVCButtonRead,      2
.equ	SVCClockRead,	    3
.equ	SVCClockWrite,	    4
.equ	SVCDisplayCls,      9
.equ	SVCDisplayPutc,     10
.equ	SVCDisplayGotoxy,   11
.equ	SVCDisplayNumLines, 12
.equ	SVCUpdateStats,     13
.equ	SVCSetName,         14
.equ	SVCReadName,        15
.equ	SVCSaveFile,        16
.equ	SVCIsNewFile,       17
.equ	SVCFeed,            18
.equ	SVCRest,            19
.equ    SVCPlay,            20
.equ	SVCStartTime,       21
.equ	SVCStopTime,        22

.thumb_func 
.global led_set
led_set:
	svc SVCLedSet
	bx lr

.thumb_func
.global led_read
led_read:
	svc SVCLedRead
	bx lr

.thumb_func
.global button_read
button_read:
	svc SVCButtonRead
	bx lr

.thumb_func
.global clock_read
clock_read:
	svc SVCClockRead
	bx lr

.thumb_func
.global clock_write
clock_write:
	svc SVCClockWrite
	bx lr

.thumb_func
.global display_cls
display_cls:
	svc SVCDisplayCls
	bx lr

.thumb_func
.global display_putc
display_putc:
	svc SVCDisplayPutc
	bx lr

.thumb_func
.global display_gotoxy
display_gotoxy:
	svc SVCDisplayGotoxy
	bx lr

.thumb_func
.global display_numlines
display_numlines:
	svc SVCDisplayNumLines
	bx lr

.thumb_func
.global update_stats
update_stats:
	svc SVCUpdateStats
	bx lr

.thumb_func
.global set_name
set_name:
	svc SVCSetName
	bx lr

.thumb_func
.global read_name
read_name:
	svc SVCReadName
	bx lr

.thumb_func
.global save_file
save_file:
	svc SVCSaveFile
	bx lr

.thumb_func
.global is_new_file
is_new_file:
	svc SVCIsNewFile
	bx lr

.thumb_func
.global feed
feed:
	svc SVCFeed
	bx lr

.thumb_func
.global rest
rest:
	svc SVCRest
	bx lr

.thumb_func
.global play
play:
	svc SVCPlay
	bx lr

.thumb_func
.global draw
draw:
	svc SVCDraw
	bx lr

.thumb_func
.global start_time
start_time:
	svc SVCStartTime
	bx lr

.thumb_func
.global stop_time
stop_time:
	svc SVCStopTime
	bx lr
