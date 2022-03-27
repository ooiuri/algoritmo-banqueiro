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

int **matriz_alocados;
int **matriz_necessarios;

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
    printf("$ Algoritmo do Banqueiro! $\n");

    // processa os argumentos de entrada e aloca os vetores de recursos
    quantidade_recursos = argc - 4;
    recursos_existentes = malloc(sizeof(int) * (quantidade_recursos));
    recursos_alocados = malloc(sizeof(int) * (quantidade_recursos));
    recursos_disponiveis = malloc(sizeof(int) * (quantidade_recursos));

    processaArgs(argc, &argv[0]);

    matriz_alocados = (int**)malloc(sizeof(int**) * num_processos);
    matriz_necessarios = (int**)malloc(sizeof(int**) * num_processos);
    
    printf("\n\n\t\tAlocando Matrizes:\n");
    for(int i = 0; i < num_processos; i++){
        matriz_alocados[i] = (int*)calloc(quantidade_recursos, sizeof(int) );
        matriz_necessarios[i] = (int*)calloc(quantidade_recursos, sizeof(int) );
    }
    

    //printa a matriz de necessarios
    printf("\n\n\t\tMatriz de necessarios:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_necessarios[i][j]);
        }
        printf("\n");
    }
    //printa a matriz de alocados
    printf("\n\n\t\tMatriz de alocados:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_alocados[i][j]);
        }
        printf("\n");
    }

    printf("\nNúmero de processos: %d\n", num_processos);
    printf("Vetor de recursos: \n");
    for(int i = 0; i < quantidade_recursos; i++){
        printf(" %d ", recursos_existentes[i]);
    }
    printf("\n");

    printSistema();
    rotinaSistema();
    return 0;
}

int requisicao_recursos(int pid, int recursos[]) {
    //muda a cor para verde
    printf("\033[0;32m");
    printf("\nRecebi uma requisição do processo %d, pedindo %d recursos: ", pid, quantidade_recursos);
    for(int i = 0; i < quantidade_recursos; i++){
        printf("%d ", recursos[i]);
    }
    printf("\n");
    int flag_libera_recursos = 1;
    for(int i = 0; i < quantidade_recursos; i++){
        if(recursos[i] > recursos_disponiveis[i]){
            flag_libera_recursos = 0;
            break;
        }
    }
    if(flag_libera_recursos == 1){
        
        printf("\nVou liberar os pedido dos recursos!\n");
        for(int i = 0; i < quantidade_recursos; i++){
            matriz_alocados[pid][i] += recursos[i];
        }
        printf("Matriz de alocados:");
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_alocados[pid][j]);
        }
        printf("\nLiberei!\n");
    }
    else{
        printf("\033[0;33m");
        printf("\nNão vai ser possivel liberar o pedido dos recursos!\n");
    }
    printf("\033[0m");
    printf("\ncalcula recursos alocados\n");
    calculaRecursosAlocados();
    calculaRecursosDisponiveis();
    return flag_libera_recursos;
}

int libera_recursos(int pid, int recursos[]) {
    printf("\033[0;33m");
    printf("\nRecebi uma requisição do processo %d liberando os recursos: ", pid);
    for(int i = 0; i < quantidade_recursos; i++){
        printf("%d ", recursos[i]);
    }
    for(int i = 0; i < quantidade_recursos; i++){
        matriz_alocados[pid][i] += recursos[i];
    }
    printf("\n\033[0m");
    // calculaRecursosAlocados();
    // calculaRecursosDisponiveis();
    return 0;
}

