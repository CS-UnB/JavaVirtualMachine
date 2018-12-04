/*! \file interfaces.h
	\brief Interfaces

	Manipula as informações de interface do .class
*/

#ifndef INTERFACES
#define INTERFACES

#include <iostream>
#include "constantPool.h"
#include "baseTypes.h"

/*! \fn unsigned short *readInterfaces (FILE *fp, int length)
	\brief Load the interfaces to the memory

	\param fp Pointer to the .class file
	\param length Number of interfaces
*/
unsigned short *readInterfaces (FILE *fp, int length);


/*! \fn void printInterfaces (unsigned short *interfaces, cp_info *cp, int length)
	\brief Show all interfaces from the file

	\param interfaces Array of interfaces.
	\param cp Pointer to the constant pool.
	\param length Number of interfaces.
*/
void printInterfaces (unsigned short *interfaces, cp_info *cp, int length);


/*! \fn printInterface (unsigned short interface, cp_info *cp)
	\brief Show information from a especific interface

	\param interface Index of the constant pool.
	\param cp Pointer to the constant pool.
*/
void printInterface (unsigned short interface, cp_info *cp);


/*! \fn printInterface (unsigned short interface, cp_info *cp, int index)
	\brief Show information from a especific interface with the interface index

	\param interface Index of the constant pool.
	\param cp Pointer to the constant pool.
	\param index Index of the specific interface.
*/
void printInterface (unsigned short interface, cp_info *cp, int index);


#endif
