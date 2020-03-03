//Lara Galvani Moura <laragalvanim@gmail.com>
//Última modificação: 13/08/2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Não esqueça do -lm para compilar o código

void exibe(int *resultado, int qt){

    printf("Resultado: ");
    for (int j = 0; j < qt; j++){
      printf("%d", resultado[j]);
    }
    printf("\n");
}

int inicializaResultado(int *resultado, int quantidadeDigitos, int numero){

  //para inicializar o resultado - colocamos o número a ter seu fatorial
  //calculado no vetor e as outras serão preenchidas com 0 
  int quantidade = quantidadeDigitos;
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
    //printf("%d\n", vet[qt]);
  }

  //preenche o restante das posições com 0
  for (int i = quantidadeDigitos; i >= 0; i--){
    resultado[i] = 0;
  }

  return *resultado;
}

int carryAcumulado(int carry, int posicao, int *resultado, int valorTemporario){

  //A ideia aqui é usar o carry acumulado (ao final de cada operação), ir 
  //pegando o resto de divisão por 10 e colocando nas posições subsequentes
  //(considerando a disposição dos algarismos da direita para a esquerda). 
  //Vamos fazendo isso enquanto o carry for maior que 0. 
  //Ideia de usar o acumulador tirada de uma discussão no site 
  //https://codereview.stackexchange.com/questions/158256/multiplying-and-adding-large-numbers
  //sobre como multiplicar e adicionar números grandes 
  for( ; carry > 0; carry = carry/10, posicao--){
    int resto = valorTemporario%10;
    resultado[posicao] = resto;
  }

  return *resultado;
}

//A ideia é ir fazendo as multiplicações, armazenar cada dígito 
//do resultado em uma posição do vetor(através do resto de divisão por 10).
//Os transportes de entrada e saída são representado através da variável carry.
//Ideia retirada do site: https://www.geeksforgeeks.org/factorial-large-number/
void calculaFatorial(int num){
   
    int qt = digitos(num);
    int *resultado;
    //alocação dinâmica que coloca o vetor resultado com a quantidade de posições
    //necessárias para a resposta do fatorial
    resultado = (int *) malloc(qt * sizeof(int));
    *resultado = inicializaResultado(resultado, qt, num);
    int carry = 0, temp = 0; 
    ///Como já inicializamos o resultado com o número, agora temos que começar
    //a multiplicação a partir do numero-1
    int aux = num - 1; 

    //enquanto o número (representado por aux) for maior ou igual a 2 iremos 
    //fazer as multiplicações para encontrar o fatorial 
    while(aux >= 2){ 
      //Multiplicamos aux (que representa o número que queremos encontrar
      //o fatorial e seus antecedentes) pelo resultado acumulado em cada
      //uma das posições do vetor resultado e adicionamos
      //o carry (se tiver - quando o resultado é maior do que 10)
      //Logo em seguida dividimos atualizamos o carry, colocando o resultado
      //do valor temporário dividido por 10 - o carry fica com valor acumulado 
      //para ir somando com os valores temporários seguintes e, no final desse 
      //for, o outro for vai cuidar do valor acumulado do carry
      //E, por último colocamos o resto da divisão por 10 de temp na última 
      //posição do vetor resultado - que representa o número menos significativo
      int posicao; //recebe o valor de j para continuar a seguir as posições no próximo for
      for(int j = qt - 1; j >= 0; j--){
        temp = (aux*resultado[j]) + carry;
        carry = temp/10;
        resultado[j] = temp%10;
        posicao = j; 
      }
      
      carryAcumulado(carry, posicao, resultado, temp);

      //Decrescemos o número de 1 em 1, para poder computar todos os números
      //referentes ao fatorial que desejamos encontrar
      aux--;
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

/*Tentei fazer o programa fazendo primeiro as multiplicações e somando as linhas.
Entretanto, ficou difícil de realizar todos os cálculos, por isso pesquisei 
sobre o assunto e pude solucionar o problema usando um acumulador do carry.

Apesar de não ter conseguindo dar continuidade (pelo fato de não ter achado uma
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