/*! \file classFlags.h
	\brief Class Flags

	ClassFlags (public, final, super, interface and abstract)
*/

/*! \def FLAGS
	\brief Macro

	Define used to avoid multiple includes of this file.
*/

#ifndef FLAGS
#define FLAGS

#include <iostream>
#include "baseTypes.h"

using namespace std;

const string flagNames[] = {"ACC_PUBLIC", "ACC_FINAL", "ACC_SUPER", "ACC_INTERFACE", "ACC_ABSTRACT"};

/*! \fn void showFlags (U2 flags)
	\brief Function that shows access flags to users.

	\param flags Hex values of the Flags.
*/
void showFlags (U2 flags);

#endif