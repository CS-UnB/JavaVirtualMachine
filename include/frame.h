/*! \file frame.h
	\brief Method 

	All the info needed for a method execution.
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
	@brief Storage structure

	Responsible for all the info needed for a method execution.
*/	
typedef struct frame_s
{
	unsigned char *pc;
	cp_info *cp;	
	PilhaOperandos *operandos;
	LocalVariables *locals;
	method_info m;
} frame;


/** @class FrameStack
	@brief Stack Frame Class

	Responsible for all operations that uses the frame.
*/	
class FrameStack {
private:
	std::stack<frame*> threads;
	/** @fn bool nextInstruction()
		@brief Updates PC, if we can't update more, pop current method
	*/
	bool nextInstruction();
	/** @var int opcode
		@brief Contêm o opcode que corresponde a uma instrução.
	*/
	int opcode;

	/** @fn void startPC(frame *f)
		@brief Puts PC in initial position

		\param f Structure that contains all the info for a method execution.
	*/
	void startPC(frame*);
public:
	/** @fn FrameStack (Leitor l)
		@brief Frame Stack Builder

		@param l What we read from .class file passed by the prompt line
	*/
	FrameStack (Leitor*);

	/** @fn void setArguments(std::vector<typedElement> param);
		@brief Adds a frame on the top of the stack
		@param Array with the arguments to be copied onto local variables array
	*/
	void setArguments(std::vector<typedElement>);

	/** @fn void execute();
		@brief Executes the current method and the called methods
	*/
	void execute();

	/** @fn void addFrame(method_info m, cp_info *cp);
		@brief Adds a frame on the top of the stack
		@param m The method where will be created the frame
		@param cp A pointer class method constant pool
	*/
	
	void addFrame(method_info, cp_info*);

	/** @fn void addFrame(method_info m, cp_info *cp);
		@brief Adds a frame on the top of the stack
		@param m Ponteir to the method where will be created the frame
		@param cp A ponteir to the class method constant pool
	*/
	void addFrame(method_info*, cp_info*);

	/** @fn void pop()
		@brief Pop current method.
	*/
	void pop();
};

#endif
