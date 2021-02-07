#include<stdio.h>
#include<stdlib.h>
#include"contador_ref.h"

/*
    No arquivo contador_ref.h estabeleci apenas o escopo das funcoes e estruturas, mas nada foi de fato criado,
ate momento.
    Neste arquivo, é desenvolvido as funcoes estabelecidas. Importante ressaltar que neste tipo de arquivo pode
acontecer de ter funcoes nao definidas no arquivo .h.
*/

/*
    Aqui defino uma estrutura que vai armazenar dados da variavel, como o endereço de memoria, o tamanho da variavel
e a quantidade de ponteiros que estao referenciando-a.
    Note que ao final, defino como "*dado", isso quer dizer que toda vez que for instanciado uma variavel do tipo
dado (Ex.: dado var_info;), ela sera um ponteiro.
*/
typedef struct Dado{
    void*obj;
    unsigned int tam_obj;
    int qtd_ref;
}*dado;

/*
    Aqui defino com mais detalhes a composicao da estrutura tabela. Basicamente contera o tamanho dos vetores, e dois
ponteiros do tipo dado, que serao usados como o vetor de dados das variaveis. Tais dados ficarao invisiveis ao usuario, quando chamado no arquivo main.c
    O vet_auxiliar vai servir como uma via segura para tratar dos casos de lixo de memoria, enquanto que o vet_dado
sera a variavel manipulada pelo usuario, ou seja, se o usuario apagar alguma referencia, a mesma ainda existira no 
vet_auxiliar.
*/
struct tabela{
    int tamanho;
    dado vet_dado;
    dado vet_auxiliar;
};

/*
    A implementacao da funcao inicaliza consiste em fazer duas alocacoes dinamicas para as variaveis vet_dado e
vet_auxiliar. Ambos serao um vetor com a o mesmo tamanho, e serao ultilizados para armazenar as alocacoes que o 
usuario vai realizar.
    Alem do proprio endereco, outros dados sao necessarios para a manipulacao ideal, tais como o tamanho da variavel,
caso seja necessario busca-lo em algum momento, e a quantidade de vezes que aquela mesma area esta sendo referenciada.
*/
tab inicializa(int tam){
    tab novo = (struct tabela*)malloc(sizeof(struct tabela));
    novo->tamanho = tam;
    novo->vet_dado = (struct Dado*)malloc(tam*sizeof(struct Dado));
    novo->vet_auxiliar = (struct Dado*)malloc(tam*sizeof(struct Dado));

    for(int i=0; i<tam; i++){
        novo->vet_dado[i].obj = NULL;
        novo->vet_dado[i].tam_obj = 0;
        novo->vet_dado[i].qtd_ref = 0;

        novo->vet_auxiliar[i].obj = NULL;
        novo->vet_auxiliar[i].tam_obj = 0;
        novo->vet_auxiliar[i].qtd_ref = 0;
    }
    return novo;
}

/*
    Essa funcao é usada apos o termino da manipulacao da tabela, quando os dados ja nao sao mais necessarios.
Primeiro o vetor auxiliar e percorrido e cada objeto alocado e liberado. O mesmo processo nao e feito no vetor dados,
pois como ambos estao apontando para a mesma area de memoria, basta que um a libere. 
    Em seguida os vetores, como um todo sao liberados, e por fim, a tabela.
*/
tab destruir(tab inst_tab){
    for(int i=0; i<inst_tab->tamanho; i++){
        if(inst_tab->vet_auxiliar[i].obj != NULL){
            free(inst_tab->vet_auxiliar[i].obj);
            inst_tab->vet_auxiliar[i].obj = NULL;
            inst_tab->vet_auxiliar[i].qtd_ref = 0;
            inst_tab->vet_auxiliar[i].tam_obj = 0;
        }
    }
    free(inst_tab->vet_auxiliar);
    free(inst_tab->vet_dado);
    free(inst_tab);
    return NULL;
}

/*
    Aqui esta a funcao principal deste trabalho. Seu papel aqui esta resumido em liberar a area que nao esta sendo
ultilizada mas que teve sua referencia perdida, isso do ponto de vista do usuario, claro.
    Do ponto de vista do programa, a referencia da variavel vet_dados e que foi perdida, porem, na vet_auxiliar, a
referencia ainda persiste, entao, basta apenas acessar o endereco pelo vetor auxiliar e liberar a area.
*/
void coletor_lixo(tab inst_tab, int pos){
    free(inst_tab->vet_auxiliar[pos].obj);
    inst_tab->vet_auxiliar[pos].obj = NULL;
    inst_tab->vet_auxiliar[pos].tam_obj = 0;
    inst_tab->vet_auxiliar[pos].qtd_ref = 0;
}

/*  Essa funcao e apenas para ilustar o que esta acontecendo no decorrer do programa*/
void imprimir_tab(tab inst_tab){
    for(int i=0; i<inst_tab->tamanho; i++){
        if(inst_tab->vet_dado[i].obj == NULL)
            printf("%d| NULL\n", i);
        else{
            // printf("%d| %p :: %d\n", i, inst_tab->vet_dado[i].obj, inst_tab->vet_auxiliar[i].qtd_ref);
            printf("%d| %p\n", i, inst_tab->vet_dado[i].obj);

        }
    }
    printf("\n");
}

/* 
    Um detalhe, em alguns casos, dividi as funcoes em partes a fim de facilitar o entendimento.
A funcao altera_aux, procura pelo endereco obj no vetor auxiliar e apos encontra-lo, altera a quantidade de referencias
no mesmo. Caso a quantidade chegue a 0, significa que nao ha mais ninguem apontando para a area no vet_dado, entao a 
funcao coletor_lixo e chamada.

*/
int altera_aux(tab inst_tab, void*obj, int qtd){
    for(int i=0; i< inst_tab->tamanho; i++){
        if(inst_tab->vet_auxiliar[i].obj == obj){
            inst_tab->vet_auxiliar[i].qtd_ref += qtd;
            
            if(inst_tab->vet_auxiliar[i].qtd_ref == 0){
                coletor_lixo(inst_tab, i);
            }

            return inst_tab->vet_auxiliar[i].qtd_ref;
        }
    }
    return -1;
}

/*
    Nessa funcao, repito mais ou menos o procedimento feito na funcao aloca, porem o que muda e apenas o vetor.
A ideia e deixar a funcao o menos confusa o possivel deixando bem claro, qual vetor esta sendo manipulado.
    No geral, ambas funcionam da seguinte forma:
Uma posicao vazia e buscada e quando encontrada, o endereco e armazenado e os outros dados sao preenchidos.
    Nao necessariamente um endereco armazenado no vet_dado estara na mesma posicao do vet_auxiliar, por isso
a funcao foi separada em duas partes.
*/
int aloca_aux(tab inst_tab, int pos_dado){
    for(int i=0; i<inst_tab->tamanho; i++){
        if(inst_tab->vet_auxiliar[i].obj == NULL){
            inst_tab->vet_auxiliar[i].obj = inst_tab->vet_dado[pos_dado].obj;
            inst_tab->vet_auxiliar[i].tam_obj = inst_tab->vet_dado[pos_dado].tam_obj;
            inst_tab->vet_auxiliar[i].qtd_ref = inst_tab->vet_dado[pos_dado].qtd_ref;
            return 1;
        }
    }
    return 0;
}

int aloca(tab inst_tab, void*obj, int tam_obj){
    for(int i=0; i<inst_tab->tamanho; i++){
        if(inst_tab->vet_dado[i].obj == NULL){
            inst_tab->vet_dado[i].obj = obj;
            inst_tab->vet_dado[i].tam_obj = tam_obj;
            inst_tab->vet_dado[i].qtd_ref = 1;

            aloca_aux(inst_tab, i);

            return 1;
        }
    }
    return 0;
}
/*
    Nessa funcao, dado uma posicao, o ponteiro dela no vet_dado aponta para NULL. Os dados quanto a quantidade de referencias no vetor
auxiliar e atualizado usando a funcao altera_aux.
    Ja na funcao aponta_outra_pos, sao fornecidos duas posicoes: uma e a que vai armazenar o novo endereco e a segunda e o endereco que
sera armazenado. Apos as atribuicoes, e chamado a funcao altera_aux para atualizar os valores de cada area, sendo uma recebera mais uma
referencia enquanto outra sera reduzida.
*/
int desaloca(tab inst_tab, int pos){
    void*obj_dado = inst_tab->vet_dado[pos].obj;
    inst_tab->vet_dado[pos].obj = NULL;
    inst_tab->vet_dado[pos].qtd_ref -= 1;

    return altera_aux(inst_tab, obj_dado, -1);
}

int aponta_outra_pos(tab inst_tab, int pos_atual, int pos_nova){
    void*ptr = inst_tab->vet_dado[pos_atual].obj;
    inst_tab->vet_dado[pos_atual].obj = inst_tab->vet_auxiliar[pos_nova].obj;
    altera_aux(inst_tab, ptr, -1);
    return altera_aux(inst_tab, inst_tab->vet_auxiliar[pos_nova].obj, 1);
}