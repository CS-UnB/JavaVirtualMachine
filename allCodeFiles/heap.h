/*! \file heap.h
	\brief Heap definition

	Manages the execution heap.
*/


#ifndef HEAP
#define HEAP

#include "classe.h"
#include <vector>

/*! \class Heap
	\brief Classe do heap

	Handles the heap operations.
*/	
class Heap {
private:
	static vector<ClasseInstancia*> objetos;

public:
	/*! \fn static void addObject(ClasseInstancia* ci)
		\brief Add the new object to the heap.

		\param ci Pointer to the new object.
	*/
	static void addObject(ClasseInstancia*);
};

#endif