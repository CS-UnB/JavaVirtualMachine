/*!
 * \file
 * \brief Heap.cpp
 */

#include "heap.h"

vector<ClasseInstancia*> Heap::objetos;

void Heap::addObject(ClasseInstancia *ci) {
	objetos.push_back(ci);
}