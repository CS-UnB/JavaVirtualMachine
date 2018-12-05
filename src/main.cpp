/*!
 * \file main.cpp
 * \brief 
 */
#include "classeLeitor.h"
#include "frame.h"
#include "methodArea.h"


/**
 * Funcao principal, dá a opção de escolha entre interpretador e exibidor
 * 
 * @param argc, *argv[]
 * @section Integrantes:
 * 	André Luis Souto 		14/0016261
	Bruno Cordeiro Mendes 		15/0007094
	Michelangelo da Rocha Machado	14/0156089
	Otto Kristian von Sperling	12/0131510
	Victor Fabre Figueiredo         15/0022948
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Parametros invalidos, o programa deve ser executado com: %s [-e ou -i] caminho_arquivo\n", argv[0]);
		return 1;
	}

	Leitor leitor(argv[2]);

	if (argv[1][1] == 'e')
	{
		leitor.run();
	}
	else if (argv[1][1] == 'i')
	{
		leitor.load();

		if (!leitor.hasMain())
		{
			printf("O arquivo %s nao possui metodo main\n", argv[2]);
			return -1;
		}
		else if (leitor.getStatus())
		{
			return leitor.getStatus();
		}

		MethodArea::path = string(leitor.getPath());
		MethodArea::addClass(&leitor);

		FrameStack frames(&leitor);
	  	frames.execute();
	}
	else
	{
		printf("Parametros invalidos, o programa deve ser executado com: %s [-e ou -i] caminho_arquivo\n", argv[0]);
		return 1;
	}

	return 0;
}
