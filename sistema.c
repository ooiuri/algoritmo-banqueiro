#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "banqueiro.h"
#include "processos.h"

extern int num_processos;
extern int quantidade_recursos;

extern int *recursos_existentes;
extern int *recursos_alocados;
extern int *recursos_disponiveis;

extern int **matriz_alocados;
extern int **matriz_necessarios;
extern int **matriz_recursos;

int *vetor_processos;

void printSistema() {
    printf("Oi eu sou o sistema!!! \n");
}

void processaArgs(int argc, char *argv[]) {
// lógica para captura de parâmetros 
    for (int i = 0; i < argc; i++){
        if (!strcmp(argv[i],"-n") && argv[i+1]){
            num_processos = atoi(argv[i+1]);
        }
        if (!strcmp(argv[i],"-a")){
            for (int j = 1; j < quantidade_recursos + 1; j++){
                if (!strcmp(argv[i + j],"-n") || !atoi(argv[i+j])){
                    break;
                }
                recursos_existentes[j - 1] = atoi(argv[i+j]); 
            }
        }
    }
}

void calculaRecursosAlocados() {
    int *cont = calloc(quantidade_recursos, sizeof(int));
    for (int i = 0; i < num_processos; i++){
        for (int j = 0; j < quantidade_recursos; j++){
            cont[j] += matriz_alocados[i][j];
        }
    }
    for (int i = 0; i < quantidade_recursos; i++){
        recursos_alocados[i] = cont[i];
    }
    printf("\n\n\t\tRecursos Alocados:\n");
    for(int i = 0; i < quantidade_recursos; i++){
        printf("%d ", recursos_alocados[i]);
    }
}

void calculaRecursosDisponiveis(int print){
    int *cont = calloc(quantidade_recursos, sizeof(int));

    printf("\n\n\t\tCalculando Recursos Disponiveis:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            cont[j] += matriz_alocados[i][j];
        }
    }
    for(int i = 0; i < quantidade_recursos; i++){
        recursos_disponiveis[i] = recursos_existentes[i] - cont[i];
    }
    if(print){
        printf("\n\n\t\tRecursos Disponiveis:\n");
        for(int i = 0; i < quantidade_recursos; i++){
            printf("%d ", recursos_disponiveis[i]);
        }
    }
}

void printMatrizAlocados(){
    printf("\n\n\t\tMatriz Alocados:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_alocados[i][j]);
        }
        printf("\n");
    }
}

void printMatrizNecessarios(){
    printf("\n\n\t\tMatriz Necessarios:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_necessarios[i][j]);
        }
        printf("\n");
    }
}

void printMatrizRecursos(){
    printf("\n\n\t\tMatriz Recursos:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_recursos[i][j]);
        }
        printf("\n");
    }
}
struct processoStruct {
    int pid;
    int quantidade_recursos;
    int *recursos_existentes;
};
typedef struct processoStruct processoArgsStruct;

processoArgsStruct *processosArgs;


void rotinaSistema(){
    // Alocação de memória para os processos
    vetor_processos = malloc(sizeof(pthread_t) * num_processos);
    // Alocação de memória para os argumentos dos processos
    processosArgs = (processoArgsStruct*)malloc(sizeof(processoArgsStruct) * num_processos);

    for(int i = 0; i < num_processos; i++){
        pthread_t vetor_processos[i];
        // passa os parãmetros para o processo
        processosArgs[i].pid = i;
        processosArgs[i].quantidade_recursos = quantidade_recursos;
        processosArgs[i].recursos_existentes = malloc(sizeof(int8_t) * quantidade_recursos);
        for(int j = 0; j < quantidade_recursos; j++){
            processosArgs[i].recursos_existentes[j] = recursos_existentes[j];
        }
        pthread_create(&vetor_processos[i], NULL, processo, &processosArgs[i]);
    }

    
    pthread_exit(NULL);
}

