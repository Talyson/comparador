#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("%s arquivo_base arquivo_comparacao arquivo_saida\n", argv[0]);
		return -1;
	}
    char *nomeBase = argv[1];
	char *nomeComparar = argv[2];
	char *nomeNovaLista = argv[3];
	long long int qtdBase = quantidadeLinhasNoArquivo(nomeBase);
	long long int qtdComparar = quantidadeLinhasNoArquivo(nomeComparar);

	char **strsBase = alocaMemoriaArquivo(nomeBase);
	char **strsComparar = alocaMemoriaArquivo(nomeComparar);
	qsort(strsBase, qtdBase, sizeof(char *), comparaString);
	FILE *arquivo = fopen(nomeNovaLista, "w");
	for(int i = 0; i < qtdComparar;i++)
	{
		if(bsearch(strsComparar+i,strsBase, qtdBase, sizeof(char *), comparaString) == NULL)
		{
			fputs(strsComparar[i], arquivo);
			fputc('\n', arquivo);
		}
	}
	fclose(arquivo);
	free(strsBase);
	free(strsComparar);
	return 0;
}
