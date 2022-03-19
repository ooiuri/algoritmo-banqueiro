#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int num_processos;
int *vetor_recursos;

/**
 * Função Principal
 * @ -n <num_processos>
 * @ -a <vetor_recursos>
 **/ 
int main (int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");
    printf("Função do Banqueiro!\n");
    int quantidade_recursos = argc - 4;
    vetor_recursos = malloc(sizeof(int8_t) * (quantidade_recursos));
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
                vetor_recursos[j - 1] = atoi(argv[i+j]); 
            }
        }
    }

    printf("\n\nNúmero de processos: %d\n", num_processos);
    printf("\n\nVetor de recursos: \n");
    for(int i = 0; i < quantidade_recursos; i++){
        printf(" %d ", vetor_recursos[i]);
    }
    return 0;
}

