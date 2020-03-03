//Lara Galvani Moura - laragalvanim@gmail.com
//Última modificação: 20/10/2019

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h> 
#define MAX 10

/*Primeramente fazemos a fila ficar vazia. Depois disso, começamos a ler o arquivo, armazenando
sempre uma letra(referente à opção do processo a ser realizado e um número(que provavelmente será
inserido na fila - se a opção for 'a'). Após isso, com o switch case verificamos o processo 
a ser realizado (verificando a letra da linha). Se a letra for 'a' nós apenas enfileiramos o item
(representado pelo número da linha). Se a letra for 'b', nós desenfileiramos o item que está a mais
tempo na fila (ou seja, o primeiro da fila). Se a letra for 'c', nós imprimimos a fila. É importante
ressaltar que na hora de chamar as funções para enfileirar, desenfileirar e imprimir, por exemplo,
quando colocamos '&' estamos passando o endereço da fila (ou do item) pois provavelmente haverá 
uma modificação no conteúdo "original", e quando não colocamos o '&' estamos passando apenas uma
cópia do conteúdo - pois não haverá mudança no conteúdo original.*/

typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
    TipoChave Chave;
}TipoItem;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
}TipoCelula;

typedef struct TipoFila {
    TipoApontador Frente, Tras;
}TipoFila;

void FFVazia(TipoFila *Fila){
    Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
} 

int Vazia(TipoFila Fila){
    return (Fila.Frente == Fila.Tras);
} 

void Enfileira(TipoItem x, TipoFila *Fila){
    Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
} 

void Desenfileira(TipoFila *Fila, TipoItem *Item){
    TipoApontador q;
    if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
    q = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    *Item = Fila->Frente->Item;
    free(q);
} 

void Imprime(TipoFila Fila){
    TipoApontador Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL) {
        printf("%d\n", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
}

void trataFila(){

    FILE *f;
    char txt[50];

    printf("Digite o nome do arquivo: ");
    scanf("%s", txt);//lê do teclado o nome do arquivo
   
    //abre o diretório atual e tenta abrir o arquivo que o usuário pediu
	DIR *d;
	d = opendir(".");
  	if(d){
		f = fopen(txt, "r"); //abrindo o arquivo e escolhendo a opção de ler, apenas
		if(f == NULL){
      		perror("Ocorreu um erro ao tentar abrir o arquivo. Tente novamente.\n");
      		exit(1);
   		}
  	}

    TipoFila Fila;
    TipoItem Item;

    FFVazia(&Fila); //antes de tudo fazemos a fila ficar vazia
    
    rewind(f); //ponteiro no início do arquivo
    while(!feof(f)){ //enquanto não chegar no final do arquivo
        char letra; //opção a ser escolhida
        int numero; //número da fila
        fscanf(f, "%c %d\n", &letra, &numero); //lê linha por linha

        switch(letra){
            case 'a': //incluir novos processos na fila de processos
                Item.Chave = numero;
                Enfileira(Item, &Fila);
                break;

            case 'b': //retirar da fila o processo com maior tempo de espera (primeiro da fila)
                Desenfileira(&Fila, &Fila.Frente->Prox->Item);
                break;

            case 'c': //imprimir o conteúdo da fila de processos em determinado momento
                printf("\nProcessos na fila:\n");
                Imprime(Fila);
                break;
            
            default:
                break;
        }
    }

}

int main(){

    trataFila();
}