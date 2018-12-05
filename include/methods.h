/** \file methods.h
*	\brief
*/
#ifndef METHOD
#define METHOD

#include "baseTypes.h"
#include "constantPool.h"
#include "attributes.h"

using namespace std;

typedef struct 
{
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	attribute_info *attributes;
} method_info;

string get_Method_Flags (uint16_t flags);
method_info read_Method (FILE* fp,cp_info *cp);
method_info *read_Methods (FILE* fp, int length,cp_info *cp);
void printMethod (method_info f, cp_info *cp);
void printMethods (method_info *f, cp_info *cp, int length);

#endif 