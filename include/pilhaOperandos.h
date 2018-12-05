/*! \file pilhaOperandos.h
	\brief Pilha de operandos

	Pilha responsável por armazenar os operandos da JVM
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


/** @class PilhaOperandos
	@brief Classe da pilha de operandos

	Responsável por armazenar e manipular a pilha de operandos
*/
class PilhaOperandos
{
private:
	//pilha para os valores armazenados
	std::stack<uint32_t> elementos;

	//pilha para o tipo dos valores armazenados
	std::stack<uint8_t> tipos;

	//pilha para o tipo dos valores armazenados
	std::stack<uint8_t> tiposReais;

	bool typePushed;

	//variavel para determinar se o sistema tem 64 bits
	static const bool bits64 = (sizeof(int*) == 8);

	//variavel para determinar tamanho máximo da pilha
	const int realMax;
public:
	/** @fn PilhaOperandos(int maxSize)
		@brief Construtor
		@param maxSize Indica tamanho máximo da pilha de operandos
	*/
	PilhaOperandos(int);

	/** @fn uint8_t top_type()
		@brief Recupera o tipo do topo da pilha de operandos
	*/
	uint8_t top_type();

	/** @fn element top_value()
		@brief Recupera o valor do topo da pilha de operandos
	*/
	element top_value();

	/** @fn element pop()
		@brief Desempilha o topo da pilha de operandos e retorna em um elemento de valor
	*/
	element pop();

	/** @fn element pop()
		@brief Desempilha o topo da pilha de operandos e retorna em um elemento tipado
	*/
	typedElement popTyped();

	/** @fn std::string getString()
		@brief Retorna o topo da pilha de operandos formatado em uma string
	*/
	std::string getString();

	/** @fn void push(int x)
		@brief Empilha um valor de tipo inteiro

		@param x Valor a ser empilhado
	*/
	void push(int);

	/** @fn void push(long x)
		@brief Empilha um valor de tipo long

		@param x Valor a ser empilhado
	*/
	void push(int64_t);

	/** @fn void push(float x)
		@brief Empilha um valor de tipo float

		@param x Valor a ser empilhado
	*/
	void push(float);

	/** @fn void push(double x)
		@brief Empilha um valor de tipo double

		@param x Valor a ser empilhado
	*/
	void push(double);

	/** @fn void push(bool x)
		@brief Empilha um valor de tipo double

		@param x Valor a ser empilhado
	*/
	void push(bool);

	/** @fn void push(int *x)
		@brief Empilha um valor de tipo referencia

		@param x Referencia a ser empilhada
	*/
	void push(int*);

	/** @fn void push(typedElement te)
		@brief Empilha um elemento tipado, chamando a função adequada ao tipo

		@param x Elemento tipado a ser empilhado
	*/
	void push(typedElement);

	/** @fn void push(element x, uint8_t tipo)
		@brief Verifica o tipo do elemento que deve ser empilhado e chama a função adequada

		@param x Elemento a ser empilhado
		@param tipo Tipo do elemento a ser empilhado
	*/
	void push(element, uint8_t);

	/** @fn int size()
		@brief Verifica o tamanho da pilha de operandos
	*/
	int size();

	/** @fn int getMaxSize()
		@brief Retorna o tamanho máximo da pilha de operandos
	*/
	int getMaxSize();

	/** @fn bool empty()
		@brief Retorna se a pilha está vazia (1) ou não (0)
	*/
	bool empty();

	void printALL();
	const int max;
};

#endif
