banqueiro: banqueiro.c banqueiro.h sistema.c processos.c
	gcc -o banqueiro banqueiro.c sistema.c processos.c -pthread 
