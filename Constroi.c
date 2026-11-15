#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.c"

void codigoHuffman(Arvore *raiz,tabela  *cabeca,char *cod);
tabela* getCabecaById(tabela *tab,int id);

int main(){
    lista *cabeca=NULL;
    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;
    char cod[TF] = "";
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
    codigoHuffman(raiz,tab,cod);
}
void codigoHuffman(Arvore *raiz,tabela *tab,char *cod){
    if(raiz!= NULL){
        if(raiz->id<0)
        {
            //arrumar
            codigoHuffman(raiz->esq,tab,strcat(cod,"0"));
            codigoHuffman(raiz->dir,tab,strcat(cod,"1"));
        }
        else{
            tab = getCabecaById(tab,raiz->id);
            strcpy(tab->huffman,cod);
        }
    }

}

tabela* getCabecaById(tabela *tab,int id){
    while(tab->id!=id)
        tab = tab->prox;
    return tab;
}