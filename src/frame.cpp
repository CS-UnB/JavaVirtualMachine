/**
 * @file frame.cpp
 * 
 */

#include "frame.h"

FrameStack::FrameStack (Leitor *l){
	frame *aux = (frame*) malloc(sizeof(frame));
	
	aux->m = l->getMain();
	aux->cp = l->getCP();
	aux->operandos = new PilhaOperandos(aux->m.attributes->info->code.max_stack);
	aux->locals = new LocalVariables(aux->m.attributes->info->code.max_locals);
	startPC(aux);

	threads.push(aux);

	//update operand stack pointers and variables array
	//used spots in current method operations

	Operacoes::setFrame(threads.top());
	Operacoes::setThreads(&threads);
	Operacoes::setFrameStack(this);

	//include reference to frame stack in method area
	//to be possible to include <clinit> when necessary

	MethodArea::setFrameStack(this);

	opcode = 0; //nop is standard instruction
}

void FrameStack::execute(){
	while (nextInstruction())
	{
		//calls function from functions array
		Operacoes::run(opcode);
	}
}

bool FrameStack::nextInstruction(){
	// empty stack?
	if (threads.empty())
	{
		return false;
	}

	//checks if current method operations is empty
	if ((threads.top()->pc - threads.top()->m.attributes->info->code.code) < threads.top()->m.attributes->info->code.code_length)
	{
		//get the next opcode to be executed
		opcode = *threads.top()->pc;
		//pc plus 1 instruction
		//if there is any arguments, the called function will use them
		//pc is incremented
		threads.top()->pc++;
		return true;
	}

	//remove the top of stack if there isn't any instructions on current method
	this->pop();

	//checks if there is any elements left
	if (threads.empty())
	{
		return false;
	}

	return true;
}

void FrameStack::pop(){
	
	if (!threads.empty()){
		
		delete threads.top()->operandos;
		delete threads.top()->locals;
		threads.pop();
	}
	if (threads.empty()) {
		Operacoes::setFrame(nullptr);
		Operacoes::setThreads(nullptr);
		exit(0);
	}
	Operacoes::setFrame(threads.top());
	Operacoes::setThreads(&threads);
}

void FrameStack::startPC(frame *f){
	
	//puts PC onto the initial position of top method
	f->pc = f->m.attributes->info->code.code;
}

void FrameStack::addFrame(method_info m, cp_info *cp){
	
	frame *aux = (frame*) malloc(sizeof(frame));

	aux->m = m;
	aux->cp = cp;
	aux->operandos = new PilhaOperandos(aux->m.attributes->info->code.max_stack);
	aux->locals = new LocalVariables(aux->m.attributes->info->code.max_locals);
	startPC(aux);
	
	//update operand stack pointers and array variables
	//used spots in current method operations
	Operacoes::setFrame(aux);
	Operacoes::setThreads(&threads);
	Operacoes::setFrameStack(this);

	//include reference to frame stack in method area
	//to be possible to include <clinit> when necessary
	MethodArea::setFrameStack(this);
	threads.push(aux);
}

void FrameStack::addFrame(method_info *m, cp_info *cp){
	
	this->addFrame(*m, cp);
}

void FrameStack::setArguments(std::vector<typedElement> param){
	
	for (int i = 0, j=0; (unsigned int) i < param.size(); i++, j++){
		
		threads.top()->locals->set(j, param[i]);
		
		//tests if the i-th argument filled two slots
		if (threads.top()->locals->get(j).type == TYPE_LONG || threads.top()->locals->get(j).type == TYPE_DOUBLE || (threads.top()->locals->get(j).type == TYPE_REFERENCE && BITS)){
			
			j++;
		}
	}
}
