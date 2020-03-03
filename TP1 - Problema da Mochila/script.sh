#!/bin/sh

#----------------------------------------------------
#LAED1 - Trabalho Pratico 1
#Alunas: Lara Galvani Moura e Lorena Gomes de O. Cabral
#Matricula: 20183020842 / 20183002361
#Descricao do programa: Script para compilar e executar os dois algoritmos sucessivamente
#Data: 16/09/2019
#----------------------------------------------------

#Referencia: http://www.possatti.com.br/shell-script/

#-o guloso é o primeiro parametro do script
#-o: utilizado para definir em seguida o nome do arquivo executavel;
gcc -o guloso guloso.c

#O $? retorna 0 se nao ocorrer nenhum erro no comando da linha 1 e retorna 
#se ocorrer. O -eq faz a comparacao para saber se o if é respeitado.
if [ $? -eq 0 ]; then
	#compilado com sucesso
	echo "Algoritmo Guloso"
	./guloso #executa
else
	echo "Não foi possível compilar o arquivo $guloso.c. Tente novamente."
fi

gcc -o tentativaErro tentativaErro.c
 
if [ $? -eq 0 ]; then
	echo "---------------------------------------------------------------"
	echo "Algoritmo Tentativa e Erro"
	./tentativaErro
else
	echo "Não foi possível compilar o arquivo $tentativaErro.c. Tente novamente."
fi





