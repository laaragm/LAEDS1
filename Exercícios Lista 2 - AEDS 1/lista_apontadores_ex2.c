#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10

typedef int TipoChave;

typedef struct {
  int Chave;
  /* outros componentes */
} TipoItem;
typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;


void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) 
  { printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
    return;
  }
  q = p -> Prox;
  *Item = q -> Item;
  p -> Prox = q -> Prox;
  if (p -> Prox == NULL) Lista -> Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { printf("%d\n", Aux -> Item.Chave);
      Aux = Aux -> Prox;
    }
}

//acha o menor elemento da lista e o move para o ínicio
void MoveMenor(TipoLista *Lista){
  
    TipoApontador aux, menor, aux2, troca;

    aux2 = Lista->Primeiro->Prox; //serve para detectar o final da lista
    menor = Lista->Primeiro->Prox; //menor é um ponteiro para o primeiro elemento da lista
    aux = menor->Prox; //aux é um ponteiro para o segundo elemento da lista
    while(aux2 != NULL){ //enquanto não chegar no final da lista
        //se o elemento apontado por aux for menor que o elemento apontado por menor
        if(aux->Item.Chave < menor->Item.Chave){ 
            menor = aux; //menor passa a apontar para aux
        }
        if(aux->Prox != NULL){ //para não tentar acessar um elemento que não existe
        	aux = aux->Prox;
        }
        aux2 = aux2->Prox; //avança o ponteiro para o próximo elemento da lista
    }

    printf("%d ", menor->Item.Chave); //primeiro elemento é o menor
    aux2 = Lista->Primeiro->Prox; //aux2 aponta para o primeiro elemento da lista
    while(aux2 != NULL){ 
      //se o elemento apontado por aux2 for igual ao elemento apontado por menor, então
      //esse elemento é o menor da lista e já foi impresso na tela, portanto não será
      //necessário fazê-lo novamente
      if(aux2->Item.Chave != menor->Item.Chave){
        printf("%d ", aux2->Item.Chave);
      }
      aux2 = aux2->Prox;
    }
    printf("\n");
}

/* ========================================================================== */

int main()
{ struct timeval t;

  TipoLista lista;
  TipoItem item;
  int vetor[MAX];
  TipoApontador p;
  int i, j, k, n;
  float  tamanho=0;
  gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);
  FLVazia(&lista);

  
  /*Gera uma permutacao aleatoria de chaves entre 1 e MAX*/
  for(i = 0; i < MAX; i++) vetor[i] = i + 1;
  for(i = 0; i < MAX; i++)
    { k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      n = vetor[k];
      vetor[k] = vetor[j];
      vetor[j] = n;
    }
  /*Insere cada chave na lista */
  for (i = 0; i < MAX; i++)
    { item.Chave = vetor[i];
      Insere(item, &lista);
      tamanho++;
      printf("Inseriu: %d \n", item.Chave);
    }
  MoveMenor(&lista);

  return(0);
}