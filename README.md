# Algoritmo do Banqueiro

Projeto com o objetivo de implementar o Algoritmo do Banqueiro de Dijkstra em C

> O Algoritmo do banqueiro é um algoritmo de alocação de recursos com prevenção de impasses desenvolvido por Edsger Dijkstra que testa a segurança pela simulação da alocação do máximo pré-determinado possível de montantes de todos os recursos computacionais, e em seguida faz uma verificação de estados-seguros para testar a possibilidade de condições de impasse para todas as outras atividades pendentes, antes de decidir se a alocação deve prosseguir.

### 🔍 Pré-requisitos
Para rodar o algoritmo é necessário utilizar uma máquina que rode um ambiente Unix

### 🛠 Tecnologias
Para implementação do processo utilizamos:
- C
- git
- VsCode
### ⚙️ Como executar o projeto
#### Clonando o repositório
Para clonar o projeto do GitHub num diretório de sua preferência utilize o seguinte comando:
```bash
cd "diretório de sua preferencia"
git clone https://github.com/ooiuri/algoritmo-banqueiro.git
```

#### Interagindo com o programa
Para fazer a compilação do projeto:
```bash
make -f Makefile
```

4 - Para rodar o programa:
```bash
./banqueiro -n <num_processos> -a <vetor_recursos>
```
por exemplo:
```bash
./banqueiro -n 2 -a 3 4 5
```
Ao rodar o comando acima, o código é iniciado com `2` processos e um número máximo de `[3 4 5]` recursos existentes

### Como funciona
Foram criados 3 arquivos principais para conter as funções do programa:
#### banqueiro.c

```int requisicao_recursos(int pid, int recursos[]);```

Função responsável por receber os pedidos do processo, verificar a quantidade de créditos que irá liberar para o processo e impedir que o sistema entre em um estado inseguro.

    Retorno:
        0 se não alocar o recurso
        1 se os recursos forem alocados com sucesso

```int libera_recursos(int pid);```

Função responsável por liberar os recursos do processo, verifica se o processo já tem todos os seus recursos alocados com sucesso, caso sim, libera todos os recursos.

    Retorno:
        0 se não liberar
        1 se os recursos forem liberados com sucesso

#### sistema.c

Arquivo que contém todas as funções auxiliares do programa, responsável por criar os processos e verificar se tem algum processo ainda rodando

```void printSistema();```

```void processaArgs(int argc, char *argv[]);```

```void rotinaSistema();```

```void calculaRecursosDisponiveis();```

```void calculaRecursosAlocados();```

```void printMatrizAlocados();```

```void printMatrizNecessarios();```

```void printMatrizRecursos();```

#### processos.c

Arquivo que contém a função de referência para criação das threads do processo.
    
    - Executa requisicao_recursos(int pid);
    - Dorme por um tempo aleatório;
    - Executa libera_recursos(int pid);
    - Dorme por um tempo aleatório;

```void *processo(void *argumento);```

### Lógica do algoritmo

Utilizamos das seguintes estruturas principais para manter o controle da informação. 

```
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
```

## Integrantes:
 - Iuri Everton Reis de Sousa (11811EMT013)
 - Leonardo Guerreiro Nascibem Nava (11811EMT010)
 - Pedro Machado Salles (11811EMT003)
 - Viviane Malardo Ferreira (11821EMT015)

## BigPicture do projeto

![Banqueiro 1](/assets/banqueiro1.jpeg)
![Banqueiro 2](/assets/banqueiro2.jpeg)
![Banqueiro 3](/assets/banqueiro3.jpeg)
![Banqueiro 4](/assets/banqueiro4.jpeg)

