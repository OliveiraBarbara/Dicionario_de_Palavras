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

int main(void){
	int j=0, k=0, i; /*Variáveis contadoras usadas na separação da string para vetor de palavras.*/
	char acao[MAX], string[MAX], str[2][MAX], str1[MAX], str2[MAX], id1[MAX], id2[MAX]; /*Acao: Variavel utilizada para ler qual operacao realizarei no processo // String: utilizada para ler as palavras que vai remover // Vetor Str: utilizada para separa a string de palavras com espaço, cada uma em uma posição do vetor // Str1 e Str2: usadas para ler as palavras que vou inserir ou buscar // Id1 e Id2: usadas para ler o idioma.*/
	hash tabela[TAM]; /*Declaração da Tabela Hash com 29 posições.*/
	
	inicializaTabela(tabela); /*inicializo cada posição do vetor*/
	
	scanf("%s", acao); /*leio o qual opção devo realizar*/

	/*While para continuar fazendo processos enquanto acao for diferente de fim*/
	while(strcmp("fim", acao)!= 0){
	
		/*Se for o comando insere, eu leio as palavras e  idioma e chamo a função para inserir na tabela*/
		if(strcmp("insere", acao) == 0){
			scanf("%s", id1);
			scanf("%s", str1);
			scanf("%s", id2);
			scanf("%s", str2);
			insereTabelaHash(tabela, str1, str2);
			insereTabelaHash(tabela, str2, str1);
		}
		
		/*Se for o comando busca eu leio a palavra que devo buscar e chamo a função.*/
		if(strcmp("busca", acao) == 0){
			scanf("%s", str1);
			buscaTabela(tabela, str1);
		}
		
		/*Se for o comando remove eu leio as palavras com espaço e armazeno na variável string*/
		if(strcmp("remove", acao) == 0){
			scanf("%[^\n]s", string);
			j=0, k=0;
			
			/*Neste trecho de código eu separo as palavras e armazeno em um vetor de string, ou seja, leio letra a letra e passo para o vetor, até eu encontrar o espaço em branco, quando encontro mudo a posição do vetor*/
			for(i = 0; i < strlen(string); i++){
				if(string[i] != ' '){
					str[j][k] = string[i];
					k++;
				}else{
					str[j][k] = '\0';
					j++;
					k = 0;
				}
			}
			
			/*Verifico se o vetor tem 1 ou 2 palavras e chamo o remover correspondente*/
			if(j == 1){
				str[1][k] = '\0'; /*insiro o caracter nulo para saber onde a palavra acaba*/
				removeTabela(tabela, str[1]);
			}else{
				str[2][k] = '\0'; /*insiro o caracter nulo para saber onde a palavra acaba*/
				removeSinonimoTabela(tabela, str[1], str[2]);
				removeSinonimoTabela(tabela, str[2], str[1]);
			}
		}
		
		scanf("%s", acao); /*Leio novamente a acao para definir qual a proxima operacao a ser realizada*/
	}
	
	return 0;
}
