//Lara Galvani Moura <laragalvanim@gmail.com>
//Última modificação: 13/08/2019
//Não esqueça do -lm para compilar o código

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int inicializaResultado(int *resultado, int quantidadeDigitos, int numero);
void calculaFatorial(int num);
int digitos(int numero);
void exibe(int *resultado, int qt);

/*Explicação do funcionamento do programa
Exemplo: se queremos achar 10000! a função inicializaValor irá colocar no vetor
resultado (alocado dinamicamente com a quantidade de dígitos necessária para
representar a resposta do fatorial - a função digitos faz isso) o número 10000 
(cada algarismo em uma posição do vetor, começando pela posição 35659 até 35655,
depois disso as outras posições recebem 0). Dessa forma, ao começar a calcular 
o fatorial, multiplicamos cada posição do resultado pelo número anterior (nesse
caso 9999 e assim por diante até chegar em 2 - não é necessário fazer isso com
o 1 pois a resposta continuará igual). Portanto, 0*9999=0, então é colocado 0
na última posição do vetor resultado. Vamos fazendo isso até chegar na posição
0 do vetor, os resultados obtidos em cada multiplicação vão sendo atualizados 
no próprio vetor resultado. Quando finalmente chegamos na operação 1*9999=9999,
pegamos o resto da divisão por 10, dividimos o carry por 10 e a próxima operação
será 0*9999+999=999, pegamos novamente o resto da divisão por 10 e colocamos
na posição em questão no vetor. Vamos fazendo isso até chegar na posição 0.
Inspiração para fazer o algoritmo: https://www.geeksforgeeks.org/factorial-large-number/ */

void exibe(int *resultado, int qt){

	printf("Resultado: ");
	for (int j = 0; j < qt; j++){
		printf("%d", resultado[j]);
	}
	printf("\n");
}

int inicializaResultado(int *resultado, int quantidadeDigitos, int numero){

  //para inicializar o resultado - o último algarismo é 1 e as outras
  //posições do vetor são preenchidas com 0 para poder fazer as multiplicações
  int algarismos = 1; //pois o número tem pelo menos 1 algarismo
  int aux = numero;

  //verifica quantos algarismos o número a ser colocado no vetor tem
  while(aux >= 10){
    algarismos++;
    aux = aux/10;
  }

  //coloca cada algarismo em uma posição do vetor (começando da unidade)
  //quantidadeDigitos está representando a posição a partir de onde colocaremos o
  //primeiro resto de divisão por 10 (último número)
  quantidadeDigitos--; 
  while(algarismos >= 1){
    if(numero < 10){
      resultado[quantidadeDigitos] = numero;
    }else{
      resultado[quantidadeDigitos] = numero%10;
      numero = numero/10;
    }
    quantidadeDigitos--;
    algarismos--;
  }

  //preenche o restante das posições com 0
  for (int i = quantidadeDigitos; i >= 0; i--){
    resultado[i] = 0;
  }

  return *resultado;
}

void calculaFatorial(int num){

	int qt = digitos(num);
	int carry = 0, temp = 0;
	int *resultado;
	//alocação dinâmica que coloca o vetor resultado com a quantidade de posições
    //necessárias para a resposta do fatorial
	resultado = (int *) malloc((qt)*sizeof(int));
	*resultado = inicializaResultado(resultado, qt, num);
	///Como já inicializamos o resultado com o número, agora temos que começar
    //a multiplicação a partir do numero-1
	num--;

	//enquanto o número (representado por aux) for maior ou igual a 2 iremos 
    //fazer as multiplicações para encontrar o fatorial 
	while(num >= 2){
		//Multiplicamos o número por cada uma das posições do resultado 
		//acumulado (este que começa com o valor do número cujo fatorial é procurado)
	  	//e adicionamos o carry (se tiver)
	  	//Logo em seguida verificamos se o temp (valor temporário) é maior ou igual a 10
	  	//Se for, dividimos atualizamos o carry, colocando neste o resultado
	  	//do valor temporário dividido por 10, e o resto da divisão por 10 no resultado
	  	//na posição correspondente à j (vai do menos significativo - última posição do
	  	//vetor - ao mais significativo - posição 0 do vetor resposta)
	  	//Se o valor temporário for menor do que 10 então seu valor é colocado na posição
	  	//j em questão do vetor resultado 
		for(int j = qt-1; j >= 0; j--){
			temp = (num*resultado[j]) + carry;
			if(temp >= 10){
				carry = temp/10;
				resultado[j] = temp%10;
			}else{
				resultado[j] = temp;
				carry = 0;
			}
		}
		num--;
	}

	//exibe a resposta
	exibe(resultado, qt);
}

//A função dígitos retorna o valor de algarismos que a resposta do fatorial terá
//Exemplo: 10000! tem 35660 dígitos, então usaremos essa informação
//para alocar dinamicamente o vetor contendo o resultado do fatorial (isso será feito
//na função fatorial)
//Usei o site https://www.johndcook.com/blog/2015/10/06/number-of-digits-in-n/
//para ver como é possível usar a fórmula de Stirling para encontrar a quantidade
//de dígitos do fatorial
int digitos(int numero){

	double algarismos = 0; 
    for(int x = 2; x <= numero; x++){
    	algarismos = algarismos + log10(x); 
    }
    algarismos = (int)algarismos + 1;
    int alg = algarismos;
	
	return alg;
}

int main(void){

  int numero;

  do{
     printf("Digite um numero inteiro: ");
     scanf("%d", &numero);  
  }while(numero < 0 || numero > 10000);

  if(numero == 0){
     printf("Resultado: 1\n");
  }else{
     calculaFatorial(numero);  
  }

  return 0;
}

/*Apesar de não ter conseguindo dar continuidade (pelo fato de não ter achado uma
forma de obter todas as casas decimais do antilog), tentei resolver também usar os
estudos de Stirling e as propriedades de logaritmos. Segue trecho de código: 

void fatorial(int num){
   
    int qt = digitos(num);
    int *resultado;
    //o vetor resultado terá será do tamanho "qt"
    resultado = (int *) malloc(qt * sizeof(int));
    int aux = num;
    double resul_parcial = 0;

    while(aux >= 1){
       resul_parcial = resul_parcial + log10(aux);
       aux--;
    }
   
    int intpart = (int)resul_parcial;
    double decpart = resul_parcial - intpart;
    int antilogDecPart = pow(10, decpart);
    double antilog = pow(10, intpart);
    printf("%d\n", intpart);
   
    for(int i = 0; i < qt; i++){
        if(antilogDecPart > 10){
            resultado[i] = (int)antilogDecPart%10;
            antilogDecPart = (int)antilogDecPart/10;
        }else{
            resultado[i] = (int)antilogDecPart/10;  
            antilogDecPart = (int)antilogDecPart/10;
        }
    }
    //exibe(resultado, qt - 1);
}*/