#include<stdio.h>
#include<stdlib.h>
#include"contRef.h"

void tabela(int**vet){
    printf("visao maquina\t\tvisao usuario\t\tquant. referencia\n");
    for(int i=0; i<max; i++){
        printf("%p\t\t%p\t\t%d\n", aux[i].ptr, vet[i], aux[i].contador);
    }
}

int main(){
    int *vetor[max], continua=1, bt;
    inicializa(vetor);

    while(continua){

        system("cls");
        tabela(vetor);
        printf("\n1)aloca\n2)aponta null\n3)realoca\n4)sair\n");
        scanf("%d",&bt);
        if(bt == 1){
            for(int i=0; i<max; i++){
                if(vetor[i] == null){
                    vetor[i]=aloca();
                    break;
                }
            }

        }
        else if(bt == 2){
            int ax;
            system("cls");
            printf("posicao: ");
            scanf("%d",&ax);
            vetor[ax]=realoca(vetor[ax], null);

        }
        else if(bt == 3){
            int ax1, ax2;
            system("cls");
            printf("posicao atual e nova: ");
            scanf("%d %d",&ax1, &ax2);
            vetor[ax1]=realoca(vetor[ax1], vetor[ax2]);
        }
        else{
            continua = 0;
        }
        system("PAUSE");




    }

}
