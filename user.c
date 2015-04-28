/*
** SCCS ID:	@(#)user.c	1.1	4/17/15
**
** File:	?
**
** Author:	CSCI-452 class of 20145
**
** Contributor: Ernesto Soltero
**		Nick Jenis
**		Max Roth
**			
** Description:	User routines.
*/

#include "common.h"

#include "ulib.h"
#include "user.h"

#include "c_io.h"

/*
** USER PROCESSES
**
** Each is designed to test some facility of the OS; see the user.h
** header file for a description of which system calls are used by
** each user process.
**
** Output from user processes is always alphabetic.  Uppercase 
** characters are "expected" output; lowercase are "erroneous"
** output.
**
** More specific information about each user process can be found in
** the header comment for that function (below).
**
** To spawn a specific user process, uncomment its SPAWN_x
** definition in the user.h header file.
*/

/*
** Prototypes for all one-letter user main routines (even
** ones that may not exist, for completeness)
*/

void user_a( void ); void user_b( void ); void user_c( void );
void user_d( void ); void user_e( void ); void user_f( void );
void user_g( void ); void user_h( void ); void user_i( void );
void user_j( void ); void user_k( void ); void user_l( void );
void user_m( void ); void user_n( void ); void user_o( void );
void user_p( void ); void user_q( void ); void user_r( void );
void user_s( void ); void user_t( void ); void user_u( void );
void user_v( void ); void user_w( void ); void user_x( void );
void user_y( void ); void user_z( void );

void helloCommand( void ); void lsCommand( void );

/*
** Users A, B, and C are identical, except for the character they
** print out via write( FD_SIO,).  Each prints its ID, then loops 30
** times delaying and printing, before exiting.  They also verify
** the status return from write( FD_SIO,).
*/

void user_a( void ) {
	int i, j, ch;

	write( FD_CONSOLE, "User A running\n", 0 );
	ch = write( FD_SIO, "A", 1 );
	if( ch != 1 ) {
		write( FD_CONSOLE, "User A, write 1\n", 0 );
	}
	for( i = 0; i < 30; ++i ) {
		for( j = 0; j < DELAY_STD; ++j )
			continue;
		ch = write( FD_SIO, "A", 1 );
		if( ch != 1 ) {
			write( FD_CONSOLE, "User A, write 2\n", 0 );
		}
	}

	write( FD_CONSOLE, "User A exiting\n", 0 );
	exit();

	ch = write( FD_SIO, "a", 1 );	/* shouldn't happen! */
	if( ch != 1 ) {
		write( FD_CONSOLE, "User A, write 3\n", 0 );
	}
}

void user_b( void ) {
	int i, j, ch;

	write( FD_CONSOLE, "User B running\n", 0 );
	ch = write( FD_SIO, "B", 1 );
	if( ch != 1 ) {
		write( FD_CONSOLE, "User B, write 1\n", 0 );
	}
	for( i = 0; i < 30; ++i ) {
		for( j = 0; j < DELAY_STD; ++j )
			continue;
		ch = write( FD_SIO, "B", 1 );
		if( ch != 1 ) {
			write( FD_CONSOLE, "User B, write 2\n", 0 );
		}
	}

	write( FD_CONSOLE, "User B exiting\n", 0 );
	exit();

	ch = write( FD_SIO, "b", 1 );	/* shouldn't happen! */
	if( ch != 1 ) {
		write( FD_CONSOLE, "User B, write 3\n", 0 );
	}
}

void user_c( void ) {
	int i, j, ch;

	write( FD_CONSOLE, "User C running\n", 0 );
	ch = write( FD_SIO, "C", 1 );
	if( ch != 1 ) {
		write( FD_CONSOLE, "User C, write 1\n", 0 );
	}
	for( i = 0; i < 30; ++i ) {
		for( j = 0; j < DELAY_STD; ++j )
			continue;
		ch = write( FD_SIO, "C", 1 );
		if( ch != 1 ) {
			write( FD_CONSOLE, "User C, write 2\n", 0 );
		}
	}

	write( FD_CONSOLE, "User C exiting\n", 0 );
	exit();

	ch = write( FD_SIO, "c", 1 );	/* shouldn't happen! */
	if( ch != 1 ) {
		write( FD_CONSOLE, "User B, write 3\n", 0 );
	}
}

/*
** User D spawns user Z.
*/

void user_d( void ) {
	int pid;

	write( FD_CONSOLE, "User D running\n", 0 );
	write( FD_SIO, "D", 1 );

	pid = spawn( user_z );
	if( pid < 0 ) {
		write( FD_CONSOLE, "User D spawn() failed\n", 0 );
	}

	write( FD_SIO, "D", 1 );

	write( FD_CONSOLE, "User D exiting\n", 0 );
	exit();
}


/*
** Users E, F, and G test the sleep facility.
**
** User E sleeps for 10 seconds at a time.
*/

void user_e( void ) {
	int i;
	char buf[16];

	write( FD_CONSOLE, "User E (pid ", 0 );
	i = itos10( buf, get_process_info( INFO_PID, 0 ) );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, ") running\n", 0 );
	write( FD_SIO, "E", 1 );
	for( i = 0; i < 5 ; ++i ) {
		sleep( SECONDS_TO_MS(10) );
		write( FD_SIO, "E", 1 );
	}

	write( FD_CONSOLE, "User E exiting\n", 0 );
	exit();
}


/*
** User F sleeps for 5 seconds at a time.
*/

void user_f( void ) {
	int i;
	char buf[16];

	write( FD_CONSOLE, "User F (pid ", 0 );
	i = itos10( buf, get_process_info( INFO_PID, 0 ) );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, ") running\n", 0 );
	write( FD_SIO, "F", 1 );
	for( i = 0; i < 5 ; ++i ) {
		sleep( SECONDS_TO_MS(5) );
		write( FD_SIO, "F", 1 );
	}

	write( FD_CONSOLE, "User F exiting\n", 0 );
	exit();
}


/*
** User G sleeps for 15 seconds at a time.
*/

void user_g( void ) {
	int i;
	char buf[16];

	write( FD_CONSOLE, "User G (pid ", 0 );
	i = itos10( buf, get_process_info( INFO_PID, 0 ) );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, ") running\n", 0 );
	write( FD_SIO, "G", 1 );
	for( i = 0; i < 5; ++i ) {
		sleep( SECONDS_TO_MS(15) );
		write( FD_SIO, "G", 1 );
	}

	write( FD_CONSOLE, "User G exiting\n", 0 );
	exit();
}


/*
** User H is like A-C except it only loops 5 times and doesn't
** call exit().
*/

void user_h( void ) {
	int i, j;

	write( FD_CONSOLE, "User H running\n", 0 );
	write( FD_SIO, "H", 1 );
	for( i = 0; i < 5; ++i ) {
		for( j = 0; j < DELAY_STD; ++j )
			continue;
		write( FD_SIO, "H", 1 );
	}

	write( FD_CONSOLE, "User H returning without exiting!\n", 0 );
}


/*
** User J tries to spawn 2*N_PROCS copies of user_y.
*/

void user_j( void ) {
	int i;
	int pid;
	char buf[16];

	write( FD_CONSOLE, "User J running\n", 0 );
	write( FD_SIO, "J", 1 );

	for( i = 0; i < N_PROCS * 2 ; ++i ) {
		pid = spawn( user_y );
		if( pid < 0 ) {
			write( FD_SIO, "j", 1 );
			write( FD_CONSOLE, "User J spawn() #", 0 );
			pid = itos10( buf, i );
			write( FD_CONSOLE, buf, pid );
			write( FD_CONSOLE, " failed\n", 0 );
		} else {
			write( FD_SIO, "J", 1 );
		}
	}

	write( FD_CONSOLE, "User J exiting\n", 0 );
	exit();
}


/*
** User K prints, goes into a loop which runs three times, and exits.
** In the loop, it does a spawn of user_x, sleeps 30 seconds, and prints.
*/

void user_k( void ) {
	int i;
	int pid;
	char buf[16];

	write( FD_CONSOLE, "User K running\n", 0 );
	write( FD_SIO, "K", 1 );

	for( i = 0; i < 3 ; ++i ) {
		pid = spawn( user_x );
		if( pid < 0 ) {
			write( FD_CONSOLE, "User K spawn() #", 0 );
			pid = itos10( buf, i );
			write( FD_CONSOLE, buf, pid );
			write( FD_CONSOLE, " failed\n", 0 );
		} else {
			sleep( SECONDS_TO_MS(30) );
			write( FD_SIO, "K", 1 );
		}
	}

	write( FD_CONSOLE, "User K exiting\n", 0 );
	exit();
}


/*
** User L is like user K, except that it prints times and doesn't sleep
** each time, it just preempts itself.
*/

void user_l( void ) {
	int i;
	int pid;
	uint32_t time;
	char buf[16];

	time = get_system_info( SYSINFO_TIME );
	i = itos16( buf, time, 1 );
	write( FD_CONSOLE, "User L running, initial time ", 0 );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, "\n", 1 );
	write( FD_SIO, "L", 1 );

	for( i = 0; i < 3 ; ++i ) {
		pid = spawn( user_x );
		if( pid < 0 ) {
			write( FD_CONSOLE, "User L spawn() #", 0 );
			pid = itos10( buf, i );
			write( FD_CONSOLE, buf, pid );
			write( FD_CONSOLE, " failed\n", 0 );
		} else {
			sleep( 0 );
			write( FD_SIO, "L", 1 );
		}
	}

	time = get_system_info( SYSINFO_TIME );
	i = itos16( buf, time, 1 );
	write( FD_CONSOLE, "User L exiting at time ", 0 );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, "\n", 1 );
	exit();
}


/*
** User M is like A except that it runs at low priority.
*/

void user_m( void ) {
	int i, j;
	int prio;
	char buf[16];

	prio = get_process_info( INFO_PRIO, 0 );
	i = itos10( buf, prio );
	write( FD_CONSOLE, "User M running @ ", 0 );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, "\n", 1 );
	write( FD_SIO, "M", 1 );
	for( i = 0; i < 30; ++i ) {
		for( j = 0; j < DELAY_STD; ++j )
			continue;
		write( FD_SIO, "M", 1 );
	}

	write( FD_CONSOLE, "User M exiting\n", 0 );
	exit();
}


/*
** User N is like user M, except that it runs at high priority.
*/

void user_n( void ) {
	int i, j;
	int prio;
	char buf[16];

	prio = get_process_info( INFO_PRIO, 0 );
	i = itos10( buf, prio );
	write( FD_CONSOLE, "User N running @ ", 0 );
	write( FD_CONSOLE, buf, i );
	write( FD_CONSOLE, "\n", 1 );
	write( FD_SIO, "N", 1 );
	for( i = 0; i < 30; ++i ) {
		for( j = 0; j < DELAY_STD; ++j )
			continue;
		write( FD_SIO, "N", 1 );
	}

	write( FD_CONSOLE, "User N exiting\n", 0 );
	exit();
}


/*
** User P runs forever, sleeping for 15 seconds at a time.
*/

void user_p( void ) {

	write( FD_CONSOLE, "User P running\n", 0 );
	for(;;){
		sleep( SECONDS_TO_MS(15) );
		write( FD_SIO, "P", 1 );
	}

	write( FD_CONSOLE, "User P exiting!?!?!\n", 0 );
	exit();
}


/*
** User Q does a bogus system call
*/

void user_q( void ) {

	write( FD_CONSOLE, "User Q running\n", 0 );
	write( FD_SIO, "Q", 1 );
	bogus();
	write( FD_SIO, "q", 1 );
	write( FD_CONSOLE, "User Q returned from bogus syscall!?!?!\n", 0 );
	exit();

}


/*
** User R loops 3 times reading/writing, then exits.
*/

void user_r( void ) {
	int ch;
	char buf[16];

	write( FD_CONSOLE, "User R running\n", 0 );
	sleep( SECONDS_TO_MS(10) );
	for( int i = 0; i < 3; ++i ) {
		do {
			write( FD_SIO, "R", 1 );
			ch = read( FD_SIO, buf, 1 );
			if( ch < 1 ) {	/* wait a bit */
				write( FD_SIO, "r", 1 );
				sleep( SECONDS_TO_MS(1) );
			}
		} while( ch < 1 );
		write( FD_SIO, buf, 1 );
	}

	write( FD_CONSOLE, "User R exiting\n", 0 );
	exit();

}


// no user S, T, U, or V

/*
** User X prints X characters 20 times.  It is spawned multiple
** times, and prints its PID and PPID when started and exiting.
*/

void user_x( void ) {
	int i, j;
	int pid, ppid;
	char buf1[16], buf2[16];

	pid = get_process_info( INFO_PID, 0 );
	ppid = get_process_info( INFO_PPID, 0 );
	i = itos10( buf1, pid );
	j = itos10( buf2, ppid );
	write( FD_CONSOLE, "User X running, PID ", 0 );
	write( FD_CONSOLE, buf1, i );
	write( FD_CONSOLE, " PPID ", 0 );
	write( FD_CONSOLE, buf2, j );
	write( FD_CONSOLE, "\n", 1 );

	for( int k = 0; k < 20 ; ++k ) {
		write( FD_SIO, "X", 1 );
		for( int k2 = 0; k2 < DELAY_STD; ++k2 )
			continue;
	}

	write( FD_CONSOLE, "User X exiting, PID ", 0 );
	write( FD_CONSOLE, buf1, i );
	write( FD_CONSOLE, " PPID ", 0 );
	write( FD_CONSOLE, buf2, j );
	write( FD_CONSOLE, "\n", 1 );
	exit();

}


/*
** User Y prints Y characters 10 times.
*/

void user_y( void ) {
	int i, j;

	write( FD_CONSOLE, "User Y running\n", 0 );
	for( i = 0; i < 10 ; ++i ) {
		write( FD_SIO, "Y", 1 );
		for( j = 0; j < DELAY_ALT; ++j )
			continue;
		sleep( SECONDS_TO_MS(1) );
	}

	write( FD_CONSOLE, "User Y exiting\n", 0 );
	exit();

}


/*
** User Z prints Z characters 10 times.
*/

void user_z( void ) {
	int n;
	int pid, ppid;
	char buf1[16], buf2[16];

	pid = get_process_info( INFO_PID, 0 );
	ppid = get_process_info( INFO_PPID, 0 );
	n = itos10( buf1, pid );
	pid = n;
	n = itos10( buf2, ppid );
	ppid = n;

	write( FD_CONSOLE, "User Z running, PID ", 0 );
	write( FD_CONSOLE, buf1, pid );
	write( FD_CONSOLE, " PPID ", 0 );
	write( FD_CONSOLE, buf2, ppid );
	write( FD_CONSOLE, "\n", 1 );
	for( int i = 0; i < 10 ; ++i ) {
		write( FD_SIO, "Z", 1 );
		for( int j = 0; j < DELAY_STD; ++j )
			continue;
	}

	write( FD_CONSOLE, "User Z exiting, PID ", 0 );
	write( FD_CONSOLE, buf1, pid );
	write( FD_CONSOLE, " PPID ", 0 );
	write( FD_CONSOLE, buf2, ppid );
	write( FD_CONSOLE, "\n", 1 );
	exit();

}


/*
** SYSTEM PROCESSES
*/



/*
** init - the initial user process
**
** starts the other top-level user processes
*/

void init( void ) {
//	int16_t pid;

	write( FD_CONSOLE, "Init started\n", 0 );

//	write( FD_SIO, "$", 1 );

#ifdef SPAWN_A
	pid = spawnp( user_a, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user A failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_B
	pid = spawnp( user_b, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user B failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_C
	pid = spawnp( user_c, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user C failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_D
	pid = spawnp( user_d, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user D failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_E
	pid = spawnp( user_e, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user E failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_F
	pid = spawnp( user_f, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user F failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_G
	pid = spawnp( user_g, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user G failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_H
	pid = spawnp( user_h, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user H failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_J
	pid = spawnp( user_j, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user J failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_K
	pid = spawnp( user_k, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user K failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_L
	pid = spawnp( user_l, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user L failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_M
	pid = spawnp( user_m, PRIO_USER_LOW );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user M failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_N
	pid = spawnp( user_n, PRIO_USER_HIGH );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user N failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_P
	pid = spawnp( user_p, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user P failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_Q
	pid = spawnp( user_q, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user Q failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_R
	pid = spawnp( user_r, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user R failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_S
	pid = spawnp( user_s, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user S failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_T
	pid = spawnp( user_t, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user T failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_U
	pid = spawnp( user_u, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user U failed\n", 0 );
		exit();
	}
#endif

#ifdef SPAWN_V
	pid = spawnp( user_v, PRIO_USER_STD );
	if( pid < 0 ) {
		write( FD_CONSOLE, "init, spawnp() user V failed\n", 0 );
		exit();
	}
#endif

//	write( FD_SIO, "!", 1 );

	exit();
}

/*
** idle - what to run when there's nothing else to run
*/

void idle( void ) {

	/*
	** Go into an infinite loop at low priority, printing dot characters.
	*/

//	write( FD_SIO, ".", 1 );

	for(;;) {
		for( int i = 0; i < DELAY_LONG; ++i )
			continue;
//		write( FD_SIO, ".", 1 );
	}

	/*
	** SHOULD NEVER REACH HERE
	*/

	write( FD_CONSOLE, "+++ IDLE EXITING!?!?!\n", 0 );

	exit();
}

/*
** hello - Process to output "Hello world!" to prove we can succesfully create new processes.
*/

void hello( void ) {
	write( FD_SIO, "\nHello world!\n", 0 );

	exit();
}

int strlen(char* str) {
	char* strptr = str;

	int counter = 0;

	while(strptr != '\0') {
		counter++;
		if(counter >= 255) {
			break;
		}
		strptr++;
	}

	return counter; 
	
}

int strcmp(char* str1, char* str2) {
	write( FD_CONSOLE, "0123456789", strlen(str1));
	write( FD_CONSOLE, "0123456789", strlen(str2));

	if(strlen(str1) != strlen(str2)) {
		return 2;
	}	

	char* strptr1 = str1;
	char* strptr2 = str2;

	while(strptr1 != '\0' || strptr2 != '\0') {

		write( FD_CONSOLE, " ", 0);
		write( FD_CONSOLE, strptr1, 1);
		write( FD_CONSOLE, strptr2, 1);
		write( FD_CONSOLE, " ", 0);
		if(strptr1 != strptr2) {
			
			return 1;
		}

		strptr1++;
		strptr2++;
	}

	return 0;
}

/*
Simple hash to figure out what command is entered in shell
*/
int hashCommand(char* commandBuffer){
	int hash = 0;
	char* temp = commandBuffer;
	for(while temp != '\0') {
		hash += (int)temp;
		temp++;
		write( FD_CONSOLE, hash, 0);
	} 

	return hash;
}

void shell( void ) {

	char readBuffer[5];
	char resultBuffer[100];
	char commandBuffer[20];
	char paramBuffer[20];
	char paramBuffer2[20];
	int resBufIndex = -1;
	int gotCommand = 0; // 0 for no, 1 for yes
	int comBufIndex = 0;
	int pBufIndex = 0;
	int pBufIndex2 = 0;
	int usedSpace = 1; // Set to 1 because you can't have a space at the beginning

	char *helloCommandString = "hello";
	char *lsCommandString = "ls";
	
<<<<<<< HEAD
=======
	
>>>>>>> 7edc596f5eb4f49a65d6037ec56fdb1fce5c1d24
	while( 1 ) {
		write( FD_SIO, "$ ", 0 );
		
		while( !gotCommand ) {
			int size = read( FD_SIO, readBuffer, 5 );
			if( size != 0 ){
				for( int i = 0; i < size; ++i ) { // I'm not sure if we need this loop
					// Only allow 1 space
					if( readBuffer[i] == ' ' ) {
						if( usedSpace ) continue;
						else usedSpace = 1;
					} else usedSpace = 0;

					resBufIndex++;
					write( FD_CONSOLE, &readBuffer[i], 1 ); // Echo the char
					write( FD_SIO, &readBuffer[i], 1 );
					if(readBuffer[i] == '\n' || readBuffer[i] == '\r') {
						gotCommand = 1;
// This might need to be changed to handle hitting enter and typing immediatly while waiting for us to handle the previous command.
						break;
					}
					resultBuffer[resBufIndex] = readBuffer[i];
					
				}
			} else { // Sleep if we didn't get any characters, Though this will give the idle process time to run, which is kind of bad becuase it puts characters on the screen, though we can change that.
				//sleep( SECONDS_TO_MS(.5) );
			}
		}
		//write( FD_CONSOLE, resultBuffer, resBufIndex);
		//write( FD_CONSOLE, "\n", 0);

		// Skip the rest of the code here if the user entered nothing
		if(resBufIndex == 0) {
			gotCommand = 0;
			resBufIndex = -1;
			usedSpace = 1;
			continue;
		}
	
		//splitCommand( resultBuffer, &resBufIndex, commandBuffer, &comBufIndex, paramBuffer, &pBufIndex, paramBuffer2, &pBufIndex2);
	
		// This code splits the entered command into at most 3 space separated words.
		// The first word is assumed to be the command, and the other 2 are parameters.
		// This probably could be split into its own function as I started to do above,
		// but that will require some parameter passing.	
		int doneCommand = 0;
		int doneParam1 = 0;
		int doneParam2 = 0;
		for( int i = 0; i < resBufIndex; ++i ) {
			if( resultBuffer[i] == ' ' ) {
				if( !doneCommand ) doneCommand = 1;
				else if( !doneParam1 ) doneParam1 = 1;
				else if( !doneParam2 ) doneParam2 = 1;
				else write( FD_CONSOLE, "Ignoring extra spaces!", 0 );

				continue;
			}

			if (!doneCommand) {
				commandBuffer[comBufIndex] = resultBuffer[i];
				comBufIndex++;
			}

			else if( !doneParam1 ) {
				paramBuffer[pBufIndex] = resultBuffer[i];
				pBufIndex++;
			}
			else if( !doneParam2 ) {
				paramBuffer2[pBufIndex2] = resultBuffer[i];
				pBufIndex2++;
			}
			else {
				write( FD_CONSOLE, "Ignoring extra params!", 0 );
			}
		}
		// Null terminate buffer.
		commandBuffer[comBufIndex] = '\0';
		paramBuffer[pBufIndex] = '\0';
		paramBuffer2[pBufIndex2] = '\0';
		

		// Here we have split the entered command into the actual command
		// and 2 parameters, if there were any.
		// Just printing them out to the console for us to see.
		write( FD_CONSOLE, "CommandBuffer\n", 0);
		write( FD_CONSOLE, commandBuffer, 0 );
		write( FD_CONSOLE, "\nParamBuffer1\n", 0);
		(pBufIndex > 0 ? write( FD_CONSOLE, paramBuffer, 0 ) : write(FD_CONSOLE, "empty", 0));
		write( FD_CONSOLE, "\nParamBuffer2\n", 0);
		(pBufIndex2 > 0 ? write( FD_CONSOLE, paramBuffer2, 0 ) : write(FD_CONSOLE, "empty", 0));
		write(FD_CONSOLE, "\n", 0);


		// Now we need to check what command the user entered.
		// Again, this probably would make sense to separate into another function.
<<<<<<< HEAD
		//checkCommand(resultBuffer

		/*easier way of doing it hash the command and we can figure out what it is
		int hash = hashCommand(commandBuffer);

		switch(hash) {
			//ls command
			case 223:
					
			//hello command
			case 532:
				int16_t pid = spawnp( helloCommand, PRIO_USER_HIGH);
				if( pid < 0) {
					write( FD_CONSOLE, "init, spawn() hello failed\n", 0);
					exit();
				}
				break;
			//cd command
			case 199:
			//mkdir command
			case 535:
			//create file command
			case 628:
			default:
				write(FD_CONSOLE, "command not recognized: ", 0);
				write(FD_CONSOLE, hash, 4);
				write(FD_CONSOLE, "\n", 0);	
		}
		*/
		int isHello = 0;
=======
		// TODO HASH function here
		int res = 1;
		if(res == 0) {
			int16_t pid;
			pid = spawnp( helloCommand, PRIO_USER_HIGH );
			if( pid < 0 ) {
				write( FD_CONSOLE, "init, spawnp() hello failed\n", 0 );
				exit();
			}
		}
		else {
			write(FD_CONSOLE, "res !=0", 0);
		}
/*
>>>>>>> 7edc596f5eb4f49a65d6037ec56fdb1fce5c1d24
		if(comBufIndex == 5) {
			for(int i = 0; i < 5; ++i) {
				if(commandBuffer[i] != helloCommandString[i]) break;
				if( i == 4 ) isHello = 1; // There's got to be a better way
			}
		}

		if(isHello) {
			int16_t pid;
			pid = spawnp( helloCommand, PRIO_USER_HIGH );
			if( pid < 0 ) {
				write( FD_CONSOLE, "init, spawnp() hello failed\n", 0 );
				exit();
			}
			isHello = 0;
		}
*/

		// Reset the parameters and wait for the next command to be entered
		gotCommand = 0;
		resBufIndex = -1;
		usedSpace = 1;
		comBufIndex = 0;
		pBufIndex = 0;
		pBufIndex2 = 0;
		

		// Should we sleep for a quarter of a second to let the spawned process run?
		// This also helps to put this next $ symbol on the line after the process
		sleep( SECONDS_TO_MS(.25) );
		
	}
}

/*
** "Hello World" type process to test process creation and command matching in the shell.
*/
void helloCommand( void ) {

	write(FD_CONSOLE, "\nIn Hello Command\n", 0);
	write(FD_SIO, "\nhello command\n", 0);

	exit();
}

/*
** Placeholder ls command process. For now just outputs sample text...
*/
void lsCommand( void ) {
	
	write(FD_CONSOLE, "\nIn ls Command\n", 0);
	write(FD_SIO, "\n  File Info...\n  file1.txt   file2.txt\n", 0);
	exit();
}

/*
void splitCommand(char *resultBuffer, int *resBufIndex, char *commandBuffer, int *comBufIndex, char *paramBuffer, int *pBufIndex, char *paramBuffer2, int *pBufIndex2) {
	int doneCommand = 0;
	int doneParam1 = 0;

	for( int i = 0; i < (*resBufIndex); ++i ) {
		if( resultBuffer == ' ' ) {
			if( !doneCommand ) doneCommand = 1;
			else if ( !doneParam1 ) doneParam1 = 1;
			else write( FD_CONSOLE, "Too many spaces!", 0 );
		}

		if (!doneCommand) {
			
		
		}


	}
}

*/














