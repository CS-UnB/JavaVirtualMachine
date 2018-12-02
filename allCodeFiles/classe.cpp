/*!
 * \file
 * \brief Class.cpp
 */

#include "classe.h"
#include "pilhaOperandos.h"

ClasseEstatica::ClasseEstatica(Leitor *classeLida)
{
	classe = classeLida;
	int count = classeLida->getFieldsCount();
	field_info *fields = classeLida->getFields();

	for (int i = 0; i < count; i++)
	{
		if ((fields[i].accessFlags & 0x08) && (fields[i].accessFlags & 0x010) == 0)
		{
			typedElement *auxValue = (typedElement *) malloc(sizeof(typedElement));
			auxValue->value.l = 0;
			string desc = dereferenceIndex(classeLida->getCP(), fields[i].descriptor_index);

			switch (desc[0])
			{
				case 'B':
					auxValue->type = TYPE_BOOL;
					break;
				case 'C':
					auxValue->type = TYPE_INT;
					break;
				case 'D':
					auxValue->type = TYPE_DOUBLE;
					break;
				case 'F':
					auxValue->type = TYPE_FLOAT;
					break;
				case 'I':
					auxValue->type = TYPE_INT;
					break;
				case 'J':
					auxValue->type = TYPE_LONG;
					break;
				case 'L':
					auxValue->type = TYPE_REFERENCE;
					break;
				case 'S':
					auxValue->type = TYPE_INT;
					break;
				case 'Z':
					auxValue->type = TYPE_BOOL;
					break;
				case '[':
					auxValue->type = TYPE_REFERENCE;
					break;
			}

			string auxName = dereferenceIndex(classeLida->getCP(), fields[i].name_index);
			staticFields.insert(pair<string, typedElement*>(auxName, auxValue));
		}
	}
}

typedElement ClasseEstatica::getField(string s)
{
	typedElement ret;
	ret.type = TYPE_NOT_SET;

	for (map<string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++)
	{
	   if (i->first == s)
	   {
	   		return *(i->second);
	   }
	}

	return ret;
}

bool ClasseEstatica::setField(string s, typedElement e)
{
	for (map<string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++)
	{
	   	if (i->first == s)
		   {
	   		if (i->second->type == e.type)
			{
		   		*(i->second) = e;
		   		return true;
	   		}
			else
			{
	   			break;
	   		}
	   	}
	}

	return false;
}

bool ClasseEstatica::setFinals(string s, typedElement e)
{
	for (map<string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++)
	{
	   	if (i->first == s)
		   {
	   		if (i->second->type == e.type)
			{
		   		*(i->second) = e;
		   		return true;
	   		}
			else
			{
	   			break;
	   		}
	   	}
	}

	return false;
}

ClasseInstancia *ClasseEstatica::getInstance()
{
	ClasseInstancia *ret = new ClasseInstancia(this);
	Heap::addObject(ret);
	
	return ret;
}

Leitor *ClasseEstatica::getDef()
{
	return classe;
}

ClasseInstancia::ClasseInstancia(ClasseEstatica* c)
{
	this->classe = c;

	int count = classe->getDef()->getFieldsCount();
	field_info *fields = classe->getDef()->getFields();
	for (int i = 0; i < count; i++)
	{
		if ((fields[i].accessFlags & 0x08) == 0)
		{
			typedElement *auxValue = (typedElement *) malloc(sizeof(typedElement));
			auxValue->value.l = 0;
			string desc = dereferenceIndex(classe->getDef()->getCP(), fields[i].descriptor_index);

			switch (desc[0])
			{
				case 'B':
					auxValue->type = TYPE_BOOL;
					break;
				case 'C':
					auxValue->type = TYPE_INT;
					break;
				case 'D':
					auxValue->type = TYPE_DOUBLE;
					break;
				case 'F':
					auxValue->type = TYPE_FLOAT;
					break;
				case 'I':
					auxValue->type = TYPE_INT;
					break;
				case 'J':
					auxValue->type = TYPE_LONG;
					break;
				case 'L':
					auxValue->type = TYPE_REFERENCE;
					break;
				case 'S':
					auxValue->type = TYPE_INT;
					break;
				case 'Z':
					auxValue->type = TYPE_BOOL;
					break;
				case '[':
					auxValue->type = TYPE_REFERENCE;
					break;
			}
			string auxName = dereferenceIndex(classe->getDef()->getCP(), fields[i].name_index);
			localFields.insert(pair<string, typedElement*>(auxName, auxValue));
		}
	}	
}

typedElement ClasseInstancia::getField(string s)
{
	typedElement ret;
	ret.type = TYPE_NOT_SET;

	for (map<string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++)
	{
	   if (i->first == s)
	   {
	   		return *(i->second);
	   }
	}

	return ret;
}

ClasseEstatica *ClasseInstancia::getStatic()
{
	return classe;
}

bool ClasseInstancia::setField(string s, typedElement e)
{
	for (map<string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++)
	{
	   	if (i->first == s)
		{
	   		if (i->second->type == e.type)
			{
		   		*(i->second) = e;
		   		return true;
	   		}
			else
			{
	   			break;
	   		}
	   	}
	}

	return false;
}

bool ClasseInstancia::setFinals(string s, typedElement e)
{
	for (map<string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++)
	{
	   	if (i->first == s)
		{
	   		if (i->second->type == e.type)
			{
		   		*(i->second) = e;
		   		return true;
	   		}
			else
			{
	   			break;
	   		}
	   	}
	}

	return false;
}

void ClasseInstancia::show()
{
	for (map<string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++)
	{
	   cout << i->first << endl;
	}
}
