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
extern int *matriz_alocados;
extern int *matriz_necessarios;

int *vetor_processos;

void printSistema() {
    printf("Oi eu sou o sistema!!! \n");
}

void processaArgs(int argc, char *argv[]) {
// lógica para captura de parâmetros 
    // printf("processaArgs(): %d \n", argc);
    for (int i = 0; i < argc; i++){
        // printf("%d parametro: %s\n", i, argv[i]);
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

struct processoStruct {
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
        processosArgs[i].quantidade_recursos = quantidade_recursos;
        processosArgs[i].recursos_existentes = recursos_existentes;
        pthread_create(&vetor_processos[i], NULL, processo, processosArgs);
    }
    
    pthread_t thread;
    int flag;
    printf("\nCriando uma thread: ");
    flag = pthread_create(&thread, NULL, processo, NULL);
    if(flag != 0){
        printf("\nErro ao criar a thread!\n");
    }
    else{
        printf("\nThread criada com sucesso!\n");
    }
    pthread_exit(NULL);
}