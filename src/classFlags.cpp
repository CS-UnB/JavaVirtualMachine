/*!
 * \file
 * \brief ClassFlags.cpp
 */

#include "classFlags.h"

/**
 * Função que mostra as flags de acesso para os usuários
 * @param flags Valor hexadecimal das flags
 */
void showFlags (U2 accessFlags)
{
	bool first = true;

	printf("Flags: ");

	// accessFlags é igual a 0x01
	if(accessFlags & 0x01)
	{
		first = false;
		printf("%s", flagNames[0].c_str());
	}

	// accessFlags é igual a 0x010
	if(accessFlags & 0x010)
	{
		if(first)
		{
			first = false;
			printf(", ");
		}

		printf("%s", flagNames[1].c_str());
	}

	// accessFlags é igual a 0x020
	if(accessFlags & 0x020)
	{
		if(first)
		{
			first = false;
			//cout << ", ";
			printf(", ");
		}

		printf("%s", flagNames[2].c_str());
	}

	// accessFlags é igual a 0x0200
	if(accessFlags & 0x0200)
	{
		if(first)
		{
			first = false;
			printf(", ");
		}
		
		printf("%s", flagNames[3].c_str());
	}

	// accessFlags é igual a 0x0400
	if(accessFlags & 0x0400)
	{
		if(first)
		{
			first = false;

			printf(", ");
		}

		printf("%s", flagNames[4].c_str());
	}
	
	cout << " (0x" << hex << accessFlags << dec << ")" << endl;
}