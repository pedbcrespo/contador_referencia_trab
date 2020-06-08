#ifndef CONTREF_H_INCLUDED
#define CONTREF_H_INCLUDED
#define null NULL
#define max 20
/**O meio pelo qual obterei o controle das alocaçoes é a partir de um vetor
de um estrutura, que possui como parametros: um ponteiro e um contador*/
typedef struct Invisivel{
    void*ptr;
    int contador;
}inv;

inv aux[max];
int coletor_lixo(int pos);
int inicializa(int**vet);
int busca(int*p);
int *aloca();
int *realoca(int*atual, int*novo);


#endif // CONTREF_H_INCLUDED
