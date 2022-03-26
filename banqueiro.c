#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "sistema.h"

int num_processos;
int quantidade_recursos;

int *recursos_existentes;
int *recursos_alocados;
int *recursos_disponiveis;

int *matriz_alocados;
int *matriz_necessarios;

void printHello(){
    printf("Oi eu sou o banqueiro");
}

/**
 * Função Principal
 * @ -n <num_processos>
 * @ -a <vetor_recursos>
 **/

int main (int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");
    printf("Algoritmo do Banqueiro! $$$\n");

    // processa os argumentos de entrada e aloca os vetores de recursos
    quantidade_recursos = argc - 4;
    recursos_existentes = malloc(sizeof(int8_t) * (quantidade_recursos));
    recursos_alocados = malloc(sizeof(int8_t) * (quantidade_recursos));
    recursos_disponiveis = malloc(sizeof(int8_t) * (quantidade_recursos));

    matriz_alocados = malloc(sizeof(int8_t) * (quantidade_recursos * 3));
    matriz_necessarios = malloc(sizeof(int8_t) * (quantidade_recursos * 3));
    processaArgs(argc, &argv[0]);
    
    printf("\nNúmero de processos: %d\n", num_processos);
    printf("Vetor de recursos: \n");
    for(int i = 0; i < quantidade_recursos; i++){
        printf(" %d ", recursos_existentes[i]);
    }

    printSistema();
    rotinaSistema();
    return 0;
}

int requisicao_recursos(int pid, int recursos[]) {
    return 0;
}

int libera_recursos(int pid, int recursos[]) {
    return 0;
}

