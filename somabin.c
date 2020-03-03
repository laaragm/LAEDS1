#include <stdio.h>
#include <stdlib.h>

void inicializa();
void combinacoes();
void condicaoParada();

int *mochila;
int n;
int *soma1;
int parada = 0;

void combinacoes(){
   
    //aritmética binária: 1+1=0 (carry=1)
    //1+0=1; 0+1=1; 0+0=0
    //comecamos adicionando os numeros a partir do LSB
    //Referências: https://codereview.stackexchange.com/questions/187398/adding-two-binary-numbers
   
    int carry = 0;
    int soma = 0;
   
    for(int i = n-1; i >= 0; i--){
        soma = mochila[i] + soma1[i] + carry;
        if(soma >= 2){
            mochila[i] = 0;
            carry = 1;
        }else if(soma == 1){
            mochila[i] = 1 ;
            carry = 0;
        }else if(soma == 0){
            mochila[i] = 0;
            carry = 0;
        }
        soma = 0;
    }
   
    for(int i = 0; i < n; i++){
        printf("%d", mochila[i]);
    }
    printf("\n");
}

void inicializa(){
   
    //alocamos dinamicamente os vetores com a quantidade n de itens que podem ser colocados na mochila
    //inicializamos o vetor soma1 com  1 e as demais posicoes ficam com 0
    //o vetor mochila fica zerado
   
    mochila = (int *)calloc(n, sizeof(int));
    soma1 = (int *)calloc(n, sizeof(int));
   
    soma1[n-1] = 1;
}

void condicaoParada(){
   
    int pos = 0;
    while(mochila[pos] == 1){
        if(pos == n-1){
            parada = 1;
        }
        pos++;
    }
}

int main(){
   
    n = 100;
   
    inicializa();
   
    while(!parada){
        combinacoes();
        condicaoParada();
    }

    return 0;
}