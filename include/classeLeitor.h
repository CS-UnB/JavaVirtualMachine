/*! \file classe.h
	\brief Definição da ClasseLeitor
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

/**
 * MACROS para os possíves erros encontrados
 * 
 */
#define MISSING_ARGUMENT 1
#define CANT_OPEN 2
#define INVALID_FILE 3
#define UNKNOWN_TYPE 4
#define INVALID_NAME 5
#define INVALID_EXTENSION 6
#define MISSING_MAIN 7

/**
 * @file classeLeitor.h
 * @author  Bruno Cordeiro 
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * A classe Leitor contém o necessário para ler o bytecode, exibilo e armazena-lo em memoria
 */
class Leitor {
public:
	/** 
		\fn Construtor de leitura
		@param in caminho do arquivo .class.
	*/
	Leitor(char *in);

	/** 
		\fn Construtor de leitura
		@param in caminho do arquivo .class.
	*/
	Leitor(std::string in);

	/** \fn int run()
		\brief Carrega todas as informções do class file e as imprime
	*/
	int run();

	/** \fn int load()
		\brief Carrega todas as informações do class file
	*/
	int load();

	/** \fn bool printGeneralInformation()
		\brief Imprime informações gerais do .class
	*/
	void printGeneralInformation();

	/** \fn bool show()
		\brief Imprime todas as informações do .class
	*/
	bool show();

	/** \fn bool validExtension ()
		\brief Verifica se a extensão do arquivo é .class
	*/
	bool validExtension ();

	/** \fn bool hasMain()
		\brief Verifica se o .class possui função main
	*/
	bool hasMain();

	/** \fn method_info getMain()
		\brief Retorna o método main
	*/
	method_info getMain();

	/** \fn bool hasClinit()
		\brief Verifica se o .class tem o método <clinit>
	*/
	bool hasClinit();

	/** \fn method_info getClinit()
		\brief Retorna o método <clinit>
	*/
	method_info getClinit();

	/** \fn bool checkThisClass ()
		\brief Verifica se a class definida é igual ao nome da classe sem extensões 
	*/
	bool checkThisClass ();


	/** \fn int getStatus()
		\brief Retorna o status lido, informando para o método que chamou o que aconteceu
	*/
	int getStatus();

	/** \fn cp_info *getCP()
		\brief Retorna referencia a constant pool
	*/
	cp_info *getCP() const;

	/** \fn U2 getLengthCP()
		\brief Retorna o valor do tamanho da constant pool
	*/
	U2 getLengthCP();

	/** \fn char *getPath()
		\brief Pega o caminho do arquivo .class
	*/
	char *getPath();

	/** \fn method_info *getMethods()
		\brief Retorna todos os métodos
	*/
	method_info *getMethods();

	/** \fn U2 getMethodsCount()
		\brief Retorna o numero de methods
	*/
	U2 getMethodsCount();

	/** \fn U2 getThis_class()
		\brief Retorna um índice da constant pool que aponta para string com nome da class
	*/
	U2 getThis_class();

	/** \fn U2 getSuper_class()
		\brief Retorna um índice da constant pool que aponta para string com nome da superclass
	*/
	U2 getSuper_class();

	/** \fn U2 getFieldsCount()
		\brief Retorna número de fields
	*/
	U2 getFieldsCount();

	/** \fn U2 getFields()
		\brief Retorna todos os fields
	*/
	field_info *getFields();


	/** \fn U2 getField()
		\brief Retorna um field

		\param field_name nome do field desejado
	*/
	field_info *getField(string field_name);


	/** \fn U2 getMethod(ClasseInstancia* i, string name, string descriptor)
		\brief Retorna o method info

		\param name Nome do method desejado
		\param descriptor Descritor do method desejado
	*/
	method_info* getMethod(string name, string descriptor);


	/** \fn U2 getClassThatHasSerachedMethod(string name, string descriptor)
		\brief Retorna o ponteiro para o leitor do .class que contém o método encontrado em getMethod
	
		\param name Nome do method desejado
		\param descriptor Descritor do method desejado
	*/
	Leitor* getClassThatHasSerachedMethod(string name, string descriptor);

private:
	/** \fn bool findMain()
		\brief Encontro em qual method está a main
	*/
	bool findMain();

	/** \fn bool findMain()
		\brief Encontra em qual method esta a <clinit>, se existir
	*/
	bool findClinit();

	/** \fn string getError(int)
		\brief Retorna a string que contém uma mensagem de erro correspondente ao índice que recebe como parâmetro
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