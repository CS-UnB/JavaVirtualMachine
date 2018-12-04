/*!
 * \file
 * \brief Class.cpp
 */

#include "classe.h"
#include "pilhaOperandos.h"

/** \fn ClasseEstatica(Leitor* classeLida)
	\brief Construtor da ClasseEstatica

	\param Leitor informação do class file já carregada na memória
*/
ClasseEstatica::ClasseEstatica(Leitor *classeLida)
{
	classe = classeLida; ///class file lido
	int count = classeLida->getFieldsCount(); ///get numero de fields
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

/**
* Retorna as informações de um field
* @return struct typedElement que contém informações sobre nome do tipo e valor
*/
typedElement ClasseEstatica::getField(string s)
{
	typedElement field_encontrado;
	field_encontrado.type = TYPE_NOT_SET;

	for (map<string, typedElement*>::const_iterator i = staticFields.begin(); i != staticFields.end(); i++)
	{
	   if (i->first == s)
	   {
	   		return *(i->second);
	   }
	}

	return field_encontrado;
}

/**
* Coloca um novo valor pra um field
* @param s nome do field desejado
* @param novo tipo para o field
* @return booleano que indica se o field foi setado com o novo tipo ou não
*/
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

/**
* Marca Field como final
* @param s nome do field desejado
* @param novo tipo para o field
* @return booleano que indica se o field foi setado com o novo tipo ou não
*/
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

/**
* Carrega no heap uma instancia da Classe
* @return objeto do tipo ClasseInstancia
*/
ClasseInstancia *ClasseEstatica::getInstance()
{
	ClasseInstancia *objeto_classe = new ClasseInstancia(this);
	Heap::addObject(objeto_classe);
	
	return objeto_classe;
}

/**
* Retorna o class file
* @return ponteiro para a instancia de ClasseLeitor que contém as informações salvas na memória
*/
Leitor *ClasseEstatica::getDef()
{
	return classe;
}

/** 
	Lida com operações que manipulam a instância da classe
*/
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

/**
* Retorna o field instanciado
* @return struct typedElement que contém informações sobre nome do tipo e valor
*/
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

/**
* Retorna referência a classe estática
* @return ponteiro para a classe estática
*/
ClasseEstatica *ClasseInstancia::getStatic()
{
	return classe;
}

/**
* Define um field da ClasseInstancia
* @param s nome do field
* @param e novo tipo que será atribuido ao field
* @return booleano indicado se o field foi definido
*/
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

/**
* Marca Field como final
* @param s nome do field desejado
* @param novo tipo para o field
* @return booleano que indica se o field foi setado com o novo tipo ou não
*/
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

/**
* Mostra todas as classes instanciadas
*/
void ClasseInstancia::show()
{
	for (map<string, typedElement*>::const_iterator i = localFields.begin(); i != localFields.end(); i++)
	{
	   cout << i->first << endl;
	}
}
