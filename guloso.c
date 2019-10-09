#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Lara Galvani Moura e Lorena Gomes de Oliveira Cabral
Matricula: 20183020842 / 20183002361
Descricao do programa: Algortimo guloso. Percorre os itens da mochila até achar o item de maior valor que não ultrapasse a capacidade máxima.
Data: 13/09/2019
************************************************/

struct itens{

    int pesoItem;
    int valorItem;
};

void tiraDaLoja(struct itens dadosItens[], int indiceMaiorValor){

    dadosItens[indiceMaiorValor].pesoItem = 0;
    dadosItens[indiceMaiorValor].valorItem = 0;
}

void imprimeArquivoSaida(FILE *fp, int somaValores, int somaPesos){

    fprintf(fp,"Soma dos pesos: %d\n", somaPesos);
    fprintf(fp,"Soma dos valores: %d\n", somaValores);
}

void imprimeItens(FILE *fp, int indiceMaiorValor, struct itens dadosItens[]){

    fprintf(fp, "Item %d, peso %d, valor %d\n\n",indiceMaiorValor + 1, dadosItens[indiceMaiorValor].pesoItem, dadosItens[indiceMaiorValor].valorItem);
}


int main(){

    int capacidadeMax = 0;
    int numItens = 0;
    char nomeArq[50];
    int i = 0;
    int somaPesos = 0;
    int somaValores = 0;
    int maiorValor = 0;
    int somaAnteriorPeso = 0;
    int somaAnteriorValor = 0;
    int indiceMaiorValor = 0;
    FILE *fp; //arquivo de entrada
    FILE *fp2; //arquivo de saida
      
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
    fp2 = fopen("saidaPrograma.txt", "w");
   
    if (fp2 == NULL)  // Se houve erro na abertura
    {
         printf("Problemas na abertura do arquivo\n");
         return 0;
    } 
            
    do{
        //a cada loop um novo maior valor e achado, então zeramos essa variavel para armazenar outro dado
        
        maiorValor = 0; 
        indiceMaiorValor = 0;
        
        //percorre a lista de itens
        
        for(i=0; i<numItens; i++){
        
            //se o valor do item for maior que o maior valor até agora...
            
            if(dadosItens[i].valorItem > maiorValor){
            
                //entao o maior valor passa a ser o valor desse item
                
                maiorValor = dadosItens[i].valorItem;
                indiceMaiorValor = i;
            }    
        }
        
        //somaPesos armazena a soma de todos os pesos dos itens de maior valor que foram selecionados
        
        somaPesos = somaPesos + dadosItens[indiceMaiorValor].pesoItem;
        
        //somaValores armazena a soma de todos os valores dos itens de maor valor que foram selecionados
        
        somaValores = somaValores + dadosItens[indiceMaiorValor].valorItem;
        
        //se o somaPesos estiver maior que a capacidade permitida... (acontece geralmente no ultimo loop)
        //quando a qtde do peso ainda nao foi atingida, mas nao ha itens q satisfacam esse limite, entao o algoritmo acaba percorrendo a lista de itens, achando um novo maior valor e somando 
        //com isso o conteudo maximo permitido é ultrapassado. Entao precisamos voltar ao estado anterior
        
        if(somaPesos > capacidadeMax){
            
            //voltamos a soma dos pesos e dos valores para o instante anterior a esse e imprimimos no arquivo
            
            somaAnteriorPeso = somaPesos - dadosItens[indiceMaiorValor].pesoItem;
            somaAnteriorValor = somaValores - dadosItens[indiceMaiorValor].valorItem;
            
            imprimeArquivoSaida(fp2, somaAnteriorPeso, somaAnteriorValor);
                                    
        //se a soma dos pesos ainda é menor ou e igual a capacidade permitida da mochila    
               
        }else if(somaPesos <= capacidadeMax){
            
            //entao imprimimos no arquivo os dados do item que foi selecionado e retiramos ele da loja zerando o peso e o valor
            
            imprimeItens(fp2,indiceMaiorValor,dadosItens);            
            tiraDaLoja(dadosItens,indiceMaiorValor);
        }
        
    //repetimos esse laco ate que a soma dos pesos dos itens de maior valor ainda nao esteja ultrapassando a capacidade da mochila      
      
    }while(somaPesos < capacidadeMax);
    
    //se a soma dos pesos dos itens de maior valor nao ultrapassou o limite da mochila (acontece geralmente quando os itens escolhidos, juntos, deram o exato peso limite)
    
    if(somaPesos <= capacidadeMax){
    
        //entao mantemos as variaveis desse instante e imprimimos no arquivo de saida
                
        imprimeArquivoSaida(fp,somaValores,somaPesos);   
    }
    
                    
    fclose(fp); //fecha o arquivo de entrada
    fclose(fp2); //fecha o arquivo de saída
    
    //------------------ arquivo fechado e dados gravados ------------------
    
    return 0; 
}
