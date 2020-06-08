#include<stdio.h>
#include<stdlib.h>
#include"contRef.h"
/** inicializa tatno o vetor de ponteiros quanto o vetor auxiliar
atribuino 0 ao contador e null para os ponteiros de ambos os vetores*/
int inicializa(int**vet){
    for(int i=0; i<max; i++){
        aux[i].ptr=null;
        aux[i].contador=0;

        vet[i] = null;
    }
    return 1;
}

/** Dado um determinado endereço como parametro,
o programa percorre o vetor auxiliar buscando a posiçao na qual possui o mesmo endereço
passado. E com isso retorna a posiçao no vetor auxilia que o possui*/
int busca(int*p){
    for(int i=0; i<max; i++){
        if(aux[i].ptr == p)
            return i;
    }
    return -1;
}

/**Aqui esta o ponto do trabalho, quando é encontrado uma area considerada como lixo, chama-se entao
essa funçao na qual, a partir do vetor auxiliar, acessa a area lixo e a libera usando o comando free*/
int coletor_lixo(int pos){
    free(aux[pos].ptr);
    aux[pos].ptr = null;
    aux[pos].contador = 0;
    return 1;
}

/**O processo de alocação aqui passa por alguns parametros a mais. No caso, antes de retornar, o endereço
é referenciado tambem pelo ponteiro do vetor auxiliar, assim como o contador do mesmo marca 1 mostrando que, fora
o vetor auxiliar, ha mais uma referencia ao endereço alocado*/
int *aloca(){
    int i = busca(null);
    aux[i].ptr = (int*)malloc(sizeof(int));
    aux[i].contador += 1;
    return aux[i].ptr;
}

/**Essa função serve tanto para apontar para o NULL quanto para outra area ja alocada.
Independente do endereço atribuido ao 'novo', o vetor auxiliar, que possui o mesmo endereço
do parametro 'atual', tem seu contador reduzido, e caso esse contado chegue a 0, indica que
nao ha mais referencias por parte do vetor ao endereço alocado. Nesse caso é chamado a função
'coletor_lixo'*/
int *realoca(int*atual, int*novo){
    aux[busca(atual)].contador--;

    if(aux[busca(atual)].contador == 0)
        coletor_lixo(busca(atual));

    if(novo != null)
        aux[busca(novo)].contador ++;


    return novo;
}


