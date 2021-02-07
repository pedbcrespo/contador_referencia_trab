#include<stdio.h>
#include<stdlib.h>
#include"contador_ref.h"

/*
    Para compilar: 
    abra a pasta pelo terminal (cmd caso esteja no windows) e digite:
        gcc main.c contador_ref.c -o main.exe
    para executar:
        main.exe

*/

int menu(char*opcoes){
    int op;
    printf(opcoes);
    scanf("%d", &op);
    return op;
}

int main(){
    int op =-1, cont = 1;
    tab tabela_principal = inicializa(20);

    while(cont != 0){
        system("cls");
        imprimir_tab(tabela_principal);
        op = menu("1)aloca 2)desaloca 3)reaponta 0)sair\n");
    
        if(op == 1){
            aloca(tabela_principal, (int*)malloc(sizeof(int)), sizeof(int));
        }
        else if(op == 2){
            int pos;
            printf("posicao: ");
            scanf("%d", &pos);
            desaloca(tabela_principal, pos);
        }
        else if(op == 3){
            int pos1, pos2;
            printf("posicao que recebera novo ender: ");
            scanf("%d", &pos1);
            printf("posicao apontada: ");
            scanf("%d", &pos2);

            aponta_outra_pos(tabela_principal, pos1, pos2);

        }
        else{
            break;
        }
    
    }

    destruir(tabela_principal);
}