#include "operacoes.h"

frame *Operacoes::f = nullptr;
stack<struct frame_s*> *Operacoes::threads = nullptr;
FrameStack *Operacoes::fs = nullptr;
bool Operacoes::isWide = false;

const fun Operacoes::functions[] =
{
	&Operacoes::nop,
	&Operacoes::aconst_null,
	&Operacoes::iconst_m1,
	&Operacoes::iconst_0,
	&Operacoes::iconst_1,
	&Operacoes::iconst_2,
	&Operacoes::iconst_3,
	&Operacoes::iconst_4,
	&Operacoes::iconst_5,
	&Operacoes::lconst_0,
	&Operacoes::lconst_1,
	&Operacoes::fconst_0,
	&Operacoes::fconst_1,
	&Operacoes::fconst_2,
	&Operacoes::dconst_0,
	&Operacoes::dconst_1,
	&Operacoes::bipush,
	&Operacoes::sipush,
	&Operacoes::ldc,
	&Operacoes::ldc_w,
	&Operacoes::ldc2_w,
	&Operacoes::iload,
	&Operacoes::lload,
	&Operacoes::fload,
	&Operacoes::dload,
	&Operacoes::aload,
	&Operacoes::iload_0,
	&Operacoes::iload_1,
	&Operacoes::iload_2,
	&Operacoes::iload_3,
	&Operacoes::lload_0,
	&Operacoes::lload_1,
	&Operacoes::lload_2,
	&Operacoes::lload_3,
	&Operacoes::fload_0,
	&Operacoes::fload_1,
	&Operacoes::fload_2,
	&Operacoes::fload_3,
	&Operacoes::dload_0,
	&Operacoes::dload_1,
	&Operacoes::dload_2,
	&Operacoes::dload_3,
	&Operacoes::aload_0,
	&Operacoes::aload_1,
	&Operacoes::aload_2,
	&Operacoes::aload_3,
	&Operacoes::iaload,
	&Operacoes::laload,
	&Operacoes::faload,
	&Operacoes::daload,
	&Operacoes::aaload,
	&Operacoes::baload,
	&Operacoes::caload,
	&Operacoes::saload,
	&Operacoes::istore,
	&Operacoes::lstore,
	&Operacoes::fstore,
	&Operacoes::dstore,
	&Operacoes::astore,
	&Operacoes::istore_0,
	&Operacoes::istore_1,
	&Operacoes::istore_2,
	&Operacoes::istore_3,
	&Operacoes::lstore_0,
	&Operacoes::lstore_1,
	&Operacoes::lstore_2,
	&Operacoes::lstore_3,
	&Operacoes::fstore_0,
	&Operacoes::fstore_1,
	&Operacoes::fstore_2,
	&Operacoes::fstore_3,
	&Operacoes::dstore_0,
	&Operacoes::dstore_1,
	&Operacoes::dstore_2,
	&Operacoes::dstore_3,
	&Operacoes::astore_0,
	&Operacoes::astore_1,
	&Operacoes::astore_2,
	&Operacoes::astore_3,
	&Operacoes::iastore,
	&Operacoes::lastore,
	&Operacoes::fastore,
	&Operacoes::dastore,
	&Operacoes::aastore,
	&Operacoes::bastore,
	&Operacoes::castore,
	&Operacoes::sastore,
	&Operacoes::pop,
	&Operacoes::pop2,
	&Operacoes::dup,
	&Operacoes::dup_x1,
	&Operacoes::dup_x2,
	&Operacoes::dup2,
	&Operacoes::dup2_x1,
	&Operacoes::dup2_x2,
	&Operacoes::swap,
	&Operacoes::iadd,
	&Operacoes::ladd,
	&Operacoes::fadd,
	&Operacoes::dadd,
	&Operacoes::isub,
	&Operacoes::lsub,
	&Operacoes::fsub,
	&Operacoes::dsub,
	&Operacoes::imul,
	&Operacoes::lmul,
	&Operacoes::fmul,
	&Operacoes::dmul,
	&Operacoes::idiv,
	&Operacoes::ldiv,
	&Operacoes::fdiv,
	&Operacoes::ddiv,
	&Operacoes::irem,
	&Operacoes::lrem,
	&Operacoes::frem,
	&Operacoes::drem,
	&Operacoes::ineg,
	&Operacoes::lneg,
	&Operacoes::fneg,
	&Operacoes::dneg,
	&Operacoes::ishl,
	&Operacoes::lshl,
	&Operacoes::ishr,
	&Operacoes::lshr,
	&Operacoes::iushr,
	&Operacoes::lushr,
	&Operacoes::iand,
	&Operacoes::land,
	&Operacoes::ior,
	&Operacoes::lor,
	&Operacoes::ixor,
	&Operacoes::lxor,
	&Operacoes::iinc,
	&Operacoes::i2l,
	&Operacoes::i2f,
	&Operacoes::i2d,
	&Operacoes::l2i,
	&Operacoes::l2f,
	&Operacoes::l2d,
	&Operacoes::f2i,
	&Operacoes::f2l,
	&Operacoes::f2d,
	&Operacoes::d2i,
	&Operacoes::d2l,
	&Operacoes::d2f,
	&Operacoes::i2b,
	&Operacoes::i2c,
	&Operacoes::i2s,
	&Operacoes::lcmp,
	&Operacoes::fcmpl,
	&Operacoes::fcmpg,
	&Operacoes::dcmpl,
	&Operacoes::dcmpg,
	&Operacoes::ifeq,
	&Operacoes::ifne,
	&Operacoes::iflt,
	&Operacoes::ifge,
	&Operacoes::ifgt,
	&Operacoes::ifle,
	&Operacoes::if_icmpeq,
	&Operacoes::if_icmpne,
	&Operacoes::if_icmplt,
	&Operacoes::if_icmpge,
	&Operacoes::if_icmpgt,
	&Operacoes::if_icmple,
	&Operacoes::if_acmpeq,
	&Operacoes::if_acmpne,
	&Operacoes::funcgoto,
	&Operacoes::jsr,
	&Operacoes::funcret,
	&Operacoes::tableswitch,
	&Operacoes::lookupswitch,
	&Operacoes::ireturn,
	&Operacoes::lreturn,
	&Operacoes::freturn,
	&Operacoes::dreturn,
	&Operacoes::areturn,
	&Operacoes::func_return,
	&Operacoes::getstatic,
	&Operacoes::putstatic,
	&Operacoes::getfield,
	&Operacoes::putfield,
	&Operacoes::invokevirtual,
	&Operacoes::invokespecial,
	&Operacoes::invokestatic,
	&Operacoes::invokeinterface,
	&Operacoes::nop,
	&Operacoes::func_new,
	&Operacoes::newarray,
	&Operacoes::anewarray,
	&Operacoes::arraylength,
	&Operacoes::athrow,
	&Operacoes::nop,
	&Operacoes::nop,
	&Operacoes::nop,
	&Operacoes::nop,
	&Operacoes::wide,
	&Operacoes::multianewarray,
	&Operacoes::ifnull,
	&Operacoes::ifnonnull,
	&Operacoes::goto_w,
	&Operacoes::jsr_w
};


Operacoes::Operacoes(struct frame_s *ref)
{
	f = ref;
}

uint32_t Operacoes::getNBytesValue(uint8_t n, unsigned char** pc)
{
  uint32_t value = **pc;
  *pc +=1;

  for(int i = 1; i < n; i++)
  {
    value = (value << 8) | **pc;
    *pc += 1;
  }

  return value;
}

void Operacoes::setFrame(struct frame_s *newRef)
{
	f = newRef;
}

void Operacoes::setThreads(stack<struct frame_s*> *t)
{
	threads = t;
}

void Operacoes::setFrameStack(FrameStack* newFS)
{
	fs = newFS;
}

void Operacoes::run(int opcode)
{
	functions[opcode] ();
}

// Do nothing
void Operacoes::nop ()
{
}

// Push in the a null reference (0) to the operands stack
void Operacoes::aconst_null ()
{
	f->operandos->push((int*)(nullptr));
}

// Push (int) -1 to the operands stack
void Operacoes::iconst_m1 ()
{
	f->operandos->push(int(-1));
}

// Push (int) 0 to the operands stack
void Operacoes::iconst_0 ()
{
	f->operandos->push(int(0));
}

// Push (int) 1 to the operands stack
void Operacoes::iconst_1 ()
{
	f->operandos->push(int(1));
}

// Push (int) 2 to the operands stack
void Operacoes::iconst_2 ()
{
	f->operandos->push(int(2));
}

// Push (int) 3 to the operands stack
void Operacoes::iconst_3 ()
{
	f->operandos->push(int(3));
}

// Push (int) 4 to the operands stack
void Operacoes::iconst_4 ()
{
	f->operandos->push(int(4));
}

// Push (int) 5 to the operands stack
void Operacoes::iconst_5 ()
{
	f->operandos->push(int(5));
}

// Push (long) 0 to the operands stack
void Operacoes::lconst_0 ()
{
	f->operandos->push(long(0));
}

// Push (long) 1 to the operands stack
void Operacoes::lconst_1 ()
{
	f->operandos->push(long(1));
}

// Push (float) 0.0 to the operands stack
void Operacoes::fconst_0 ()
{
	f->operandos->push(float(0.0));
}

// Push (float) 1.0 to the operands stack
void Operacoes::fconst_1 ()
{
	f->operandos->push(float(1.0));
}

// Push (float) 2.0 to the operands stack
void Operacoes::fconst_2 ()
{
	f->operandos->push(float(2.0));
}

// Push (double) 0.0 to the operands stack
void Operacoes::dconst_0 ()
{
	f->operandos->push(double(0.0));
}

// Push (double) 1.0 to the operands stack
void Operacoes::dconst_1 ()
{
	f->operandos->push(double(1.0));
}


// Push a byte with signal extension 
void Operacoes::bipush ()
{
	int32_t aux;
	int8_t byte = getNBytesValue(1, &f->pc);
	aux = (int32_t) (int8_t) byte; // signal extension
	f->operandos->push(int(aux));
}

// Push two bytes 
void Operacoes::sipush ()
{
	uint16_t valShort;
	int32_t valPushShort;
	valShort = getNBytesValue(2, &f->pc);
	valPushShort = (int32_t) (int16_t) valShort;  // signal extension
	f->operandos->push(int(valPushShort));  
}

// Push a value from constant pool
void Operacoes::ldc ()
{
	uint8_t index = getNBytesValue(1, &f->pc);
	cp_info cp = f->cp[index]; 
	if (cp.tag == STRING)
	{
		f->operandos->push((int*)(f->cp[cp.info[0].u2].info[1].array));	
	}
	else
	{
		element aux;
		aux.i = cp.info[0].u4;
		if (cp.tag == INTEGER)
		{	
			f->operandos->push(aux, TYPE_INT);
		} else {
			f->operandos->push(aux, TYPE_FLOAT);
		}
	}
}

// Push a value from constant pool (ldc wide)
void Operacoes::ldc_w ()
{
	uint16_t index = getNBytesValue(2, &f->pc);
	cp_info cp = f->cp[index]; 
	if (cp.tag == STRING)
	{
		f->operandos->push((int*)(f->cp[cp.info[0].u2].info[1].array));	
	}
	else
	{
		f->operandos->push(int(cp.info[0].u4));	
	}
}

// Push a long or double value from constant pool
void Operacoes::ldc2_w ()
{
	uint8_t index = getNBytesValue(2, &f->pc);
	long valPushLong;
	double valPushDouble; 
	if (f->cp[index].tag == LONG)
	{
		valPushLong = u4_to_long(f->cp[index].info[0], f->cp[index+1].info[0]);
		f->operandos->push(long(valPushLong));
	} else {
		valPushDouble = u4_to_double(f->cp[index].info[0], f->cp[index+1].info[0]);
		f->operandos->push(double(valPushDouble));
	}
}

// Reads an integer from the local variables and pushes it
void Operacoes::iload ()
{
	uint16_t index = 0;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	} else {
		index = getNBytesValue(1, &f->pc);
	}
	
	typedElement aux = f->locals->get(int(index));
	f->operandos->push(int(aux.value.i));
}

// Reads an long from the local variables and pushes it
void Operacoes::lload ()
{
	uint16_t index = 0;
	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	}else
		index = getNBytesValue(1, &f->pc);
	
	typedElement aux = f->locals->get(int(index));
	f->operandos->push(long(aux.value.l));
}

// Reads an float from the local variables and pushes it
void Operacoes::fload ()
{
	uint16_t index = 0;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	}else
		index = getNBytesValue(1, &f->pc);
	
	typedElement aux = f->locals->get(int(index));
	f->operandos->push(float(aux.value.f));
}

// Reads an double from the local variables and pushes it
void Operacoes::dload ()
{
	uint16_t index;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	} else
		index = getNBytesValue(1, &f->pc);
	
	typedElement aux = f->locals->get(int(index));
	f->operandos->push(double(aux.value.d));
}

// Reads a reference from the local variables and pushes it
void Operacoes::aload ()
{
	uint16_t index = 0;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	}else
		index = getNBytesValue(1, &f->pc);
	
	typedElement aux = f->locals->get(int(index));
	f->operandos->push((int*)(aux.value.pi));
}

// Reads an integer from the local variables, in the position 0, and pushes it
void Operacoes::iload_0 ()
{
	typedElement aux = f->locals->get(0);
	f->operandos->push(int(aux.value.i));
}

// Reads an integer from the local variables, in the position 1, and pushes it
void Operacoes::iload_1 ()
{
	typedElement aux = f->locals->get(1);
	f->operandos->push(int(aux.value.i));
}

// Reads an integer from the local variables, in the position 2, and pushes it
void Operacoes::iload_2 ()
{
	typedElement aux = f->locals->get(2);
	f->operandos->push(int(aux.value.i));
}

// Reads an integer from the local variables, in the position 3, and pushes it
void Operacoes::iload_3 ()
{
	typedElement aux = f->locals->get(3);
	f->operandos->push(int(aux.value.i));
}

// Reads an long from the local variables, in the position 0, and pushes it
void Operacoes::lload_0 ()
{
	lload_n(0);
}

// Reads an long from the local variables, in the position 1, and pushes it
void Operacoes::lload_1 ()
{
	lload_n(1);
}


// LLOAD_<N>
void Operacoes::lload_n(short index)
{
	typedElement aux = f->locals->get(index);
	f->operandos->push(long(aux.value.l));
}

void Operacoes::lload_2()
{
	lload_n(2);
}

void Operacoes::lload_3()
{
 	lload_n(3);
}

// FLOAD_<N>
void Operacoes::fload_n(short index)
{
	typedElement aux = f->locals->get(index);
	f->operandos->push(aux.value.f);
}

void Operacoes::fload_0()
{
	fload_n(0);
}

void Operacoes::fload_1()
{
	fload_n(1);
}

void Operacoes::fload_2()
{
	fload_n(2);
}

void Operacoes::fload_3()
{
	fload_n(3);
}

// DLOAD_<N>
void Operacoes::dload_n(short index)
{
	typedElement aux = f->locals->get(index);
	f->operandos->push(aux.value.d);
}

void Operacoes::dload_0()
{
	dload_n(0);
}

void Operacoes::dload_1()
{
	dload_n(1);
}

void Operacoes::dload_2()
{
	dload_n(2);
}

void Operacoes::dload_3()
{
	dload_n(3);
}


// ALOAD_<N>
void Operacoes::aload_n(short index)
{
	typedElement aux = f->locals->get(index);
	f->operandos->push(aux.value.pi);
}

void Operacoes::aload_0()
{
	aload_n(0);
}

void Operacoes::aload_1()
{
	aload_n(1);
}

void Operacoes::aload_2()
{
	aload_n(2);
}

void Operacoes::aload_3()
{
	aload_n(3);
}

void Operacoes::iaload()
{
	element_u value1, value2;

	value1 = f->operandos->pop();
  	value2 = f->operandos->pop();
  	int *ref = value2.pi;

  	if (ref == nullptr)
    	throw runtime_error("Null pointer");
	f->operandos->push(ref[value1.i]);

}

void Operacoes::laload()
{
	element_u value1, value2;
	//struct typedElement_s result;

	value1 = f->operandos->pop();
  	value2 = f->operandos->pop();
  	LocalVariables *ref = (LocalVariables *) value2.pi;
  	if (ref == nullptr)
    	throw runtime_error("Null pointer");

	f->operandos->push(ref->get(value1.i));
}

void Operacoes::lstore_0()
{
	typedElement var = f->operandos->popTyped();
	if(var.type == TYPE_LONG)
	{
		f->locals->set(0, var);
	}
	else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operacoes::lstore()
{
   uint16_t index = 0;

   if (isWide)
   {
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	}else
		index = getNBytesValue(1, &f->pc);
	
	if(f->operandos->top_type() == TYPE_LONG)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(index, aux);
	}
	else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operacoes::istore()
{
   uint16_t index = 0;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	}else
		index = getNBytesValue(1, &f->pc);   

	if(f->operandos->top_type() == TYPE_INT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(index, aux);
	}
	else
		printf("Operando no topo != TYPE_INT\n");
}

void Operacoes::fstore()
{
	uint16_t index = 0;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	}else
		index = getNBytesValue(1, &f->pc); 
	
	if(f->operandos->top_type() == TYPE_FLOAT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(index, aux);
	}
	else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operacoes::dstore()
{
   uint16_t index = 0;

	if (isWide)
	{
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	} else
		index = getNBytesValue(1, &f->pc); 

	if(f->operandos->top_type() == TYPE_DOUBLE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(index, aux);
	}
	else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operacoes::astore()
{
   uint16_t index = 0;

   	if (isWide)
	   {
		index = getNBytesValue(2, &f->pc);
		isWide = false;
	} else
		index = getNBytesValue(1, &f->pc); 

	if(f->operandos->top_type() == TYPE_REFERENCE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(index, aux);
	}
	else
		printf("Operando no topo != TYPE_REFERECE\n");
}


void Operacoes::istore_0()
{
	if(f->operandos->top_type() == TYPE_INT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(0, aux);
	}
	else
		printf("Operando no topo != TYPE_INT\n");
}


void Operacoes::istore_1()
{
	if(f->operandos->top_type() == TYPE_INT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(1, aux);
	}
	else
		printf("Operando no topo != TYPE_INT\n");
}

void Operacoes::istore_2()
{
	if(f->operandos->top_type() == TYPE_INT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(2, aux);
	}
	else
		printf("Operando no topo != TYPE_INT\n");
}

void Operacoes::istore_3()
{
	if(f->operandos->top_type() == TYPE_INT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(3, aux);
	}
	else
		printf("Operando no topo != TYPE_INT\n");
}

// Read the fload value from a array and push to the operand stack
void Operacoes::faload()
{
	int index = f->operandos->pop().i;
	LocalVariables *arrayref = (LocalVariables *) f->operandos->pop().pi;
	if(arrayref == NULL)
	{
	}
	f->operandos->push(arrayref->get(index));
}

// Read the double value from a array and push to the operand stack
void Operacoes::daload()
{
	int index = f->operandos->pop().i;
	LocalVariables *arrayref = (LocalVariables *) f->operandos->pop().pi;
	f->operandos->push(arrayref->get(index));
}

// Read a reference value from a array and push to the operand stack
void Operacoes::aaload()
{
	int index = f->operandos->pop().i;
	LocalVariables *arrayref = (LocalVariables *) f->operandos->pop().pi;
	f->operandos->push(arrayref->get(index));
}

// Read the boolean value from a array and push to the operand stack
void Operacoes::baload()
{
	int index = f->operandos->pop().i;
	LocalVariables *arrayref = (LocalVariables *) f->operandos->pop().pi;
	f->operandos->push(arrayref->get(index));
}

// Read the char value from a array and push to the operand stack
void Operacoes::caload()
{
	int index = f->operandos->pop().i;
	std::vector<char> *arrayref = (std::vector<char> *) f->operandos->pop().pi;
	f->operandos->push(arrayref->at(index));
}

void Operacoes::saload()
{
	int index = f->operandos->pop().i;
	LocalVariables *arrayref = (LocalVariables *) f->operandos->pop().pi;
	f->operandos->push(arrayref->get(index));
}

void Operacoes::lstore_1()
{
	if(f->operandos->top_type() == TYPE_LONG)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(1, aux);
	}
	else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operacoes::lstore_2()
{
	if(f->operandos->top_type() == TYPE_LONG)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(2, aux);
	}
	else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operacoes::lstore_3()
{
	if(f->operandos->top_type() == TYPE_LONG)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(3, aux);
	}
	else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operacoes::fstore_0()
{
	if(f->operandos->top_type() == TYPE_FLOAT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(0, aux);
	}
	else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operacoes::fstore_1()
{
	if(f->operandos->top_type() == TYPE_FLOAT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(1, aux);
	}
	else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operacoes::fstore_2()
{
	if(f->operandos->top_type() == TYPE_FLOAT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(2, aux);
	}
	else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operacoes::fstore_3()
{
	if(f->operandos->top_type() == TYPE_FLOAT)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(3, aux);
	}
	else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operacoes::dstore_0()
{
	if(f->operandos->top_type() == TYPE_DOUBLE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(0, aux);
	}
	else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operacoes::dstore_1()
{
	if(f->operandos->top_type() == TYPE_DOUBLE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(1, aux);
	}
	else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operacoes::dstore_2()
{
	if(f->operandos->top_type() == TYPE_DOUBLE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(2, aux);
	}
	else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operacoes::dstore_3()
{
	if(f->operandos->top_type() == TYPE_DOUBLE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(3, aux);
	}
	else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operacoes::astore_0()
{
	if(f->operandos->top_type() == TYPE_REFERENCE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(0, aux);
	}
	else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operacoes::astore_1()
{
	if(f->operandos->top_type() == TYPE_REFERENCE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(1, aux);
	}
	else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operacoes::astore_2()
{
	if(f->operandos->top_type() == TYPE_REFERENCE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(2, aux);
	}
	else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operacoes::astore_3()
{
	if(f->operandos->top_type() == TYPE_REFERENCE)
	{
		typedElement aux = f->operandos->popTyped();
		f->locals->set(3, aux);
	}
	else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operacoes::iastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	int *vetor = f->operandos->pop().pi;

	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
	/*typedElement aux;
	aux.value.i = valor.i;
	aux.type = TYPE_INT;
	aux.realType = RT_INT;*/
	vetor[indice.i] = valor.i;
}

// Stores a double in the operands stack as a array element
void Operacoes::lastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	LocalVariables *vetor = (LocalVariables *) f->operandos->pop().pi;
	
	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		typedElement aux;
		aux.value.l = valor.l;
		aux.type = TYPE_LONG;
		aux.realType = RT_LONG;
		vetor->set(indice.i, aux);
}

// Stores a float in the operands stack as a array element
void Operacoes::fastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	LocalVariables *vetor = (LocalVariables *) f->operandos->pop().pi;
	
	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		typedElement aux;
		aux.value.f = valor.f;
		aux.type = TYPE_FLOAT;
		aux.realType = RT_FLOAT;
		vetor->set(indice.i, aux);
}

// Stores a double in the operands stack as a array element
void Operacoes::dastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	LocalVariables *vetor = (LocalVariables *) f->operandos->pop().pi;
	
	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		typedElement aux;
		aux.value.d = valor.d;
		aux.type = TYPE_DOUBLE;
		aux.realType = RT_DOUBLE;
		vetor->set(indice.i, aux);
}

// Stores a reference in the operands stack as a array element
void Operacoes::aastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	LocalVariables *vetor = (LocalVariables *) f->operandos->pop().pi;

	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		typedElement aux;
		aux.value.pi = valor.pi;
		aux.type = TYPE_REFERENCE;
		aux.realType = RT_REFERENCE;
		vetor->set(indice.i, aux);
}

// Stores a byte in the operands stack as a array element
void Operacoes::bastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	LocalVariables *vetor = (LocalVariables *) f->operandos->pop().pi;

	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		typedElement aux;
		aux.value.i = valor.i;
		aux.type = TYPE_INT;
		aux.realType = RT_BOOL;
		vetor->set(indice.i, aux);
}

// Stores a char in the operands stack as a array element
void Operacoes::castore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	std::vector<uint8_t> *vetor = (std::vector<uint8_t> *) f->operandos->pop().pi;

	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		vetor->at(indice.i) = valor.bs;	
}

// Stores a short in the operands stack as a array element
void Operacoes::sastore()
{
	element valor = f->operandos->pop();
	element indice = f->operandos->pop();
	LocalVariables *vetor = (LocalVariables *) f->operandos->pop().pi;

	if (vetor == nullptr) throw std::runtime_error("NullPointerException");
		typedElement aux;
		aux.value.i = valor.i;
		aux.type = TYPE_INT;
		aux.realType = RT_SHORT;
		vetor->set(indice.i, aux);	
}


void Operacoes::iadd()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_INT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

    if (f->operandos->top_type() == TYPE_INT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

	result.type = TYPE_INT;
	result.realType = RT_INT;
	result.value.i = value1.i + value2.i;
	f->operandos->push(result);
}

void Operacoes::ladd()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_LONG)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

    if (f->operandos->top_type() == TYPE_LONG)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

	result.type = TYPE_LONG;
	result.realType = RT_LONG;
	result.value.l = value1.l + value2.l;
	f->operandos->push(result);
}

void Operacoes::fadd()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

	result.type = TYPE_FLOAT;
	result.realType = RT_FLOAT;
	result.value.f = value1.f + value2.f;
	f->operandos->push(result);
}

void Operacoes::dadd()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

	result.type = TYPE_DOUBLE;
	result.realType = RT_DOUBLE;
	result.value.d = value1.d + value2.d;
	f->operandos->push(result);
}

void Operacoes::isub() 
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_INT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

    if (f->operandos->top_type() == TYPE_INT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

	result.type = TYPE_INT;
	result.realType = RT_INT;
	result.value.i = value1.i - value2.i;
	f->operandos->push(result);
}

void Operacoes::lsub()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_LONG)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

    if (f->operandos->top_type() == TYPE_LONG)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

	result.type = TYPE_LONG;
	result.realType = RT_LONG;
	result.value.l = value1.l - value2.l;
	f->operandos->push(result);
}

void Operacoes::fsub()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

	result.type = TYPE_FLOAT;
	result.realType = RT_FLOAT;
	result.value.f = value1.f - value2.f;
	f->operandos->push(result);
}

void Operacoes::dsub()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

	result.type = TYPE_DOUBLE;
	result.realType = RT_DOUBLE;
	result.value.d = value1.d - value2.d;
	f->operandos->push(result);
}

void Operacoes::imul()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_INT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

    if (f->operandos->top_type() == TYPE_INT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

	result.type = TYPE_INT;
	result.realType = RT_INT;
	result.value.i = value1.i * value2.i;
	f->operandos->push(result);
}

void Operacoes::lmul()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_LONG)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

    if (f->operandos->top_type() == TYPE_LONG)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

	result.type = TYPE_LONG;
	result.realType = RT_LONG;
	result.value.l = value1.l * value2.l;
	f->operandos->push(result);
}

void Operacoes::fmul()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

	result.type = TYPE_FLOAT;
	result.realType = RT_FLOAT;
	result.value.f = value1.f * value2.f;
	f->operandos->push(result);
}

void Operacoes::dmul()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

	result.type = TYPE_DOUBLE;
	result.realType = RT_DOUBLE;
	result.value.d = value1.d * value2.d;
	f->operandos->push(result);
}

void Operacoes::idiv()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_INT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

    if (f->operandos->top_type() == TYPE_INT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um inteiro!");
    }

	result.type = TYPE_INT;
	result.realType = RT_INT;
	result.value.i = value1.i / value2.i;
	f->operandos->push(result);
}

void Operacoes::ldiv()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_LONG)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

    if (f->operandos->top_type() == TYPE_LONG)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um long!");
    }

	result.type = TYPE_LONG;
	result.realType = RT_LONG;
	result.value.l = value1.l / value2.l;
	f->operandos->push(result);
}

void Operacoes::fdiv()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

    if (f->operandos->top_type() == TYPE_FLOAT)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um float!");
    }

	result.type = TYPE_FLOAT;
	result.realType = RT_FLOAT;
	result.value.f = value1.f / value2.f;
	f->operandos->push(result);
}

void Operacoes::ddiv()
{
	element_u value1, value2;
	struct typedElement_s result;

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
    	value2 = f->operandos->pop();
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

    if (f->operandos->top_type() == TYPE_DOUBLE)
	{
		value1 = f->operandos->pop();	
    } else {
    	throw std::runtime_error("Elemento lido nao era um double!");
    }

	result.type = TYPE_DOUBLE;
	result.realType = RT_DOUBLE;
	result.value.d = value1.d / value2.d;
	f->operandos->push(result);
}


void Operacoes::irem ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    if (value2.i == 0)
	{
        throw std::runtime_error("Arithmetic Exeption: divisao por z    ");
    }


    value1 = f->operandos->pop();

    result.type = TYPE_INT;
    result.realType = RT_INT;
    result.value.i = value1.i - int(value1.i/value2.i) * value2.i;
    f->operandos->push(result);
}

void Operacoes::lrem ()
{
    element_u value1, value2;
    struct typedElement_s result;

    
    value2 = f->operandos->pop();
    if (value2.l == 0)
	{
        throw std::runtime_error("Arithmetic Exeption: divisao por zero.");
    }

    value1 = f->operandos->pop();

    result.type = TYPE_LONG;
    result.realType = RT_LONG;
    result.value.l = value1.l - int(value1.l/value2.l) * value2.l;
    f->operandos->push(result);
}


void Operacoes::frem ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();

    if (checkFloat(value1.f) == 3 || checkFloat(value2.f) == 3)
	{
        result.value.i = Float_NaN;
    } else if (checkFloat(value1.f) == 1 || checkFloat(value1.f) == 2 || value2.f == 0.0)
	{
        result.value.i = Float_NaN;
    } else if (checkFloat(value1.f) == 0 && (checkFloat(value2.f) == 1 || checkFloat(value2.f) == 2))
	{
        result.value.f = value1.f;
    } else if (value1.f == 0.0 && checkFloat(value2.f) == 0)
	{
        result.value.f = 0.0;
    } else {
        result.value.f = fmod(value1.f, value2.f);
    }

    result.type = TYPE_FLOAT;
    result.realType = RT_FLOAT;
    f->operandos->push(result);
}

void Operacoes::drem ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();

    if (checkDouble(value1.d) == 3 || checkDouble(value2.d) == 3)
	{
        result.value.l = Double_NaN;
    } else if (checkDouble(value1.d) == 1 || checkDouble(value1.d) == 2 || value2.d == double(0.0))
	{
        result.value.l = Double_NaN;
    } else if (checkDouble(value1.d) == 0 && (checkDouble(value2.d) == 1 || checkDouble(value2.d) == 2))
	{
        result.value.d = value1.d;
    } else if (value1.d == 0.0 && checkDouble(value2.d) == 0)
	{
        result.value.d = 0.0;
    } else {
        result.value.d = fmod(value1.d, value2.d);
    }

    result.type = TYPE_DOUBLE;
    result.realType = RT_DOUBLE;
    f->operandos->push(result);
}

void Operacoes::ineg ()
{
    element_u value;
    struct typedElement_s result;

    value = f->operandos->pop();

    result.type = TYPE_INT;
    result.realType = RT_INT;
    result.value.is = 0 - value.is;
    f->operandos->push(result);
}

void Operacoes::lneg ()
{
    element_u value;
    struct typedElement_s result;

    value = f->operandos->pop();

    result.type = TYPE_LONG;
    result.realType = RT_LONG;
    result.value.ls = 0 - value.ls;
    f->operandos->push(result);
}

void Operacoes::fneg ()
{
    element_u value;
    struct typedElement_s result;

    value = f->operandos->pop();

    result.type = TYPE_FLOAT;
    result.realType = RT_FLOAT;
    //inverte o bit 31
    result.value.i = value.i + 0x80000000;
    f->operandos->push(result);
}

void Operacoes::dneg ()
{
    element_u value;
    struct typedElement_s result;

    value = f->operandos->pop();

    result.type = TYPE_DOUBLE;
    result.realType = RT_DOUBLE;
    //inverte o bit 63
    result.value.l = value.l + 0x8000000000000000;
    f->operandos->push(result);
}

void Operacoes::ishl()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();   

    result.type = TYPE_INT;
    result.realType = RT_INT;
    result.value.i = value1.i << (value2.i & 0b011111);
    f->operandos->push(result);
}

void Operacoes::lshl()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();   

    result.type = TYPE_LONG;
    result.realType = RT_LONG;
    result.value.l = value1.l << (value2.i & 0b0111111);
    f->operandos->push(result);
}

void Operacoes::ishr ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();   

    result.type = TYPE_INT;
    result.realType = RT_INT;
    result.value.is = value1.is >> (value2.i & 0b011111);
    f->operandos->push(result);
}

void Operacoes::lshr ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();

    result.type = TYPE_LONG;
    result.realType = RT_LONG;
    result.value.ls = value1.ls >> (value2.i & 0b0111111);
    f->operandos->push(result);
}

void Operacoes::iushr ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();

    result.type = TYPE_INT;
    result.realType = RT_INT;
    result.value.i = value1.i >> (value2.i & 0b011111);
    f->operandos->push(result);
}

void Operacoes::lushr ()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();

    result.type = TYPE_LONG;
    result.realType = RT_LONG;
    result.value.l = value1.l >> (value2.i & 0b0111111);
    f->operandos->push(result);
}

void Operacoes::iand()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();   

    result.type = TYPE_INT;
    result.realType = RT_INT;
    result.value.i = value1.i & value2.i;
    f->operandos->push(result);
}

void Operacoes::land()
{
    element_u value1, value2;
    struct typedElement_s result;

    value2 = f->operandos->pop();
    value1 = f->operandos->pop();   

    result.type = TYPE_LONG;
    result.realType = RT_LONG;
    result.value.l = value1.l & value2.l;
    f->operandos->push(result); 
}


void Operacoes::ior()
{
	element aux1 = f->operandos->pop();
	element aux2 = f->operandos->pop();
	aux1.i |= aux2.i;
	f->operandos->push(aux1, TYPE_INT);
}

void Operacoes::lor()
{
	element aux1 = f->operandos->pop();
	element aux2 = f->operandos->pop();
	aux1.l |= aux2.l;
	f->operandos->push(aux1, TYPE_LONG);
}

void Operacoes::ixor()
{
	element aux1 = f->operandos->pop();
	element aux2 = f->operandos->pop();
	aux1.i ^= aux2.i;
	f->operandos->push(aux1, TYPE_INT);
}

void Operacoes::lxor()
{
	element aux1 = f->operandos->pop();
	element aux2 = f->operandos->pop();
	aux1.l ^= aux2.l;
	f->operandos->push(aux1, TYPE_LONG);
}

void Operacoes::iinc()
{
	uint16_t var;
	int16_t n;
	if(isWide)
	{
		 var = getNBytesValue(2, &f->pc);
		 n = int16_t(getNBytesValue(2, &f->pc));
	}
	else {
		 var = getNBytesValue(1, &f->pc);
		 n = int8_t(getNBytesValue(1, &f->pc));
	}

	typedElement aux = f->locals->get(var);
	if(aux.type == TYPE_INT)
		aux.value.i += (int32_t)n;
	f->locals->set(var, aux);
}

void Operacoes::i2l()
{
	f->operandos->push(f->operandos->pop(), TYPE_LONG);
}

void Operacoes::i2f()
{
	element aux = f->operandos->pop();
	aux.f = (float)aux.is;
	f->operandos->push(aux.f);
}

void Operacoes::i2d()
{
	element aux = f->operandos->pop();
	aux.d = (double)aux.is;
	f->operandos->push(aux.d);
}

void Operacoes::l2i()
{
	element aux = f->operandos->pop();
	aux.i = (uint32_t)aux.l;
	f->operandos->push(aux, TYPE_INT);
}

void Operacoes::l2f()
{
	element aux = f->operandos->pop();
	aux.f = (float)aux.l;
	f->operandos->push(aux, TYPE_FLOAT);
}

void Operacoes::l2d()
{
	element aux = f->operandos->pop();
	aux.d = (double)aux.l;
	f->operandos->push(aux.d);
}

void Operacoes::f2i()
{
	element aux = f->operandos->pop();
	aux.is = (int32_t)aux.f;
	f->operandos->push(aux.is);
}

void Operacoes::f2l()
{
	element aux = f->operandos->pop();
	aux.l = (int64_t)aux.f;
	f->operandos->push(aux, TYPE_LONG);
}

void Operacoes::f2d()
{
	element aux = f->operandos->pop();
	aux.d = (double)aux.f;
	f->operandos->push(aux.d);
}

void Operacoes::d2i()
{
	element aux = f->operandos->pop();
	aux.is = (int32_t)aux.d;
	f->operandos->push(aux.is);
}

void Operacoes::d2l()
{
	element aux = f->operandos->pop();
	aux.l = (int64_t)aux.d;
	f->operandos->push(aux, TYPE_LONG);
}


void Operacoes::d2f ()
{
	element aux = f->operandos->pop();
	aux.f = (float)aux.d;
	f->operandos->push(aux.f);
}

//le um int do topo da pilha (truncado para byte), extende com sinal para um int e reinsere na pilha de operandos
void Operacoes::i2b()
{
	int8_t value = f->operandos->pop().bs;
	
	f->operandos->push(int(value));
}

//le um int do topo da pilha (truncado para char), extende com 0 para um int  e reinsere na pilha de operandos
void Operacoes::i2c()
{
	typedElement value;
	value.type = TYPE_INT;
	value.realType = RT_CHAR;
	value.value.b = f->operandos->pop().b;
	f->operandos->push(value);
}

//le um int do topo da pilha (truncado para short), extende com sinal para um int e reinsere na pilha de operandos
void Operacoes::i2s()
{
	typedElement value;
	value.type = TYPE_INT;
	value.realType = RT_SHORT;
	value.value.ss = f->operandos->pop().ss;

	f->operandos->push(value);
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo long) e os compara
void Operacoes::lcmp()
{
	int64_t value2 = f->operandos->pop().ls;
	int64_t value1 = f->operandos->pop().ls;
	
	if (value1 > value2)
		f->operandos->push(int(1));
	if (value1 == value2)
		f->operandos->push(int(0));
	if (value1 < value2)
		f->operandos->push(int(-1));
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo float) e os compara
void Operacoes::fcmpl()
{
	float value2 = f->operandos->pop().f;
	float value1 = f->operandos->pop().f;
	int res1, res2;
	
	res1 = checkFloat(value1);
	res2 = checkFloat(value2);
	//se value1 ou value2 for NaN entao adiciona -1 na pilha de operandos
	if (res1 == 3 || res2 == 3)
	{
		f->operandos->push(int(-1));
	} else {
		if (value1 > value2)
			f->operandos->push(int(1));
		if (value1 == value2)
			f->operandos->push(int(0));
		if (value1 < value2)
			f->operandos->push(int(-1));
	}
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo float) e os compara
void Operacoes::fcmpg()
{
	float value2 = f->operandos->pop().f;
	float value1 = f->operandos->pop().f;
	int res1, res2;
	
	res1 = checkFloat(value1);
	res2 = checkFloat(value2);
	//se value1 ou value2 for NaN entao adiciona 1 na pilha de operandos
	if (res1 == 3 || res2 == 3)
	{
		f->operandos->push(int(1));
	} else {
		if (value1 > value2)
			f->operandos->push(int(1));
		if (value1 == value2)
			f->operandos->push(int(0));
		if (value1 < value2)
			f->operandos->push(int(-1));
	}
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo double) e os compara
void Operacoes::dcmpl()
{
	double value2 = f->operandos->pop().d;
	double value1 = f->operandos->pop().d;
	int res1, res2;
	
	res1 = checkDouble(value1);
	res2 = checkDouble(value2);
	//se value1 ou value2 for NaN entao adiciona 1 na pilha de operandos
	if (res1 == 3 || res2 == 3)
	{
		f->operandos->push(int(1));
	} else {
		if (value1 > value2)
			f->operandos->push(int(1));
		if (value1 == value2)
			f->operandos->push(int(0));
		if (value1 < value2)
			f->operandos->push(int(-1));
	}
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo double) e os compara
void Operacoes::dcmpg()
{
	double value2 = f->operandos->pop().d;
	double value1 = f->operandos->pop().d;
	int res1, res2;
	
	res1 = checkDouble(value1);
	res2 = checkDouble(value2);
	//se value1 ou value2 for NaN entao adiciona 1 na pilha de operandos
	if (res1 == 3 || res2 == 3)
	{
		f->operandos->push(int(1));
	} else {
		if (value1 > value2)
			f->operandos->push(int(1));
		if (value1 == value2)
			f->operandos->push(int(0));
		if (value1 < value2)
			f->operandos->push(int(-1));
	}
}

//le o valor do topo da pilha, se for igual a 0 salta
void Operacoes::ifeq()
{
	int value = f->operandos->pop().i;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (value == 0)
		f->pc += branchbyte - 3;
	
}

//le o valor do topo da pilha, se for diferente de 0 salta
void Operacoes::ifne()
{
	int value = f->operandos->pop().i;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (value != 0)
		f->pc += branchbyte - 3;
	
}

//le o valor do topo da pilha, se for menor que 0 salta
void Operacoes::iflt()
{
	int value = f->operandos->pop().i;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (value < 0)
		f->pc += branchbyte - 3;
	
}

//le o valor do topo da pilha, se for maior ou igual a 0 salta
void Operacoes::ifge()
{
	int value = f->operandos->pop().i;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (value >= 0)
		f->pc += branchbyte - 3;
	
}

//le o valor do topo da pilha, se for maior que 0 salta
void Operacoes::ifgt()
{
	int value = f->operandos->pop().i;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (value > 0)
		f->pc += branchbyte - 3;
}

//le o valor do topo da pilha, se for menor ou igual a 0 salta
void Operacoes::ifle()
{
	int value = f->operandos->pop().i;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (value <= 0)
		f->pc += branchbyte - 3;
}

//le dois valores da pilha, se forem iguais salta
void Operacoes::if_icmpeq ()
{
	int value1, value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().i;
	value1 = f->operandos->pop().i;

	if (value1 == value2)
	{
		f->pc += branchbyte - 3;
	}
}


void Operacoes::if_icmpne ()
{
	int value1, value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().i;
	value1 = f->operandos->pop().i;

	if (value1 != value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::if_icmplt()
{
	int value1, value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().i;
	value1 = f->operandos->pop().i;

	if (value1 < value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::if_icmpge()
{
	int value1, value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().is;
	value1 = f->operandos->pop().is;

	if (value1 >= value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::if_icmpgt()
{
	int value1, value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().i;
	value1 = f->operandos->pop().i;

	if (value1 > value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::if_icmple()
{
	int value1, value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().i;
	value1 = f->operandos->pop().i;

	if (value1 <= value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::if_acmpeq()
{
	int *value1, *value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().pi;
	value1 = f->operandos->pop().pi;

	if (value1 == value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::if_acmpne()
{
	int *value1, *value2;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));
	
	value2 = f->operandos->pop().pi;
	value1 = f->operandos->pop().pi;

	if (value1 != value2)
	{
		f->pc += branchbyte - 3;
	}
}

void Operacoes::funcgoto()
{
	int16_t offset;

	offset = int16_t(getNBytesValue(2, &f->pc));

	f->pc += offset - 3;
}

void Operacoes::jsr()
{
	int16_t offset;

	offset = int16_t(getNBytesValue(2, &f->pc));

	f->operandos->push((int*)f->pc);

	f->pc += offset - 3;
}

//pode ser utilizada em conjunto com wide
void Operacoes::funcret()
{
	if (isWide)
	{
		f->pc = (unsigned char *) f->locals->get(getNBytesValue(2, &f->pc)).value.pi;
		isWide = false;
	}
	else
		f->pc = (unsigned char *) f->locals->get(getNBytesValue(1, &f->pc)).value.pi;
}

void Operacoes::tableswitch()
{
	//guarda o valor inicial do pc
	unsigned char *bkpPC = (f->pc) - 1;
	uint8_t mod = (f->pc - f->m.attributes->info->code.code) % 4;
	f->pc += mod;

	int32_t defaults, low, high, offset;
	defaults = int32_t(getNBytesValue(4, &f->pc));
	low = int32_t(getNBytesValue(4, &f->pc));
	high = int32_t(getNBytesValue(4, &f->pc));

	int32_t index = f->operandos->popTyped().value.is;

	//salto padrão caso index não esteja no range correto
	if (index < low || index > high)
	{
		f->pc = bkpPC;
		f->pc += defaults;
		return;
	} 

	for (; low < high+1; low++)
	{
		offset = int32_t(getNBytesValue(4,&f->pc));
		if (index == low)
		{
			break;
		}
		
	}
	f->pc = bkpPC;
	f->pc += offset;
}

void Operacoes::lookupswitch()
{
	unsigned char *aux = (f->pc) - 1;
	int diff = (f->pc - f->m.attributes->info->code.code) % 4;

	f->pc += diff;

    int32_t defaultValue = getNBytesValue(4,&f->pc);
	int32_t npairs = getNBytesValue(4,&f->pc);
    int32_t match, offset, key = f->operandos->pop().is;
    int i;

    for(i = 0; i < npairs; i++)
	{
    	match = getNBytesValue(4,&f->pc);
    	offset = getNBytesValue(4,&f->pc); 

    	if (match == key)
		{
    		f->pc = aux + offset;
    		break;
    	}
    }

    if (i == npairs)
	{
    	f->pc = aux + defaultValue;
    }
}

void Operacoes::ireturn()
{
	int value = f->operandos->pop().i;
	
	while (!f->operandos->empty())
	{
		f->operandos->pop();
	}

	threads->pop();
	f = threads->top();
	f->operandos->push(value);
}

void Operacoes::lreturn()
{
	long value = f->operandos->pop().l;
	
	while (!f->operandos->empty())
	{
		f->operandos->pop();
	}

	threads->pop();
	f = threads->top();
	f->operandos->push(value);
}

void Operacoes::freturn()
{
	float value = f->operandos->pop().f;
	
	while (!f->operandos->empty())
	{
		f->operandos->pop();
	}

	threads->pop();
	f = threads->top();
	f->operandos->push(value);
}

void Operacoes::dreturn()
{
	double value = f->operandos->pop().d;
	
	while (!f->operandos->empty())
	{
		f->operandos->pop();
	}

	threads->pop();
	f = threads->top();
	f->operandos->push(value);
}


void Operacoes::areturn()
{
    element_u value;

    if (f->operandos->top_type() == TYPE_REFERENCE)
	{
        value = f->operandos->pop();
    
        while (!f->operandos->empty())
		{
            f->operandos->pop();
        }

    } else {
        throw std::runtime_error("Elemento lido nao era uma referencia!");
    }

    threads->pop();
    f = threads->top();

    f->operandos->push(value.pi);
}

void Operacoes::func_return()
{    
    while (!f->operandos->empty())
	{
        f->operandos->pop();
    }

    fs->pop();
}

ClasseEstatica* Operacoes::getStaticClassThatHasField(ClasseEstatica* base, string field_name) 
{
    typedElement ret = base->getField(field_name);
    if(ret.type != TYPE_NOT_SET)
	{
        return base;
    }

    int cp_index = base->getDef()->getSuper_class();
    if( cp_index == 0 )
	{
        return NULL;
    }

    ClasseEstatica* child = MethodArea::getClass(dereferenceIndex(base->getDef()->getCP(), cp_index));
    return getStaticClassThatHasField(child, field_name); 
}

void Operacoes::getstatic()
{
    uint16_t indexByte = getNBytesValue(2, &f->pc);

    //volta pc para o inicio da instrucao, para caso ela tenha que ser executada novamente
    f->pc -= 3;

    frame *aux = f;
    cp_info cp_element = f->cp[indexByte];
    if(cp_element.tag != FIELD_REF)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para FIELD_REF!");
    }

    string class_name = dereferenceIndex(f->cp, cp_element.info[0].u2);

    cp_info name_and_type_element = f->cp[cp_element.info[1].u2];
    if(name_and_type_element.tag != NAME_AND_TYPE)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
    }

    string name = dereferenceIndex(f->cp, name_and_type_element.info[0].u2);
    string descriptor = dereferenceIndex(f->cp, name_and_type_element.info[1].u2);

    // JAVA LANG
    if (class_name == "java/lang/System" && descriptor == "Ljava/io/PrintStream;" )
	{
        f->pc+=3;
        return;
    }

    ClasseEstatica* static_class = getStaticClassThatHasField( MethodArea::getClass(class_name), name);

    if(static_class == NULL) throw std::runtime_error("Field nao existe na classe definida!");

    // Caso <clinit> seja empilhado.
    if (threads->top() != aux)
	{
        return;
    }

    typedElement element = static_class->getField(name);

    if(element.type == TYPE_BOOL) 
    {
        element.type = TYPE_INT;
    }

    f->operandos->push(element);

    //anda com o pc para a proxima instrucao
    f->pc += 3;
}

void Operacoes::putstatic()
{
    frame *aux = f;

    uint16_t indexByte = getNBytesValue(2, &f->pc);
    cp_info cp_element = f->cp[indexByte];
    if(cp_element.tag != FIELD_REF)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para FIELD_REF!");
    }

    string class_name = dereferenceIndex(f->cp, cp_element.info[0].u2);

    cp_info name_and_type_element = f->cp[cp_element.info[1].u2];
    if(name_and_type_element.tag != NAME_AND_TYPE)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
    }

    string name = dereferenceIndex(f->cp, name_and_type_element.info[0].u2);
    string descriptor = dereferenceIndex(f->cp, name_and_type_element.info[1].u2);

    // JAVA LANG
    if (class_name == "java/lang/System" && descriptor == "Ljava/io/PrintStream;" )
	{
        return;
    }

    ClasseEstatica* static_class = getStaticClassThatHasField( MethodArea::getClass(class_name), name);

    if(static_class == NULL) throw std::runtime_error("Field nao existe na classe definida!");

    // Caso <clinit> seja empilhado.
    if (threads->top() != aux)
	{
        return;
    }

    typedElement stack_element = f->operandos->popTyped();

    if(descriptor[0] == 'B') 
    {
        stack_element.type = TYPE_BOOL;
    }

    static_class->setField(name,stack_element);
}

void Operacoes::getfield()
{
    uint16_t indexbyte = getNBytesValue(2, &f->pc);

    ClasseInstancia *ci = (ClasseInstancia *) f->operandos->pop().pi;
    
    if (ci == nullptr)
	{
        throw std::runtime_error("Null Pointer Exception");
    }

    int index = f->cp[indexbyte].info[1].u2;
    index = f->cp[index].info[0].u2;
    typedElement ret = ci->getField(dereferenceIndex(f->cp, index));
    f->operandos->push(ret);
}

void Operacoes::putfield()
{
    typedElement value = f->operandos->popTyped();
    ClasseInstancia *ci = (ClasseInstancia *) f->operandos->pop().pi;
    uint16_t indexbyte = getNBytesValue(2, &f->pc);

    if (ci == nullptr)
	{
        throw std::runtime_error("Null Pointer Exception");
    }

    int index = f->cp[indexbyte].info[1].u2;
    index = f->cp[index].info[0].u2;

    if (dereferenceIndex(f->cp, f->m.name_index) == "<init>")
	{
        ci->setFinals(dereferenceIndex(f->cp, index), value);
    } else {
        ci->setField(dereferenceIndex(f->cp, index), value);
    }
}

void Operacoes::invokevirtual()
{
    frame *aux = f;

    uint16_t indexByte = getNBytesValue(2, &f->pc);

    cp_info cp_element = f->cp[indexByte];
    if(cp_element.tag != METHOD_REF)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para METHOD_REF!");
    }

    string class_name = dereferenceIndex(f->cp, cp_element.info[0].u2);

    cp_info name_and_type_element = f->cp[cp_element.info[1].u2];
    if(name_and_type_element.tag != NAME_AND_TYPE)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
    }

    string name = dereferenceIndex(f->cp, name_and_type_element.info[0].u2);
    string descriptor = dereferenceIndex(f->cp, name_and_type_element.info[1].u2);


    if (class_name.find("java/") != string::npos)
	{
        // simulando println ou print
        if (class_name == "java/io/PrintStream" && (name == "print" || name == "println"))
		{
            if (descriptor != "()V")
			{
                typedElement element = f->operandos->popTyped();
                switch (element.realType)
				{
                    case RT_DOUBLE:
                        printf("%f", element.value.d);
                        break;
                    case RT_FLOAT:
                        printf("%f", element.value.f);
                        break;
                    case RT_LONG:
                        printf("%ld", element.value.ls);
                        break;
                    case RT_REFERENCE:
                        cout << showUTF8((unsigned char *)element.value.pi, 0);
                        break;
                    case RT_BOOL:
                        printf("%s", element.value.b == 0 ? "false" : "true");
                        break;
                    case RT_BYTE:
                        printf("%d", element.value.b);
                        break;
                    case RT_CHAR:
                        printf("%c", element.value.bs);
                        break;
                    case RT_SHORT:
                        printf("%d", element.value.ss);
                        break;
                    case RT_INT:
                        printf("%d", element.value.is);
                        break;
                    default:
                        // PRECISA ?
                    	//cout << "" << endl;
                        //throw std::runtime_error("Dado Invalido.");
                        printf("%d", element.value.is);
                        break;
                }
            }

            if (name == "println") printf("\n");

        } else if (class_name == "java/lang/String" && name == "length")
		{

            typedElement element = f->operandos->popTyped();

            if(element.realType == RT_REFERENCE)
			{
                typedElement ret;
                ret.type = TYPE_INT;
                ret.realType = RT_INT;

                ret.value.i = showUTF8((unsigned char *)element.value.pi, 0).size();

                f->operandos->push(ret);
            }
            else 
            {
            	throw std::runtime_error("Dado Invalido.");
            }



        } else if (class_name == "java/lang/String" && name == "equals")
		{

            typedElement element_1 = f->operandos->popTyped();
            typedElement element_2 = f->operandos->popTyped();

            if(element_1.realType == RT_REFERENCE && element_2.realType == RT_REFERENCE)
			{
                typedElement ret;
                ret.type = TYPE_INT;
                ret.realType = RT_INT;

                if (showUTF8((unsigned char *)element_1.value.pi, 0) == showUTF8((unsigned char *)element_2.value.pi, 0))
				{
                    ret.value.b = 1;
                } else {
                    ret.value.b = 0;
                }

                f->operandos->push(ret);
            }
            else 
            {
            	throw std::runtime_error("Dados Invalidos.");
            }


        } else {
            throw std::runtime_error("Metodo Invalido.");
        }
    } else {
        
        uint16_t num_args = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (descriptor[i] != ')') 
        {
            char baseType = descriptor[i];
            if (baseType == 'D' || baseType == 'J')
			{
                num_args += 2;
            } else if (baseType == 'L')
			{
                num_args++;
                while (descriptor[++i] != ';');
            } else if (baseType == '[')
			{
                num_args++;
                while (descriptor[++i] == '[');
                if (descriptor[i] == 'L') while (descriptor[++i] != ';');
            } else {
                num_args++;
            }
            i++;
        }

        vector<typedElement> args;
        for (int i = 0; i < num_args; i++) 
        {
            typedElement element = f->operandos->popTyped();
            args.insert(args.begin(), element);
        }

        typedElement object_element = f->operandos->popTyped();
        if(object_element.type == TYPE_REFERENCE)
        {
            throw std::runtime_error("Elemento não é uma referencia para REFERENCE!");
        }
        args.insert(args.begin(), object_element);

        ClasseInstancia* instance = (ClasseInstancia *) object_element.value.pi;

        //ClasseEstatica *classRuntime = MethodArea::getClass(class_name);
		MethodArea::getClass(class_name);

        // Caso <clinit> seja empilhado.
        if (threads->top() != aux)
		{
        	f->pc = f->pc - 3;
        	return;
    	}

        fs->addFrame(
            instance->getStatic()->getDef()->getMethod(name,descriptor), 
            instance->getStatic()->getDef()->getClassThatHasSerachedMethod(name,descriptor)->getCP()
        );
        fs->setArguments(args);
    }
}

void Operacoes::invokespecial()
{
    frame *auxFrame = threads->top();
    uint16_t indexByte = getNBytesValue(2, &f->pc);

    cp_info cp_element = f->cp[indexByte];
    if(cp_element.tag != METHOD_REF)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para METHOD_REF!");
    }

    string classe = dereferenceIndex(f->cp, cp_element.info[0].u2);

    cp_info metodo = f->cp[cp_element.info[1].u2];
    if(metodo.tag != NAME_AND_TYPE)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
    }

    string name = dereferenceIndex(f->cp, metodo.info[0].u2);
    string desc = dereferenceIndex(f->cp, metodo.info[1].u2);

    //checa se é uma das classes simuladas
    if ((classe == "java/lang/Object" || classe == "java/lang/String") && name == "<init>")
	{
        if (classe == "java/lang/String")
		{
            f->operandos->pop();
        }
        return;
    }
    
    //checa se o metodo que irá executar é válido
    if (classe.find("java/") != string::npos)
	{
        cerr << "ERRO: \"" << name << "\" nao definido." << endl;
        exit(1);
    } else {
        uint16_t count = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; //variavel para andar pelo descritor

        while (desc[i] != ')')
		{
            char baseType = desc[i];
            if (baseType == 'D' || baseType == 'J')
			{
                (++count)++;
            } else if (baseType == 'L')
			{
                count++;
                //para pular o nome da classe
                while (desc[++i] != ';');
            } else if (baseType == '[')
			{
                count++;
                //para pegar todas as dimensões mais rapidamente
                while (desc[++i] == '[');
                if (desc[i] == 'L')
				{
                    //para pular o nome da classe
                    while (desc[++i] != ';');
                }
            } else {
                count++;
            }
            i++;
        }

        //desempilha a quantidade de parametros calculada acima
        vector<typedElement> parametros;
        for (int i = 0; i < count; i++)
		{
            typedElement prox = f->operandos->popTyped();
            parametros.insert(parametros.begin(), prox);
        }
        
        typedElement object_element = f->operandos->popTyped();

        parametros.insert(parametros.begin(), object_element);

        ClasseInstancia* instance = (ClasseInstancia *) object_element.value.pi;

        //ClasseEstatica *classRuntime = MethodArea::getClass(classe);
		MethodArea::getClass(classe);

        //checa se houve uma mudança no método corrente, caso tenha, deixa o novo método executar
        if (threads->top() != auxFrame)
		{
            //empilha de volta os operandos desempilhados na ordem contrária que saíram
            f->operandos->push(parametros[0]);
            while (count-- > 0)
			{
                f->operandos->push(parametros[count]);
            }
            //volta com o pc para o opcode que vai ser executado novamente
            //ele já havia sido deslocado para o próximo opcode pela função getNBytes
            f->pc -= 3;
            return;
        }

        //cria o frame no topo da pilha
        fs->addFrame(
            instance->getStatic()->getDef()->getMethod(name,desc), 
            instance->getStatic()->getDef()->getClassThatHasSerachedMethod(name,desc)->getCP()
        );        
        //adiciona os parâmetros ao vetor de variáveis locais
        fs->setArguments(parametros);
    }
}

void Operacoes::invokestatic()
{
    frame *auxFrame = threads->top();
    uint16_t indexbyte = getNBytesValue(2, &f->pc);
    cp_info cp_element = f->cp[indexbyte];

    if(cp_element.tag != METHOD_REF)
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para METHOD_REF!");
    
    string class_name = dereferenceIndex(f->cp, cp_element.info[0].u2);
    cp_info name_and_type_element = f->cp[cp_element.info[1].u2];

    if(name_and_type_element.tag != NAME_AND_TYPE)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
    }

    
    string name = dereferenceIndex(f->cp, name_and_type_element.info[0].u2);
    string descriptor = dereferenceIndex(f->cp, name_and_type_element.info[1].u2);

    if (class_name == "java/lang/Object" && name == "registerNatives")
	{
        f->pc += 3;
        return;
    }

    if (class_name.find("java/") != string::npos)
	{
        cerr << "Tentando invocar metodo estatico invalido: " << name << endl;
    }
    else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (descriptor[i] != ')')
		{
            char baseType = descriptor[i];
            if (baseType == 'D' || baseType == 'J')
			{
                nargs += 2;
            } else if (baseType == 'L')
			{
                nargs++;
                while (descriptor[++i] != ';');
            } else if (baseType == '[')
			{
                nargs++;
                while (descriptor[++i] == '[');
                if (descriptor[i] == 'L') while (descriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<typedElement> args;
        for (int i = 0; i < nargs; i++)
		{
            typedElement elemento = f->operandos->popTyped();
            args.insert(args.begin(), elemento);
        }

        ClasseEstatica *ce = MethodArea::getClass(class_name);

        // Caso <clinit> seja empilhado.
        if (threads->top() != auxFrame)
		{
            //empilha de volta os operandos desempilhados na ordem contrária que saíram
            while (nargs-- > 0)
			{
                f->operandos->push(args[nargs]);
            }
            //volta com o pc para o opcode que vai ser executado novamente
            //ele já havia sido deslocado para o próximo opcode pela função getNBytes
            f->pc -= 3;
            return;
        }
        
        //cria o frame no topo da pilha
        fs->addFrame(
            ce->getDef()->getMethod(name,descriptor), 
            ce->getDef()->getClassThatHasSerachedMethod(name,descriptor)->getCP()
        );

        //adiciona os parâmetros ao vetor de variáveis locais
        fs->setArguments(args);

    }


}

void Operacoes::invokeinterface()
{
    frame *auxFrame = threads->top();
    uint16_t indexbyte = getNBytesValue(2, &f->pc);
    cp_info cp_element = f->cp[indexbyte];

    if (cp_element.tag != INTERFACE_REF)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para INTERFACE_REF!");
    }

    string class_name = dereferenceIndex(f->cp, cp_element.info[0].u2);
    cp_info name_and_type_element = f->cp[cp_element.info[1].u2];
    if(name_and_type_element.tag != NAME_AND_TYPE)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
    }

    string name = dereferenceIndex(f->cp, name_and_type_element.info[0].u2);
    string descriptor = dereferenceIndex(f->cp, name_and_type_element.info[1].u2);

    if (class_name.find("java/") != string::npos)
	{
        throw std::runtime_error("Tentativa de invocar metodo de interface invalido!");
    } else {
        uint16_t num_args = 0; //numero de argumentos na pilha de operandos
        uint16_t i = 1; //pulando primeiro argumento '('
        while (descriptor[i] != ')')
		{
            char baseType = descriptor[i];
            if (baseType == 'D' || baseType == 'J')
			{      //64 bits
                num_args += 2;
            } else if (baseType == 'L')
			{                  //referencia - instancia de class
                num_args++;
                while (descriptor[++i] != ';');
            } else if (baseType == '[')
			{                  // referencia
                num_args++;
                while (descriptor[++i] == '[');
                if (descriptor[i] == 'L') while (descriptor[++i] != ';');
            } else {
                num_args++;
            }
            i++;
        }
        
        vector<typedElement> parametros;
        for (int i = 0; i < num_args; i++)
		{
            typedElement elemento = f->operandos->popTyped();
            parametros.insert(parametros.begin(), elemento);
        }

        typedElement object_element = f->operandos->popTyped();
        if (object_element.type != TYPE_REFERENCE)
		{
            throw std::runtime_error("Elemento do topo da pilha não e uma referencia!");
        }
        parametros.insert(parametros.begin(), object_element);
        
        ClasseInstancia *instance = (ClasseInstancia *) object_element.value.pi;

        // Caso <clinit> seja empilhado.
        if (threads->top() != auxFrame)
		{
            //empilha de volta os operandos desempilhados na ordem contrária que saíram
            while (num_args-- > 0)
			{
                f->operandos->push(parametros[num_args]);
            }
            //volta com o pc para o opcode que vai ser executado novamente
            //ele já havia sido deslocado para o próximo opcode pela função getNBytes
            f->pc -= 3;
            return;
        }
        //cria o frame no topo da pilha
        fs->addFrame(
            instance->getStatic()->getDef()->getMethod(name,descriptor), 
            instance->getStatic()->getDef()->getClassThatHasSerachedMethod(name,descriptor)->getCP()
        );
        //adiciona os parâmetros ao vetor de variáveis locais
        fs->setArguments(parametros);
    }
}

void Operacoes::func_new()
{
    uint16_t indexbyte = getNBytesValue(2, &f->pc);
    string classe = dereferenceIndex(f->cp, indexbyte);
    ClasseEstatica *aux =  MethodArea::getClass(classe);

    if (aux == nullptr)
	{
        MethodArea::addClass(classe);
        aux = MethodArea::getClass(classe);
    }

    f->operandos->push((int*)aux->getInstance());
}

void Operacoes::newarray()
{
    uint8_t type = getNBytesValue(1, &f->pc);
    int32_t index = f->operandos->pop().is;

    if (index < 0)
        throw std::runtime_error("Negative Array Size.");

    int *array;

    switch(type)
	{
        case 4:
        array = (int*) new LocalVariables(index);
        break;
        case 5:
        array = (int*) new std::vector<uint8_t>(index);
        break;
        case 6:
        array = (int*) new LocalVariables(index);
        break;
        case 7:
        array = (int*) new LocalVariables(2*index, true);
        break;
        case 8:
        array = (int*) new LocalVariables(index);
        break;
        case 9:
        array = (int*) new LocalVariables(index);
        break;
        case 10:
        array = (int*) malloc(sizeof(index));
        break;
        case 11:
        array = (int*) new LocalVariables(2*index, true);
        break;
        default:
        array = (int*) new LocalVariables(index);
        break;
    }
    cout << array << endl;
    f->operandos->push(array);
}

void Operacoes::anewarray()
{
    //uint16_t indexbyte = getNBytesValue(2, &f->pc);
	getNBytesValue(2, &f->pc);
    int32_t count = f->operandos->pop().is;

    if (count < 0)
        throw std::runtime_error("Negative Array Size.");

    LocalVariables *array = new LocalVariables(count * (BITS ? 2:1), BITS);
    for (int i = 0; i < count; i++)
	{
        typedElement aux;
        aux.type = TYPE_REFERENCE;
        aux.value.pi = nullptr;
        array->set(i, aux);
    }

    f->operandos->push((int*)array);
}

void Operacoes::arraylength()
{
    LocalVariables *arrayref;

    arrayref = (LocalVariables *) f->operandos->pop().pi;
    if (arrayref == nullptr)
        throw runtime_error("Null pointer");

    f->operandos->push(arrayref->getMax());
}

void Operacoes::athrow()
{
    int type = f->operandos->top_type();
    element_u value = f->operandos->pop();

    while (!f->operandos->empty())
	{
        f->operandos->pop();
    }

    f->operandos->push(value, type); 
}


void Operacoes::wide()
{
	//seta a variavel global wide -> TRUE
	isWide = true;
	Operacoes::run(getNBytesValue(1, &f->pc));
}

//terminar
void Operacoes::multianewarray()
{

	uint16_t indexbyte = getNBytesValue(2, &f->pc);
	uint8_t dimensions = getNBytesValue(1, &f->pc);

    cp_info cp_element = f->cp[indexbyte];
    if(cp_element.tag != CLASS)
	{
        throw std::runtime_error("Elemento da constant pool apontado por index, não é uma referencia para CLASS!");
    }

    string class_name = dereferenceIndex(f->cp, cp_element.info[0].u2);

    typedElement element;

    int count = 0;
    
	   while (class_name[count] == '[')
	   {
	   		count++;
	   }


	   string multiArrayType = class_name.substr(count+1, class_name.size()-count-2); // em caso de ser uma referência (e.g. [[[Ljava/lang/String;)

	   switch (class_name[count])
	   {
	       case 'L':
	           if (multiArrayType != "java/lang/String")
			   {
	               MethodArea::getClass(multiArrayType); // verifica se existe classe com esse nome
	           }
	           element.realType = RT_REFERENCE;
	           element.type = TYPE_REFERENCE;
	           break;
	       case 'B':
	           element.realType = RT_BYTE;
	           element.type = TYPE_INT;
	           break;
	       case 'C':
	           element.realType = RT_CHAR;
	           element.type = TYPE_INT;
	           break;
	       case 'D':
	           element.realType = RT_DOUBLE;
	           element.type = TYPE_DOUBLE;
	           break;
	       case 'F':
	           element.realType = RT_FLOAT;
	           element.type = TYPE_FLOAT;
	           break;
	       case 'I':
	           element.realType = RT_INT;
	           element.type = TYPE_INT;
	           break;
	       case 'J':
	           element.realType = RT_LONG;
	           element.type = TYPE_LONG;
	           break;
	       case 'S':
	           element.realType = RT_SHORT;
	           element.type = TYPE_INT;
	           break;
	       case 'Z':
	           element.realType = RT_BOOL;
	           element.type = TYPE_INT;
	           break;
	       default:
	           exit(1);
	   }
    
    stack<int> count_dim;
    for (int i = 0; i < dimensions; i++)
	{
        // PRECISO VERIFICAR O TIPO (INT)?
        count_dim.push(f->operandos->popTyped().value.i);
    }

	int* p = (int*)(getNewMultiArray(count_dim));

	element.value.pi = p;
    
	f->operandos->push(element);
    
}

double Operacoes::getValue(n_array array, stack<int> access_indexes)
{
	int index = 1;
	int aux = 0;

	for(int i = 0 ; (unsigned int) i < sizeof(array.dims)/sizeof(*(array.dims)); i++)
	{
		aux += array.dims[i] * access_indexes.top();

		index = (aux * index) + aux;
		access_indexes.pop();
	}

	return array.array[index];

}

n_array *Operacoes::getNewMultiArray(stack<int> count_dim)
{
	int size = 1;
	int value;

	n_array *array = (n_array*) malloc(sizeof(n_array)) ;

	int* dims = (int*) malloc(sizeof(double) * count_dim.size());

	for(int i = 0; count_dim.size() > 0; i++)
	{

		value = count_dim.top();
		size *= value;
		dims[i] = value;
		count_dim.pop();
	}

	int* p = (int*) malloc(sizeof(double) * size);

	for(int i = 0; i < size; i++)
	{
		p[i] = 0;
	}

	array->dims = dims;
	array->array = p;

	return array;

}


void Operacoes::ifnull()
{
	int* ref = f->operandos->pop().pi;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (ref == nullptr)
		f->pc += branchbyte - 3;
}

void Operacoes::ifnonnull()
{
	int* ref = f->operandos->pop().pi;
	int16_t branchbyte = int16_t(getNBytesValue(2, &f->pc));

	if (ref != nullptr)
		f->pc += branchbyte - 3;
}

void Operacoes::goto_w()
{
	int32_t branchbyte = int32_t(getNBytesValue(4, &f->pc));

	f->pc += branchbyte - 5;
}

void Operacoes::jsr_w()
{
	int32_t offset = int32_t(getNBytesValue(4, &f->pc));

	f->operandos->push(f->pc);

	f->pc += offset - 5;
}

//Opcionais

void Operacoes::dup()
{
	typedElement value = f->operandos->popTyped();
	f->operandos->push(value);
	f->operandos->push(value);
}

void Operacoes::pop()
{
	f->operandos->popTyped();
}

void Operacoes::pop2()
{
	typedElement aux = f->operandos->popTyped();
	if (aux.type == TYPE_LONG || aux.type == TYPE_DOUBLE)
	{
		f->operandos->popTyped();
	}
}

void Operacoes::dup_x1()
{
	if (f->operandos->top_type() != TYPE_LONG && f->operandos->top_type() != TYPE_DOUBLE)
	{
		typedElement aux = f->operandos->popTyped();
		if (f->operandos->top_type() != TYPE_LONG && f->operandos->top_type() != TYPE_DOUBLE)
		{
			f->operandos->popTyped();
		} else {
			f->operandos->push(aux);
		}
	}
}

void Operacoes::dup_x2()
{
	typedElement aux = f->operandos->popTyped();
	if (f->operandos->top_type() != TYPE_LONG && f->operandos->top_type() != TYPE_DOUBLE)
	{
		typedElement aux2 = f->operandos->popTyped(), aux3 = f->operandos->popTyped();
		f->operandos->push(aux);
		f->operandos->push(aux3);
		f->operandos->push(aux2);
		f->operandos->push(aux);
	} else {
		typedElement aux2 = f->operandos->popTyped();
		f->operandos->push(aux);
		f->operandos->push(aux2);
		f->operandos->push(aux);
	}
}

void Operacoes::dup2()
{
	typedElement aux = f->operandos->popTyped();

	if (f->operandos->top_type() != TYPE_LONG && f->operandos->top_type() != TYPE_DOUBLE)
	{
		typedElement aux2 = f->operandos->popTyped();
		f->operandos->push(aux2);
		f->operandos->push(aux);
		f->operandos->push(aux2);
		f->operandos->push(aux);
	} else {
		f->operandos->push(aux);
		f->operandos->push(aux);
	}
}

void Operacoes::dup2_x1()
{
	typedElement aux = f->operandos->popTyped();

	if (f->operandos->top_type() != TYPE_LONG && f->operandos->top_type() != TYPE_DOUBLE)
	{
		typedElement aux2 = f->operandos->popTyped(), aux3 = f->operandos->popTyped();
		f->operandos->push(aux2);
		f->operandos->push(aux);
		f->operandos->push(aux3);
		f->operandos->push(aux2);
		f->operandos->push(aux);
	} else {
		typedElement aux2 = f->operandos->popTyped();
		f->operandos->push(aux);
		f->operandos->push(aux2);
		f->operandos->push(aux);
	}
}

void Operacoes::dup2_x2()
{
	typedElement aux = f->operandos->popTyped();

	if (f->operandos->top_type() != TYPE_LONG && f->operandos->top_type() != TYPE_DOUBLE)
	{
		typedElement aux2 = f->operandos->popTyped(), aux3 = f->operandos->popTyped();
		if (aux3.type == TYPE_LONG || aux3.type == TYPE_DOUBLE)
		{
			f->operandos->push(aux2);
			f->operandos->push(aux);
			f->operandos->push(aux3);
			f->operandos->push(aux2);
			f->operandos->push(aux);
		} else {
			typedElement aux4 = f->operandos->popTyped();
			f->operandos->push(aux2);
			f->operandos->push(aux);
			f->operandos->push(aux4);
			f->operandos->push(aux3);
			f->operandos->push(aux2);
			f->operandos->push(aux);
		}
	} else {
		typedElement aux2 = f->operandos->popTyped();
		if (aux2.type == TYPE_LONG || aux2.type == TYPE_DOUBLE)
		{
			f->operandos->push(aux);
			f->operandos->push(aux2);
			f->operandos->push(aux);
		} else {
			typedElement aux3 = f->operandos->popTyped();
			f->operandos->push(aux);
			f->operandos->push(aux3);
			f->operandos->push(aux2);
			f->operandos->push(aux);
		}
	}
}

void Operacoes::swap()
{
	typedElement aux = f->operandos->popTyped(), aux2 = f->operandos->popTyped();
	f->operandos->push(aux);
	f->operandos->push(aux2);
}