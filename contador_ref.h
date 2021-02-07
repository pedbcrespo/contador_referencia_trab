/*
    Aqui neste arquivo esta o escopo das principais funçoes que serao ultilizadas na main

    Ao instanciar a estrutura tabela, é necessario chamar a funçao inicializa. E ao final do programa, 
    a fim de manter a ideia de manipular bem o uso da memoria, é preciso usar a funcao destruir para liberar 
    toda a memoria usada na estrutura.

*/
typedef struct tabela*tab;

tab inicializa(int tam);
tab destruir(tab inst_tab);

int aloca(tab inst_tab, void*obj, int tam_obj);
int desaloca(tab inst_tab, int pos);
int aponta_outra_pos(tab inst_tab, int pos_atual, int pos_nova);

void imprimir_tab(tab inst_tab);