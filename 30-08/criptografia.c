//Lara Galvani Moura - laragalvanim@gmail.com
//Última modificação: 03/09/2019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h> 

/*Objetivo do algoritmo: Ler uma mensagem criptografada de um arquivo e imprimir a 
mensagem descriptografada na saída padrão*/

/*Primeiramente o usuário entra com o nome do arquivo cujos dados serão verificados e
em seguida armazenamos essa frase no vetor de char conteudoArquivo[]. Depois disso a
função decodifica() é chamada (contendo os passos para fazer o caminho inverso
da cifra de césar - para decodificar a frase), nela chamamos a função verificaTrocas(), 
esta primeiramente verifica e troca os pares de lugar. Por exemplo, troca o primeiro par
de caracteres com o último, o terceiro com o antepenúltimo e assim por diante. Em seguida,
trocamos as posições das duplas. Por exemplo, se temos a dupla LA na frase codificada,
trocando as posições teremos AL. Com as trocas de blocos e posições feitas vamos para
o último passo que é verificar a letra correspondente de cada caractere da frase codificada.
Isso é feito através da função verificaLetra(), onde cada letra é passada por parâmetro
e é retornada a sua correspondente no alfabeto comum. Por exemplo, se temos a letra 'd'
e queremos achar a sua correspondente no alfabeto comum, pegamos a posição da letra 'd'
no alfabeto cifrado e verificamos qual é a letra naquela mesma posição no alfabeto comum.
Depois de decifrar a letra printamos na saída padrão, caractere por caractere, até chegar
no final da frase.

Os seguintes sites foram utilizados para pesquisar sobre arquivos e diretórios:
https://www.programiz.com/c-programming/c-file-input-output
https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
http://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
*/

void decodifica();
char verificaLetra(char letra);
void leTxt(FILE *f);
void verificaTrocas();

//variáveis globais
char conteudoArquivo[10000];
//alfabeto normal
char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
//alfabeto com a cifra de césar (rotação de 3 posições)
char cifrado[] = {'d', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c'};
int tamanho; //quantidade de caracteres da mensagem codificada
char *mensagemDecodificada;
int duplas;

void leTxt(FILE *f){

	char temp = fgetc(f);
	int pos = 0;

	//enquanto não chegar no final do arquivo vai lendo e armazenando no vetor
	while(temp != EOF){
		if(temp != '\0'){
			//temp = tolower(temp); //transforma a letra em minúscula
			conteudoArquivo[pos] = temp;
			printf("%c", conteudoArquivo[pos]);
			pos++;
			temp = fgetc(f);
		}
		if(pos%2 == 0){
			duplas++; //olha a quantidade de blocos de 2 que tem no código cifrado
		}
	}

	pos--; //estamos tirando o \0 do final 

	if(pos%2 != 0){ //se o número de caracteres for ímpar colocamos um # no final
		pos++;
		conteudoArquivo[pos] = '#';
		printf("%c", conteudoArquivo[pos]);
		if(pos%2 == 0){
			duplas++; //olha a quantidade de blocos de 2 que tem no código cifrado
		}
	}

	tamanho = pos;

	//alocamos dinamicamente o tamanho necessário para armazenar a frase a ser decodificada
	mensagemDecodificada = (char *) malloc(tamanho * sizeof(char));

}

char verificaLetra(char letra){

	//recebemos como parâmetro uma letra cifrada e verificamos qual a letra correspondente
	//no alfabeto comum
	char letraDecodificada;

	if(isupper(letra)){ //se a letra for maiúscula
		//coloca a letra minúscula para verificar se é sua correspondente na cifra de césar
		letra = tolower(letra);
		for(int i = 0; i < 26; i++){
			if(letra == cifrado[i]){
				letraDecodificada = alfabeto[i];
				letraDecodificada = toupper(letraDecodificada); //letra volta a ser maiúscula
			}
		}
	}else{
		for(int i = 0; i < 26; i++){
			if(letra == cifrado[i]){ //se não for maiúscula e se tiver achado sua correspondente no alfabeto cifrado
				letraDecodificada = alfabeto[i];
			}else if(letra == '#'){ //se o caractere for # trocamos por espaço
				letraDecodificada = ' ';
			}
		}
	}

	return letraDecodificada;
}

//essa função serve para verificar os blocos trocados (primeiro com último, terceiro com
//antepenúltimo e assim por diante) e destrocar
//também destroca a posição das duplas (EX: se temos a dupla AM na frase cifrada,
//essa função vai destrocar, vai ficar MA - faz parte do método para cifrar na cifra de César)
void verificaTrocas(){

	char *novaFraseComBlocosDestrocados = (char *) malloc(tamanho * sizeof(char));
	int inicio = 0; 
	int final = tamanho-1;

	//o conteúdo do vetor de char conteudoArquivo é passado para o vetor de char novaFraseComBlocosDestrocados
	for(int i = 0; i < tamanho; i++){
		novaFraseComBlocosDestrocados[i] = conteudoArquivo[i];
	}

	//enquanto não chegarmos na metade do tamanho da frase trocaremos os blocos
	//primeiro com último, terceiro com antepenúltimo e assim por diante
	//basicamente saltamos uma dupla e continuamos trocando
	while(inicio < tamanho/2){
		//coloca a dupla do início no fim
		novaFraseComBlocosDestrocados[final-1] = conteudoArquivo[inicio];
		novaFraseComBlocosDestrocados[final] = conteudoArquivo[inicio+1];
				
		//coloca a dupla do fim no início
		novaFraseComBlocosDestrocados[inicio] = conteudoArquivo[final-1];
		novaFraseComBlocosDestrocados[inicio+1] = conteudoArquivo[final];

		//atualiza as posições (o quanto cada vamos andar em cada vetor)
		inicio = inicio + 4; //pois iremos agora para a primeira posição da terceira dupla
		final = final - 4; //agora iremos para a última posição da antepenúltima dupla
	}

	char aux;
	//troca as posições de cada bloco de 2 (duplas)
	for(int i = 0; i < tamanho-1; i+=2){
		aux = novaFraseComBlocosDestrocados[i];
		novaFraseComBlocosDestrocados[i] = novaFraseComBlocosDestrocados[i+1];
		novaFraseComBlocosDestrocados[i+1] = aux;
	}

	//coloca as "atualizações" feitas na variável global que estamos verificando
	//para decodificar usando a cifra de César
	for(int i = 0; i < tamanho; i++){
		conteudoArquivo[i] = novaFraseComBlocosDestrocados[i];
	}
}

void decodifica(){

	int aux = 0;

	verificaTrocas();
	
	//como todas as trocas já foram feitas (revertendo os processos de cada uma dos 
	//passos da cifra de César), agora é só pegar cada letra da frase cifrada e
	//ver qual é a sua correspondente no alfabeto normal
	//À medida que essa verificação é feita, já vamos exibindo na saída padrão os
	//caracteres da frase decodificada
	while(aux < tamanho){
		mensagemDecodificada[aux] = verificaLetra(conteudoArquivo[aux]);
		printf("%c", mensagemDecodificada[aux]);
		aux++;
	}
	printf("\n");
}

int main(){
	
   	char txt[50]; //nome do arquivo
	printf("Digite o nome do arquivo: ");
	scanf("%s", txt); //lê do teclado o nome do arquivo

	//abre o diretório atual e tenta abrir o arquivo que o usuário pediu
	DIR *d;
	FILE *f;
	d = opendir(".");
  	if (d) {
		f = fopen(txt, "r"); //abrindo o arquivo e escolhendo a opção de ler, apenas
		if(f == NULL) {
      		perror("Ocorreu um erro ao tentar abrir o arquivo. Tente novamente.\n");
      		return(-1);
   		}
  	}

  	printf("\n");
  	printf("--------------------\n");
  	printf("Mensagem codificada:\n");
  	printf("--------------------\n");

  	//chama a função que vai ler o arquivo .txt e salvar o conteúdo na variável global conteudoArquivo
  	leTxt(f);
  	fclose(f); //fecha o arquivo após ler o txt

  	printf("\n");
  	printf("----------------------\n");
  	printf("Mensagem decodificada:\n");
  	printf("----------------------\n");

  	decodifica();

	return 0;
}