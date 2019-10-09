//Lara Galvani Moura - laragalvanim@gmail.com
//Última modificação: 29/08/2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void possiveisCombinacoes(int numero, int *armazenaSomas, int posicaoAtual, int numeroMinimo);
void ordenaMatriz(int qtCombinacoes);
int verificaColuna(int linha);
void exibe(int linha);

//variáveis globais
int qtCombinacoes = 0; //possíveis combinações da soma do número digitado pelo usuário
int NUM; 
int **m; //matriz que vai armazenar todas as combinações antes de serem exibidas na tela
int *posicoesM;

/* Cada chamada da função recursiva vai sendo colocada na pilha, ou seja, a primeira chamada
da função será a última a ser resolvida pois estará no fim da pilha. A última chamada
recursiva será, muito provavelmente, a condição de parada (no caso desse algoritmo, na
função possiveisCombinacoes, essa condição é o numero ser igual a zero pois dessa forma
a primeira possível combinação será armazenada para depois ser printada na tela). 
Dessa forma, após a execução da condição de parada da última chamada da função, 
será executada a próxima chamada recursiva que está na pilha, ou seja, a penúltima 
chamada da função no algoritmo, e assim por diante até que todas as chamadas
sejam executadas.

Explicação exemplificada do funcionamento do algoritmo:
EX: numero digitado pelo usuário = 3;
Parâmetros da função possiveisCombinacoes(numero, armazenaSomas, posicaoAtual, numeroMinimo)
-numero: é de fato o número digitado pelo usuário, mas na primeira chamada recursiva
ele já passa a ser tratado como uma soma reduzida (numero - numero anterior) pois o nosso
objetivo é fazê-lo ficar igual a 0 para acharmos uma combinação.
-armazenaSomas: vetor que vai armazenando as somas do número para depois armazenar tudo
//em uma matriz (m) e colocar em ordem decrescente para depois printar na tela. É importante
ressaltar que os números do vetor armazenaSomas vão sendo sobrescritos.
-posicaoAtual: posicao atual do vetor armazenaSomas - necessário para sabermos qual será
a próxima posição onde poderemos colocar um número que fará parte da combinação
-numeroMinimo: na main passamos como parâmetro o número 1, pois ele é o primeiro (menor)
numero possível para realizarmos a combinação. Já nas chamadas recursivas ele passará 
a ser "interpretado" como o número anterior pois será o último elemento a ser colocado
no vetor armazenaSomas

Executando o algoritmo com o exemplo em questão temos que:
A main chama: possiveisCombinacoes(3, armazenaSomas, 0, 1);
Depois disso temos as chamadas recursivas:
1ª- possiveisCombinacoes(2, armazenaSomas, 1, 1);
2ª- possiveisCombinacoes(1, armazenaSomas, 2, 1);
3ª- possiveisCombinacoes(0, armazenaSomas, 3, 1); - esse é o caso que queremos
para a primeira combinação pois como numero = somaReduzida = 0,
as combinações encontradas serão printadas na tela (1 + 1 + 1).
No laço while, depois de printar a primeira combinação possível, a seguinte verificação
será feita: 1 <= 0 ? Sabemos que isso não é verdade, então dessa vez não entrará no while
Assim, é executada a próxima chamada recursiva da pilha:
(2ª) possiveisCombinacoes(1, armazenaSomas, 2, 2); - numeroAnterior = 2, não continua no
while e, depois disso, temos a seguinte função recursiva na pilha:
(1ª) possiveisCombinacoes(2, armazenaSomas, 1, 2); - como 2 = 2, o loop while é
executado novamente, dessa vez chamando: (4ª) possiveisCombinacoes(0, armazenaSomas, 2, 2),
como estamos no caso que nos dá uma combinação, agora temos a seguinte soma (1 + 2).
saímos do laço while e é executada a chamada da função feita na main:
possiveisCombinacoes(3, armazenaSomas, 0, 2); - como 2 é menor que 3, repetimos tudo
o que está dentro do while e é executada a próxima da pilha:
possiveisCombinacoes(1, armazenaSomas, 1, 2); - como 2 não é menor ou igual a 1,
saímos do while e essa chamada da função termina. Dessa maneira, voltamos para a
função que a chamou (aquela que chamamos primeiro na main):
possiveisCombinacoes(3, armazenaSomas, 0, 3); - assim, uma nova função recursiva é chamada:
5ª- possiveisCombinacoes(0, armazenaSomas, 1, 3); - essa função tem a nossa condição de
parada, então é printado na tela a última possível combinação: o número 3.
As outras chamadas da pilha também são executadas, mas como nenhuma tem a condição de
"parada", nada acontece.
Portanto, as chamadas que, de fato, geram as 3 possíveis combinações de somas para o
número 3 são: 
	1. possiveisCombinacoes(0, armazenaSomas, 3, 1);
	2. possiveisCombinacoes(0, armazenaSomas, 2, 2);
	3. possiveisCombinacoes(0, armazenaSomas, 1, 3);
OBS: se você executar o programa com o número 3 e tirar o comentário da linha 125
as chamadas recursivas serão printadas na tela e será possível verificar o que está
acontecendo no algoritmo conforme a explicação acima.

As seguintes fontes foram consultadas para conhecer mais sobre o assunto e, 
consequentemente, ter uma ideia de como fazer o algoritmo usando recursão e 
como determinar a condição de "parada": 
https://www.guj.com.br/t/todas-as-somas-possiveis-que-resultam-em-um-numero/139100/3
https://www.geeksforgeeks.org/find-all-combinations-that-adds-upto-given-number-2/
https://www.techiedelight.com/print-all-combination-numbers-from-1-to-n/
https://www.sanfoundry.com/c-program-find-number-ways-write-number-as-sum-numbers-smaller-than-itself/
https://programacaodescomplicada.wordpress.com/2012/11/09/aula-64-alocacao-dinamica-pt-6-alocacao-de-matrizes/
https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/aed1_20172/tecnicas.pdf?attachauth=ANoY7crJgwMrWODP7kxqp6K9R7f4fbRZOw6Hxhf1GsdYk1yB94Wa5ep10Sv_XmKEtOuHmruWAZsel0IDeqiFpdfjSTCN2yJkLzrcboWg4ca4MASxB4Hw7bCC6Y1UY0qVLFCYvkJxrWDKEkFRafU-zajATps_NylxpMgoa6pXTI4mwhuTtd_nhMzFrrJqO2tQwr72xEpQkt55KvmkUKOxR6pBokPke-X7LsmzNT-HHzaPV5zeql60XAfKae9YqHkzw9gDOMRCpgS3&attredirects=0
*/

//A função possiveisCombinacoes é executada até que todas as ocorrências tenham 
//sido resolvidas (após a primeira chamada recursiva)
void possiveisCombinacoes(int numero, int *armazenaSomas, int posicaoAtual, int numeroMinimo){
   
   	//começamos a procurar as combinações a partir do menor elemento possível, que é o 1
    int numeroAnterior = numeroMinimo;

    //Se a soma for igual ao número então vamos armazenar as combinações possíveis
    //nesse caso estamos tratando da somaReduzida, que é o numero - numeroAnterior
    //ou seja, no primeiro caso, se queremos achar as decomposições do número 5,
    //as combinações só serão exibidas a partir do momento em que a somaReduzida
    //(representada pela variável numero) for igual a 0
    //Se entrar no default, será feita uma comparação para verificar se o número
    //anterior é menor ou igual ao número e isso será feito até que essa comparação
    //não seja verdadeira. Dentro do do-while teremos a chamada recursiva da nossa função
    //O objetivo é que a cada chamada possamos fazer pequenas alterações nos parâmetros
    //com o objetivo de entrar na condição do número ser igual a 0. Como foi dito
    //anteriormente a cada soma reduzida (representada pela variável numero) igual
    //a 0, é uma possível combinação 
    switch(numero){
    	case 0: 
    		posicoesM[qtCombinacoes] = posicaoAtual-1;
        	for(int coluna = posicaoAtual-1; coluna >= 0; coluna--){
            	m[qtCombinacoes][coluna] = armazenaSomas[coluna];
        	}
        	qtCombinacoes++;
        	break;

        default:
        	if(numeroAnterior <= numero){
	        	do{
		            armazenaSomas[posicaoAtual] = numeroAnterior;
		            int somaReduzida = numero - numeroAnterior;
		            //printf("soma reduzida %d, posição atual %d, número anterior %d\n", somaReduzida, posicaoAtual+1, numeroAnterior);
		            possiveisCombinacoes(somaReduzida, armazenaSomas, posicaoAtual+1, numeroAnterior);
		            numeroAnterior = numeroAnterior + 1;
	        	}while(numeroAnterior <= numero);
    		}
    		break;
    }
}

int verificaColuna(int linha){

	//Verifica a posição do maior elemento de uma combinação pois como todos estão
	//alocados em uma matriz com tamanho fixo e cada combinação tem uma quantidade
	//diferente de números (diferentes de 0), fica difícil de saber onde está o 
	//primeiro elemento de determinada linha (combinação) sem fazer uma verificação
	//Iremos verificar qual é o maior número da linha e em qual coluna ele está
	//pois, dessa forma, seremos capazes de ordenar a matriz de 
	//acordo com o maior elemento de cada linha

	int maior = m[linha][NUM-1];
	int posMaior = 0;

	for(int coluna = NUM-1; coluna >= 0; coluna--){
		if(m[linha][coluna] > maior){
			maior = m[linha][coluna];
			posMaior = coluna;
		}
	}

	return posMaior;
}

void ordenaMatriz(int qtCombinacoes){
    
    int aux = NUM;
    int posMaior = 0;

    //Coloca a matriz em ordem decrescente de acordo com o maior elemento de
    //cada linha(combinação) - essa verificação é feita através da função
    //verificaColuna() pois através dela achamos a posição do elemento 
    //que queremos comparar
    while(aux > 0){
        for(int linha = qtCombinacoes-1; linha >= 0; linha--){
        	posMaior = verificaColuna(linha);
            if(m[linha][posMaior] == aux){
                exibe(linha);
            }
        }
        aux--;
    }
}

void exibe(int linha){

	//Exibe cada uma das combinações possíveis

	for(int coluna = NUM-1; coluna >= 0; coluna--){
	    if(m[linha][coluna] != 0){
	        if(coluna > 0){
	            printf("%d + ", m[linha][coluna]);
	        }else{
	            printf("%d", m[linha][coluna]);
	        }
	    }
    }
    printf("\n");
}

int main(){

    int posicaoAtual = 0;
    int numeroMinimo = 1; 
   
    printf("Digite um numero inteiro: ");
    scanf("%d", &NUM);
   
    int *armazenaSomas;
    armazenaSomas = (int *) calloc(NUM, sizeof(int));
    posicoesM = (int *) calloc(NUM, sizeof(int));

    //alocação dinâmica da matriz
    int quantidadeLinhas = 3000000;
    m = (int**) calloc(quantidadeLinhas, sizeof(int*)); 
    for(int i = 0; i < quantidadeLinhas; i++){
    	m[i] = (int *)calloc(NUM, sizeof(int));
    }
   
    printf("Decomposicao: \n");
   
    possiveisCombinacoes(NUM, armazenaSomas, posicaoAtual, numeroMinimo);
    
    ordenaMatriz(qtCombinacoes);
   
    return 0;
}