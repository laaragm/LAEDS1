//Lara Galvani Moura - laragalvanim@gmail.com
//Última modificação: 25/10/2019

//O programa a ser feito consistirá na alteração da especificação do programa ET do livro texto
//da disciplina. Incluir o comando cancela palavra, cujo efeito é cancelar a palavra anterior
//na linha que está sendo editada. 

#include <stdio.h>

#define MAXTAM          70
#define CANCELACARATER  '#'
#define CANCELALINHA    '\\'
#define SALTALINHA      '*'
#define MARCAEOF        '~'
#define CANCELAPALAVRA  '$'

typedef char TipoChave;

typedef int TipoApontador;

typedef struct{
    TipoChave Chave;
}TipoItem;

typedef struct{
    TipoItem Item[MAXTAM];
    TipoApontador Topo;
}TipoPilha;

void FPVazia(TipoPilha *Pilha){ 
    Pilha->Topo = 0;
}

int Vazia(TipoPilha Pilha){ 
    return (Pilha.Topo == 0);
}  

void Empilha(TipoItem x, TipoPilha *Pilha){ 
    if(Pilha->Topo == MAXTAM){
        printf(" Erro   pilha est  a  cheia\n");
    }else{
        Pilha->Topo++;
        Pilha->Item[Pilha->Topo - 1] = x;
    }
}  

void Desempilha(TipoPilha *Pilha, TipoItem *Item){ 
    if(Vazia(*Pilha)){
        printf(" Erro   pilha est  a  vazia\n");
    }else{
        *Item = Pilha->Item[Pilha->Topo - 1];
        Pilha->Topo--;
    }
}  

int Tamanho(TipoPilha Pilha){ 
    return (Pilha.Topo);
}  

void Imprime(TipoPilha *Pilha){ 
    TipoPilha Pilhaux;
    TipoItem x;
    FPVazia(&Pilhaux);
    while(!Vazia(*Pilha)){ 
        Desempilha(Pilha, &x); 
        Empilha(x, &Pilhaux); 
    }
    while(!Vazia(Pilhaux)){ 
        Desempilha(&Pilhaux, &x); 
        putchar(x.Chave); 
    }
    putchar('\n');
} 

//argc indica o n umero de argumentos na linha decomando ao se executar o programa.
//*argv[] ́e um vetor de ponteiros para caracteres(ou seja vetor de strings) que cont́em os
//argumentos da linha de comando, um em cada posição do vetor.

int main(int argc, char *argv[]){ 

    TipoPilha Pilha;
    TipoItem x;

    FPVazia(&Pilha);

    x.Chave = getchar();
    if(x.Chave == '\n'){
        x.Chave = ' ';
    }

    while(x.Chave != MARCAEOF){ 
        if(x.Chave == CANCELACARATER){ 
            if(!Vazia(Pilha)){
                Desempilha(&Pilha, &x);
            } 
        }else if(x.Chave == CANCELAPALAVRA){
            //se o caractere for o de cancelar a palavra ($) vamos chamar a função desempilha
            //para ir "apagando" cada caractere até encontrar um espaço, que significa que
            //o final da palavra
            if(!Vazia(Pilha)){
                do{
                    Desempilha(&Pilha, &x);
                }while(x.Chave != ' ');
            }
        }else if(x.Chave == CANCELALINHA){
            FPVazia(&Pilha);
        }else if(x.Chave == SALTALINHA){
            Imprime(&Pilha);
        }else{ 
            if(Tamanho(Pilha) == MAXTAM){ 
                Imprime(&Pilha);
            }
            Empilha(x, &Pilha);
        }

        x.Chave = getchar();
        if(x.Chave == '\n'){
            x.Chave = ' ';
        }
    } 

    if(!Vazia(Pilha)){
        Imprime(&Pilha);
    } 

    return 0;
} 