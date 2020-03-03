#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#define MAX 10

typedef struct TipoPilha{
  TipoApontador Fundo, Topo;
  int Tamanho;
} TipoPilha;
typedef struct TipoCelula *TipoApontador;
typedef int TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
} TipoItem;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
} 

int Vazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras); } 

void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Tras->Prox;
  Fila->Tras->Item = x;
  Fila->Tras->Prox = NULL;
} 

void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
  q = Fila->Frente;
  Fila->Frente = Fila->Frente->Prox;
  *Item = Fila->Frente->Item;
  free(q);
} 

void Imprime(TipoFila Fila)
{ TipoApontador Aux;
  Aux = Fila.Frente->Prox;
  while (Aux != NULL) 
    { printf("%d\n", Aux->Item.Chave);
      Aux = Aux->Prox;
    }
}

void FPVazia(TipoPilha *Pilha)
{ Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Fundo = Pilha->Topo;
  Pilha->Topo->Prox = NULL;
  Pilha->Tamanho = 0;
} 

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

int main(int argc, char *argv[])
{ struct timeval t;

  TipoFila fila;
  TipoItem item;
  int vetor[MAX];
  int i, j, k, n;

  gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);

  FFVazia(&fila);
  
  /*Gera uma permutacao aleatoria de chaves entre 1 e MAX*/
  for(i = 0; i < MAX; i++) vetor[i] = i + 1;
  for(i = 0; i < MAX; i++)
    { k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));

      j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      n = vetor[k];
      vetor[k] = vetor[j];
      vetor[j] = n;
    }
  /*Insere cada chave na fila */
  for (i = 0;i < MAX; i++)
    { item.Chave = vetor[i];
      Enfileira(item, &fila);
      printf("Enfileirou: %d \n", item.Chave);
    }
  /*Desenfieleira cada chave */
  for (i = 0; i < MAX; i++)
    { Desenfileira(&fila, &item);
      printf("Desenfileirou: %d \n", item.Chave);
    }
  return 0;
}
/*void InverteFila(TipoFila *fila) {
  TipoPilha pilha;
  TipoItem aux;

  while(!Vazia(fila)){ //enquanto a fila não estiver vazia
    Desenfileira(&fila, &aux); //tira o item da fila (first in, first out)
    Empilha(aux, &pilha); //coloca o item na pilha (first in, last out)
  }

  while(!Vazia(pilha)){ //enquanto a pilha não estiver vazia
    Desempilha(&pilha, &aux); //tira o item da pilha (first in, last out)
    Enfileira(aux, &fila); //coloca o item na fila (first in, first out)
  }
}
Fonte: https://homepages.dcc.ufmg.br/~cunha/teaching/20121/aeds2/ex2g.pdf
*/