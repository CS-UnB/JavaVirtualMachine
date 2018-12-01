/*! \file classeLeitor.h
	\brief Reader and Exhibitor

	It has all informations about the .class that makes reading, can display it or not.
*/

/*! \def CLASSE_LEITOR
	\brief Macro

	Define used to avoid multiple inclusions of this file
*/
#ifndef CLASSE_LEITOR
#define CLASSE_LEITOR

class Leitor;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include "baseTypes.h"
#include "constantPool.h"
#include "classFlags.h"
#include "fields.h"
#include "attributes.h"
#include "interfaces.h"
#include "methods.h"
#include "methodArea.h"

//defines for possible errors
#define MISSING_ARGUMENT 1
#define CANT_OPEN 2
#define INVALID_FILE 3
#define UNKNOWN_TYPE 4
#define INVALID_NAME 5
#define INVALID_EXTENSION 6
#define MISSING_MAIN 7

/*! \class Leitor
	\brief All reading/exhibition functions

	Contains all functions to realize reading and exhibition of .class informations
*/
class Leitor {
public:
	/*! \fn Leitor(char *in)
		\brief Reader constructor.

		\param in Path of .class file.
	*/
	Leitor(char *in);

	/*! \fn Leitor(char *in)
		\brief Reader constructor.

		\param in Path of .class file.
	*/
	Leitor(std::string in);

	/*! \fn int run()
		\brief Loads all .class informations and display them
	*/
	int run();

	/*! \fn int load()
		\brief Loads all .class informations
	*/
	int load();

	/*! \fn bool printGeneralInformation()
		\brief Display .class general informations
	*/
	void printGeneralInformation();

	/*! \fn bool show()
		\brief Display all .class informations
	*/
	bool show();

	/*! \fn bool validExtension ()
		\brief Verify if extension it is .class
	*/
	bool validExtension ();

	/*! \fn bool hasMain()
		\brief Verify if .class has main function
	*/
	bool hasMain();

	/*! \fn method_info getMain()
		\brief Returns method that it is main
	*/
	method_info getMain();

	/*! \fn bool hasClinit()
		\brief Verify if .class has method <clinit>
	*/
	bool hasClinit();

	/*! \fn method_info getClinit()
		\brief Returns the <clinit> method
	*/
	method_info getClinit();

	/*! \fn bool checkThisClass ()
		\brief Verify if defined class name is equal to class name without extensions
	*/
	bool checkThisClass ();


	/*! \fn int getStatus()
		\brief Returns reading status, informing to called method what happened
	*/
	int getStatus();

	/*! \fn cp_info *getCP()
		\brief Returns a reference to constant pool
	*/
	cp_info *getCP() const;

	/*! \fn U2 getLengthCP()
		\brief Gets size of .class Constant Pool
	*/
	U2 getLengthCP();

	/*! \fn char *getPath()
		\brief Gets path to .class directory
	*/
	char *getPath();

	/*! \fn method_info *getMethods()
		\brief Gets all .class methods
	*/
	method_info *getMethods();

	/*! \fn U2 getMethodsCount()
		\brief Gets all .class methods
	*/
	U2 getMethodsCount();

	/*! \fn U2 getThis_class()
		\brief Returns an index from constant pool that points to string with class name
	*/
	U2 getThis_class();

	/*! \fn U2 getSuper_class()
		\brief Returns an index from constant pool that points to string with superclass name
	*/
	U2 getSuper_class();

	/*! \fn U2 getFieldsCount()
		\brief Returns number of fields from .class file
	*/
	U2 getFieldsCount();

	/*! \fn U2 getFields()
		\brief Gets all .class fields
	*/
	field_info *getFields();


	/*! \fn U2 getField()
		\brief Gets a field from .class

		\param field_name Field's desired name
	*/
	field_info *getField(string field_name);


	/*! \fn U2 getMethod(ClasseInstancia* i, string name, string descriptor)
		\brief Returns method_info the reader contains the method with name and descriptor specified

		\param name Method's name to be searched
		\param descriptor Method's descriptor to be searched
	*/
	method_info* getMethod(string name, string descriptor);


	/*! \fn U2 getClassThatHasSerachedMethod(string name, string descriptor)
		\brief Returns pointer to reader from class that contains method found on getMethod

		\param name Method's name to be searched
		\param descriptor Method's descriptor to be searched
	*/
	Leitor* getClassThatHasSerachedMethod(string name, string descriptor);

private:
	/*! \fn bool findMain()
		\brief Finds which .class methods is main
	*/
	bool findMain();

	/*! \fn bool findMain()
		\brief Finds which .class methods is <clinit>, in case he exists
	*/
	bool findClinit();

	/*! \fn string getError(int)
		\brief Returns the string that contains an error message corresponding to the index that receives as parameter
	
		\param error Index that localizes the string that contains the error message
	*/
	string getError(int);

	int status, mainMethod, clinit;
	bool foundMain, foundClinit;
	char *fileName;
	U2 minVersion, majVersion, lengthCP;
	U2 this_class, super_class, interfacesCount, fieldsCount;
	U2 methodsCount, accessFlags, attributesCount;
	U2 *interfaces;
	cp_info *constantPool;
	field_info *fields;
	method_info *methods;
	attribute_info *attributes;
	FILE *fp;
};

#endif