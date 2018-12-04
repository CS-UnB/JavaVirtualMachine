/** @file heap.h
	@brief Definição do Heap

	Gerencia a execução do heap.
*/

/** @def HEAP 
	@brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef HEAP
#define HEAP

#include "classe.h"
#include <vector>

/** @class Heap
	@brief Classe do heap

	Gerencia as operações do heap.
*/	
class Heap {
private:
	static vector<ClasseInstancia*> objetos;

public:
	/** @fn static void addObject(ClasseInstancia* ci)
		@brief Adiciona novo objeto no heap.

		@param ci - ponteiro para o novo objeto.
	*/
	static void addObject(ClasseInstancia*);
};

#endif
