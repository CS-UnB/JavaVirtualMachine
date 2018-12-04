/*! \file classFlags.h
	\brief Class Flags

	ClassFlags (public, final, super, interface and abstract)
*/

/*! \def FLAGS
	\brief Macro

	Define usado para evitar vários includes do arquivo.
*/

#ifndef FLAGS
#define FLAGS

#include <iostream>
#include "baseTypes.h"

using namespace std;

const string flagNames[] = {"ACC_PUBLIC", "ACC_FINAL", "ACC_SUPER", "ACC_INTERFACE", "ACC_ABSTRACT"};

/*! \fn void showFlags (U2 flags)
	\brief Função que mostra as flags de acesso para os usuários

	\param flags Valor hexadecimal das flags
*/
void showFlags (U2 flags);

#endif