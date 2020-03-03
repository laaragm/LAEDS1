#include <limits.h>
#include <stdio.h>
#include <sys/resource.h> //getrusage
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h> //gettimeofday
#include <string.h>

/************************************************
LAED1 - Trabalho Pratico 2
Alunas: Lara Galvani Moura e Lorena Gomes de Oliveira Cabral
Matricula: 20183020842 / 20183002361
Descricao do programa: Implementacao e analise de algoritmos de ordenacao
Data: 29/11/2019 
************************************************/

/*Primeiramente, para compilar o programa é necessário digitar no terminal do Linux o 
seguinte comando: gcc algoritmosOrdenacao.c
Para executar é só digitar ./a.out e inserir os parâmetros comentados e especificados
na main do algoritmo (Ex.: ./a.out -a Quicksort -n 100 -t 1 -v S -r S)
Após verificar o algoritmo escolhido e salvar os outros parâmetros passados, é alocado
dinamicamente um vetor com tamanho+1 posições (pois o ziviani usa a posição 0 como 
sentinela ou então começa na posição 1 mesmo sem usar sentinela), a função geraVetor é
chamada com o intuito de gerar um vetor, usando a função rand(), de acordo com o que foi
pedido pelo usuário. Se o usuário pediu um vetor ordenado, então um número aleatório é
gerado e os próximos números são incrementos daquele gerado. Se o usuário pede um vetor
em ordem decrescente, é feita a mesma coisa porém decrementando esse número gerado. Se
for pedido um vetor aleatório, então sempre serão gerados novos números. E, por fim, se
o usuário escolher a opção para gerar um vetor parcialmente ordenado, então 20% dos
elementos ficam fora do lugar, ou seja, geramos um vetor ordenado (usando o método para
gerar vetores crescentes citado acima) e depois trocamos elementos distintos, de forma
que 1/5 do vetor esteja desordenado. Em seguida, a função ordena() é chamada e esta,
por sua vez, verifica qual será o algoritmo de ordenação a ser usado e faz a chamada 
deste. A função correspondente ao método de ordenação a ser utilizado ordena o vetor e,
logo em seguida, de volta na função ordena() printamos na tela o vetor ordenado (caso
o usuário tenha requisitado essa funcionalidade). É importante ressaltar que os algoritmos
dos métodos de ordenação (BubbleSort, QuickSort, MergeSort, HeapSort, Inserção e Seleção)
foram todos retirados do material referenciado abaixo:
http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-04.php
https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/aed1_20172/Selecao.pdf?attachauth=ANoY7cryclTEO0ilpe2x3KxfltRrZCs17Vougrm-GKYO-2YwnvyGyqJB-vKE7oI4M5HjdUB1oh9_wnBOzTJy92X3y0zVtzx0pmpFHBxNiLsMFushfNcQHZyiyHRUX5ZXBeP3kqJ3v-Gw0JTAQt09MjfKG_MiTCUgbbr5PUswPMmzPHnIZTCPvbLpnSV4wZUSOkSpNfvld_n5T0KdAuhUKDeSOb1E96oYgmx3lH9HCKJeKDZRp8prvRVt2hruV73Q79stKShIiQfF&attredirects=0
https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/aed1_20172/Ordenacao_p2.pdf?attachauth=ANoY7crEi_srxkOsigXw_iOQ5uXf2qbM6Iiw2xokQEJNjsa0PWu6lpJNemZBhisoES6mrZlnAF688uBu8wAAFIRa7w5XXBNvdWagYtgHhi1vAtrm5OpdHg0f3dhFDvStsyb9V88GlRfMT0fyvVlLUjaW_yznaf7rds5Dku6RKuFV1Ln_sfiF4lOc_b2ROYbMofmCU-dLWbI8X-QgoAthLKYl4UazQiPwOXvjMOE--RMxq7TiuEWb5HVtjPBRDmiHL19kWoZqHqfL&attredirects=0
https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/aed1_20172/Ordenacao_p3.pdf?attachauth=ANoY7coBA6bQ8_4uURCozK5hHrgFYySXZiV95WwkFdEbwzBemlNRnOXIkF0aKahjXupSG3c6ps_HHEn88kGlwr3X88q3Dpk5OI9nEFZvvjywVvr3CTinUKm23gwdQ8yIiaPR9j-U5AuCyIUPKMBPDnTI56GjSbC4d_83H4qVub3lIadUkWmog4_cuc7nvg99dMLtEsgM-fVsCa62c8fiXKgXY_XaWC_DbcAvx9lVy4l1W3Jgw8RF3TT_7uGW-g6JTq9lNqQAmkg9&attredirects=0
https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/aed1_20172/Ordenacao_p4.pdf?attachauth=ANoY7coNsLvYH_ErUnMs2oueOHpTU39PZIjALfpRBnGnKsULF4osbTWxHdKRsaF8nUhwWrHqin6o7hIqAxmlU7KK42OkDK3zQmL9saopSF8Vjk8HeFqE7UFeEdxZBWO4kmtHf2tDglHmyw4se4VOEvCxLXumkXHnfH4ZVQTjn-mrUr0aKz_fwY_Flj-iGcHg9NBAgMH7_rx-8WdsBZk5IDsICx7Q8ksqJhR-dbaCtmEFG4CNA4Vwe216656XTK2U8rCkUbylv3dt&attredirects=0
http://www2.dcc.ufmg.br/livros/algoritmos/cap4/slides/c/completo1/cap4.pdf

As funções para medição do tempo de usuário foram retiradas da seguinte fonte:
https://3d702930-a-62cb3a1a-s-sites.googlegroups.com/site/nataliacefetmg/home/anteriores/laed1_20181/medicao_tempo.pdf?attachauth=ANoY7cobJiJCPMYXromqiywJNgfSWiqX74BzPjGrFN-Qt70yKPB6TWpU_xSq8Cc2MK-CqX2AV-oLZJK1WnFAHRh-P3o2FRFNb-XCnPhPNjsq76D8qAJiyqgFSqzxKLYanatsRPHZiwYMrDbt5YBT9-bNg9Vum__LDNTQmsDypYJXFGgsNBt7YRk7a1IpHBWj41B5KXZHAuI7sXFRG71YHzf9ZxGSamuWbJa_aTwPI84vLDpmiww3eSrZCO_oO97J6oFdVKjnWpWzPdWEiosbjdLSEWbArcDsCw%3D%3D&attredirects=0
*/

typedef int TipoChave;
typedef int TipoIndice;
typedef struct TipoItem{
  	TipoChave Chave;
  	TipoIndice indice;
}TipoItem;


//assinatura metodos
void BubbleSort(TipoItem *A, int n);
void InsertionSort(TipoItem *A, int n);
void SelectionSort(TipoItem *A, int n);
void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A);
void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void QuickSort(TipoItem *A, int n);
void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void Constroi(TipoItem *A, int n);
void Heapsort(TipoItem *A, int n);
void Merge(TipoItem *A, int i, int m, int j);
void Mergesort (TipoItem *A, int i, int j);
TipoItem* geraVetor(TipoItem *vetor, int op, int tamanhoVetor);
void ordena(TipoItem *vetor, int algoritmo, int tamanhoVetor, char* imprimirOriginal, char* imprimirOrdenado);
void printaVetor(TipoItem *vetor, int tamanhoVetor);

//-----------------------------------------------------------------------------------------
//Algoritmos ordenacao

//BubbleSort
void BubbleSort(TipoItem *A, int n){ 

    int i, j;
    TipoItem aux;

    for (j = 0; j < n-1; j++){
        for (i = 0; i < n-1; i++){
            if (A[i].Chave > A[i+1].Chave){
                aux = A[i];
                A[i] = A[i+1];  
                A[i+1] = aux;
            }
        }
    }
}

//Inserção
void InsertionSort(TipoItem *A, int n){

    TipoIndice i, j;
    TipoItem x;

    for(i = 2; i <= n; i++){
        x = A[i];
        j = i-1;
        A[0] = x;
        while(x.Chave < A[j].Chave){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
}

//Seleção
void SelectionSort(TipoItem *A, int n){
    
    TipoIndice i,j,Min;
    TipoItem x;

    for (i = 1; i <= n-1; i++){
        Min = i;
        for (j = i+1; j <= n; j++){
            if (A[j].Chave < A[Min].Chave){
                Min = j;
            }
        	x = A[Min];
        	A[Min] = A[i];
        	A[i] = x;        
    	}
    }
}

//QuickSort
void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A){

  	TipoItem x, w;
  	*i = Esq;  
  	*j = Dir;
  	x = A[(*i + *j) / 2]; 
  
  	do{ 
      	while (x.Chave > A[*i].Chave){
        	(*i)++;
      	}
      	while (x.Chave < A[*j].Chave){
        	(*j)--;
      	}
      
      	if (*i <= *j){ 
	        w = A[*i]; 
	        A[*i] = A[*j]; 
	        A[*j] = w;
	        (*i)++; 
	        (*j)--;
      	}
    }while(*i <= *j);
}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A){

  	TipoIndice i, j;

  	Particao(Esq, Dir, &i, &j, A);

  	if(Esq < j){
  		Ordena(Esq, j, A);
  	}	

  	if(i < Dir){
  		Ordena(i, Dir, A);
  	} 
}

void QuickSort(TipoItem *A, int n){ 

    Ordena(1, n, A); 
}

//HeapSort
void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A){

  	TipoIndice i = Esq;
  	int j;
  	TipoItem x;
  	j = i * 2;
  	x = A[i];
  
  	while(j <= Dir){
   		if(j < Dir){
     		if (A[j].Chave < A[j+1].Chave){
     			j++;
     		}
      	}

      	if(x.Chave >= A[j].Chave){
      		goto L999;
      	} 

      	A[i] = A[j];
      	i = j;
      	j = i * 2;
    }

  	L999: A[i] = x;
}

void Constroi(TipoItem *A, int n){ 
  
  	TipoIndice Esq;

  	Esq = n / 2 + 1;

  	while (Esq > 1){ 
    	Esq--;
    	Refaz(Esq, n, A);
  	}
}

void Heapsort(TipoItem *A, int n){ 
  
  	TipoIndice Esq, Dir;
  	TipoItem x;

  	Constroi(A, n);

  	Esq = 1;
  	Dir = n;

  	while (Dir > 1){ 
    	x = A[1];  
    	A[1] = A[Dir];  
    	A[Dir] = x;
    	Dir--;

    	Refaz(Esq, Dir, A);
	}	
}

//MergeSort
void Merge(TipoItem *A, int i, int m, int j){

    TipoItem *B = (TipoItem*)calloc(j+1, sizeof(TipoItem));
    
    int x;
    int k = i;
    int l = m+1;

    for(x = i; x <= j; x++){
        B[x] = A[x];
    }

    x = i;

    while((k <= m) && (l <= j)){
        if(B[k].Chave <= B[l].Chave){
            A[x++] = B[k++];
        }else{
            A[x++] = B[l++];
        }
    }

    while(k <= m){
        A[x++] = B[k++];
    }

    while(l <= j){
        A[x++] = B[l++];
    }

    free(B);    
}

void Mergesort(TipoItem *A, int i, int j){

  	int m;

  	if(i < j){
    	m = (i+j-1)/2;
    	Mergesort(A, i, m);
    	Mergesort(A, m+1, j);
    	Merge(A, i, m, j); 
  	}
}
//Fim algoritmos ordenacao
//----------------------------------------------------------------------------------------

TipoItem* geraVetor(TipoItem *vetor, int op, int tamanhoVetor){

	srand(time(NULL));
	int semente;

	switch(op){
		case 1: //vetor em ordem crescente
			semente = (rand()%10)+32;
			for(int i = 1; i <= tamanhoVetor; i++){
				vetor[i].Chave = semente;
				semente++;
			}
			break;

		case 2: //vetor em ordem decrescente
			semente = (rand()%10)+tamanhoVetor;
			for(int i = 1; i <= tamanhoVetor; i++){
				vetor[i].Chave = semente;
				semente--;
			}
			break;

		case 3: //vetor aleatório
			for(int i = 1; i <= tamanhoVetor; i++){
				vetor[i].Chave = (((rand()%i+1)+(i*372))/5);
			}
			break;

		case 4: //vetor quase ordenado (20% dos elementos fora de ordem)
			semente = (rand()%10)+23;
			//coloca em ordem crescente
			for(int i = 1; i <= tamanhoVetor; i++){
				vetor[i].Chave = semente;
				semente++;
			}
			//tira 20% dos elementos do lugar
			int aux = tamanhoVetor-1;
			int aux2 = 2;
			int qtForaDeOrdem = 0.2*tamanhoVetor;
			int temp;
			while(qtForaDeOrdem > 0){
				temp = vetor[aux].Chave;
				vetor[aux].Chave = vetor[aux2].Chave;
				vetor[aux2].Chave = temp;
				qtForaDeOrdem =  qtForaDeOrdem - 2;
				aux--;
				aux2++;
			}
			break;

		default:
			printf("Opção não encontrada. Tente novamente\n");
			exit(1);
			break;
	}

	return vetor;
}

void printaVetor(TipoItem *vetor, int tamanhoVetor){

	for (int i = 1; i <= tamanhoVetor; i++){
		printf("%d ", vetor[i].Chave);
	}
	printf("\n");
}

void ordena(TipoItem *vetor, int algoritmo, int tamanhoVetor, char* imprimirOriginal, char* imprimirOrdenado){

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


	//imprime vetor original caso o usuario tenha digitado "S" para essa opcao
	if(strcasecmp(imprimirOriginal, "S") == 0){
		printf("Vetor original: ");
		printaVetor(vetor, tamanhoVetor);
	}

	switch(algoritmo){
		case 1: //BubbleSort
			BubbleSort(vetor, tamanhoVetor);
			break;

		case 2: //Insercao
			InsertionSort(vetor, tamanhoVetor);
			break;

		case 3: //Selecao
			SelectionSort(vetor, tamanhoVetor);
			break;

		case 4: //QuickSort
			QuickSort(vetor, tamanhoVetor);
			break;

		case 5: //HeapSort
			Heapsort(vetor, tamanhoVetor);
			break;

		case 6: //MergeSort
			Mergesort(vetor, 1, tamanhoVetor);
			break;

		default:
			break;
	}

	//imprime vetor ordenado caso o usuario tenha digitado "S" para essa opcao
	if(strcasecmp(imprimirOrdenado, "S") == 0){
		printf("Vetor ordenado: ");
		printaVetor(vetor, tamanhoVetor);
	}

	//obtenção do tempo final do programa usando a função gettimeofday
    //obtem tempo final do programa
    gettimeofday(&fim, NULL);
   
    //diferenca em segundos
    totalseg = fim.tv_sec - inicio.tv_sec;    
   
    //diferenca em microsegundos
    totalmicroseg = fim.tv_usec - inicio.tv_usec;
   
    //se a diferenca em microssegundos for negativa, os segundos terao que emprestar
    //uma unidade; 1 microseg = 10E-6 s
    if (totalmicroseg < 0){
        totalmicroseg += 1000000;
        totalseg -= 1;
    };

    getrusage(who, &usage);
   
    //tempo de usuário na CPU
    stotalseg = usage.ru_stime.tv_sec; //segundos
    stotalmicroseg = usage.ru_stime.tv_usec; //microsegundos

    printf ("Tempo de usuário: %ld segundos e %ld microssegundos \n", utotalseg, utotalmicroseg);
}

int main(int argc, char *argv[]){

	//parametros 
	//-a: algoritmo a ser executado
	//-n: número de elementos do vetor
	//-t: tipo de entrada. O programa deverá gerar um vetor de entrada de um
	//dos tipos a seguir: 1 - em ordem crescente (ordenado) 2 - em ordem descrescente 
	//3 - aleatório 4 - quase ordenado
	//-v: imprimir vetor original sim (S) ou não (N)
	//-r: imprimir vetor ordenado sim (S) ou não (N)

	//argv[0]: ./a.out ; argv[2]: algoritmo ; argv[4]: quantidade elementos vetor
	//argv[6]: tipo do entrada do vetor a ser gerado ; argv[8]: imprimir vetor original
	//argv[10]: imprimir vetor ordenado 
	/*for(int cont = 0; cont < argc; cont++){
  		printf("%d Parametro: %s\n", cont, argv[cont]);
	}*/

	//verifica qual o algoritmo a ser testado
	int algoritmo;
	if(strcasecmp(argv[2], "Bubblesort") == 0){
		algoritmo = 1;
	}else if(strcasecmp(argv[2], "Insercao") == 0){
		algoritmo = 2;
	}else if(strcasecmp(argv[2], "Selecao") == 0){
		algoritmo = 3;
	}else if(strcasecmp(argv[2], "Quicksort") == 0){
		algoritmo = 4;
	}else if(strcasecmp(argv[2], "Heapsort") == 0){
		algoritmo = 5;
	}else if(strcasecmp(argv[2], "Mergesort") == 0){
		algoritmo = 6;
	}else{
		printf("Algoritmo não encontrado. Tente novamente\n");
		exit(1);
	}
	//printf("%s\n", algoritmo);

	//verifica qual o numero de elementos do vetor
	int tamanhoVetor = atoi(argv[4]); //converte string em int
	//printf("%d\n", tamanhoVetor);

	//verifica o tipo de entrada do vetor a ser gerado
	int tipoVetorASerGerado = atoi(argv[6]); 
	//printf("%d\n", tipoVetorASerGerado);

	//verifica se é para imprimir o vetor original
	int tam = strlen(argv[8]);
	char *imprimirOriginal = malloc(tam*sizeof(char));
	imprimirOriginal = argv[8];
	//printf("%s\n", imprimirOriginal);

	//verifica se é para imprimir o vetor a ser ordenado
	tam = strlen(argv[10]);
	char *imprimirOrdenado = malloc(tam*sizeof(char));
	imprimirOrdenado = argv[10];
	//printf("%s\n", imprimirOriginal);


	//tamanhoVetor+1 pois o ziviani nao usa a posicao 0 do vetor (sentinela)
	//gera o vetor
	TipoItem *vetor = (TipoItem*)malloc((tamanhoVetor+1)*sizeof(TipoItem));
	vetor = geraVetor(vetor, tipoVetorASerGerado, tamanhoVetor);
	/*for(int i = 1; i <= tamanhoVetor; i++){
		printf("%d ", vetor[i].Chave);
	}*/

	//ordena de acordo com o algoritmo selecionado pelo usuario
	ordena(vetor, algoritmo, tamanhoVetor, imprimirOriginal, imprimirOrdenado);


	return 0;
}