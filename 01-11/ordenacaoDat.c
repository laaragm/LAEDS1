//Lara Galvani Moura - laragalvanim@gmail.com
//Última modificação: 04/11/2019

/*Materiais consultados:
https://www.linuxquestions.org/questions/programming-9/c-howto-read-binary-file-into-buffer-172985/
http://www.cmaismais.com.br/referencia/cstdio/fseek/
https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm
https://fresh2refresh.com/c-programming/c-file-handling/fseek-seek_set-seek_cur-seek_end-functions-c/
https://terminalroot.com.br/2014/10/exemplos-de-funcoes-fread-fwrite-remove.html
https://stackoverflow.com/questions/7013307/read-the-full-content-of-a-binary-file
https://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer
https://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-03.php*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TipoChave[100];
typedef struct {
    TipoChave Nome;
    int Nota;
}TipoItem;

typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct {
    TipoApontador Fundo, Topo;
    int Tamanho;
} TipoPilha;

void FPVazia(TipoPilha *Pilha){
    Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
    Pilha->Fundo = Pilha->Topo;
    Pilha->Topo->Prox = NULL;
    Pilha->Tamanho = 0;
}

int Vazia(TipoPilha Pilha){
    return (Pilha.Topo == Pilha.Fundo);
} 

void Empilha(TipoItem x, TipoPilha *Pilha){
    TipoApontador Aux;
    Aux = (TipoApontador) malloc(sizeof(TipoCelula));
    Pilha->Topo->Item = x;
    Aux->Prox = Pilha->Topo;
    Pilha->Topo = Aux;
    Pilha->Tamanho++;
}

void Desempilha(TipoPilha *Pilha, TipoItem *Item){
    TipoApontador q;

    if (Vazia(*Pilha)) {
        printf("Erro: lista vazia\n");
        return;
    }

    q = Pilha->Topo;
    Pilha->Topo = q->Prox;
    *Item = q->Prox->Item;
    free(q);
    Pilha->Tamanho--;
}

void readingAndSorting(){

    FILE *f; //file pointer
    char dat[50]; //nome do arquivo
    TipoPilha *pilha; //pilha que será usada na hora de ordenar usando o método bucketsort
    TipoPilha bucket; //pilha que irá armazenar o conteúdo do vetor infosAlunos
    TipoItem *infosAlunos; //vetor com as informações dos alunos (nome e nota)

    FPVazia(&bucket);

    /*Leitura do nome do arquivo*/
    printf("Digite o nome do arquivo: ");
    scanf("%s", dat);
    /*Nova linha antes da impressão do resultado*/
    printf ("\n");

    f = fopen(dat, "rb"); //abre o arquivo para ler binário
    if(!f){
        printf("Ocorreu um erro ao abrir o arquivo. Tente novamente.\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END); //move o ponteiro para o final do arquivo
    int len = ftell(f); //tamanho do arquivo em bytes
    //para saber a quantidade de alunos pegamos o tamanho total do arquivo e dividimos por 104
    //que é a quantidade total de bytes de cada aluno (considerando o nome (100*sizeof(char))) = 100
    //e nota (1*sizeof(int)) = 4. Portanto, 104 bytes para armazenas as informações de cada
    //aluno na struct
    int qtAlunos = len/104; 

    rewind(f); //move o ponteiro para o início do arquivo

    pilha = (TipoPilha *)malloc(qtAlunos*sizeof(TipoPilha));
    infosAlunos = (TipoItem *)malloc(qtAlunos*sizeof(TipoItem));

    //esvazia a pilha antes de começar a empilhar
    for(int i = 0; i < qtAlunos; i++){
        FPVazia(&pilha[i]);
    }

    //unsigned fread(void *buffer, int numero_de_bytes, int count, FILE *fp);
    //grava as todas as informações lidas do ".dat"(através do file pointer "f") no vetor infosAlunos
    //lê byte a byte (pois isso o 1 no segundo parâmetro)
    //count indica quantas unidades devem ser lidas, ou seja, o arquivo inteiro (por isso "len")
    fread(infosAlunos, 1, len, f); 

    fclose(f); //fecha o arquivo
    
    /*for(int i = 0; i < qtAlunos; i++){
        printf("%s %d\n", infosAlunos[i].Nome, infosAlunos[i].Nota);
    }*/

    for(int i = 0; i < qtAlunos; i++){
        Empilha(infosAlunos[i], &bucket); //empilha o que foi gravado no vetor infosAlunos
    }

    //bucketsort: coloca o item de chave "k" no balde (variável pilha) pilha[k]
    for(int i = 0; i < qtAlunos; i++){
        if(bucket.Topo->Prox != NULL){
            TipoItem aux = bucket.Topo->Item;
            Desempilha(&bucket, &aux);
            Empilha(aux, &pilha[aux.Nota]);
            //printf("%d\n", aux.Nota);
        }else{
            break;
        }
    }

    for(int i = 0; i < qtAlunos; i++){ //imprime 
        TipoItem aux = pilha->Topo->Item;
        //como podem ter notas repetidas armazenadas na mesma pilha vamos desempilhando
        //até que a pilha esteja vazia
        while(!Vazia(pilha[i])){ 
            Desempilha(&pilha[i], &aux);
            /*Impressao dos nomes e das notas*/
            printf("%s\n", aux.Nome);
            printf("%d\n", aux.Nota);
        }
    }  

    //libera memória alocada dinamicamente
    free(pilha);
    free(infosAlunos);
}

int main(){

    readingAndSorting();
}