/*!
 * \file
 * \brief Interfaces.cpp
 */

#include "interfaces.h"

/*!
 * \brief 
*/
unsigned short *readInterfaces (FILE* fp, int length)
{
	unsigned short *ret = (unsigned short *) malloc(sizeof(int) * length);

	for (int i = 0; i < length; i++)
	{
		ret[i] = readU2(fp);
	}

	return ret;
}


void printInterfaces (unsigned short *interfaces, cp_info *cp, int length)
{
	for (int i = 0; i < length; i++)
	{
		printInterface(interfaces[i], cp, i);		
	}
}


void printInterface (unsigned short interface, cp_info *cp, int index)
{
	cout << "\tInterface " << index << ": " << dereferenceIndex(cp, interface) << endl;
}