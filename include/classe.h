/*! \file classe.h
	\brief Definition of class ClasseEstatica and ClasseInstancia.
*/


#ifndef CLASSE_CLASSE
#define CLASSE_CLASSE

class ClasseEstatica;
class ClasseInstancia;

#include "classeLeitor.h"
#include "heap.h"
#include <map>

using namespace std;

/*! \class ClasseEstatica
	\brief Static fields shared between all instances.

	Defines operations that manages static classes.
*/	
class ClasseEstatica {
private:
	map<string, typedElement*> staticFields;
	Leitor *classe;

public:
	/*! \fn ClasseEstatica(Leitor* classeLida)
		\brief Constructor of ClasseEstatica.

		\param Leitor .class information already loaded in memory.
	*/
	ClasseEstatica(Leitor*);


	/*! \fn typedElement getField(string s)
		\brief Returns the static field of a class file.

		\param s class name.
	*/
	typedElement getField(string);


	/*! \fn bool setField(string s, typedElement e)
		\brief Define a static field.

		\param s Class name.
		\param e Value to be defined.
	*/
	bool setField(string, typedElement);


	/*! \fn bool setFinals(string s, typedElement e)
		\brief Mark field as final.

		\param s Class name.
		\param e Value to be defined.
	*/
	bool setFinals(string, typedElement);


	/*! \fn ClasseInstancia *getInstance()
		\brief Returns a class instance.
	*/
	ClasseInstancia *getInstance();


	/*! \fn Leitor *getDef()
		\brief Returns the info from .class file.
	*/
	Leitor *getDef();
};



/*! \class ClasseInstancia
	\brief Class instantiation.

	Handles operations that manage a class instance.
*/	
class ClasseInstancia {
private:
	map<string, typedElement*> localFields;
	ClasseEstatica *classe;

public:
	/*! \fn ClasseInstancia(ClasseEstatica* c)
		\brief Constuctor

		\param c Reference to the ClasseEstatica.
	*/
	ClasseInstancia(ClasseEstatica*);


	/*! \fn ClasseEstatica *getStatic()
		\brief Returns a reference to ClasseEstatica.
	*/
	ClasseEstatica *getStatic();


	/*! \fn typedElement getField(string s)
		\brief Returns instantiated field.

		\param s Class name.
	*/
	typedElement getField(string);


	/*! \fn bool setField(string s, typedElement e)
		\brief Define a field of the ClasseInstancia.

		\param s Class name.
		\param e Value to be defined.
	*/
	bool setField(string, typedElement);


	/*! \fn bool setFinals(string s, typedElement e)
		\brief Define the final field of the ClasseInstancia.

		\param s Class name.
		\param e Value to be defined.
	*/
	bool setFinals(string, typedElement);


	/*! \fn void show()
		\brief Show all instantiated classes.
	*/
	void show();
};

#endif