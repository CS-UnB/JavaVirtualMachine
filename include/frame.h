/** @file frame.h
	@brief Contém tudo necessário para a execução de um método.
	
*/

/** @def FRAME 
	@brief Macro

	Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef FRAME
#define FRAME

class FrameStack;

#include "classeLeitor.h"
#include "pilhaOperandos.h"
#include "localVariables.h"
#include "baseTypes.h"
#include "operacoes.h"
#include "attributes.h"
#include "methodArea.h"

/** @struct frame_s
	@brief Estrutura de armazenamento

	Responsável por todas as informações necessárias para a execução de um método.
*/	
typedef struct frame_s{
	unsigned char *pc;
	cp_info *cp;	
	PilhaOperandos *operandos;
	LocalVariables *locals;
	method_info m;
} frame;


/** @class FrameStack
	@brief Classe de pilha de frames

	Responsável por todas as operações que usam o frame.
*/	
class FrameStack {
private:
	std::stack<frame*> threads;
	/** @fn bool nextInstruction()
		@brief Atualiza o PC, se não for possível atualizar, dá um pop no método atual
	*/
	bool nextInstruction();
	/** @var int opcode
		@brief Contêm o opcode que corresponde a uma instrução.
	*/
	int opcode;

	/** @fn void startPC(frame *f)
		@brief Põe o PC na posição inicial

		@param f Estrutura do tipo frame.
	*/
	void startPC(frame*);
public:
	/** @fn FrameStack (Leitor l)
		@brief Contrutor da pilha de frame

		@param l O que é lido do arquivo .class.
	*/
	FrameStack (Leitor*);

	/** @fn void setArguments(std::vector<typedElement> param);
		@brief Configura os argumentos.
		@param Vetor com os argumentos a serem copiados para o vetor de variáveis locais
	*/
	void setArguments(std::vector<typedElement>);

	/** @fn void execute();
		@brief Executa o método atual e os métodos chamados.
	*/
	void execute();

	/** @fn void addFrame(method_info m, cp_info *cp);
		@brief Adiciona um frame no topo da pilha.
		@param m Método no qual o frame será criado.
		@param cp Um ponteiro para o pool de constantes.
	*/
	
	void addFrame(method_info, cp_info*);

	/** @fn void addFrame(method_info m, cp_info *cp);
		@brief Adiciona um frame no topo da pilha.
		@param m Ponteiro para o método no qual o frame será criado.
		@param cp Um ponteiro para o pool de constantes.
	*/
	void addFrame(method_info*, cp_info*);

	/** @fn void pop()
		@brief Dá um pop no método atual.
	*/
	void pop();
};

#endif
