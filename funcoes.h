#ifndef FUNCOES_H
#define FUNCOES_H
/*Função responsável de remover caracteres de nova linha*/
void removeCRLF(char *buffer);
/*Função responsável por comparar duas strings:
    -Retorna 0 se as string forem iguais
    -Retorna 1 se a string A > B
    -Retorna -1 se a string A < B
Sim faz a mesma coisa que a strcmp, mas essa é usa vesão feita para ser usada com a funcao qsort e bsearch.
*/
int comparaString(const void *str1, const void *str2);
/*Retorna a quantidade de linha em um arquivo.*/
long long int quantidadeLinhasNoArquivo(char *nomeArquivo);
/*Lê e aloca memória para o conteudo de um arquivo.*/
char **alocaMemoriaArquivo(char *nomeArquivo);

#endif