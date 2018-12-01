/*! \file pilhaOperandos.h
	\brief Operands Stack

	Stack responsible for stores operands on JVM 
*/

/*! \def PILHAOPERANDOS
	\brief Macro

	Define used to avoid multiple inclusions on this file
*/

#ifndef PILHAOPERANDOS
#define PILHAOPERANDOS

#include <stack>
#include <cstdint>
#include <string>
#include <sstream>
#include <stdbool.h>
#include "baseTypes.h"

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6


/*! \class PilhaOperandos
	\brief Operand Stack's Class

	Responsible for manipulation on the operands stack
*/	
class PilhaOperandos 
{
private:
	//stack for stored values
	std::stack<uint32_t> elementos;
	//stack for types of stored values
	std::stack<uint8_t> tipos;
	//stack for types of stored values
	std::stack<uint8_t> tiposReais;
	bool typePushed;
	//variable to know if system has 64 bits
	static const bool bits64 = (sizeof(int*) == 8);
	//variable to know if maximum stack size
	const int realMax;
public:
	/*! \fn PilhaOperandos(int maxSize)
		\brief Constructor

		\param maxSize Indicates maximum size of operands stack
	*/
	PilhaOperandos(int);

	/*! \fn uint8_t top_type()
		\brief Recovers type of operands stack's top
	*/
	uint8_t top_type();

	/*! \fn element top_value()
		\brief Recovers value from operand's stack's top
	*/
	element top_value();

	/*! \fn element pop()
		\brief Unstacks the top's operand
	*/
	element pop();

	/*! \fn element pop()
		\brief 
		\brief Unstacks the top's operands return it's types
	*/
	typedElement popTyped();

	/*! \fn std::string getString()
		\brief Function to receives the top formatted in string
	*/
	std::string getString();
	
	/*! \fn void push(int x)
		\brief Function that empiles a x value of integer type

		\param x Value to be stacked on stack
	*/
	void push(int);

	/*! \fn void push(long x)
		\brief Function that stacks a x value of long type

		\param x Value to be stacked on stack
	*/
	void push(int64_t);

	/*! \fn void push(float x)
		\brief Function that stacks a x value of float type

		\param x Value to be stacked on stack
	*/
	void push(float);

	/*! \fn void push(double x)
		\brief Function that stacks a x value of double type

		\param x Value to be stacked on stack
	*/
	void push(double);

	/*! \fn void push(bool x)
		\brief Function that stacks a x value of boolean type

		\param x Value to be stacked on stack
	*/
	void push(bool);

	/*! \fn void push(int *x)
		\brief Function that stacks a x vlaue of an integer reference

		\param x Reference to be stacked on the stack
	*/
	void push(int*);

	/*! \fn void push(typedElement te)
		\brief Function that stacks an typed element, calling the adequate function

		\param x Element typed to be stacked on stack
	*/
	void push(typedElement);

	/*! \fn void push(element x, uint8_t tipo)
		\brief Function checks the element type that must be added and calls the adequate function

		\param x Typed element to be stacked on stack
		\param tipo Type of past element
	*/
	void push(element, uint8_t);

	/*! \fn int size()
		\brief Function that verifys the size of operands stack
	*/
	int size();

	/*! \fn int getMaxSize()
		\brief Function that returns maximum size of operands stack
	*/
	int getMaxSize();

	/*! \fn bool empty()
		\brief Function that returns if stack is empty or not
	*/
	bool empty();

	void printALL();
	const int max;
};

#endif