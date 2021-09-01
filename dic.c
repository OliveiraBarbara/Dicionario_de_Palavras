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
#include "dic.h"

/*Inicializo todas as posicoes da tabela hash*/
void inicializaTabela(hash table[]){
	int i;
	
	for(i = 0; i < TAM; i++){
		inicializarListaHash(&table[i]); /*para cada posicao da tabela, inicializo a lista*/
	}
}

void inicializarListaHash(hash *table){ /*inicializo a lista com cabeça de cada posição da tabela hash*/
	strcpy(table->palavra, "");
	table->primeiro_conceito = NULL;
	table->prox = NULL;
}

/*Funcao aloca uma posicao na memoria para guardar uma celula da lista de sinonimos*/
lista_sin *aloca_sin(char *s){
	lista_sin *nova;
	
	nova = (lista_sin *) malloc (sizeof (lista_sin)); /*aloco um espaco na memoria*/
	
	if(nova != NULL){
		strcpy(nova->sinonimo, s); /*na posição da lista na variavel do sinonimo eu atribuo o sinonimo correto*/
		nova->prox_sin = NULL;
	}else{ /*se a alocacao nao deu certo, informo na tela*/
		printf("Erro ao alocar memória\n");
	}
	return nova;
}

/*Funcao aloca: Aloca na memoria uma posicao em uma lista para guardar uma celula*/
hash *aloca(char *p, char *s){
	hash *nova;
	
	nova = (hash *) malloc (sizeof (hash)); /*aloco um espaço na memoria*/
	
	if(nova!= NULL){
		strcpy(nova->palavra, p); /*na posicao alocada da lista atibuo a palavra na variavel*/
		nova->primeiro_conceito = aloca_sin(s); /*aloco a posicao da lista de sinonimos*/
		nova->prox = NULL;
		
	}else{ /*se a alocacao nao deu certo, informo na tela*/
		printf("Erro ao alocar memória\n");
	}
	return nova;
}

/*Funcao que defino qual sera o criterio de espalhamento*/
int funcaoEspalhamento(char *palavra){
	int ascii;
	
	ascii = palavra[0]; /*para saber em qual posicao vou colocar a palvra, faco a primeira letra da palavra ser um inteiro correspondente da Tabela ASCII*/
	return ascii % TAM; /*o valor correspondente da letra na Tabela Ascii mod o tamanho da tabela hash, corresponde a posicao da hash que a palavra vai ocupar*/
}

void insereTabelaHash(hash *table, char *palavra, char *sinonimo){ /*Funcao utilizada na main para passar a tabela hash e a palavra*/
	int indice = funcaoEspalhamento(palavra); /*Envio a palavra que quero inserir por parametro para a funcao de Espalhamento para fazer o  calculo*/
	insereListaHash(&table[indice], palavra, sinonimo); /*com a posicao que que devo inserir, chamo a funcao que ira criar uma nova posicao na lista na posicao*/
}

void insereListaHash(hash *table, char *termo, char *sinonimo){
	hash *nova;
	lista_sin *q;

	if(table->prox == NULL){ /*Se aquela posicao ainda estivar vazia, faco uma alocacao no  inicio*/
		nova = aloca(termo, sinonimo);
		nova->prox = table->prox;
		table->prox = nova;
	}else{ /*se nao estiver vazia eu verifico se a palavra encontra-se na lista, se não estiver faco a alocacao da palavra e do seu respectivo sinonimo, e se a palavra ja estiver na lista, eu só aloco o sinonimo naquela palavra*/
		nova = table->prox;
		while (!(nova == NULL) && (strcmp(nova->palavra, termo) != 0)){
			nova = nova->prox;
		}
		if (nova == NULL){
			nova = aloca(termo, sinonimo);
			nova->prox = table->prox;
			table->prox = nova;
		}else{
			q = aloca_sin(sinonimo);
			q->prox_sin = nova->primeiro_conceito;
			nova->primeiro_conceito = q;
		}
	}
}

void buscaTabela(hash *table, char *str){ /*Funcao que utilizo na main para passar a tabela e a palavra*/
	int indice = funcaoEspalhamento(str); /*Envio a palavra que quero procurar por parametro para a funcao de Espalhamento para saber em qual posicao ela se encontra*/
	busca(&table[indice], str); /*chamo a funcao para buscar, na lista correspondente a posicao da tabela*/
}

void busca(hash *table, char *str){
	hash *p;
	lista_sin *q;
	
	if(table->prox == NULL){ /*verifico se a lista contem elementos, se não tiver já retorno a mensagem*/
		printf("hein?\n");
	}else{ /*se a lista não for nula, primeiro verifico se a palavra se encontra na lista, se não tiver retorno a mensagem e se tiver elementos, acesso a lista de sinonimos da palavra para retorna-los*/
		p = table->prox;
		while (p != NULL && (strcmp(p->palavra, str) != 0)){
			p = p->prox;
		}
		if(p == NULL){
			printf("hein?\n");			
		}else{
			for(q = p->primeiro_conceito; q != NULL; q = q->prox_sin)
				printf("%s\n", q->sinonimo);
		}
	}
}

void removeTabela(hash *table, char *str){ /*Funcao que utilizo na main para passar a tabela e a palavra*/
	int indice = funcaoEspalhamento(str); /*Envio a palavra que quero remover por parametro para a funcao de Espalhamento para saber em qual posicao ela se encontra*/
	remover(&table[indice], str);  /*chamo a funcao para remover, na lista correspondente a posicao da tabela*/
}

void remover(hash *table, char *str){
	hash *p, *q;
	p = NULL;
	q = table->prox;
	
	while (q != NULL && (strcmp(q->palavra, str) != 0)){ /*procuro a palavra na lista*/
		p = q;
		q = q->prox;
	}
	
	if (q != NULL){ /*se ela estiver na lista eu verifico se ela é a primeira palavra, se for a primeira eu faco a primeira posicao da tabela receber a palavra seguinte da que eu vou remover, e se ela nao for a primeira, faco a palavra anterior receber a seguinte da que vou remover*/
		if (p != NULL){
			p->prox = q->prox;
		}else{
			table->prox = q->prox;
		} 
		free(q); /*removo a palavra da lista*/
	}
}

void removeSinonimoTabela(hash *table, char *str1, char *str2){ /*Funcao que utilizo na main para passar a tabela, a palavra e o sinonimo*/
	int indice = funcaoEspalhamento(str1); /*Envio a palavra que quero remover por parametro para a funcao de Espalhamento para saber em qual posicao ela se encontra*/
	removeSinonimo(&table[indice], str1, str2);  /*chamo a funcao para remover, na lista correspondente a posicao da tabela*/
}

void removeSinonimo(hash *table, char *str1, char *str2){
	hash *q;
	lista_sin *p, *c;
	q = table->prox;
	c = NULL;
	
	while (q != NULL && (strcmp(q->palavra, str1) != 0)){ /*procuro a palavra na lista*/
		q = q->prox;
	}
	
	if (q != NULL){
		p = q->primeiro_conceito; /*o ponteiro para a lista de sinonimos recebe a posicao inicial para o primeiro sinonimo*/
		while (p != NULL && (strcmp(p->sinonimo, str2) != 0)){ /*procuro o sinonimo na lista de sinonimo*/
			c = p;
			p = p->prox_sin;
		}
		if (p != NULL){ /*se ele estiver na lista eu verifico se ele é o primeiro sinonimo, se for o primeiro eu faco a primeira posicao da lista de sinonimo receber o sinonimo seguinte da que eu vou remover, e se ele nao for o primeiro, faco o sinonimo anterior receber o seguinte da que vou remover*/
			if(c != NULL){
				c->prox_sin = p->prox_sin;
			}else{
				q->primeiro_conceito = p->prox_sin;
			}
			free(p); /*removo o sinonimo*/
		}
	}
	
	verificaPalavraNula(table, str1); /*chamo a funcao para verificar se a palavra ainda tem sinonimo*/
}

void verificaPalavraNula(hash *table, char *str){
	hash *aux, *p;
	aux = table->prox;
	p = NULL;
	
	while (aux != NULL && (strcmp(aux->palavra, str) != 0)){ /*procuro a palavra na lista*/
		p = aux;
		aux = aux->prox;
	}
	
	if(aux != NULL && aux->primeiro_conceito == NULL){ /*verifico se a palavra existe na lista e se a palavra tem sinonimos, se não tiver sinonimo e verifico se é a primeira palavra e faco a primeira posicao da tabela receber a palavra seguinte da que eu vou remover, e se ela nao for a primeira, faco a palavra anterior receber a seguinte da que vou remover*/
		if(p != NULL){
			p->prox = aux->prox;
		}else{
			table->prox = aux->prox;
		}
		free(aux); /*removo a palavra da lista*/
	}	
}
