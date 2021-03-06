/*
** SCCS ID:	@(#)system.c	1.1	4/17/15
**
** File:	system.c
**
** Author:	CSCI-452 class of 20145
**
** Contributor:
**
** Description:	Miscellaneous OS support implementations
*/

#define	__SP_KERNEL__

#include "common.h"

#include "system.h"
#include "clock.h"
#include "process.h"
#include "bootstrap.h"
#include "syscall.h"
#include "sio.h"
#include "scheduler.h"

// need address of the initial user process
#include "user.h"

// need the __default_exit__() prototype
#include "ulib.h"

// include file system
#include "fileSystem.h"

/*
** PRIVATE DEFINITIONS
*/

/*
** PRIVATE DATA TYPES
*/

/*
** PRIVATE GLOBAL VARIABLES
*/

/*
** PUBLIC GLOBAL VARIABLES
*/

/*
** PRIVATE FUNCTIONS
*/

/*
** PUBLIC FUNCTIONS
*/

/*
** _create_process(entry,prio)
**
** allocate and initialize a new process' data structures (PCB, stack)
**
** returns:
**      pointer to the new PCB
*/

pcb_t *_create_process( uint32_t entry, uint8_t prio ) {
	pcb_t *new;
	uint32_t *ptr;
	
	// allocate the new structures

	new = _pcb_alloc();
	if( new == NULL ) {
		return( NULL );
	}

	// clear all the fields in the PCB

	_memset( (void *) new, sizeof(pcb_t), 0 );

	// allocate the runtime stack

	new->stack = _stack_alloc();
	if( new->stack == NULL ) {
		_pcb_dealloc( new );
		return( NULL );
	}

	/*
	** We need to set up the initial stack contents for the new
	** process.  The low end of the initial stack must look like this:
	**
	**      esp ->  ?     <- context save area
	**              ...   <- context save area
	**              ?     <- context save area
	**              exit  <- return address for faked call to main()
	**              0     <- last word in stack
	*/

	// first, create a pointer to the longword after the stack

	ptr = (uint32_t *) (new->stack + 1);

	// save the buffering 0 at the end

	*--ptr = 0;

	// fake a return address so that if the user function returns
	// without calling exit(), we return "into" a function which
	// calls exit()

	*--ptr = (uint32_t) __default_exit__;

	// locate the context save area

	new->context = ((context_t *) ptr) - 1;

	// fill in the non-zero entries in the context save area

	new->context->eip    = entry;
	new->context->cs     = GDT_CODE;
	new->context->ss     = GDT_STACK;
	new->context->ds     = GDT_DATA;
	new->context->es     = GDT_DATA;
	new->context->fs     = GDT_DATA;
	new->context->gs     = GDT_DATA;
	new->context->eflags = DEFAULT_EFLAGS;

	// fill in the remaining important fields

	new->prio = prio;
	new->pid  = _next_pid++;
	new->default_quantum = QUANTUM_DEFAULT;
	new->state = STATE_READY;
	
	// all done - return the new PCB

	return( new );
}

/*
** _init - system initialization routine
**
** Called by the startup code immediately before returning into the
** first user process.
*/

void _init( void ) {
	pcb_t *pcb;

	/*
	** BOILERPLATE CODE - taken from basic framework
	**
	** Initialize interrupt stuff.
	*/

	__init_interrupts();	// IDT and PIC initialization

	/*
	** Console I/O system.
	*/

	c_io_init();
	c_setscroll( 0, 7, 99, 99 );
	c_puts_at( 0, 6, "================================================================================" );

	/*
	** 20145-SPECIFIC CODE STARTS HERE
	*/

	/*
	** Initialize various OS modules
	**
	** Note:  the clock, SIO, and syscall modules also install
	** their ISRs.
	*/

	c_puts( "Module init: " );

	_queue_modinit();		// must be first
	_pcb_modinit();
	_stack_modinit();
	_sched_modinit();
	_sio_modinit();
	_sys_modinit();
	_clock_modinit();
	_sfs_init();

	c_puts( "\n" );

	/*
	** Create the initial system ESP
	**
	** This will be the address of the next-to-last
	** longword in the system stack.
	*/

	_system_esp = ((uint32_t *) ( (&_system_stack) + 1)) - 2;

	/*
	** Create the initial process
	**
	** Code mostly stolen from _sys_spawnp(); if that routine
	** changes, SO MUST THIS!!!
	*/

	pcb = _create_process( (uint32_t) init, PRIO_SYSTEM );
	if( pcb == NULL ) {
		_kpanic( "_init", "init() creation failed" );
	}

	_pcb_dump( "init() pcb", pcb );
	_context_dump( "init() context", pcb->context );

	_schedule( pcb );

	/*
	** Next, create the idle process
	*/

	pcb = _create_process( (uint32_t) idle, PRIO_USER_LOW );
	if( pcb == NULL ) {
		_kpanic( "_init", "idle() creation failed" );
	}

	_schedule( pcb );

	/*
	** Turn on the SIO receiver (the transmitter will be turned
	** on/off as characters are being sent)
	*/

	_sio_enable( SIO_RX );

	/*
	** Start the hello world process, see if this thing works -- Max Roth
	*/
	
	pcb = _create_process( (uint32_t) hello, PRIO_USER_HIGH );
	if( pcb == NULL ) {
		_kpanic( "_init", "hello() creation failed" );
	}

	_schedule( pcb );

	/*
	** Send the first process off to play
	*/

	_dispatch();

	/*
	** END OF 20145-SPECIFIC CODE
	**
	** Finally, report that we're all done.
	*/

	c_puts( "System initialization complete.\n" );



	/*
	** Create the shell
	*/

	// Clear the terminal for our shell
	_sio_writec(26);

	pcb = _create_process( (uint32_t) shell, PRIO_USER_STD );
	if( pcb == NULL ) {
		_kpanic( "_init", "shell() creation failed" );
	}

	_schedule( pcb );

	//Basic file system test

	if(1){
	c_puts( "Creating file...\n" );
	int c_test = _sfs_create("/TEST.txt", FILE);
	c_puts( "File Created...\n" );

	sfs_entry* exists = _sfs_exists("/TEST.txt", FILE);
	if(compare((char*)&exists->name,ROOT) != 0)
		c_puts( "File exists...\n" );
	else
		c_puts( "uh oh...\n" );
	c_puts("E:");
	c_puts((char*)&exists->name);
	c_puts("\n");

	c_puts( "Writing to file...\n" );
	char* buf = "THIS IS FILE DATA!";
	int w_test = _sfs_write("/TEST.txt", len(buf), (uint8_t *) buf, 0);

	c_puts( "Writing to ghost file...\n" );
	char* buf2 = "THIS IS FILE DATA!";
	int g_test = _sfs_write("/ST.txt", len(buf2), (uint8_t *) buf2, 0);

	c_puts( "Read from file...\n" );
	uint8_t* buffer = _sfs_read("/TEST.txt");
	//if(buffer != 0) c_puts("YES\n");
	c_puts((char *) buffer);
	c_puts("\n");

	c_puts( "Deleting file...\n" );
	int d_test = _sfs_delete("/TEST.txt");

	c_printf("\n%x%x%x%x\n", c_test, w_test, g_test, d_test);

	c_puts(_get_directory());
	c_puts("\n");
	int z_test = _sfs_create("/hello", DIRECTORY);
	sfs_entry* exists2 = _sfs_exists("hello", DIRECTORY);
	if(compare((char*)&exists2->name,ROOT) != 0)
		c_puts( "Directory exists...\n" );
	else
		c_puts( "uh oh...\n" );
	int x_test = _set_directory("/hello");
	c_puts("Changing directory to ");
	c_puts(_get_directory());
	c_puts("\n");
	int test_1 = _sfs_create("test1.t", FILE);
	int test_2 = _sfs_create("/test2.t", FILE);
	int test_3 = _sfs_create("/hello/test3.t", FILE);
	int test_4 = _sfs_create("folder", DIRECTORY);
	int test_5 = _sfs_create("/hello/folder/test5.t", FILE);
	int test_6 = _sfs_create("/DNE/test6.t", FILE);
	int test_7 = _sfs_delete("/hello");
	
	c_printf("\n%x%x%x%x%x%x%x%x%x\n", z_test, x_test, test_1, test_2, test_3, test_4, test_5, test_6, test_7);
	
	c_puts("\nStopping on getchar()...\n");
	c_getchar();
	}
}
