/** @file constantPool.h
	@brief Módulo Constant pool

	@details Este módulo contém as funções necessárias para a manipulação do pool de constantes.
*/

/** @def CONSTANTPOOL 
	@brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef CONSTANTPOOL
#define CONSTANTPOOL

#include "baseTypes.h"

using namespace std;

/** @struct cp_info
	@brief Possui um elemento pool de constante.
*/	
typedef struct {
	U1 tag;
	ClassLoaderType *info;
} cp_info;


/// Formatos de dados no pool de constantes
const string typeNames[] = {"UTF-8", "-", "Integer", "Float", "Long", "Double", "Class", "String", "Field", "Method", "Interface", "Name and Type"};


#define INVALID 99 
#define UTF8 1
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define CLASS 7
#define STRING 8
#define FIELD_REF 9
#define METHOD_REF 10
#define INTERFACE_REF 11
#define NAME_AND_TYPE 12


/** @fn int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp)
		@brief Carrega o pool de constantes
		@param constantPool - um ponteiro para o pool de contantes
		@param lengthCP - o tamanho do pool de constantes
		@param fp - ponteiro para o arquivo .class
		@section desc Descrição
			Função responsável por carregar o pool de constantes e todos os campos a ele relacionados
		@return o número de elementos do pool de constantes
*/
int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp);


/** @fn string dereferenceIndex (cp_info *cp, U2 index)
		@brief Retorna os dados no índice.

		@param cp - um ponteiro para o pool de contantes
		@param index - um índice para a posição no pool de constantes
		@section desc Descrição
			Função responsável por obter os dados correspondentes ao índice informado
*/
string dereferenceIndex (cp_info *cp, U2 index);


/** @fn void printConstantPool (cp_info *constantPool, int lengthCP)
		@brief Imprime o pool de constantes
		@param constantPool - um ponteiro para o pool de contantes
		@param lengthCP - o tamanho do pool de constantes
		@section desc Descrição
			Função responsável por imprimir na tela o pool de constantes e todos os campos a ele relacionados
*/
void printConstantPool (cp_info *constantPool, int lengthCP);

#endif
