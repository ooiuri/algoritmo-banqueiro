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

void printSistema() {
    printf("Oi eu sou o sistema!!! \n");
}

void processaArgs(int argc, char *argv[]) {
// lógica para captura de parâmetros 
    printf("processaArgs(): %d \n", argc);
    for (int i = 0; i < argc; i++){
        printf("%d parametro: %s\n", i, argv[i]);
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

void rotinaSistema(){
    pthread_t thread;
    int flag;
    printf("\nCriando uma thread: ");
    flag = pthread_create(&thread, NULL, processo, NULL);
}