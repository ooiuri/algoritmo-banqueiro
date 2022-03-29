#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "banqueiro.h"
#include "sistema.h"

extern int num_processos;
extern int quantidade_recursos;
extern int *recursos_existentes;
extern int *recursos_alocados;
extern int *recursos_disponiveis;

extern int **matriz_alocados;
extern int **matriz_necessarios;
extern int **matriz_recursos;

int *vetor_processos;

#define TIME 5
extern struct processoStruct {
    int pid;
    int quantidade_recursos;
    int *recursos_existentes;
};

void *processo(void *argumento) {
    printf("\n\t\tOi eu sou um processo!\n");
    // Verifica os argumentos do processo
    struct processoStruct *processoArgs = argumento;
    printf("Sou o processo %d que tem: %d recursos disponiveis",processoArgs->pid, processoArgs->quantidade_recursos);
    for (int i = 0; i < processoArgs->quantidade_recursos; i++) {
        printf(" %d", processoArgs->recursos_existentes[i]);
    }
    printf("\n\t\t\t\tAlocando a quantidade de recursos");
    //printa a matriz de necessidades
    //define a quantidade de recursos necessários
    for(int i = 0; i < processoArgs->quantidade_recursos; i++){
        matriz_necessarios[processoArgs->pid][i] = rand() % processoArgs->recursos_existentes[i];
        matriz_recursos[processoArgs->pid][i] = matriz_necessarios[processoArgs->pid][i];
    }

    printMatrizNecessarios();

    int flagRecursosPendentes = 1;
    while(1) {
        // PEDIDO DE RECURSOS
        
        int flagRequisicao = 0;
        int* pedidoRecursos = malloc((int)sizeof(int) * processoArgs->quantidade_recursos);
        for(int i = 0; i < processoArgs->quantidade_recursos; i++){
            pedidoRecursos[i] = matriz_recursos[processoArgs->pid][i];
        }
        flagRequisicao = requisicao_recursos(processoArgs->pid, pedidoRecursos);

        if(flagRequisicao == 1){
            printf("\nProcesso: consegui recurso!!\n");
        }
        else{
            printf("\nProcesso: não consegui recurso!!\n");
        }

        sleep(rand() % TIME);

        int flagLiberacao = libera_recursos(processoArgs->pid);
        // printMatrizNecessarios();
        if(flagLiberacao == 1){
            printf("Sou o processo %d e estou finalizando!", processoArgs->pid);
            break;
        }
        sleep(rand() % TIME);
    }
}