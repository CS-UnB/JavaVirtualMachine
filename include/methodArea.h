/*! \file methodArea.h
	\brief Methods Aread

	Manages the methods from a instantiated class 
*/


#ifndef METHOD_AREA
#define METHOD_AREA

class MethodArea;

#include "classeLeitor.h"
#include "baseTypes.h"
#include "constantPool.h"
#include "frame.h"
#include "classe.h"
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

/*! \class MethodArea
	\brief Classe da área de métodos

	Responsável por todas as operações que gerenciam os métodos.
*/	
class MethodArea
{
private:
	static map<string, ClasseEstatica*> classes;
	static FrameStack *fs;


public:
	static string path;
	/*! \fn static ClasseEstatica *getClass(string s)
		\brief Returns a reference to the static class.

		\param s Class name.
	*/
	static ClasseEstatica *getClass(string);


	/*! \fn static bool addClass(string s)
		\brief Load a class in the memory.

		\param s Class name.
	*/
    static bool addClass(string);


    /*! \fn bool addClass(Leitor* l)
		\brief Load a class in the memory.

		\param l .class info in the memory.
	*/
    static bool addClass(Leitor*);


    /*! \fn static void setFrameStack(FrameStack* newFS)
		\brief Update the framestack reference to the next framestack.

		\param newFS next framestack.
	*/
    static void setFrameStack(FrameStack*);
};

#endif