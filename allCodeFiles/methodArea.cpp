/*!
 * \file
 * \brief MethodArea.cpp
 */

#include "methodArea.h"

map<string, ClasseEstatica*> MethodArea::classes;
string MethodArea::path = "";
FrameStack *MethodArea::fs = nullptr;


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

bool MethodArea::addClass(string s)
{
    // Check if class already have been loaded
    for (map<string, ClasseEstatica*>::const_iterator i = classes.begin(); i != classes.end(); i++)
    {
       if (i->first == s)
       {
            return false;
       }
    }

    Leitor *l = new Leitor(string(path+s));


    // Check if it's a .class file
    if (!l->validExtension())
    {
        delete l;
        l = new Leitor(string(path+s+".class"));
    }

    // Read the file and check if it finish OK
    if (l->load())
    {
        return false;
    }

    // Add the new loaded class no the map, without the extension
    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(s, add));

    // Check if there is a method <clinit> in the class and add this method on the top of frame heap
    if (l->hasClinit())
    {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

bool MethodArea::addClass(Leitor *l)
{
    // Load a class in the memory if it's not loaded yet
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

    // Add the new loaded class no the map, without the extension
    ClasseEstatica *add = new ClasseEstatica(l);
    classes.insert(pair<string, ClasseEstatica*>(dereferenceIndex(l->getCP(), l->getThis_class()), add));

    // Check if there is a method <clinit> in the class and add this method on the top of frame heap
    if (l->hasClinit())
    {
        fs->addFrame(l->getClinit(), l->getCP());
    }

    return true;
}

void MethodArea::setFrameStack(FrameStack *newFS)
{
    fs = newFS;
}