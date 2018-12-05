/*!
 * \file localVariables.cpp
 * \brief 
 */

#include "localVariables.h"

LocalVariables::LocalVariables (uint16_t maxSize) : max(maxSize), realMax(2*maxSize), dois(false)
{
	elements = (uint32_t *) calloc(max*2, sizeof(uint32_t));
	types = (uint8_t *) calloc(max*2, sizeof(uint8_t));
}

LocalVariables::LocalVariables (uint16_t maxSize, bool slots) : max(maxSize), realMax(2*maxSize), dois(slots)
{
	elements = (uint32_t *) calloc(max*2, sizeof(uint32_t));
	types = (uint8_t *) calloc(max*2, sizeof(uint8_t));
}

LocalVariables::~LocalVariables () 
{
	if (elements)
		free(elements);
	if (types)
		free(types);
}

void LocalVariables::set(int index, typedElement x) 
{
	if (index < 0)
		throw std::runtime_error("Indice fora dos limites!");

	index *= 2;

	this->types[index] = x.type;
	if (this->types[index] == TYPE_LONG || this->types[index] == TYPE_DOUBLE || (this->types[index] == TYPE_REFERENCE && BITS)) 
	{
		if (index+1 >= realMax)
			throw std::runtime_error("Indice fora dos limites!");

		this->elements[index] = x.value.i;
		this->elements[++index] = int(x.value.l >> 32);
		this->types[index] = INVALID;
	} 
	else 
	{
		if (index >= realMax)
			throw std::runtime_error("Indice fora dos limites!");

		this->elements[index] = x.value.i;
	}
}

typedElement LocalVariables::get(int index) const 
{
	index *= 2;
	if (index >= realMax || index < 0)
		throw std::runtime_error("Indice fora dos limites!");


	if (this->types[index] == INVALID)
		throw std::runtime_error("A posicao acessada contem a segunda parte de uma informacao de 2 slots!");

	typedElement ret;
	ret.type = this->types[index];

	if (this->types[index] == TYPE_LONG || this->types[index] == TYPE_DOUBLE || (this->types[index] == TYPE_REFERENCE && BITS)) 
	{
		ret.value.l = (int64_t(this->elements[index+1]) << 32) + this->elements[index];
	} 
	else 
	{
		ret.value.i = this->elements[index];
	}

	return ret;
}

void LocalVariables::printall() const 
{
	for (int i = 0; i < max; ++i) 
	{
		std::cout << i << ": ";
		
		switch(this->types[i]) 
		{
			case INVALID:
				std::cout << "(Extensao do indice anterior)" << std::endl;
				break;
			case TYPE_NOT_SET:
				std::cout << "(Posicao ainda nao inicializada)" << std::endl;
				break;
			case TYPE_INT:
				std::cout << "(INT) " << this->get(i).value.i << std::endl;
				break;
			case TYPE_FLOAT:
				std::cout << "(FLOAT) " << this->get(i).value.f << std::endl;
				break;
			case TYPE_LONG:
				std::cout << "(LONG) " << this->get(i).value.l << std::endl;
				break;
			case TYPE_DOUBLE:
				std::cout << "(DOUBLE) " << this->get(i).value.d << std::endl;
				break;
			case TYPE_BOOL:
				std::cout << "(BOOL) " << (int) this->get(i).value.b << std::endl;
				break;
			case TYPE_REFERENCE:
				std::cout << "(REFERENCE) " << this->get(i).value.pi << std::endl;
				break;
		}
	}
}

int LocalVariables::getMax() const 
{
	return max;
}

const typedElement LocalVariables::operator[] (const int index) const 
{
	return this->get(index);
}