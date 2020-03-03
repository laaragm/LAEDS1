#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

/************************************************
LAED1 - Trabalho Pratico 1
Alunas: Lara Galvani Moura e Lorena Gomes de Oliveira Cabral
Matricula: 20183020842 / 20183002361
Descricao do programa: Algortimo guloso. Percorre os itens da mochila até achar o item de maior valor que não ultrapasse a capacidade máxima da mochila.
Data: 13/09/2019
************************************************/


struct itens{

    int pesoItem;
    int valorItem;
};

int main(){

    int capacidadeMax = 0;
    int numItens = 0;
    char nomeArq[50];
    int i = 0;
    int somaPesos = 0;
    int somaValores = 0;
    int maiorValor = 0;
    int totalPeso = 0;
    int totalValor = 0;
    int indiceMaiorValor = 0;
    FILE *fp; //arquivo de entrada
    FILE *fp2; //arquivo de saida
    
    //------------------------------------ variaveis relacionadas com a medicao do tempo usando a funcao gettimeofday ------------------------------------
    
    //estrutura que armazena o tempo total que o programa gasta, relaciona-se com a funcao gettimeofday()
    struct timeval inicio, fim; 
    
    //tempo total do programa   
    //armazenam a diferenca entre o tempo inicial e o final, ou seja, o tempo total gasto pelo programa todo
    long totalmicroseg, totalseg;
    
    //obtendo o tempo em que o programa comeca.  
    gettimeofday(&inicio, NULL);
    
    //----------------------------------- fim variaveis relacionadas com a medicao do tempo usando a função gettimeofday ----------------------------------
    
    //------------------------------------ variaveis relacionadas com a medicao do tempo usando a funcao getrusage ------------------------------------
    
    int who = RUSAGE_SELF;
    
    struct rusage usage;
    
    //tempo usuario: tempo que a CPU gasta executando o programa
    long utotalmicroseg, utotalseg;
    
    //tempo sistema: tempo que a CPU gasta executando chamadas de sistemas para o programa
    long stotalmicroseg, stotalseg;
    
    //------------------------------------ fim variaveis relacionadas com a medicao do tempo usando a funcao getrusage ------------------------------------
    
    
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArq);
    printf("\n");
    
    //------------------ abertura e leitura do arquivo ------------------
    
    fp = fopen(nomeArq, "r");
   
    if (fp == NULL)  // Se houve erro na abertura
    {
         printf("Problemas na abertura do arquivo\n");
         return 0;
    }
    
    //le as primeiras duas linhas do arquivo e atribui os valores a capacidade maxima da mochila a ao numero de itens, respectivamente
    fscanf(fp, "%d\n%d\n", &capacidadeMax, &numItens);
    
    //inicializando a estrutura de dados dentro da main
    struct itens dadosItens[numItens];
    
    //ler linha por linha do arquivo e armazenar o peso e valor do item, respectivamente
    for(i=0; i<numItens; i++){
    
        fscanf(fp, "%d %d\n", &dadosItens[i].pesoItem, &dadosItens[i].valorItem);
    }
            
    fclose(fp);
    
    //------------------ fim abertura e leitura do arquivo ------------------
        
    //------------------ abrindo o arquivo e gravando dados ------------------
     
    //cria arquivo de saida   
    fp2 = fopen("outGuloso.txt", "w");
   
    if (fp2 == NULL)  // Se houve erro na abertura
    {
         printf("Problemas na abertura do arquivo\n");
         return 0;
    } 
            
    do{
        //a cada loop um novo maior valor é achado, entao zeramos essa variavel para armazenar outro dado
        maiorValor = 0; 
        
        //percorre a lista de itens
        for(i=0; i<numItens; i++){
            //se o valor do item for maior que o maior valor ate agora...
            if(dadosItens[i].valorItem > maiorValor){
                //então o maior valor passa a ser o valor desse item
                maiorValor = dadosItens[i].valorItem;
                indiceMaiorValor = i;
            }    
        }
        
        //somaPesos armazena a soma de todos os pesos dos itens de maior valor que foram selecionados
        somaPesos = somaPesos + dadosItens[indiceMaiorValor].pesoItem;
        //somaValores armazena a soma de todos os valores dos itens de maor valor que foram selecionados
        somaValores = somaValores + dadosItens[indiceMaiorValor].valorItem;
        
        //se o somaPesos estiver maior que a capacidade permitida... (acontece geralmente no ultimo loop)
        //Quando a qtde do peso ainda não foi atingida, mas nao ha itens q satisfacam esse limite, entao o algoritmo acaba percorrendo a lista de itens, achando um novo maior valor e somando 
        //com isso o conteudo máximo permitido é ultrapassado. Entao precisamos voltar ao estado anterior
        if(somaPesos > capacidadeMax){
            
            //voltamos a soma dos pesos e dos valores para o instante anterior a esse e imprimimos no arquivo
            totalPeso = somaPesos - dadosItens[indiceMaiorValor].pesoItem;
            totalValor = somaValores - dadosItens[indiceMaiorValor].valorItem; 
            fprintf(fp2,"Soma dos pesos: %d\n", totalPeso);
            fprintf(fp2,"Soma dos valores: %d\n", totalValor);
            
        //se a soma dos pesos ainda é menor ou igual a capacidade permitida da mochila           
        }else if(somaPesos <= capacidadeMax){
            
            //entao imprimimos no arquivo os dados do item que foi selecionado e retiramos ele da mochila zerando o peso e o valor
            fprintf(fp2, "Item %d, peso %d, valor %d\n\n",indiceMaiorValor + 1, dadosItens[indiceMaiorValor].pesoItem, dadosItens[indiceMaiorValor].valorItem);
            dadosItens[indiceMaiorValor].pesoItem = 0;
            dadosItens[indiceMaiorValor].valorItem = 0;
        }
    //repetimos esse laco ate que a soma dos pesos dos itens de maior valor ainda nao esteja ultrapassando a capacidade da mochila        
    }while(somaPesos < capacidadeMax);
    
    //se a soma dos pesos dos itens de maior valor nao ultrapassou o limite da mochila (acontece geralmente quando os itens escolhidos, juntos, deram o exato peso limite)
    if(somaPesos <= capacidadeMax){
        //então mantemos as variáveis desse instante e imprimimos no arquivo de saída
        fprintf(fp2,"Soma dos pesos: %d\n", somaPesos);
        fprintf(fp2,"Soma dos valores: %d\n", somaValores);
    }
    
                    
    fclose(fp); //fecha o arquivo de entrada
    fclose(fp2); //fecha o arquivo de saida
    
    //------------------ arquivo fechado e dados gravados ------------------
    
    //------------------------------------ obtencao do tempo final do programa usando a funcao gettimeofday -----------------------------------
    
    //obtem tempo final do programa
    gettimeofday(&fim, NULL);
    
    //diferenca em segundos
    totalseg = fim.tv_sec - inicio.tv_sec;     
    
    //diferenca em microsegundos
    totalmicroseg = fim.tv_usec - inicio.tv_usec; 
    
    //se a diferenca em microssegundos for negativa, os segundos terao que emprestar uma unidade; 1 microseg = 10E-6 s
    if (totalmicroseg <0){
    
        totalmicroseg += 1000000;
        totalseg -= 1;
    };
    
    printf ("***************************************************************\n");
    printf ("Tempo total: %ld segundos e %ld microssegundos.\n", totalseg, totalmicroseg);
    printf ("***************************************************************\n");
    printf ("\n");
    
    //------------------------------------ fim obtencao do tempo final do programa usando a funcao gettimeofday -----------------------------------
    
    //------------------------------------ obtencao do tempo final do programa usando a funcao getrusage -----------------------------------
    
    getrusage(who, &usage); 
    
    //tempo de usuario na CPU
    stotalseg = usage.ru_stime.tv_sec; //segundos
    stotalmicroseg = usage.ru_stime.tv_usec; //microsegundos

    printf ("***************************************************************\n");
    printf ("Tempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);
    printf ("Tempo de sistema: %ld segundos e %ld microssegundos.\n", stotalseg, stotalmicroseg);
    printf ("***************************************************************\n");
    printf ("\n");
    
    //------------------------------------ fim obtencao do tempo final do programa usando a funcao getrusage -----------------------------------
    
    return 0; 
}
