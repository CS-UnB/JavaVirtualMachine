#include "methodArea.h"

map<string, ClasseEstatica*> MethodArea::classes;
string MethodArea::path = "";
FrameStack *MethodArea::fs = nullptr;

/**
 * Retorna referência para classe estática
 * 
 * @param s Nome da classe
 * 
 */
ClasseEstatica *MethodArea::getClass(string s)
{    
    for (map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
    {
        if (i->first == s)
        {
            return i->second;
        }
    }
    return nullptr;
}

/**
 * Carrega a classe na memória
 * 
 * @param s Nome da classe
 * 
 */
bool MethodArea::addClass(string s)
{
    for (map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
    {
       if (i->first == s)
       {
            return false;
       }
    }

    Leitor *l = new Leitor(string(path+s));


    if (!l->validExtension())
    {
        delete l;
        l = new Leitor(string(path+s+".class"));
    }

    if (l->load())
    {
        return false;
    }

    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(s, add));

    if (l->hasClinit())
    {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

/**
 * Carrega classe na memória
 * 
 * @param l informação do arquivo .class na memória
 * 
 */
bool MethodArea::addClass(Leitor *l)
{
    if (l->getStatus() == -1)
    {
        l->load();
    }

    switch (l->getStatus())
    {
        case 0:
            break;
        default:
            return false;
    }

    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(dereferenceIndex(l->getCP(), l->getThis_class()), add));

    if (l->hasClinit())
    {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

/**
 * Atualiza a referência da pilha de frames para o próximo frame
 * 
 * @param newFS próximo frame
 * 
 */
void MethodArea::setFrameStack(FrameStack *newFS)
{
    fs = newFS;
}