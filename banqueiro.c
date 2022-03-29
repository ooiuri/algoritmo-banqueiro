#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "sistema.h"
#include <pthread.h>

// ALGORITMO DO BANQUEIRO
// ## Integrantes:
//  - Iuri Everton Reis de Sousa (11811EMT013)
//  - Leonardo Guerreiro Nascibem Nava (11811EMT010)
//  - Pedro Machado Salles (11811EMT003)
//  - Viviane Malardo Ferreira (11821EMT015)

// numero de processos do programa
int num_processos;
// quantidade de recursos do vetor
int quantidade_recursos;

// vetor com a soma dos recursos existentes
int *recursos_existentes;
// vetor com a soma dos recursos alocados
int *recursos_alocados;
// vetor com os recursos disponíveis
int *recursos_disponiveis;


// matriz que contem os valores dos recursos alocados
int **matriz_alocados;
// matriz com os valores dos recursos necessários para cada processo
int **matriz_necessarios;
// matriz com os recursos originalmente necessarios para cada processo
int **matriz_recursos;

// sync mutex
pthread_mutex_t mutex;


/**
 * Função Principal
 * @ -n <num_processos>
 * @ -a <vetor_recursos>
 **/
int main (int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");
    printf("----$ Algoritmo do Banqueiro! $ ----\n");

    // inicia o mutex que sincroniza os processos
    if (pthread_mutex_init(&mutex, NULL) != 0){ 
        printf("\n mutex init failed\n");
        return 1;
    }

    // processa os argumentos de entrada e aloca os vetores de recursos
    quantidade_recursos = argc - 4;
    recursos_existentes = malloc(sizeof(int) * (quantidade_recursos));
    recursos_alocados = malloc(sizeof(int) * (quantidade_recursos));
    recursos_disponiveis = malloc(sizeof(int) * (quantidade_recursos));

    processaArgs(argc, &argv[0]);

    printf("\n\n\t\tAlocando Matrizes:\n");
    matriz_alocados = (int**)malloc(sizeof(int**) * num_processos);
    matriz_necessarios = (int**)malloc(sizeof(int**) * num_processos);
    matriz_recursos = (int**)malloc(sizeof(int**) * num_processos);
    
    for(int i = 0; i < num_processos; i++){
        matriz_alocados[i] = (int*)calloc(quantidade_recursos, sizeof(int) );
        matriz_necessarios[i] = (int*)calloc(quantidade_recursos, sizeof(int) );
        matriz_recursos[i] = (int*)calloc(quantidade_recursos, sizeof(int) );
    }

    printMatrizAlocados();
    printMatrizNecessarios();
    printMatrizRecursos();

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
    pthread_mutex_lock(&mutex);
    //muda a cor para verde
    printf("\033[0;32m");
    printf("\nRecebi uma requisição do processo %d, pedindo %d recursos: ", pid, quantidade_recursos);
    for(int i = 0; i < quantidade_recursos; i++){
        printf("%d ", recursos_disponiveis[i]);
    }
    printf("\n");

    // O banqueiro vai decidir quantos recursos irá liberar para o processo
    int *creditos = malloc(sizeof(int) * quantidade_recursos);
    for(int i = 0; i < quantidade_recursos; i++){
        if(recursos_disponiveis[i] == 0){
            creditos[i] = 0;
        }
        else {
            creditos[i] = rand() % (recursos_disponiveis[i]);
        }
        //limita o valor dos creditos com base nas necessidades do processo
        if(creditos[i] > matriz_necessarios[pid][i]){
            printf("\n\tLimitando o valor dos créditos %d  matriz necessarios: %d", creditos[i], matriz_necessarios[pid][i]);
            creditos[i] = matriz_necessarios[pid][i];
        }
    }

    printf("\n\n Creditos:");
    for(int i = 0; i < quantidade_recursos; i++){
        printf(" %d ", creditos[i]);
    }
    // decide se vai liberar os recursos ou se ele vai entrar em estado inseguro
    // o banqueiro vai liberar os recursos somente se a 
    // matriz_alocados + (recursos_disponiveis - creditos) > matriz_recursos_necessarios 
    // recursos existentes
    // 5 7 9
    // alocados     disponivel      creditos        recursos necessarios
    // 0 1 3        2 4 6           1 2 3           4 3 5  
    // nesse caso entra em estado inseguro
    printMatrizNecessarios();
    // flag que indica que o recurso sera liberado
    int flag_libera_recursos = 1;
    for(int i = 0; i < quantidade_recursos; i++){
        int atende_recursos = matriz_necessarios[pid][i];// - creditos[i];
        if(atende_recursos > recursos_disponiveis[i]){
            flag_libera_recursos = 0;
            break;
        }
    }
    if(flag_libera_recursos == 1){
        printf("\nVou liberar os pedido dos recursos!\n");
        for(int i = 0; i < quantidade_recursos; i++){
            matriz_alocados[pid][i] += creditos[i];
            matriz_necessarios[pid][i] -= creditos[i];
        }
        printMatrizAlocados();
        printf("\n$Banqueiro$: Liberei os recursos!\n");
    }
    else{
        printf("\033[0;33m");
        printf("\nNão vai ser possivel liberar o pedido dos recursos!\n");
    }
    printf("\033[0m");
    printf("\ncalcula recursos alocados\n");
    calculaRecursosAlocados();
    calculaRecursosDisponiveis();
    pthread_mutex_unlock(&mutex);
    return flag_libera_recursos;
}

int libera_recursos(int pid, int recursos[]) {
    pthread_mutex_lock(&mutex);
    printf("\033[0;33m");
    
    int flag_libera_recursos = 1;

    for(int i = 0; i < quantidade_recursos; i++){
        if(matriz_necessarios[pid][i] != 0){
            flag_libera_recursos = 0;
            break;
        }
    }
    

    printf("\n -------- O processo %d pediu para liberar os recursos!!", pid);

    
    for(int i = 0; i < quantidade_recursos; i++){
        matriz_alocados[pid][i] = 0;
    }
    calculaRecursosDisponiveis(0);
    printMatrizNecessarios();

    printf("\n\033[0m");
    pthread_mutex_unlock(&mutex);
    return flag_libera_recursos;
}

