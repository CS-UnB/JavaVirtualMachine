/* 
	Classe que irá realizar a leitura do bytecode e salvar as informações do class file
*/
#include "classeLeitor.h"


/**
* Construtor que configura um objeto da classe Leitor com o nome do arquivo passado.
* 
* @param in argumento passado como nome do arquivo na inicializacao do programa
*/
Leitor::Leitor(char *in) 
{
	if (in) 
	{	//associa o nome do arquivo passado a variavel filename
		fileName = in;
	}
	status = -1;
}

/**
* Construtor que configura um objeto da classe Leitor com o nome do arquivo passado.
* 
* @param in argumento passado como nome do arquivo na inicializacao do programa
*/
Leitor::Leitor(std::string in) 
{
	//verifica se o arquivo passado é vazio
	if (!in.empty()) 
	{
		//copia para fileName o nome do arquivo lido
		fileName = new char[in.size() + 1];
		std::copy(in.begin(), in.end(), fileName);
		fileName[in.size()] = 0; 
	}
	status = -1;
}

/**
* Armazenador e exibidor do programa
* @return variavel status que indica se houve erro no programa
*/
int Leitor::run() 
{	
	//carrega o bytecode na classe e verifica se nao retornou erro
	if(load() == 0) 
	{
		//imprime o bytecode lido
		show();
	}

	//retorna o status que indica se houve erro na leitura ou nao
	return this->status;
}

/**
* Carrega o class file na classe
* @return variavel status que indica se houve erro no programa
*/
int Leitor::load() 
{
	int checkCP;

	//verifica se o arquivo passado existe
	if (!fileName) 
	{
		//imprime "Argumento passado invalido!"
		printf("%s\n", getError(MISSING_ARGUMENT).c_str());
		return (status = MISSING_ARGUMENT);
	}

	//verifica se o arquivo possui a extensao .class
	if (!validExtension()) 
	{
		// imprime "ERRO: O arquivo deve ter a extensao .class!\n"
		printf("%s\n", getError(INVALID_EXTENSION).c_str());
		return (status = INVALID_EXTENSION);
	}

	//abre o arquivo para leitura
	fp = fopen(fileName, "rb");

	//verifica se o arquivo conseguiu ser aberto para leitura
	if (fp == NULL) 
	{
		//imprime "ERRO: nao foi possivel abrir o arquivo ..."
		printf("%s\n", getError(CANT_OPEN).c_str());
		return (status = CANT_OPEN);
	}

	//verifica se o arquivo comeca com o magic number
	if (readU4(fp) != 0xcafebabe) //le 32 bits
	{
		//se nao possui 0xcafebabe o arquivo é invalido
		printf("%s\n", getError(INVALID_FILE).c_str());
		return (status = INVALID_FILE);
	}

	//armazena o minor version
	minVersion = readU2(fp);

	//armazena major version
	majVersion = readU2(fp);
	
	//le o numero de constantes na constant pool
	lengthCP = readU2(fp);

	//carrega a ConstantPool na memoria chamando o metodo que se encontra na classe da constantPool
	constantPool = (cp_info *) malloc(sizeof(cp_info) * lengthCP);
	checkCP = loadConstantPool(constantPool, lengthCP, fp);

	//verifica se todos os elementos foram lidos
	if (checkCP != lengthCP) 
	{
		//se todos n tiverem sido lidos entao alguma constante tem um tipo nao conhecido
		cerr << getError(UNKNOWN_TYPE);
		return (status = UNKNOWN_TYPE);
	}

	//le as Flags de acesso
	accessFlags = readU2(fp);

	//le a classe definida pelo arquivo
	this_class = readU2(fp);

	//verifica se o nome do arquivo bate com o nome da class definida no bytecode
	if (!checkThisClass()) 
	{
		cerr << getError(INVALID_NAME);
		return (status = INVALID_NAME);
	}

	//armazena informacao sobre a superclass
	super_class = readU2(fp);

	//le o numero de interfaces
	interfacesCount = readU2(fp);

	//carrega as interfaces
	interfaces = readInterfaces(fp, interfacesCount);

	//le o numero de fields
	fieldsCount = readU2(fp);

	//carrega os fields na memoria
	fields = readFields(fp, fieldsCount,constantPool);

	//le o numero de metodos
	methodsCount = readU2(fp);

	//carrega os metodos na memoria
	methods = read_Methods(fp, methodsCount,constantPool);

	//le o numero de atributos
	attributesCount = readU2(fp);

	//carrega atributos
	attributes = readAttributes(fp, constantPool, attributesCount);

	//verifica se o metodo main esta entre os metodos lidos no bytecode
	foundMain = findMain();

	//verifica se existe o metodo <clinit>
	foundClinit = findClinit();

	//fecha o arquivo
	fclose(fp);
	fp = NULL;

	//se nao houve nenhum erro retorna 0
	return (status = 0);
}

/**
* Impressão do programa
* @return true ou false dependendo se a variavel status indicar que houve erro na leitura
*/
bool Leitor::show() 
{
	//verifica se o arquivo foi lido
	if (status != 0) 
	{
		return false;
	}

	//imprime as informacoes basicas lidas
	printGeneralInformation();

	//chama o metodo que se encontra na classe constantPool para imprimir as constantes
	printConstantPool(constantPool, lengthCP);

	//chama o metodo que se encontra na classe interfaces para imprimi-las
	printInterfaces(interfaces, constantPool, interfacesCount);

	//chama o metodo que se encontra na classe fields para imprimir os fields
	printFields(fields, constantPool, fieldsCount);

	//chama o metodo que se encontra na classe methods para imprimir os metodos
	printMethods(methods, constantPool, methodsCount);

	//chama o metodo que se encontra na classe attributes para imprimir os atributos
	printAttributes(attributes, constantPool, attributesCount);

	return true;
}

/**
* Exibidor do programa
* @return variavel status que indica se houve erro no programa
*/
void Leitor::printGeneralInformation ()
{
	cout << "" << endl;
	
	cout << "Minor version:\t\t " << minVersion << endl;
	
	cout << "Major version:\t\t " << majVersion << endl;

	cout << "Constant pool count:\t " << lengthCP << endl;

	//imprime as flags 
	showFlags(accessFlags);
			
	//imprime a classe e o indice apontado
	cout << "This class:\t\t cp info #" << this_class << " <" << dereferenceIndex(constantPool, this_class) << ">" << endl;

	//imprime a super classe e o indice apontado
	cout << "Super class:\t\t cp info #" << super_class << " <" << dereferenceIndex(constantPool, super_class) << ">" << endl;	
	
	cout << "Interfaces count:\t " << interfacesCount << endl;
	
	cout << "Fields count:\t\t " << fieldsCount << endl;
	
	cout << "Methods count:\t\t " << methodsCount << endl;
		
	cout << "Attributes count:\t " << attributesCount << endl;

	cout << "" << endl;
}

/**
* Lê os ultimos caracteres do arquivo pra ver se formam a extensao .class
* @return booleano que indica se existe o .class
*/
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

/**
* verifia se o metodo main existe nos metodos lidos no bytecode
* @return booleano que indica se existe o metodo main
*/
bool Leitor::findMain () 
{
	bool encontrou = false;

	for (int i = 0; i < methodsCount; i++) 
	{
		int name = methods[i].name_index, desc = methods[i].descriptor_index, flags = methods[i].access_flags;
		
		//verifica se o nome do metodo se encontra dentro das referencias das constantes
		if ("main" == dereferenceIndex(constantPool, name)) 
		{
			//verifica se o descritor do metodo esta correto
			if ("([Ljava/lang/String;)V" == dereferenceIndex(constantPool, desc)) 
			{
				if ((flags & 0x09) == 0x09) 
				{
					mainMethod = i;
					encontrou = true;
					break;
				}
			}
		}
	}

	//se encontrou a main retorna true
	return encontrou;
}

/**
* verifia se o metodo clinit existe nos metodos lidos no bytecode
* @return booleano que indica se existe o metodo clinit
*/
bool Leitor::findClinit() 
{
	bool encontrou = false;

	for (int i = 0; i < methodsCount; i++) 
	{
		//pega o nome do metodo
		int name = methods[i].name_index;
		
		//verifica se o nome do metodo se encontra nas constantes
		if ("<clinit>" == dereferenceIndex(constantPool, name)) 
		{
			clinit = i;
			encontrou = true;
			break;
		}
	}

	return encontrou;
}

/**
* verifia se o metodo main foi encontrado
* @return booleano que indica se existe o metodo main
*/
bool Leitor::hasMain () 
{
	//retorna valor de foundMain
	return foundMain;
}

/**
* verifia se o metodo clinit foi encontrado
* @return booleano que indica se existe o metodo clinit
*/
bool Leitor::hasClinit () 
{
	//retorna o valor de foundClinit
	return foundClinit;
}

/**
* Retorna o metodo main no formato da struct method_info
* @return struct method_info contendo informações sobre o método
*/
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

/**
* Retorna o metodo clinit no formato da struct method_info
* @return struct method_info contendo informações sobre o método
*/
method_info Leitor::getClinit() 
{
	return methods[clinit];
}

/**
* Verifica se a .class lida no bytecode é a mesma que foi declarada no nome do arquivo
* @return booleano indicando se a .class está correta
*/
bool Leitor::checkThisClass () 
{
	int auxPos;
	
	string auxFilename(this->fileName);
	string auxClass = dereferenceIndex(this->constantPool, this->this_class);
	
	//remove extensao .class
	auxFilename = auxFilename.substr(0, auxFilename.size()-6);
	
	//remove nomes de pastas no Windows
	auxPos = auxFilename.find("\\");

	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	return (auxClass == auxFilename);
}

/**
* Retorna a variavel status que indica se houve erro na leitura do bytecode
* @return status
*/
int Leitor::getStatus () 
{
	return status;
}

/**
* Verifica qual foi o erro encontrado pelo programa
* @param error MACRO com o erro que foi encontrado
* @return string contendo informação sobre o tipo de erro encontrado
*/
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

/**
* método para pegar a constant pool lida
* @return Retorna a array com a constant pool
*/
cp_info* Leitor::getCP () const 
{
	return constantPool;
}

/**
* método para pegar a constant pool lida
* @return Retorna a array com a constant pool
*/
U2 Leitor::getLengthCP () 
{
	return lengthCP;
}

/**
* Verifica o caminho mais o nome do arquivo dependendo do sistema operacional
* @return Retorna a string com o caminho total do arquivo
*/
char *Leitor::getPath () 
{
	string path= "", auxFilename(this->fileName);
	char *caminho_arquivo;
	int auxPos;

	//navega pelas pastas do windows
	auxPos = path.find("\\");
	while(auxPos >= 0 && (unsigned int) auxPos <= path.size()) 
	{
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("\\");
	}

	//navega pelas pastas do linux
	auxPos = auxFilename.find("/");
	while(auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) 
	{
		path += auxFilename.substr(0, auxPos+1);
		auxFilename = auxFilename.substr(auxPos+1);
		auxPos = auxFilename.find("/");
	}

	//copia o resulta para a string caminho_arquivo
	caminho_arquivo = (char *) malloc(sizeof(char) * (path.size() + 1));
	for (unsigned int i = 0; i < path.size(); i++) 
	{
		caminho_arquivo[i] = path[i];
	}
	caminho_arquivo[path.size()] = '\0';

	return caminho_arquivo;
}

/**
* Retorna a array contendo os métodos
* @return array do tipo method_info
*/
method_info *Leitor::getMethods() 
{
	return methods;
}

/**
* Retorna o número de methods
* @return uint16_t indicando o numero de metodos
*/
U2 Leitor::getMethodsCount() 
{
	return methodsCount;
}

/**
* Retorna a variavel que indica o this_class
* @return uint16_t this_class
*/
U2 Leitor::getThis_class() 
{
	return this_class;
}

/**
* Retorna a variável que indica o super_class
* @return uint16_t super_class
*/
U2 Leitor::getSuper_class() 
{
	return super_class;
}

/**
* Retorna o número de fields
* @return uint16_t indicando o numero de fields
*/
U2 Leitor::getFieldsCount() 
{
	return fieldsCount;
}

/**
* Retorna a array com as fields lidas
* @return a array da struct field_info
*/
field_info *Leitor::getFields() 
{
	return fields;
}

/**
* Retorna um field
* @param field_name nome do field que deseja retornar 
* @return struct field_info com a informação da field passada no parâmetro
*/
field_info* Leitor::getField(string field_name) 
{
	//percorre a array com as fields  ate encontrar field desejada
	for(int i = 0; i < getFieldsCount(); i++) 
	{
		if(dereferenceIndex(constantPool, fields[i].name_index) == field_name )
		{
			return fields+i; 
		}
	}
	return NULL;

}

/**
* Retorna um method
* @param name nome do method 
* @param descriptor descritor do method
* @return struct field_info com a informação da field passada no parâmetro
*/
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

/**
* Retorna a classe do metodo que esta sendo procurado
* @param name nome do method 
* @param descriptor descritor do method
* @return classe Leitor
*/
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