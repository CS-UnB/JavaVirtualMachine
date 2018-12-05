/*! \file interfaces.h
	\brief Interfaces

	Manipula as informações de interface do .class
*/

#ifndef INTERFACES
#define INTERFACES

#include <iostream>
#include "constantPool.h"
#include "baseTypes.h"

/** @fn unsigned short *readInterfaces (FILE *fp, int length)
	@brief Carrega as interfaces na memória a partir do arquivo class.
	@param flags Flags em haxadecimal que serão convertidas para string.
	@param fp Ponteiro para o arquivo class.
	@param length Numero de interfaces a serem lidas.
*/
unsigned short *readInterfaces (FILE *fp, int length);


/** @fn void printInterfaces (unsigned short *interfaces, cp_info *cp, int length)
	@brief Mostra todas as interfaces do arquivo.

	@param interfaces Array de interfaces.
	@param cp Ponteiro para a constantpool.
	@param length Número de interfaces.
*/
void printInterfaces (unsigned short *interfaces, cp_info *cp, int length);


/** @fn printInterface (unsigned short interface, cp_info *cp)
	@brief Mostra informações de uma interface específica.

	@param interface Indice do constantpool.
	@param cp Ponteiro para a constantpool.
*/
void printInterface (unsigned short interface, cp_info *cp);


/** @fn printInterface (unsigned short interface, cp_info *cp, int index)
	@brief Mostra informação de uma interface específica com o índice da interface.

	@param interface Indice do constantpool.
	@param cp Ponteiro para o constantpool.
	@param index Indice da interface específica.
*/
void printInterface (unsigned short interface, cp_info *cp, int index);


#endif
