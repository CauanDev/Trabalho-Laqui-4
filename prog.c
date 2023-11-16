#include <stdio.h>
#include <stdlib.h>
#include "prog.h"
/*
Programa: Visualização de uma árvore geral
Descrição:
    O projeto se trata de um quadrado de asteristicos que fica ao redor de uma area, o programa permite que seja controlado o tamanho e a cor da area.
    É possível também controlar a velocidade e a direção que o quadrado de asteristicos irá se locomover, caso o usuario não interfira na direção, o programa
    de forma aleatoria irá escolher uma direção, e quando o quadrado chega no final da area, ele começa a se locomover para o sentido contrário. O programa irá permitir também
    que você crie outras áreas, sendo cada uma independente da outra, tendo cada uma a sua própria velocidade, e tamanho. Podendo o usúario alterar o foco do programa.
    O programa será encerrado quando for pressionado a tecla ESC.

Programador: Kelvin Cauan da Silva Matos
RGM: 47583
Data da ultima modificacão: 20/11/2023
*/

/*
COMO COMPILAR E EXECUTAR O CODIGO:
1. iniciar o CMD
2. selecionar no CMD a pasta em que os arquivos estão
3. escrever no CMD:
   "gcc prog.c -o prog.exe progs.c -Wall -Werror -Wextra -pedantic"
4. depois de compilado irá ser gerado um arquivo executável "prog.exe", para executar basta escrever no CMD o nome do executavel:
   "prog < in.txt"
*/

int main(int argc, char **argv)
{   
    
    int numeros[TAMANHO];
    int i = 0;
    int tamanho;
    ARVORE *arvore, arvore1;
    
    
    argc = argc;
    argv = argv;  
    arvore = &arvore1;

    arvore->indice = 0;
    tamanho = Leitura(numeros);
    printf("Construcao de Arvore1\n");
    arvore->pilha = (int *)malloc((tamanho) * sizeof(int)); 
    arvore->indice1 = 0;
    arvore->vetor = (int *)malloc(tamanho * sizeof(int));  
    for(i = 0; i != tamanho; i++)
    {
        arvore->vetor[i] = numeros[i];
    }
    construirArvore(arvore);

    return 0;
}
