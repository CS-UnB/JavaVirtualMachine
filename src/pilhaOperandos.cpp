/*!
 * \file pilhaOperandos.cpp
 * \brief Pilha de operandos
 */
#include "pilhaOperandos.h"

/**
* Construtor
*/
PilhaOperandos::PilhaOperandos (int maxSize) : realMax(maxSize), max(2*maxSize)
{
	typePushed = false;
}

/**
* Retorna topo da pilha de tipos
*/
uint8_t PilhaOperandos::top_type()
{
	return ((!this->empty()) ? (this->tipos.top()) : (-1));
}

/**
* Retorna topo da pilha de valores
*/
element PilhaOperandos::top_value()
{
	element ret;

	//Se pilha estiver vazia, retorna elemento vazio
	if (this->empty())
	{
		return ret;
	}

	//Pega primeiro valor da pilha de valores
	ret.i = this->elementos.top();

	//Se o tipo do valor empilhado � maior que 32bits, concatena os dois primeiros elementos da pilha na variavel de retorno.
	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64))
	{
		uint32_t aux = ret.i;
		this->elementos.pop();
		ret.l = int64_t((int64_t(ret.i)<<32) + this->elementos.top());
		this->elementos.push(aux);
	}

	return ret;
}

/**
* Retorna e remove topo da pilha de valores e da pop na pilha de tipos
*/
element PilhaOperandos::pop()
{
	element ret;
	//Se a pilha estiver vazia, retorna um elemento vazio.
	if (this->empty())
	{
		return ret;
	}

	//Pega o valor do topo da pilha
	ret = this->top_value();

	//Da pop na pilha de valores
	this->elementos.pop();

	//Se o valor recebendo pop tiver mais de 32bits, da pop em mais um item (um long fica como dois itens na pilha)
	if (this->tipos.top() == TYPE_LONG || this->tipos.top() == TYPE_DOUBLE || (this->tipos.top() == TYPE_REFERENCE && bits64))
	{
		this->elementos.pop();
	}

	//remove da pilha de tipos o tipo do elemento que sofreu pop
	this->tipos.pop();
	this->tiposReais.pop();

	return ret;
}

/**
* Retorna estrutura com valor e tipo associados e da pop na pilha de valores e na de tipos
*/
typedElement PilhaOperandos::popTyped()
{
	typedElement ret;
	ret.type = this->tipos.top();
	ret.realType = this->tiposReais.top();
	ret.value = this->pop();

	return ret;
}

/**
* Auxiliar do printAll, imprime a string correspondente ao tipo do elemento
*/
std::string PilhaOperandos::getString ()
{
	std::stringstream ret;

	//Switch no tipo do elemento do topo da pilha de operandos
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

/**
* Empilha um int na pilha de valores e seu tipo na pilha de tipos
*/
void PilhaOperandos::push(int x)
{
	//Se chegou no limite da pilha, n�o empilha
	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	//empilha o tipo int na pilha de tipos
	this->tipos.push(TYPE_INT);
	if (!typePushed)
	{
		this->tiposReais.push(RT_INT);
	}

	//empilha o valor na pilha de valores
	this->elementos.push(x);

	typePushed = false;
}

/**
* Empilha um float na pilha de valores e seu tipo na pilha de tipos
*/
void PilhaOperandos::push(float x)
{
	//Se chegou no limite da pilha, n�o empilha
	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.f = x;

	//empilha o tipo float na pilha de tipos
	this->tipos.push(TYPE_FLOAT);
	if (!typePushed)
		this->tiposReais.push(RT_FLOAT);

	//empilha o valor na pilha de valores
	this->elementos.push(aux.i);

	typePushed = false;
}

/**
* Empilha um double na pilha de valores e seu tipo na pilha de tipos
*/
void PilhaOperandos::push(double x)
{
	//Se n�o houver 2 espa�os dispon�veis na pilha, n�o empilha
	if (this->size()+1 >= max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.d = x;

	//empilha o tipo double na pilha de tipos
	this->tipos.push(TYPE_DOUBLE);
	if (!typePushed)
	{
		this->tiposReais.push(RT_DOUBLE);
	}

	//Empilha 32 bits inferiores do valor 
	this->elementos.push(aux.i);
	//Traz os 32 bits superiores para baixo
	aux.l >>= 32;
	//Empilha 32 bits inferiores do valor (superiores)
	this->elementos.push(aux.i);
	

	typePushed = false;
}

/**
* Empilha um long na pilha de valores e seu tipo na pilha de tipos
*/
void PilhaOperandos::push(int64_t _x)
{
	uint64_t x = _x;
	//Se n�o houver 2 espa�os dispon�veis na pilha, n�o empilha
	if (this->size()+1 >= max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	//empilha o tipo long na pilha de tipos
	this->tipos.push(TYPE_LONG);
	if (!typePushed)
	{
		this->tiposReais.push(RT_LONG);
	}

	//Empilha 32 bits inferiores do valor
	this->elementos.push(x);
	//Traz os 32 bits superiores para baixo
	x >>= 32;
	//Empilha 32 bits inferiores do valor (superiores)
	this->elementos.push(x);

	typePushed = false;
}

/**
* Empilha um bool na pilha de valores e seu tipo na pilha de tipos
*/
void PilhaOperandos::push(bool x)
{
	//Se chegou no limite da pilha, n�o empilha
	if (this->size() == max)
	{
		throw std::out_of_range("Excedeu o limite maximo da pilha!");
	}

	element aux;
	aux.b = x;

	//empilha o tipo bool na pilha de tipos
	this->tipos.push(TYPE_BOOL);
	if (!typePushed)
	{
		this->tiposReais.push(RT_BOOL);
	}

	//empilha o valor na pilha de valores
	this->elementos.push(aux.i);

	typePushed = false;
}

/**
* Empilha uma referencia na pilha de valores e seu tipo na pilha de tipos
*/
void PilhaOperandos::push(int *x)
{
	//Se chegou no limite da pilha, n�o empilha
	if (this->size()+bits64 >= max)
	{
		throw std::out_of_range("Passou do limite maximo da pilha!");
	}

	element aux;
	aux.pi = x;

	//empilha o tipo referencia na pilha de tipos
	this->tipos.push(TYPE_REFERENCE);
	if (!typePushed)
	{
		this->tiposReais.push(RT_REFERENCE);
	}

	//empilha o valor na pilha de valores
	this->elementos.push(aux.i);

	//Se a referencia for de 64bits (x64), empilha mais um valor na pilha de valores
	if (bits64)
	{
		aux.l >>= 32;
		this->elementos.push(aux.i);
	}

	typePushed = false;
}

/**
* Empilha valor e tipo de estrutura com valor e tipo associados
*/
void PilhaOperandos::push(typedElement te)
{
	this->tiposReais.push(te.realType);
	typePushed = true;
	this->push(te.value, te.type);
}

/**
* Chama a fun��o para empilhar de acordo com o tipo do elemento recebido
*/
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

/**
* Retorna valor m�ximo da pilha de operandos
*/
int PilhaOperandos::getMaxSize()
{
	return this->realMax;
}

/**
* Retorna o tamanho da pilha de valores
*/
int PilhaOperandos::size()
{
	return this->elementos.size();
}

/**
* Percorre e imprime toda a pilha de operandos
*/
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


/**
* returna 1 se a pilha de valores estiver vazia, 0 caso contr�rio
*/
bool PilhaOperandos::empty()
{
	return this->elementos.empty();
}
