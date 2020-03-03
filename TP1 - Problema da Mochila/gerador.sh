#!/bin/sh

#----------------------------------------------------
#LAED1 - Trabalho Pratico 1
#Alunas: Lara Galvani Moura e Lorena Gomes de O. Cabral
#Matricula: 20183020842 / 20183002361
#Descricao do programa: Script para compilar e executar os dois algoritmos sucessivamente
#Data: 16/09/2019
#----------------------------------------------------

#Referencia: http://www.possatti.com.br/shell-script/

echo "Entre com a capacidade da mochila: "
read W  
echo "Entre com a quantidade de itens: "
read n

file="n"$n".txt" #cria um arquivo chamado n10 por exemplo - caso o valor de n seja 10

echo "$W" > $file #escreve o conteudo de W no arquivo
echo "$n" >> $file #acrescenta o valor de n no arquivo

RANDOM=$$
contador=0
while [ $contador -lt $n ]; do #enquanto o contador for menor que "n"
	peso=$((RANDOM%99+3))	#gera pesos aleatorios 
	valor=$((RANDOM%107+10)) #gera valores aleatorios 
	echo "$peso $valor" >> $file #coloca o peso e o valor gerados no arquivo
	contador=$((contador+1))
	RANDOM=$((RANDOM+12-234/23+143-102%3))
done
