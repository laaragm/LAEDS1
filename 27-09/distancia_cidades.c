//Lara Galvani Moura - laragalvanim@gmail.com
//Última modificação: 20/10/2019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//variável para representar um número indefinido/muito grande
#define INF 9999999 

/*Dadas N cidades e as distâncias entre elas, calcular o total de km do menor percurso entre
duas dessas cidades.
O arquivo teste é lido duas vezes. Na primeira vez, as cidades são salvas na matrizCidades
e a matriz distancias é alocada (conforme o número de cidades).
Na segunda vez que o arquivo é lido, são armazenadas as distâncias entre as cidades
na matriz distancias.
Cada cidade será representada por um número na hora de colocar e tratar os dados da 
matriz distancias (que vai ter os números que representam cada cidade e as respectivas
distâncias entre elas). Esses números utilizados para representar as cidades serão 
determinados com base na linha correspondente à cidade. Por exemplo, se está armazenado 
"curitiba" na terceira linha da matrizCidades então a cidade curitiba será representada
pelo número 2 (começa no índice 0).
O menor caminho entre 'origem' e 'destino' será calculado atráves do algoritmo de
Dijkstra, consultado nas seguintes referências:
https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dijkstra.html
https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
https://www.hackerearth.com/pt-br/practice/algorithms/graphs/shortest-path-algorithms/tutorial/
*/

int ** Aloca_matriz(int lin, int col);
int verificaSeCidadeJaFoiAlocada(char *A);
void preenche();
int verificaLinhaCidade(char *A);
void dijkstra();

//Variáveis globais
int km = 0;
int *dist;
int alocar = 1;
int *path;
bool *visitados;
int **distancias; //matriz com as cidades e a distância entre elas
int cidades = 0;
int indiceOrigem;
int indiceDestino;
char *origem;
char *destino;
char matrizCidades[50][20]; //serão no máximo 50 cidades e cada cidade é escrita com até 20 caracteres


int ** Aloca_matriz(int lin, int col){

	if(alocar){ //só faz isso na primeira vez que a função é chamada 
		//alocando a matriz distancias dinamicamente
		distancias = (int **)calloc(lin, sizeof(int *)); //aloca as linhas da matriz
		for(int i = 0; i < lin; i++){ //aloca as colunas da matriz distancias
			distancias[i] = (int *)calloc(col, sizeof(int));
		}

		/*Formato da matriz distâncias (ex de matriz com 5 cidades)
		0 x x x x
		x 0 x x x 
		x x 0 x x
		x x x 0 x
		x x x x 0
		onde estamos representando com 'x' será colocada a distância entre as duas cidades*/

		alocar = 0;
	}else{
		//coloca a distância entre as duas cidades em questão nas devidas posições 
		distancias[lin][col] = km;
		distancias[col][lin] = km;
	}

	return distancias; //retorna o ponteiro para a matriz
}

int verificaSeCidadeJaFoiAlocada(char *A){

	int contador = 0;
	for(int i = 0; i < cidades; i++){
		char *temp = (char*)malloc(sizeof(char)*20); 
		for(int j = 0; j < 20; j++){
			if(matrizCidades[i][j] != '\n'){
				//passa a palavra que está na matriz para uma string temp
				temp[j] = matrizCidades[i][j];
				contador++;
			}
		}
		//realoca temp para não comparar errado devido aos espaços que não estão sendo usados
		temp = (char*)realloc(temp, sizeof(char)*contador);
		//if return value = 0 then it indicates str1 is equal to str2 - strcasecmp não é case sensitive
		if(strcmp(temp, A) == 0){
			return i;
		}		
		if(strcasecmp(temp, A) == 0 && strlen(temp) == strlen(A)){
			return 1;
		}

		contador = 0;
		free(temp);
	}

	return 0;
}

int verificaLinhaCidade(char *A){

	int contador = 0;
	for(int i = 0; i < cidades; i++){
		char *temp = (char*)malloc(sizeof(char)*20); 
		for(int j = 0; j < 20; j++){
			if(matrizCidades[i][j] != '\n'){
				//passa a palavra que está na matriz para uma string temp
				temp[j] = matrizCidades[i][j];
				contador++;
			}
		}
		//realoca temp para não comparar errado devido aos espaços que não estão sendo usados
		temp = (char*)realloc(temp, sizeof(char)*contador);
		//if return value = 0 then it indicates str1 is equal to str2 - strcasecmp não é case sensitive
		//só por garantia caso tenha algum problema com letras maiúsculas e minúsculas
		if(strcmp(temp, A) == 0){
			return i;
		}
		if(strcasecmp(temp, A) == 0){
			return i; //retorna a linha onde a cidade está
		}

		contador = 0;
		free(temp);
	}

	return cidades-1; 
}

void preenche(){

	for(int i = 0; i < 50; i++){
		for(int j = 0; j < 20; j++){
			matrizCidades[i][j] = '\n';
		}
	}
}

void leTxt(){

	FILE *f;
	char txt[50]; //nome do arquivo
	char A[20], B[20]; //cidades
	int arestas = 0, linha = 0, primeira = 1, cont = 0;;

	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", txt); 

    f = fopen(txt, "r"); //abre o arquivo em modo leitura
    if(f == NULL) {
        perror("Ocorreu um erro ao tentar abrir o arquivo. Tente novamente.\n");
        exit(1);
    }

    rewind(f); //coloca o ponteiro no inicio do arquivo

	//faz a leitura do arquivo e verifica se cada cidade já foi alocada
    fscanf(f, "%d", &arestas);

	while(!feof(f)){ //enquanto não chegar no final do arquivo
		fscanf(f, "%s", A); //lê a primeira cidade da linha
		if((cont <= arestas) && (primeira)){ //a primeira cidade é sempre alocada
			int tamA = strlen(A);
			int j = 0;
			for(; j < tamA; j++){
				matrizCidades[linha][j] = A[j];
			}
			linha++;
			cidades++;
			primeira = 0;
		}else
		//se a cidade não tiver sido previamente alocada
		if((cont <= arestas) && (verificaSeCidadeJaFoiAlocada(A) == 0)){ 
			int tamA = strlen(A);
			int j = 0;
			for(; j < tamA; j++){
				matrizCidades[linha][j] = A[j];
			}
			linha++;
			cidades++;
		}

		//faz com B a mesma coisa que fizemos com A 
		fscanf(f, "%s", B); 
		if((cont <= arestas) && (verificaSeCidadeJaFoiAlocada(B) == 0)){ 
			int tamB = strlen(B);
			int j = 0;
			for(; j < tamB; j++){
				matrizCidades[linha][j] = B[j];
			}
			linha++;	
			cidades++;
		} 
		cont++;
		if(cont > arestas){
			int tam = strlen(A);
			origem = (char *)malloc(tam*sizeof(char));
			strcpy(origem, A); //destination, source
			indiceOrigem = verificaLinhaCidade(origem);
			tam = strlen(B);
			destino = (char *)malloc(tam*sizeof(char));
			strcpy(destino, B); //destination, source
			indiceDestino = verificaLinhaCidade(destino);
		}else{
			fscanf(f, "%d", &km); 
		}
	}

	//aloca a matriz com base na quantidade de cidades (linha cidades e coluna cidades)
	distancias = Aloca_matriz(cidades, cidades); 

	//volta com o ponteiro para o início do arquivo pois agora serão, de fato, colocadas
	//as informações que precisamos na matriz distâncias
	rewind(f); 

	fscanf(f, "%d", &arestas);
	int aux = arestas;
	while(aux > 0){
		//lê a linha
		fscanf(f, "%s %s %d", A, B, &km);
		//verifica a linha que está a cidade (origem) na matrizCidades
		int linhaOrigem = verificaLinhaCidade(A);
		//verifica a coluna que está a cidade (destino) na matrizCidades
		int colunaDestino = verificaLinhaCidade(B);
		//coloca a distância na matriz distancias nas posições encontradas acima
		distancias = Aloca_matriz(linhaOrigem, colunaDestino);
		aux--;
	}

	fclose(f); //fecha o arquivo
}

void dijkstra(){

	//O objetivo é sair do indiceOrigem e chegar no indiceDestino através do menor caminho
	//Calcular o total de km do menor percurso entre duas dessas cidades
	//O número de vértices do grafo é igual ao número de cidades
	//Suporemos também que dispomos de uma constante  INF de valor estritamente
	//maior que o custo de qualquer caminho simples no grafo. 

	//*dist will hold the shortest distance from 'origem' to 'destino'
	dist = (int *)malloc(cidades*sizeof(int));  
	path = (int *)malloc(cidades*sizeof(int)); 
	visitados = (bool *)malloc(cidades*sizeof(bool)); //true: city has been visited
	int mindistance, nextnode;
    
	//iniciamos colocando false em todas as posições do vetor visitados, deixando apenas
	//a origem como visitada(true)
	for(int i = 0; i < cidades; i++){
		for(int j = 0; j < cidades; j++){
			visitados[i] = false;
			dist[i] = INF;
			//If there is no edge between vertices i and j then distancias[i][j] is infinity
			if(distancias[i][j] == 0){
				distancias[i][j] = INF;
			}
		}
	}

	//Distance of source vertex from itself is always 0
	dist[indiceOrigem] = 0;
	visitados[indiceOrigem] = true;

	printf("Menor percurso: ");

	//initialize path[], dist[] and visitados[]
	for(int i = 0; i < cidades; i++){
		dist[i] = distancias[indiceOrigem][i];
		path[i] = indiceOrigem;
	}

	// Find shortest path for all vertices 
	for(int count = 1; count < cidades-1; count++) {  
        mindistance = INF;

        //nextnode gives the node at minimum distance
		for(int i = 0; i < cidades; i++){
			if((dist[i] < mindistance) && (visitados[i] == false)){
				mindistance = dist[i]; 
				nextnode = i;
			}
		}

        visitados[nextnode] = true; // Mark the picked vertex as processed 
                  
        //check if a better path exists through nextnode			
		for(int i = 0; i < cidades; i++){
			if((mindistance + distancias[nextnode][i] < dist[i]) && (visitados[i] == false)){
				dist[i] = mindistance + distancias[nextnode][i];
				path[i] = nextnode;
			}
		}
    }

	//Imprime o caminho e a distância da origem até o destino
    int j = indiceDestino;
    int aux[cidades];
    int contador = 0;

    for(int i = 0; i < cidades; i++){
		if(i == indiceDestino){
			aux[contador] = i;
			contador++;
			j = i;
			do{
				j = path[j];
				aux[contador] = j;
				contador++;
			}while(j != indiceOrigem);
		}
	}

	for(int i = contador-1; i >= 0; i--){
		int temp = aux[i];
		for(int c = 0; c < 20; c++){
			if(matrizCidades[temp][c] != '\n'){
				printf("%c", matrizCidades[temp][c]);
			}
		}
		printf(" ");
	}

	printf("\n");
	printf("Distancia total: %d Km\n", dist[indiceDestino]);
}

int main(){

	//preenche() coloca '\n' em todas as posições da matriz cidades para, posteriormente, 
	//sobrescrevermos com o nome da cidade e o '\n' vai marcar o fim da palavra
	preenche();

	//lê o arquivo txt, chama as devidas funções para alocar a matriz distancias
	//e colocar as distancias entre cada dupla de cidades 
	leTxt(); 

	//calcula a menor distância usando o algoritmo de Dijkstra
	dijkstra();

	//liberando os espaços alocados
	free(distancias);
	free(dist);
	free(visitados);
	free(origem);
	free(destino);
	free(path);

	return 0;
}