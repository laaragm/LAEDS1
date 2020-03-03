/************************************************
LAED1 - Trabalho Pratico 1
Alunas: Lara Galvani Moura e Lorena Gomes de O. Cabral
Matricula: 20183020842 e 20183002361 
Descricao do programa: Problema da Mochila - Algoritmo de Tentativa e Erro
Data: 12/09/2019
************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/resource.h> //getrusage
#include <sys/time.h> //gettimeofday
#include <time.h>

//Referências: 
//https://www.inf.pucrs.br/~pinho/LaproI/Arquivos/Arquivos.htm
//http://www.informit.com/articles/article.aspx?p=23618&seqNum=7
//https://codereview.stackexchange.com/questions/187398/adding-two-binary-numbers
//https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/laed1_20181/medicao_tempo.pdf?attachauth=ANoY7cpd0vl2hXYL8sOWUQ7EsSOglTscbu5xzMguzC-wvwjD2mtHX8WeSowv1SuYkYN5eiagFiYQWcmpck_AwtBuJTqZojLYbqlBkPKaLXAKikK8zAQB9BwqPslcBqwt133BusqA3An488crWWoCQO6fBnKTZBCF3uvBAVbd9ZBRNQtm6VB_CJ6EW4R8cJSy4Iy1fjuzJ-Ig4KmbF9VjB4Dmo18oOfdsvSvf2TeS0crKnC_58fLZEA1D79gobOO7zDhGUVzkJoipxFnG-8rJOpa2_I3LwDAaLg%3D%3D&attredirects=0

//teremos (2^n)-1 possiveis combinacoes pois, para cada item consideramos que ele pode 
//ou nao ser colocado na mochila. O "-1" é dado pelo fato de que a combinacao onde todos
//os itens recebem o valor 0 (fora da mochila) nao importa pois o valor sera zero.

void tentativaErro();
void verificaMaior(int valorAtual, int pesoAtual);
void inicializa();
void combinacoes();
void saidaTxt();
void condicaoParada();
void zeraVetorCombinacoes();
void leTxt();

//variaveis globais
int W; //capacidade da mochila
int n; //quantidade de itens
int *peso;
int *valor;
int *mochila;
int maiorValor = 0;
int pesoMaiorValor = 0;
int parada = 0; 
int *soma1;
int *combinacaoPesos;
int *combinacaoValores;
int *pesostxt;
int *valorestxt;
int posicaoVetor = 0;
int *itemtxt;
int *numeroItem;
int *combinacaoItens;
int tamanho = 0;

void combinacoes(){
   
    //aritmética binária: 1+1=0 (carry=1)
    //1+0=1; 0+1=1; 0+0=0
    //comecamos adicionando os numeros a partir do LSB
   
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
}

void inicializa(){
   
    //alocamos dinamicamente os vetores com a quantidade n de itens que podem ser colocados na mochila
    //inicializamos o vetor soma1 com  1 e as demais posicoes ficam com 0
    //o vetor mochila fica zerado
   
    mochila = (int *)calloc(n, sizeof(int));
    soma1 = (int *)calloc(n, sizeof(int));
    peso = (int *)calloc(n, sizeof(int));
    valor = (int *)calloc(n, sizeof(int));
    mochila = (int *)calloc(n, sizeof(int));
    combinacaoPesos = (int *)calloc(n, sizeof(int));
    combinacaoValores = (int *)calloc(n, sizeof(int));
    combinacaoItens = (int *)calloc(n, sizeof(int));
    pesostxt = (int *)calloc(n, sizeof(int));
    itemtxt = (int *)calloc(n, sizeof(int));
    valorestxt = (int *)calloc(n, sizeof(int));
    numeroItem = (int *)calloc(n, sizeof(int));
   
    soma1[n-1] = 1;
}

void condicaoParada(){
   
    int pos = 0;
    while(mochila[pos] == 1){
        if(pos == n-1){
            parada = 1;
        }
        pos++;
        if(pos >= n){
            break;
        }
    }
}

void zeraVetorCombinacoes(){

    for(int i = 0; i < n; i++){
        combinacaoValores[i] = 0;
        combinacaoPesos[i] = 0;
    }
}

void tentativaErro(){
   
    int valorAtual = 0;
    int pesoAtual = 0;
   
    //Primeiramente é gerada uma combinacao (funciona igual a uma tabela verdade. 
    //Todas as combinacoes possiveis sao analisadas).
    //a variavel parada (que é a condicao do while) é usada como uma maquina de estados.
    //Vai sair do while quando parada for igual a 1 (condicao verificada atraves do 
    //procedimento condicaoParada() - parada sera igual a 1 quando todos os elementos do vetor
    //mochila forem iguais a 1 pois, dessa forma, sabemos que chegamos no ultimo caso
    //possivel.
    //Depois de gerar uma nova combinacao e verificar a condicao de parada, o laço for
    //percorre todo o vetor mochila e onde tem o numero 1 (que significa que o item esta
    //dentro da mochila) vamos somando o valor daquele item, peso, e colocamos suas informacoes
    //nos vetores combinacao (usados para exibir os dados de cada item colocado na mochila).
    //Depois disso, verificamos se o pesoAtual (encontrado atraves da soma dos itens iguais
    //a 1 no vetor mochila) é menor ou igual a capacidade da mochila. Se isso acontece,
    //o procedimento verificaMaior() compara o maior anteriormente encontrado (ou aquele setado
    //no inicio do programa) com o maior atual. Se o maior atual (passado como parametro
    //no procedimento verificaMaior()) for maior, este passara a ser o maior.
    //Em seguida, atualizamos as variaveis e zeramos o vetor combinacoes (atraves do 
    //procedimento zeraVetorCombinacoes()) para receber as proximas combinacoes.
    //Esses passos descritos anteriormente sao realizados enquanto a variavel parada for
    //igual a 0.
    while(!parada){
        //alocamos dinamicamente o vetor mochila com a quantidade de posições igual à 
        //quantidade de itens disponíveis calloc serve para inicializar todas as posições 
        //com 0
        combinacoes();
        condicaoParada();
       
        for(int i = 0; i < n; i++){
            if(mochila[i] == 1){
                valorAtual = valorAtual + valor[i];
                pesoAtual = pesoAtual + peso[i];
                if(pesoAtual > W){
                    break;
                }
                combinacaoPesos[posicaoVetor] = peso[i];
                combinacaoValores[posicaoVetor] = valor[i];
                combinacaoItens[posicaoVetor] = numeroItem[i];
                posicaoVetor++;
            }
        }
   
        if(pesoAtual <= W){
            verificaMaior(valorAtual, pesoAtual);
        }  

        valorAtual = 0;
        pesoAtual = 0;
        posicaoVetor = 0;
        zeraVetorCombinacoes();
    }
}

void verificaMaior(int valorAtual, int pesoAtual){
   
    if(valorAtual >= maiorValor){
        maiorValor = valorAtual;
        pesoMaiorValor = pesoAtual;
        tamanho = posicaoVetor;
        for(int i = 0; i < tamanho; i++){
            pesostxt[i] = combinacaoPesos[i];
            valorestxt[i] = combinacaoValores[i];
            itemtxt[i] = combinacaoItens[i];
        }
    }
}

void leTxt(){

    FILE *f;
    char nomeArquivo[100];

    printf("Entre com o nome do arquivo a ser aberto: ");
    scanf("%s", nomeArquivo);

    //abre o arquivo em modo leitura
    f = fopen(nomeArquivo, "r"); 
    if(f == NULL) {
        perror("Ocorreu um erro ao tentar abrir o arquivo. Tente novamente.\n");
        exit(1);
    }

    //coloca o ponteiro no inicio do arquivo 
    //isso evita possiveis problemas com a leitura dos dados nao comecar do inicio
    rewind(f);

    fscanf(f, "%d", &W); //peso maximo da mochila
    fscanf(f, "%d", &n); //quantidade de itens
    inicializa();
    for(int i = 0; i < n; i++){
        fscanf(f, "%d%d", &peso[i], &valor[i]); //le e salva peso e valor, respectivamente
        numeroItem[i] = i+1; //determina o número de cada item
    }

    fclose(f); //fecha o arquivo
}

void saidaTxt(){

    //abre o arquivo em modo escrita
    FILE *fout = fopen("outTentativaErro.txt", "w"); 
    if(fout == NULL){
      perror("Ocorreu um erro ao tentar abrir o arquivo. Tente novamente.\n");
      exit(1);
    } 

    //escreve no arquivo "out.txt" as devidas informacoes encontradas testando
    //todas as combinacoes possiveis (atraves do procedimento tentativaErro()).
    fprintf(fout, "Item\t Peso\t Valor\n");
    for(int i = 0; i < tamanho; i++){
        fprintf(fout, " %d\t  %d\t  %d\t\n", itemtxt[i], pesostxt[i], valorestxt[i]);
    }
    fprintf(fout, "Peso total: %d\n", pesoMaiorValor);
    fprintf(fout, "Valor total: %d\n", maiorValor);

    fclose(fout); //fecha o arquivo
}

int main(){

    //variaveis relacionadas a medicao do tempo usando a funcao gettimeofday    
    //estrutura que armazena o tempo total que o programa gasta, relaciona-se 
    //com a funcao gettimeofday()
    struct timeval inicio, fim;
   
    //tempo total do programa  
    //armazenam a diferenca entre o tempo inicial e o final, ou seja, o tempo 
    //total gasto pelo programa como um todo
    long totalmicroseg, totalseg;
   
    //obtendo o tempo em que o programa comeca.  
    gettimeofday(&inicio, NULL);
   
    //variáveis relacionadas a medição do tempo usando a função getrusage  
    int who = RUSAGE_SELF;
    struct rusage usage;
   
    //tempo usuario: tempo que a CPU gasta executando o programa
    long utotalmicroseg, utotalseg;
   
    //tempo sistema: tempo que a CPU gasta executando chamadas de sistemas para o programa
    long stotalmicroseg, stotalseg;
  
    //função para ler o arquivo e gravar as variáveis em arrays
    leTxt();    

    //testa todas as combinacoes possiveis e verifica qual (dentro do
    //peso maximo permitido) possui maior valor
    tentativaErro();

    //escreve em um arquivo "out.txt" a saida informando as combinacoes dos pesos
    //valores, peso total e valor total
    saidaTxt();

    //obtenção do tempo final do programa usando a função gettimeofday
    //obtem tempo final do programa
    gettimeofday(&fim, NULL);
   
    //diferenca em segundos
    totalseg = fim.tv_sec - inicio.tv_sec;    
   
    //diferenca em microsegundos
    totalmicroseg = fim.tv_usec - inicio.tv_usec;
   
    //se a diferenca em microssegundos for negativa, os segundos terao que emprestar
    //uma unidade; 1 microseg = 10E-6 s
    if (totalmicroseg <0){
        totalmicroseg += 1000000;
        totalseg -= 1;
    };
   
    printf ("***************************************************************\n");
    printf ("Tempo total: %ld segundos e %ld microssegundos.\n", totalseg, totalmicroseg);
    printf ("***************************************************************\n");
    printf ("\n");
   
    getrusage(who, &usage);
   
    //tempo de usuário na CPU
    stotalseg = usage.ru_stime.tv_sec; //segundos
    stotalmicroseg = usage.ru_stime.tv_usec; //microsegundos
   
    printf ("***************************************************************\n");
    printf ("Tempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);
    printf ("Tempo de sistema: %ld segundos e %ld microssegundos.\n", stotalseg, stotalmicroseg);
    printf ("***************************************************************\n");
    printf ("\n");

    return 0;
}

