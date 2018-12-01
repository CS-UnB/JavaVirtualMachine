/*!
 * \file
 * \brief ClasseLeitor.cpp
 */

#include "classeLeitor.h"

Leitor::Leitor(char *in) 
{
	if (in) 
	{
		fileName = in;
	}
	status = -1;
}

Leitor::Leitor(std::string in) 
{
	if (!in.empty()) 
	{
		fileName = new char[in.size() + 1];
		std::copy(in.begin(), in.end(), fileName);
		fileName[in.size()] = 0;
	}
	status = -1;
}

int Leitor::run() 
{	
	if(load() == 0) 
	{
		show();
	}

	return this->status;
}

int Leitor::load() 
{
	int checkCP;

	//checks if file has been passed and it is valid
	if (!fileName) 
	{
		printf("%s\n", getError(MISSING_ARGUMENT).c_str());
		//cerr << getError(MISSING_ARGUMENT);
		return (status = MISSING_ARGUMENT);
	}

	//checks if file has .class extension
	if (!validExtension()) 
	{
		printf("%s\n", getError(INVALID_EXTENSION).c_str());
		//cerr << getError(INVALID_EXTENSION);
		return (status = INVALID_EXTENSION);
	}

	fp = fopen(fileName, "rb");

	//checks if file has been succesfully opened
	if (fp == NULL) 
	{
		printf("%s\n", getError(CANT_OPEN).c_str());
		//cerr << getError(CANT_OPEN);
		return (status = CANT_OPEN);
	}

	//checks if assignment from file 0xcafebabe is ready
	if (readU4(fp) != 0xcafebabe) 
	{
		printf("%s\n", getError(INVALID_FILE).c_str());
		//cerr << getError(INVALID_FILE);
		return (status = INVALID_FILE);
	}

	//reads minor version
	minVersion = readU2(fp);

	//reads major version
	majVersion = readU2(fp);
	
	//reads number of constants on constant pool
	lengthCP = readU2(fp);

	//loads Constant Pool on Memmory
	constantPool = (cp_info *) malloc(sizeof(cp_info) * lengthCP);
	checkCP = loadConstantPool(constantPool, lengthCP, fp);

	//checks if all elements have been readed
	if (checkCP != lengthCP) 
	{
		cerr << getError(UNKNOWN_TYPE);
		return (status = UNKNOWN_TYPE);
	}

	//reads access flags from class
	accessFlags = readU2(fp);

	//reads class defined by file
	this_class = readU2(fp);

	if (!checkThisClass()) 
	{
		cerr << getError(INVALID_NAME);
		return (status = INVALID_NAME);
	}

	//reads superclass from file
	super_class = readU2(fp);

	//reads number of interfaces
	interfacesCount = readU2(fp);

	//loads interfaces
	interfaces = readInterfaces(fp, interfacesCount);

	//reads number of fields
	fieldsCount = readU2(fp);

	//loads fields
	fields = readFields(fp, fieldsCount,constantPool);

	//reads number of methods
	methodsCount = readU2(fp);

	//loads methods
	methods = read_Methods(fp, methodsCount,constantPool);

	//loads number of attributes
	attributesCount = readU2(fp);

	//loads attributes
	attributes = readAttributes(fp, constantPool, attributesCount);

	//checks if has main method on this class
	foundMain = findMain();

	//checks if has method <clinit>
	foundClinit = findClinit();

	//close file after reading has been finished
	fclose(fp);
	fp = NULL;

	return (status = 0);
}

bool Leitor::show() 
{
	//check if file has been read
	if (status != 0) 
	{
		return false;
	}

	//show .class general information
	printGeneralInformation();

	//show constant pool while dereferencing
	printConstantPool(constantPool, lengthCP);

	//show read interfaces
	printInterfaces(interfaces, constantPool, interfacesCount);

	//show present fields
	printFields(fields, constantPool, fieldsCount);

	//show present methods
	printMethods(methods, constantPool, methodsCount);

	//show presente attributes
	printAttributes(attributes, constantPool, attributesCount);

	return true;
}

void Leitor::printGeneralInformation ()
{
	cout << "" << endl;
	
	cout << "Minor version:\t\t " << minVersion << endl;
	
	cout << "Major version:\t\t " << majVersion << endl;

	cout << "Constant pool count:\t " << lengthCP << endl;

	//mostra as flags setadas
	showFlags(accessFlags);
			
	//dereferencia o indice apontado e o mostra
	cout << "This class:\t\t cp info #" << this_class << " <" << dereferenceIndex(constantPool, this_class) << ">" << endl;

	//dereferencia o indice apontado e o mostra
	cout << "Super class:\t\t cp info #" << super_class << " <" << dereferenceIndex(constantPool, super_class) << ">" << endl;	
	
	cout << "Interfaces count:\t " << interfacesCount << endl;
	
	cout << "Fields count:\t\t " << fieldsCount << endl;
	
	cout << "Methods count:\t\t " << methodsCount << endl;
		
	cout << "Attributes count:\t " << attributesCount << endl;

	cout << "" << endl;
}

bool Leitor::validExtension () 
{
	string aux = "", auxFilename(this->fileName);
	int size = auxFilename.size();

	if (size > 7) 
	{
		for (int i = size-6; i < size; i++) 
		{
			aux += auxFilename[i];
		}
	}

	return aux == ".class";
}

bool Leitor::findMain () 
{
	bool ret = false;

	for (int i = 0; i < methodsCount; i++) 
	{
		int name = methods[i].name_index, desc = methods[i].descriptor_index, flags = methods[i].access_flags;
		
		if ("main" == dereferenceIndex(constantPool, name)) 
		{
			if ("([Ljava/lang/String;)V" == dereferenceIndex(constantPool, desc)) 
			{
				if ((flags & 0x09) == 0x09) 
				{
					mainMethod = i;
					ret = true;
					break;
				}
			}
		}
	}

	return ret;
}

bool Leitor::findClinit() 
{
	bool ret = false;

	for (int i = 0; i < methodsCount; i++) 
	{
		int name = methods[i].name_index;
		// int desc = methods[i].descriptor_index, flags = methods[i].access_flags;
		
		if ("<clinit>" == dereferenceIndex(constantPool, name)) 
		{
			clinit = i;
			ret = true;
			break;
		}
	}

	return ret;
}


bool Leitor::hasMain () 
{
	return foundMain;
}

bool Leitor::hasClinit () 
{
	return foundClinit;
}

method_info Leitor::getMain() 
{
	if (foundMain) 
	{
		return methods[mainMethod];
	} 
	else 
	{
		throw runtime_error("Nao foi encontrado um metodo main!");
	}
}

method_info Leitor::getClinit() 
{
	return methods[clinit];
}

bool Leitor::checkThisClass () 
{
	int auxPos;
	
	string auxFilename(this->fileName);
	string auxClass = dereferenceIndex(this->constantPool, this->this_class);
	
	//removes extension
	auxFilename = auxFilename.substr(0, auxFilename.size()-6);
	
	//removes names from folders on Windows
	auxPos = auxFilename.find("\\");

	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//removes names from folders on linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	//removes names from folders on Windows 
	auxPos = auxClass.find("\\");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxClass.size()) 
	{
		auxClass = auxClass.substr(auxPos+1);
		auxPos = auxClass.find("\\");
	}

	//removes names from folders on linux
	auxPos = auxClass.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxClass.size()) 
	{
		auxClass = auxClass.substr(auxPos+1);
		auxPos = auxClass.find("/");
	}

	return (auxClass == auxFilename);
}

int Leitor::getStatus () 
{
	return status;
}

string Leitor::getError (int error) 
{
	string ret = "";
	switch (error) 
	{
		case MISSING_ARGUMENT:
				ret = "ERRO: Argumento passado invalido!\n";
				break;
			case CANT_OPEN:
				ret = "ERRO: nao foi possivel abrir o arquivo \"" + string(fileName) + "\"!\n";
				break;
			case INVALID_FILE:
				ret = "ERRO: Arquivo invalido!\nAssinatura \"cafe babe\" nao encontrada.\n";
				break;
			case UNKNOWN_TYPE:
				ret = "ERRO: Tipo nao reconhecido para o pool de constantes!\nNao foi possivel carregar todo o PC.";
				break;
			case INVALID_NAME:
				ret = "ERRO: O nome da classe definida nao bate com o do arquivo!\n";
				break;
			case INVALID_EXTENSION:
				ret = "ERRO: O arquivo deve ter a extensao .class!\n";
				break;
			default:
				break;
	}
	return ret;
}

cp_info* Leitor::getCP () const 
{
	return constantPool;
}

U2 Leitor::getLengthCP () 
{
	return lengthCP;
}

char *Leitor::getPath () 
{
	string path= "", auxFilename(this->fileName);
	char *ret;
	int auxPos;

	//navigates on folders on Windows 
	auxPos = path.find("\\");
	while(auxPos >= 0 && (unsigned int) auxPos <= path.size()) 
	{
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//navigates on folders on linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	//copy result to return path
	ret = (char *) malloc(sizeof(char) * (path.size() + 1));
	for (unsigned int i = 0; i < path.size(); i++) 
	{
		ret[i] = path[i];
	}
	ret[path.size()] = '\0';

	return ret;
}

method_info *Leitor::getMethods() 
{
	return methods;
}

U2 Leitor::getMethodsCount() 
{
	return methodsCount;
}

U2 Leitor::getThis_class() 
{
	return this_class;
}

U2 Leitor::getSuper_class() 
{
	return super_class;
}

U2 Leitor::getFieldsCount() 
{
	return fieldsCount;
}

field_info *Leitor::getFields() 
{
	return fields;
}

field_info* Leitor::getField(string field_name) 
{

	for(int i = 0; i < getFieldsCount(); i++) 
	{
		if(dereferenceIndex(constantPool, fields[i].name_index) == field_name )
		{
			return fields+i; 
		}
	}
	return NULL;

}

method_info* Leitor::getMethod(string name, string descriptor)
{
	method_info method;

	for(int i = 0; i < this->methodsCount; i++)
	{
		method = this->methods[i];
		string method_name = dereferenceIndex(this->constantPool, method.name_index);
		string method_desc = dereferenceIndex(this->constantPool, method.descriptor_index);

		if(descriptor == method_desc && name == method_name) 
		{
			return methods+i;
		}
	}

	if(getSuper_class() == 0) 
	{
		return NULL;
	}
	else 
	{
		ClasseEstatica* a = MethodArea::getClass(dereferenceIndex(this->constantPool, getSuper_class()));
		Leitor* l = a->getDef();
		
		return l->getMethod(name, descriptor);
	}
}

Leitor* Leitor::getClassThatHasSerachedMethod(string name, string descriptor)
{
	method_info* method;

	for(int i = 0; i < this->methodsCount; i++)
	{
		method = (this->methods)+i;

		string method_name = dereferenceIndex(this->constantPool, method->name_index);
		string method_desc = dereferenceIndex(this->constantPool, method->descriptor_index);

		if(descriptor == method_desc && name == method_name) 
		{
			return this;
		}
	}

	if(getSuper_class() == 0) 
	{
		return NULL;
	}
	else 
	{
		Leitor* l = MethodArea::getClass(dereferenceIndex(this->constantPool, getSuper_class()))->getDef();
		return l->getClassThatHasSerachedMethod(name, descriptor);
	}
}