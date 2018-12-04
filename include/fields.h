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

/*! \struct field_info
	\brief Storage struct.

	Struct responsable to store declared fields.
*/

typedef struct {
	unsigned char accessFlags;
	unsigned char name_index;
	unsigned char descriptor_index;
	unsigned char attributes_count;
	attribute_info *attributes;
} field_info;

/*! \fn string getFieldFlags(unsigned short flags)
	\brief Function to show fields flags

	\param flags Flags in hexadecimal that will be converted to string.
*/

string getFieldFlags (unsigned short flags);

/*! \fn field_info readField (FILE* fp, cp_info *cp)
	\brief Function to read a field

	\param fp Pointer to .class archive.
	\param cp Pointer to constant pool.
*/

field_info readField (FILE* fp, cp_info *cp);


/*! \fn field_info *readFields (FILE* fp, int length,cp_info *cp)
	\brief Function that alloc field_info space and call readField lenght vezes
	

	\param fp Pointer to .class archive.
	\param cp Pointer to constant pool.
	\param length Define number of calls of readField.
*/
field_info *readFields (FILE* fp, int length,cp_info *cp);


/*! \fn void printField (field_info f, cp_info *cp)
	\brief Function to show a field with array index.

	\param f Struct with field informations.
	\param index Index of vector that contains a field.
	\param cp Pointer to constant pool.
*/
void printField (field_info f, cp_info *cp, int index);

/*! \fn void printFields (field_info *f, cp_info *cp, int length)
	\brief Function that invokes printField lenght times

	\param f Struct that contains field infos. 
	\param cp Pointer to constant pool.
	\param length Define number of calls of printField.
*/
void printFields (field_info *f, cp_info *cp, int length);

#endif
