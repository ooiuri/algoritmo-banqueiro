#ifndef BANQUEIRO_H_INCLUDED   /* Include guard */
#define BANQUEIRO_H_INCLUDED

void printHello();
int requisicao_recursos(int pid, int recursos[]);
int libera_recursos(int pid);

#endif // BANQUEIRO_H_INCLUDED