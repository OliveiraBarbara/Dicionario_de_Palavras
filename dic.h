/***************************************************
Nome: Bárbara Beatriz Bueno de Oliveira
RGA: 2019.0743.014-8
Implementacao 1
Disciplina: Estruturas de Dados e Programacao I
Professor: Ronaldo Fiorilo
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 
#define TAM 29 /*Tamanho da Tabela Hash*/

/*Struct da lista para armazenar os sinonimos*/
typedef struct lista_sin{
	char sinonimo[MAX];
	struct lista_sin *prox_sin; 
}lista_sin;

/*Struct da lista para armazenar as palavras*/
typedef struct hash{
	char palavra[MAX];
	struct lista_sin *primeiro_conceito;
	struct hash *prox; 
}hash;

/*Escopo de todas as funções utilizadas para solução dos problemas*/
lista_sin *aloca_sin(char *s);
hash *aloca(char *p, char *s);

void inicializarListaHash(hash *table);
void inicializaTabela(hash table[]);

int funcaoEspalhamento(char *palavra);
void insereListaHash(hash *table, char *termo, char *sinonimo);
void insereTabelaHash(hash *table, char *palavra, char *sinonimo);

void busca(hash *table, char *str);
void buscaTabela(hash *table, char *str);

void remover(hash *table, char *str);
void removeTabela(hash *table, char *str);

void verificaPalavraNula(hash *table, char *str);
void removeSinonimo(hash *table, char *str1, char *str2);
void removeSinonimoTabela(hash *table, char *str1, char *str2);

