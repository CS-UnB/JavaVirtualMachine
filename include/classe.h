/*! \file classe.h
	\brief Definição da ClasseEstatica e da ClasseInstancia
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
	\brief Fields Estáticos compartilhados por todas as instâncias

	Define operações que manipulam classes estáticas
*/	
class ClasseEstatica {
private:
	map<string, typedElement*> staticFields;
	Leitor *classe;

public:
	/*! \fn ClasseEstatica(Leitor* classeLida)
		\brief Construtor da ClasseEstatica

		\param Leitor informação do class file já carregada na memória
	*/
	ClasseEstatica(Leitor*);


	/*! \fn typedElement getField(string s)
		\brief Retorna o field estático

		\param s nome da class.
	*/
	typedElement getField(string);


	/*! \fn bool setField(string s, typedElement e)
		\brief Define um field estático.

		\param s Nome da Classe.
		\param e Valor que será setado
	*/
	bool setField(string, typedElement);


	/*! \fn bool setFinals(string s, typedElement e)
		\brief Marca campo como final

		\param s Nome da classe.
		\param e Valor que vai ser definido.
	*/
	bool setFinals(string, typedElement);


	/*! \fn ClasseInstancia *getInstance()
		\brief Retorna a instância da classe
	*/
	ClasseInstancia *getInstance();


	/*! \fn Leitor *getDef()
		\brief Retorna as informações do class file.
	*/
	Leitor *getDef();
};



/*! \class ClasseInstancia
	\brief Class instantiation.

	Lida com operações que lidam com uma instância da classe
*/	
class ClasseInstancia {
private:
	map<string, typedElement*> localFields;
	ClasseEstatica *classe;

public:
	/*! \fn ClasseInstancia(ClasseEstatica* c)
		\brief Construtor

		\param c Referência para a classe estática
	*/
	ClasseInstancia(ClasseEstatica*);


	/*! \fn ClasseEstatica *getStatic()
		\brief Retorna referência para a classe estatica.
	*/
	ClasseEstatica *getStatic();


	/*! \fn typedElement getField(string s)
		\brief Retorna field instanciado

		\param Nome do field.
	*/
	typedElement getField(string);


	/*! \fn bool setField(string s, typedElement e)
		\brief Defina um valor para um field da ClasseInstancia

		\param s Nome do field.
		\param e Valor que será colocado
	*/
	bool setField(string, typedElement);


	/*! \fn bool setFinals(string s, typedElement e)
		\brief Define to final field da Classe Instância

		\param s Nome da classe
		\param e Valor a ser definido
	*/
	bool setFinals(string, typedElement);


	/*! \fn void show()
		\brief Mostra todas as classes instanciadas
	*/
	void show();
};

#endif