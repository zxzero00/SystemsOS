/*
** File:	fileSystem.c
**
** Authors:	Max Roth, Nicholas Jenis, Ernesto Soltero
**
** Description:	Implementation of Simple File System
*/

#include "types.h"
#include "fileSystem.h"

/*
** Create and initialize a file system, returning it's representative
** sfs_file_table structure
*/
void sfs_init( void ) {

	//Set file system to a point 1 gig into the RAM
	fileSystem = (void *)0x40000000;

	//*fileSystem = (sfs_file_table*) malloc(sizeof(sfs_file_table)); //find malloc equivalent

	//Find another way to do this, not neccesary but would be nice
	//memset(filesys, 0, sizeof(&filesys));
	//filesys->current_location = -1;
}

sfs_file_table* get_fileSystem( void ) {
	return fileSystem;
}