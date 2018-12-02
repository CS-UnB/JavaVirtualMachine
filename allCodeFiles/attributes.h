/*! \file attributes.h
	\brief Atributos 
*/

/*! \def ATTRIBUTE
	\brief
*/

#ifndef ATTRIBUTE
#define ATTRIBUTE

#include <iostream>
#include <stdlib.h>
#include <string>
#include "constantPool.h"

using namespace std;
/*!
	Prototype of struct attribute_info
*/
struct attribute_info;

/*! \struct constantvalue_attribute
	\brief Struct to load.
	Struct responsable to save att. of type constatvalue
*/
typedef struct 
{
	unsigned short constantvalue_index;
} constantvalue_attribute;

/*! \struct t_exception_table
	\brief Componente de outra struct

	Struct de Exception que faz parte da struct code_attribute
*/	
typedef struct 
{
	unsigned short start_pc;
	unsigned short end_pc;
	unsigned short handler_pc;
	unsigned short catch_type;
} t_exception_table;

/*! \struct code_attribute
	\brief 
	Struct responsable to save att. of type code
*/	
typedef struct 
{
	unsigned short max_stack;
	unsigned short max_locals;
	unsigned int code_length;
	unsigned char* code;
	unsigned short exception_table_length;
	t_exception_table** exception_table;
	unsigned short attribute_count;
	attribute_info* attributes;
} code_attribute;

/*! \struct code_attribute
	\brief COmponet of another struct
	Struct responsable to save att. of type execption
*/	
typedef struct 
{
	unsigned short number_of_exceptions;
	unsigned short* exception_index_table;
} exception_attribute;

/*! \union t_info
	\brief Representação de diferentes atributos
	
	Union responsable reoresent diferent fields of att.
*/	
typedef union 
{
	constantvalue_attribute constantvalue;
	code_attribute code;
	exception_attribute exception;
} t_info;

/*! \struct attribute_info
	\brief Struct to save	
	Struct responsable to save os att.
*/	
struct attribute_info 
{
	unsigned short name_index;
	unsigned int length;

	t_info* info;
};

/*! \fn t_exception_table* readExceptionHandler(FILE* fp)
	\brief Function to read the exception
	\param fp Ponter to file .class
*/
t_exception_table* readExceptionHandler(FILE* fp);

/*! \fn t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length)
	\brief Read the info of att

	\param fp POinter to .class file.
	\param cp Pointer to constant pool.
	\param index point to element of constant pool.
	\param length Size in bytes of att. who gonna be read.
*/
t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length);

/*! \fn attribute_info readAttribute (FILE* fp, cp_info *cp)
	\brief Read the att.

	\param fp Pointer to .class file.
	\param cp Pointer to constant pool.
*/
attribute_info readAttribute (FILE* fp, cp_info *cp);

/*! \fn attribute_info* readAttributes(FILE* fp, cp_info *cp, int length)
	\brief Read the attribute

	\param fp Pointer .class file.
	\param cp Pointer to constant pool.
	\param length Number of att.
*/
attribute_info* readAttributes(FILE* fp, cp_info *cp, int length);

/*! \fn void printAttribute (attribute_info a, cp_info *cp)
	\brief Function to show to user an att.
	\param cp Pointer to constant pool.

*/
void printAttribute (attribute_info a, cp_info *cp);

/*! \fn void printAttributes(attribute_info* attributes, cp_info* cp, int length)
	\brief Function calls printAttribute length times

	\param attributes Pointer to struct of types att.
	\param cp Pointer to constant pool.
	\param length Number of times of the function printAttribute gonna be called.
*/
void printAttributes(attribute_info* attributes, cp_info* cp, int length);

/*! \fn string getMnemonic(int opcode)
	\brief Return the name of operation
	\param opcode Opcode of some JVM's function.
*/
string getMnemonic(int opcode);

/*! \fn uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index)
	\brief Function which returns a value 
	\param n NUmber of bytes wanted to read.
	\param code Pointer of bytes .
	\param index Index point to addres of opcode parameter.
*/
uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index);

/*! \fn void getOpcodeParams(unsigned char* code, int* index)
	\brief Função que mostra na tela os parâmetros dos opcodes
	\brief Function shows on screen parameter of opcodes
	\param code Pointer of bytes wich are code and your arg.
	\param index Index point to address.
*/
void getOpcodeParams(unsigned char* code, int* index);

#endif
