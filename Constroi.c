#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.c"

void codigoHuffman(Arvore *raiz,tabela  *cabeca,char *cod);
tabela* getCabecaById(tabela *tab,int id);
void exibeTabela(tabela *tab);
void grava(FILE *arq,tabela *tab);


int main(){
    lista *cabeca=NULL;
    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;
    char cod[TF] = "";
    criaListaTabela(&cabeca,tab);

    while(cabeca->prox!= NULL){
        arv1 = removeLista(&cabeca);
        arv2 = removeLista(&cabeca);
        nova = criaArvore(-1,arv1->frequencia+arv2->frequencia);
        nova->dir = arv2;
        nova->esq = arv1;
        insereLista(&cabeca,nova);
    }
    raiz = cabeca->arvore;

    FILE *arq = fopen("registro.dat","wb");
    grava(arq,tab);
    fclose(arq);
    codigoHuffman(raiz,tab,cod);
    exibeTabela(tab);
}
void codigoHuffman(Arvore *raiz,tabela *tab,char *cod){
    if(raiz!= NULL){
        if(raiz->id<0)
        {
            //arrumar
            codigoHuffman(raiz->esq,tab,strcat(cod,"0"));
            cod[strlen(cod)-1] = '\0';

            codigoHuffman(raiz->dir,tab,strcat(cod,"1"));
            cod[strlen(cod) - 1] = '\0';
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

void grava(FILE *arq,tabela *tab){
    Registro reg;
    while(tab!=NULL){
        strcpy(reg.huffman,tab->huffman);
        reg.id = tab->id;
        strcpy(reg.palavra,tab->palavra);
        fwrite(&reg,sizeof(Registro),1,arq);
        tab = tab->prox;
    }
}

void exibeTabela(tabela *tab)
{
   
}

void exibeArvore(tabela *tab)
{

}