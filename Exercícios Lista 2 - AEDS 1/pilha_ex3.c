#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TipoChave;
typedef struct {
  char Chave;
} TipoItem;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct {
  TipoApontador Fundo, Topo;
  int Tamanho;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{ Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Fundo = Pilha->Topo;
  Pilha->Topo->Prox = NULL;
  Pilha->Tamanho = 0;
} 

int Vazia(TipoPilha Pilha)
{ return (Pilha.Topo == Pilha.Fundo); } 

void Empilha(TipoItem x, TipoPilha *Pilha)
{ TipoApontador Aux;
  Aux = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Topo->Item = x;
  Aux->Prox = Pilha->Topo;
  Pilha->Topo = Aux;
  Pilha->Tamanho++;
} 

void Desempilha(TipoPilha *Pilha, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Pilha)) { printf("Erro: lista vazia\n"); return; }
  q = Pilha->Topo;
  Pilha->Topo = q->Prox;
  *Item = q->Prox->Item;
  free(q);  Pilha->Tamanho--;
} 

int Tamanho(TipoPilha Pilha)
{ return (Pilha.Tamanho); } 

void verifica(){

    TipoPilha pilha, pilhaux;
    TipoItem item;
    int i;
    
    FPVazia(&pilha);
    FPVazia(&pilhaux);
  
    //first in, last out
    char *x, *y;
    //Alocação dinâmica de x e y
    x = (char *) malloc(1000);
    y = (char *) malloc(1000);
    printf("Entre com a cadeia de caracteres x: ");
    scanf("%s", x);
    int tamX = strlen(x);
    printf("Entre com a cadeia de caracteres y: ");
    scanf("%s", y);
    int tamY = strlen(y);
    //Realocando x e y com base na quantidade de caracteres que cada uma tem
    x = (char *) realloc(x, tamX);
    y = (char *) realloc(y, tamY);

    /*Empilha cada chave */
    for (i = 0; i < tamX; i++){ //empilhando x
        item.Chave = x[i];
        Empilha(item, &pilha);
    }
    item.Chave = 'C'; 
    Empilha(item, &pilha); //coloca o C na pilha para separar x e y
    for (i = 0; i < tamY; i++){ //empilhando y
        item.Chave = y[i];
        Empilha(item, &pilha);
    }
  
    //Desempilhando y e colocando na pilha auxiliar (pilhaux)
    for(i = 0; i < tamY; i++){ 
        //para ver o que está sendo empilhado/desempilhado fazemos %c e item.Chave
        Desempilha (&pilha, &item);
        Empilha(item, &pilhaux);
    }

    //Desempilhamos C para ficar mais fácil a leitura
    //Agora podemos desempilhar ambas e verificar se cada item desempilhado é igual
    //nas duas pilhas. Se isso acontecer podemos concluir que a string é da forma xCy
    int xCy = 1; //variável funciona como uma máquina de estados para ver se é ou não da forma
    Desempilha(&pilha, &item);
    if(tamX != tamY){
        printf("A string não é da forma xCy.\n");
    }else{
        char itemPilha, itemPilhaux;
        for(int i = 0; i < tamX; i++){
            Desempilha(&pilha, &item);
            itemPilha = item.Chave;
            Desempilha(&pilhaux, &item);
            itemPilhaux = item.Chave;
            if(itemPilhaux != itemPilha){
                printf("A string não é da forma xCy.\n");
                xCy = 0;
                break;
            }
        }
        if(xCy){
            printf("A string é da forma xCy.\n");
        }
    }
}

int main(int argc, char *argv[]){ 
  
    verifica();

    return(0);
}
