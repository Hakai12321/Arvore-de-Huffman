#include <stdio.h>
#include <ctype.h>
#include "Lista.c"

int main(){
    lista *cabeca;
    tabela *tab;
    Arvore *arv1,*arv2,*nova,*raiz;
    criaLista(&cabeca,tab);

    while(cabeca->prox!= NULL){
        arv1 = removeLista(&cabeca);
        arv2 = removeLista(&cabeca);
        nova = criaArvore(-1,arv1->frequencia+arv2->frequencia);
        nova->dir = arv2;
        nova->esq = arv1;
        insereLista(&cabeca,nova);
    }
    raiz = cabeca->arvore;
}