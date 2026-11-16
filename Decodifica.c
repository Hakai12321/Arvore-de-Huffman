#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.c"

int main(){
    FILE *arq = fopen("registro.dat","rb");
    lista *cabeca=NULL;
    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;
    char cod[TF] = "";
    criaListaArquivo(&cabeca,arq);

    while(cabeca->prox!= NULL){
        arv1 = removeLista(&cabeca);
        arv2 = removeLista(&cabeca);
        nova = criaArvore(-1,arv1->frequencia+arv2->frequencia);
        nova->dir = arv2;
        nova->esq = arv1;
        insereLista(&cabeca,nova);
    }
    raiz = cabeca->arvore;



    fclose(arq);
}