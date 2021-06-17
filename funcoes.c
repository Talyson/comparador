#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"
#define TAMBUFFER 4096
char **alocaMemoriaArquivo(char *nomeArquivo)
{
	long long int qtdLinhaArquivo = quantidadeLinhasNoArquivo(nomeArquivo), contador = 0;
	FILE *arquivo = fopen(nomeArquivo, "r");
	char buffer[TAMBUFFER];
	if(arquivo == NULL)
	{
		perror("[-] Erro ao abrir arquivo");
		exit(1);
	}
	char **lista = (char **) malloc(qtdLinhaArquivo * sizeof(char *));
	if(lista == NULL)
	{
		perror("[-] Erro ao alocar memoria");
		exit(1);
	}

	while(!feof(arquivo)){
		memset(buffer, '\0', TAMBUFFER);
		fgets(buffer, TAMBUFFER, arquivo);
		removeCRLF(buffer);
		lista[contador] = strndup(buffer, strlen(buffer)+1);
		strcpy(lista[contador], buffer);
		contador++;
	}
	fclose(arquivo);
	return lista;
}

void removeCRLF(char *buffer)
{
	char *posCRLF;
	if ((posCRLF = strchr(buffer, '\n')) != NULL)
	{
		*posCRLF = '\0';
	}
	if ((posCRLF = strchr(buffer, '\r')) != NULL)
	{
		*posCRLF = '\0';
	}
}

long long int quantidadeLinhasNoArquivo(char *nomeArquivo)
{
	int quantidade = 0;
	char buffer[TAMBUFFER];
	FILE *arquivo = fopen(nomeArquivo, "r");
	if(arquivo == NULL)
	{
		perror("[-] Erro ao abrir arquivo");
		return -1;
	}
	while(!feof(arquivo))
	{
		fgets(buffer, TAMBUFFER, arquivo);
		quantidade++;
	}
	fclose(arquivo);
	return --quantidade;
}

int comparaString(const void *str1, const void *str2)
{
    const char *a = *(const char**)str1;
    const char *b = *(const char**)str2;
    return strcmp(a, b);
}
