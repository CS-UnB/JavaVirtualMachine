/** @file fields.h
	@brief Classe field

	Field used at archives with .class format
*/

/** @def FIELDS 
	@brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef FIELDS
#define FIELDS

#include "baseTypes.h"
#include "constantPool.h"
#include "attributes.h"

using namespace std;

/** @struct field_info
	@brief Struct de armazenamento.

	Struct responsável por armazenar os campos declarados.
*/

typedef struct {
	unsigned char accessFlags;
	unsigned char name_index;
	unsigned char descriptor_index;
	unsigned char attributes_count;
	attribute_info *attributes;
} field_info;

/** @fn string getFieldFlags(unsigned short flags)
	@brief Função para mostrar as flags dos campos

	@param flags Flags em haxadecimal que serão convertidas para string.
*/

string getFieldFlags (unsigned short flags);

/** @fn field_info readField (FILE* fp, cp_info *cp)
	@brief Função que lê um campo

	@param fp Ponteiro para arquivo .class.
	@param cp Ponteiro para pool de constantes.
*/

field_info readField (FILE* fp, cp_info *cp);


/** @fn field_info *readFields (FILE* fp, int length,cp_info *cp)
	@brief Função que aloca field_info espaço e chama readField "lenght" vezes
	

	@param fp Ponteiro para arquivo .class.
	@param cp Ponteiro para pool de constantes.
	@param length Define o número de chamadas à readField.
*/
field_info *readFields (FILE* fp, int length,cp_info *cp);


/** @fn void printField (field_info f, cp_info *cp)
	@brief Função que imprime um campo.

	@param f Struct com informações do campo.
	@param index Índice do vetor que contém um campo.
	@param cp Ponteiro para pool de constantes.
*/
void printField (field_info f, cp_info *cp, int index);

/** @fn void printFields (field_info *f, cp_info *cp, int length)
	@brief Fuunção que chama printField o número de vezes determinado por "length"

	@param f Struct que contém informação dos campos. 
	@param cp Ponteiro para pool de constantes.
	@param length Define o número de chamadas à printField.
*/
void printFields (field_info *f, cp_info *cp, int length);

#endif
