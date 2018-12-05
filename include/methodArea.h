/** \file methodArea.h
*	\brief
*/
#ifndef METHOD_AREA
#define METHOD_AREA

class MethodArea;

#include "classeLeitor.h"
#include "baseTypes.h"
#include "constantPool.h"
#include "frame.h"
#include "classe.h"
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

///Classe responsável por todas as operações que gerenciam os métodos.
class MethodArea
{
private:
	static map<string, ClasseEstatica*> classes;
	static FrameStack *fs;


public:
	static string path;
	static ClasseEstatica *getClass(string);
    static bool addClass(string);
    static bool addClass(Leitor*);
    static void setFrameStack(FrameStack*);
};

#endif