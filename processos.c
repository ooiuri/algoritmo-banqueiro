#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "banqueiro.h"
#include "sistema.h"

extern int num_processos;
extern int quantidade_recursos;
extern int *recursos_existentes;
extern int *recursos_alocados;
extern int *recursos_disponiveis;

extern int **matriz_alocados;
extern int **matriz_necessarios;

int *vetor_processos;
extern struct processoStruct {
    int pid;
    int quantidade_recursos;
    int *recursos_existentes;
};

void *processo(void *argumento) {
    printf("\n\t\tOi eu sou um processo!\n");
    // Verifica os argumentos do processo
    struct processoStruct *processoArgs = argumento;
    printf("Sou o processo %d que tem: %d recursos",processoArgs->pid, processoArgs->quantidade_recursos);
    for (int i = 0; i < processoArgs->quantidade_recursos; i++) {
        printf(" %d", processoArgs->recursos_existentes[i]);
    }
    printf("\n\t\t\t\tAlocando a quantidade de recursos");
    //printa a matriz de necessidades
    //define a quantidade de recursos necessários
    for(int i = 0; i < processoArgs->quantidade_recursos; i++){
        matriz_necessarios[processoArgs->pid][i] = rand() % processoArgs->recursos_existentes[i];
    }

    printf("\n\n\t\tMatriz de necessidades:\n");
    for(int i = 0; i < num_processos; i++){
        for(int j = 0; j < quantidade_recursos; j++){
            printf("%d ", matriz_necessarios[i][j]);
        }
        printf("\n");
    }
    int flagRecursosPendentes = 1;
    while(flagRecursosPendentes) {
        // PEDIDO DE RECURSOS
        int *pedidoRecursos;
        pedidoRecursos = (int*)malloc(sizeof(int) * processoArgs->quantidade_recursos);
        //define a quantidade de recursos pedido pelo processo
        calculaRecursosDisponiveis(1);
        for(int i = 0; i < processoArgs->quantidade_recursos; i++){
            if (matriz_necessarios[processoArgs->pid][i] == 0){
                pedidoRecursos[i] = 0;
            }
            else {
                pedidoRecursos[i] = rand() % (matriz_necessarios[processoArgs->pid][i]);
            }
        }
        printf("\n\t\t\t\tPedido de recursos: ");
        for(int i = 0; i < processoArgs->quantidade_recursos; i++){
            printf("%d ", pedidoRecursos[i]);
        }
        printf("\nProcesso: vou pedir recurso!!\n");
        int flagRequisicao = 0;
        flagRequisicao = requisicao_recursos(processoArgs->pid, pedidoRecursos);
        printf("\nProcesso: consegui recurso!!\n");

        if (flagRequisicao == 1){
            printf("\n\t\t\t\tflagRequisicao: %d\n", flagRequisicao);
            for(int i = 0; i < quantidade_recursos; i++){
                matriz_necessarios[processoArgs->pid][i] -= pedidoRecursos[i]; ;
                printf(" %d ", pedidoRecursos[i]);
            }
            printf("\n");
        }
        sleep(rand() % 5);

        // LIBERACAO DE RECURSOS
        int *liberaRecursos;
        liberaRecursos = (int*)malloc(sizeof(int) * processoArgs->quantidade_recursos);
        //define a quantidade de recursos liberados pelo processo
        calculaRecursosAlocados(1);
        
        printf("liberando recursos1");
        for(int i = 0; i < processoArgs->quantidade_recursos; i++){
            if(matriz_alocados[processoArgs->pid][i] == 0){
                liberaRecursos[i] = 0;
            }
            else {
                liberaRecursos[i] = rand() % (matriz_alocados[processoArgs->pid][i]);
            }
        }
        printf("\n\t\t\t\tLiberação de recursos: ");
        for(int i = 0; i < processoArgs->quantidade_recursos; i++){
            printf("%d ", liberaRecursos[i]);
        }

        printf("\n\tprocessos: vou pedir os recursos");
        int flagLiberacao = libera_recursos(processoArgs->pid, liberaRecursos);
        printf("\n\tprocessos: liberado recursos");
        printf("\n\n\t\tMatriz de necessidades:\n");
        for(int i = 0; i < num_processos; i++){
            for(int j = 0; j < quantidade_recursos; j++){
                printf("%d ", matriz_necessarios[i][j]);
            }
            printf("\n");
        }
        // Verifica se ainda existen recursos pendentes
        flagRecursosPendentes = 0;
        for(int i = 0; i < quantidade_recursos; i++){
            if(matriz_necessarios[processoArgs->pid][i] != 0){
                flagRecursosPendentes = 1;
                break;
            }
        }

    }
}