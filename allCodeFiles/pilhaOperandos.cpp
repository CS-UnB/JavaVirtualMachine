/*!
 * \file
 * \brief PilhaOperandos.cpp
 */

#include "pilhaOperandos.h"

PilhaOperandos::PilhaOperandos (int maxSize) : realMax(maxSize), max(2*maxSize)
{
	typePushed = false;
}

//return top type
uint8_t PilhaOperandos::top_type()
{
	return ((!this->empty()) ? (this->tipos.top()) : (-1));
}

//return on union element the the value on the top
element PilhaOperandos::top_value()
{
	element ret;

	//if empty stack, retorns a empty element
	if (this->empty())
	{
		return ret;
	}

	//first slot of stack
	ret.i = this->elementos.top();

	//checks if is necessary to put one more slot together 
	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64))
	{
		uint32_t aux = ret.i;
		this->elementos.pop();
		ret.l = int64_t((int64_t(ret.i)<<32) + this->elementos.top());
		this->elementos.push(aux);
	}	

	return ret;
}

//returns the value on the top
element PilhaOperandos::pop()
{
	element ret;
	//if empty stack, retorns a empty element
	if (this->empty())
	{
		return ret;
	}

	ret = this->top_value();

	//pop slot
	this->elementos.pop();

	//checks if one more pop is necessary
	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64))
	{
		this->elementos.pop();
	}

	//removes the poped element type of types stack
	this->tipos.pop();
	this->tiposReais.pop();

	return ret;
}

typedElement PilhaOperandos::popTyped()
{
	typedElement ret;
	ret.type = this->tipos.top();
	ret.realType = this->tiposReais.top();
	ret.value = this->pop();

	return ret;
}

std::string PilhaOperandos::getString ()
{
	std::stringstream ret;

	switch (this->top_type())
	{
		case TYPE_INT:
			ret << "(int) " << int(this->top_value().i);
			break;
		case TYPE_LONG:
			ret << "(long) " << long(this->top_value().l);
			break;
		case TYPE_FLOAT:
			ret << "(float) " << this->top_value().f;
			break;
		case TYPE_DOUBLE:
			ret << "(double) " << this->top_value().d;
			break;
		case TYPE_BOOL:
			ret << "(bool) " << (int) this->top_value().b;
			break;
		case TYPE_REFERENCE:
			ret << "(reference) " << this->top_value().pi;
			break;
	}

	return ret.str();
}

//adds a float to stack top
void PilhaOperandos::push(int x)
{
	//if already reached max length, don't stack up
	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}
	this->tipos.push(TYPE_INT);
	if (!typePushed)
	{
		this->tiposReais.push(RT_INT);
	}
	this->elementos.push(x);

	typePushed = false;
}

//adds a float to stack top
void PilhaOperandos::push(float x)
{
	//if already reached max length, don't stack up
	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.f = x;
	this->tipos.push(TYPE_FLOAT);
	if (!typePushed)
		this->tiposReais.push(RT_FLOAT);
	this->elementos.push(aux.i);

	typePushed = false;
}

//adds a double to stack top, using 2 slots
void PilhaOperandos::push(double x)
{
	//if there isn't 2 slots available, don't stack up
	if (this->size()+1 >= max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.d = x;
	this->tipos.push(TYPE_DOUBLE);
	if (!typePushed)
	{
		this->tiposReais.push(RT_DOUBLE);
	}
	this->elementos.push(aux.i);
	aux.l >>= 32;
	this->elementos.push(aux.i);

	typePushed = false;
}

//adds a long to stack top, using 2 slots
void PilhaOperandos::push(int64_t _x)
{
	uint64_t x = _x;
	//if there isn't 2 slots available, don't stack up
	if (this->size()+1 >= max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	this->tipos.push(TYPE_LONG);
	if (!typePushed)
	{
		this->tiposReais.push(RT_LONG);
	}
	this->elementos.push(x);
	x >>= 32;
	this->elementos.push(x);

	typePushed = false;
}

//adds an int to stack top
void PilhaOperandos::push(bool x)
{
	//if already reached max length, don't stack up
	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}	

	element aux;
	aux.b = x;
	this->tipos.push(TYPE_BOOL);
	if (!typePushed)
	{
		this->tiposReais.push(RT_BOOL);
	}
	this->elementos.push(aux.i);

	typePushed = false;
}

//adds an int to stack top
void PilhaOperandos::push(int *x)
{
	//if there isn't enough slots available, don't stack up
	if (this->size()+bits64 >= max)
	{
		throw std::out_of_range("Passou do limite maximo da pilha!");
	}	

	element aux;
	aux.pi = x;
	this->tipos.push(TYPE_REFERENCE);
	if (!typePushed)
	{
		this->tiposReais.push(RT_REFERENCE);	
	}
	this->elementos.push(aux.i);
	if (bits64)
	{
		aux.l >>= 32;
		this->elementos.push(aux.i);
	}

	typePushed = false;
}

//receives a typed element and calls proper function to handle the type
void PilhaOperandos::push(typedElement te)
{
	this->tiposReais.push(te.realType);
	typePushed = true;
	this->push(te.value, te.type);
}

//chacks if the element type to be added and calls proper function
void PilhaOperandos::push(element x, uint8_t tipo) {
	switch (tipo)
	{
		case TYPE_DOUBLE:
			this->push(x.d);
			break;
		case TYPE_LONG:
			this->push(long(x.l));
			break;
		case TYPE_FLOAT:
			this->push(x.f);
			break;
		case TYPE_INT:
			this->push(int(x.i));
			break;
		case TYPE_REFERENCE:
			this->push((int*)(x.pi));
			break;
		case TYPE_BOOL:
			this->push(x.b);
			break;
		default:
			break;
	}
}

int PilhaOperandos::getMaxSize()
{
	return this->realMax;
}

//return stack length
int PilhaOperandos::size()
{
	return this->elementos.size();
}

void PilhaOperandos::printALL()
{
	PilhaOperandos aux(this->max);

	while (!this->empty())
	{
		cout << this->getString() << endl;
		aux.push(this->popTyped());
	}

	while (!aux.empty())
	{
		this->push(aux.popTyped());
	}
}

//return 1 if empty stack and 0 otherwise
bool PilhaOperandos::empty()
{
	return this->elementos.empty();
}