/** @file attributes.h
	@brief Atributos a serem usados na execuçao da JVM 
*/

/** @def ATTRIBUTE
	@brief
*/

#ifndef ATTRIBUTE
#define ATTRIBUTE

#include <iostream>
#include <stdlib.h>
#include <string>
#include "constantPool.h"

using namespace std;
/**
*	Protótipo da struct "attribute_info"
*/
struct attribute_info;

/** @struct constantvalue_attribute
*	@brief Struct para carregar o index dos atributos da "constantpool"
*/
typedef struct 
{
	unsigned short constantvalue_index;
} constantvalue_attribute;

/** @struct t_exception_table
*	@brief Struct para salvar exceções identificadas. Será utilizada
*	como componente da struct "code_attribute"
*/	
typedef struct 
{
	unsigned short start_pc;
	unsigned short end_pc;
	unsigned short handler_pc;
	unsigned short catch_type;
} t_exception_table;

/** @struct code_attribute
*	@brief Estrutura de dados para salvar atributos do tipo code
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

/** @struct code_attribute
*	@brief Estrutura de dados para salvar atributos de tipo "exception"
*/	
typedef struct 
{
	unsigned short number_of_exceptions;
	unsigned short* exception_index_table;
} exception_attribute;

/** @union t_info
*	@brief Estrutura de dados que agrega informações sobre cada atributo lido
*/	
typedef union 
{
	constantvalue_attribute constantvalue;
	code_attribute code;
	exception_attribute exception;
} t_info;

/** @struct attribute_info
*	@brief Estrutura de dados para salvar a posição do atributo na constantpool e seu tamanho
*/	
struct attribute_info 
{
	unsigned short name_index;
	unsigned int length;

	t_info* info;
};

/** @fn t_exception_table* readExceptionHandler(FILE* fp)
*	@brief Função de leitura de exceções
*	@param fp Ponteiro para arquivo tipo .class
*/
t_exception_table* readExceptionHandler(FILE* fp);

/** @fn t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length)
*	@brief Faz a leitura das informações de um atributo
*	@param fp Ponteirp para arquivo .class.
*	@param cp Ponteiro pra constantpool.
*	@param Posição do atributo na constantpool.
*	@param Tamanho em bytes do atributo a ser lido.
*/
t_info* readAttributeInfo(FILE* fp, cp_info *cp, unsigned short index, unsigned short length);

/** @fn attribute_info readAttribute (FILE* fp, cp_info *cp)
*	@brief Faz a leitura de um atributo da constantpool.
*	@param fp Ponteiro pro arquivo .class.
*	@param cp Pointeiro pra constantpool.
*/
attribute_info readAttribute (FILE* fp, cp_info *cp);

/** @fn attribute_info* readAttributes(FILE* fp, cp_info *cp, int length)
*	@brief Faz a leitura de n atributos da constantpool
*	@param fp Ponteiro pro arquivo .class.
*	@param cp Poteiro pra constant pool.
*	@param length Número de atributos.
*/
attribute_info* readAttributes(FILE* fp, cp_info *cp, int length);

/** @fn void printAttribute (attribute_info a, cp_info *cp)
*	@brief Função que imprime na tela informações de um atributo.
*	@param cp Poteiro pra constant pool.
*/
void printAttribute (attribute_info a, cp_info *cp);

/** @fn void printAttributes(attribute_info* attributes, cp_info* cp, int length)
*	@brief Função que imprime na tela informações de n atributos
*	@param attributes Pointer to struct of types att.
*	@param cp Poteiro pra constant pool.
*	@param length Number of times of the function printAttribute gonna be called.
*/
void printAttributes(attribute_info* attributes, cp_info* cp, int length);

/** @fn string getMnemonic(int opcode)
*	@brief Returna o nome da operação.
*	@param opcode Opcode de operações da JVM
*/
string getMnemonic(int opcode);

/** @fn uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index)
*	@brief Função para retornar o conteúdo dos próximos n bytes  
*	@param n Número de bytes a serem lidos.
*	@param code Ponteiro pra um vetor de bytes.
*	@param index Posição do opcode no vetor.
*/
uint32_t getNBytesValue(uint8_t n, unsigned char* code, int* index);

/** @fn void getOpcodeParams(unsigned char* code, int* index)
*	@brief Função que mostra na tela os parâmetros dos opcodes
*	@param code Pointer of bytes wich are code and your arg. Ponteiro para vetor de bytes do código e seus parâemtros.
*	@param index Posição na constantpool.
*/
void getOpcodeParams(unsigned char* code, int* index);

#endif
