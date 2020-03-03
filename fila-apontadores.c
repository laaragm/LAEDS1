#include <stdlib.h>
#include <stdio.h>

typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
  TipoChave Chave;
} TipoItem;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
  TipoApontador Ant;
} TipoCelula;

typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
  Fila->Frente->Ant = NULL;
} 

int Vazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras); } 

void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras->Prox->Ant = Fila->Tras;
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

TipoApontador BuscaItem(TipoFila Fila, TipoItem Item)
{ TipoApontador Aux;
  Aux = Fila.Frente->Prox;
  while (Aux != NULL)
    { if (Aux->Item.Chave == Item.Chave)
        return Aux;
      Aux = Aux->Prox; 
    }
    return NULL;
}

void AumentaPrioridade(TipoFila *Fila, TipoItem *Item)
{  TipoApontador Aux;
   Aux = BuscaItem(*Fila, *Item);
   if (Vazia(*Fila) || Aux == NULL)
     printf("Erro fila vazia ou item inexistente\n");
   else  
   {  if (Aux == Fila->Frente)
        return;
      if (Aux == Fila->Tras)
      {  Aux->Ant->Prox = NULL;
         Aux->Prox = Fila->Frente->Prox;
	 Fila->Frente->Prox->Ant = Aux;
	 Fila->Frente->Prox = Aux; 
         Aux->Ant = Fila->Frente;	
      }  
      else 
      {  Aux->Prox->Ant = Aux->Ant;
	 Aux->Ant->Prox = Aux->Prox;
         Aux->Prox = Fila->Frente->Prox;
  	 Fila->Frente->Prox->Ant = Aux;
	 Fila->Frente->Prox = Aux;
	 Aux->Ant = Fila->Frente;
      }
   }  
       	 
} 

void Imprime(TipoFila Fila)
{ TipoApontador Aux;
  Aux = Fila.Frente->Prox;
  printf("(Frente) ");
  while (Aux != NULL) 
    { printf("%d ", Aux->Item.Chave);
      Aux = Aux->Prox;
    }
    printf("(Tras)\n\n");
}


int main(int argc, char *argv[])
{ TipoFila fila;
  TipoItem item;
  int op;

  FFVazia(&fila);
  
  while (op != 5)
  {  printf("MENU PRINCIPAL\n");
     printf("1. Inserir item na fila\n");
     printf("2. Remover item na fila\n");
     printf("3. Aumentar prioridade de um item\n");
     printf("4. Imprimir fila\n");
     printf("5. Sair\n\n");

     printf("Opcao: ");
     scanf("%d", &op);

     if (op == 1)
     {  printf("\nInserindo item na fila...\n");
	printf("Digite um item: ");
        scanf("%d", &item.Chave);
        Enfileira(item, &fila);
        printf("\n\n");        
     }

     if (op == 2)
     {  printf("\nItem removido da fila.\n\n");
        Desenfileira(&fila, &item);
     }

     if (op == 3)
     {  printf("\nAumentando prioridade de um item...\n");
	printf("Digite um item: ");
        scanf("%d", &item.Chave);
        AumentaPrioridade(&fila, &item);
        printf("\n\n");     
     }

     if (op == 4)
     {  printf("\nImprimindo fila...\n");
	Imprime(fila);
     }

     if (op == 5)
       return 0;	     
  }

  return 0;
}
