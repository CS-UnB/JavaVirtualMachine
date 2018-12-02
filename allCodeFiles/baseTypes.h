/*! \file baseTypes.h
	\brief Tipos Base 

	Tipos básicos utilizados para implementarmos a JVM.
*/

/*! \def BASE
	\brief Macro

	Define utilizado para evitar múltiplas inclusões desse arquivo.
*/
#ifndef BASE
#define BASE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

#define Float_NaN 0x7f800001
#define Float_PlusInfinity 0x7f800000
#define Float_MinusInfinity 0xff800000
#define Double_NaN 0x7ff0000000000001L 
#define Double_PlusInfinity 0x7ff0000000000000L
#define Double_MinusInfinity 0xfff0000000000000L

#define RT_BYTE 1
#define RT_BOOL 2
#define RT_CHAR 3
#define RT_SHORT 4
#define RT_INT 5
#define RT_FLOAT 6
#define RT_DOUBLE 7
#define RT_REFERENCE 8
#define RT_LONG 9

typedef uint8_t U1;
typedef uint16_t U2;
typedef uint32_t U4;

/*! \union ClassLoaderType
	\brief Storage structure

	Union responsable for store every variable sizes that will be read.
*/	

typedef union {
	U1 *array; //ponteiro para uma string
	U1 u1; //8 bytes
	U2 u2; //16 bytes
	U4 u4; //32 bytes
} ClassLoaderType;

/*! \union element_u
	\brief Generalization of return/input functions

	Union responsable for generalize functions of return and one of input function.
*/	

typedef union element_u {
	double d;
	float f;
	uint32_t i;
	int32_t is;
	uint64_t l;
	int64_t ls;
	uint16_t s;
	int16_t ss;
	uint8_t b;
	int8_t bs;
	int* pi;
} element;

typedef struct {
	int* dims;
	int* array; 
} n_array;


/*! \struct typedElement_s
	\brief Aggregator of type and information

	Struct responsable for join type with information of element.
*/	

typedef struct typedElement_s {
	element value;
	uint8_t type;
	uint8_t realType;
} typedElement;

/*! \fn U1 readU1 (FILE *fp)
	\brief Function to read 1 byte of archive

	\param fp. Pointer to .class archive.
*/
U1 readU1 (FILE *fp);

/*! \fn U2 readU2 (FILE *fp)
	\brief Function to read 2 byte of archive

	\param fp Pointer to .class archive.
*/
U2 readU2 (FILE *fp);

/*! \fn U4 readU4 (FILE *fp)
	\brief Function to read 4 byte of archive

	\param fp Pointer to .class archive.
*/
U4 readU4 (FILE *fp);

/*! \fn U1 * readUTF8 (FILE* fp, int size)
	\brief Função para ler os bytes de uma string UTF-8

	\param fp Pointer to .class archive.
	\param size Size of what will be allocated.
*/
U1 * readUTF8 (FILE* fp, int size);

/*! \fn string showUTF8 (unsigned char * s, int size)
	\brief Funtion to assembly and show a UTF-8 string

	\param s Pointer to initial position of Unicode string. 
	\param size Size of what will be printed at screen.
*/

string showUTF8 (unsigned char * s, int size);

/*! \fn int checkFloat(float)
	\brief Function to check infinity and Not a Number at floats

	\param float Number to be checked.
*/

int checkFloat(float);

/*! \fn int checkDouble(double)
	\brief Function to check infinity and Not a Number at floats

	\param float Number to be checked.
*/

int checkDouble(double);

/*! \fn string float_to_string(float)
	\brief Function to convert a float to string

	\param double Number to be converted.

*/

string float_to_string(float);

/*! \fn string double_to_string(double)
	\brief Function to convert a double to string

	\param float Number to be converted.
*/

string double_to_string(double);

/*! \fn float u4_to_float (ClassLoaderType in)
	\brief Function to convert 4 bytes to a float

	\param in Four bytes to be converted.
*/

float u4_to_float (ClassLoaderType in);

/*! \fn long u4_to_long (ClassLoaderType high, ClassLoaderType low)
	\brief Function to convert 8 bytes to a long

	\param high Four most significant bytes to be converted.
	\param low Four last significant bytes to be converted.
*/

long u4_to_long (ClassLoaderType high, ClassLoaderType low);


/*! \fn double u4_to_double (ClassLoaderType high, ClassLoaderType low)
	\brief Function to convert 8 bytes to a double

	\param high Four most significant bytes to be converted.
	\param low Four last significant bytes to be converted.
*/

double u4_to_double (ClassLoaderType high, ClassLoaderType low);


#endif