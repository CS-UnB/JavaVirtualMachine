/*! \file constantPool.h
	\brief Constant pool

	Stores all informations from a class constant pool.
*/


#ifndef CONSTANTPOOL
#define CONSTANTPOOL

#include "baseTypes.h"

using namespace std;

/*! \struct cp_info
	\brief Holds a constant pool element.
*/	
typedef struct {
	U1 tag;
	ClassLoaderType *info;
} cp_info;


//! Data formats int the constant pool
const string typeNames[] = {"UTF-8", "-", "Integer", "Float", "Long", "Double", "Class", "String", "Field", "Method", "Interface", "Name and Type"};


// Possible types for the constant pool elements
#define INVALID 99 //< Is a slot that holds the second part of a long or doube
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


/*! \fn int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp)
		\brief Load the constant pool information to the memory.

		\param constantPool Pointer to the constant pool structure.
		\param lengthCP Number of elements in the constant pool.
		\param fp Pointer to the .class file.
*/
int loadConstantPool (cp_info *constantPool, int lengthCP, FILE* fp);


/*! \fn string dereferenceIndex (cp_info *cp, U2 index)
		\brief Return the data in the index.

		\param cp Pointer to the constant pool structure
		\param index Index of an element in the constant pool.
*/
string dereferenceIndex (cp_info *cp, U2 index);


/*! \fn void printConstantPool (cp_info *constantPool, int lengthCP)
		\brief Show all the data in the constant pool.

		\param constantPool Pointer to the constant pool structure.
		\param lengthCP Number of elements in the constant pool.
*/
void printConstantPool (cp_info *constantPool, int lengthCP);

#endif