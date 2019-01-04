#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAMBUFFER 4096
void removeCRLF(char *buffer);
int comparaString(const void *str1, const void *str2);
long long int quantidadeLinhasNoArquivo(char nomeArquivo[]);
char **alocaMemoriaArquivo(char nomeArquivo[]);
long long int buscaBinaria(char **str, int n, char *procurando);
int main(){
    char nomeBase[] = "1.txt";
	char nomeComparar[] = "2.txt";
	char nomeNovaLista[] = "diferente.txt";
	long long int qtdBase = quantidadeLinhasNoArquivo(nomeBase);
	long long int qtdComparar = quantidadeLinhasNoArquivo(nomeComparar);

	qtdBase = qtdBase - 1;
	qtdComparar = qtdComparar - 1;

	char **strsBase = alocaMemoriaArquivo(nomeBase);
	char **strsComparar = alocaMemoriaArquivo(nomeComparar);
	int i;
	qsort(strsBase, qtdBase, sizeof(strsBase), comparaString);
	FILE *arquivo = fopen(nomeNovaLista, "a+");
	for(i = 0; i < qtdComparar;i++){
		if(buscaBinaria(strsBase, qtdBase, strsComparar[i]) == -1){
			fputs(strsComparar[i], arquivo);
			fputc('\n', arquivo);
		}
	}
	fclose(arquivo);
	free(strsBase);
	free(strsComparar);
	return 0;
}
char **alocaMemoriaArquivo(char nomeArquivo[]){
	long long int qtdLinhaArquivo = quantidadeLinhasNoArquivo(nomeArquivo), contador = 0;
	FILE *arquivo = fopen(nomeArquivo, "r");
	char buffer[TAMBUFFER];
	if(arquivo == NULL){
		printf("[-] Erro ao abrir arquivo!\n");
		exit(1);
	}
	char **lista = (char **) malloc(qtdLinhaArquivo * sizeof(char *));
	if(lista == NULL){
		printf("[-] Erro ao alocar memoria!\n");
		exit(1);
	}

	while(!feof(arquivo)){
		memset(buffer, '\0', TAMBUFFER);
		fgets(buffer, TAMBUFFER, arquivo);
		removeCRLF(buffer);
		lista[contador] = strdup(buffer);
		strcpy(lista[contador], buffer);
		contador++;
	}
	fclose(arquivo);
	return lista;
}

void removeCRLF(char *buffer){
	char *posCRLF;
	if ((posCRLF = strchr(buffer, '\n')) != NULL){
		*posCRLF = '\0';
	}
	if ((posCRLF = strchr(buffer, '\r')) != NULL){
		*posCRLF = '\0';
	}
}

long long int quantidadeLinhasNoArquivo(char nomeArquivo[]){
	int quantidade = 0;
	char buffer[TAMBUFFER];
	FILE *arquivo = fopen(nomeArquivo, "r");
	if(arquivo == NULL){
		printf("[-] Erro ao abrir arquivo!\n");
		return -1;
	}
	while(!feof(arquivo)){
		fgets(buffer, TAMBUFFER, arquivo);
		quantidade++;
	}
	fclose(arquivo);
	return quantidade;
}

int comparaString(const void *str1, const void *str2){
    const char *a = *(const char**)str1;
    const char *b = *(const char**)str2;
    return strcmp(a, b);
}

long long int buscaBinaria(char **str, int n, char *procurando){
	long long int i, inicio, meio, fim;
	int resultado;
	inicio = 0;
	fim = n - 1;
	while(inicio <= fim){
		meio = (inicio + fim) / 2;
		resultado = strcmp(procurando, str[meio]);
		if(resultado < 0){
			fim = meio - 1;
		}
		else{
			if(resultado > 0){
				inicio = meio + 1;
			}
			else{
				return meio;
			}
		}
	}
	return -1;
}
