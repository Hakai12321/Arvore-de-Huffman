#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.c"

struct bits{
    unsigned char b7:1;
    unsigned char b6:1;
    unsigned char b5:1;
    unsigned char b4:1;
    unsigned char b3:1;
    unsigned char b2:1;
    unsigned char b1:1;
    unsigned char b0:1;

};typedef bits bits;
union byte{
    bits b;
    unsigned char num;
};typedef byte byte;

void codigoHuffman(Arvore *raiz,tabela  *cabeca,char *cod);
tabela* getCabecaById(tabela *tab,int id);
void exibeTabela(tabela *tab);
void grava(FILE *arq,tabela *tab);


int main(){
    lista *cabeca=NULL;
    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;
    char cod[TF] = "";


    //CRIA ARVORE
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

    //GRAVA TABELA
    FILE *arq = fopen("registro.dat","wb");
    grava(arq,tab);
    fclose(arq);


    //EXIBE TABELA E ARVORE
    codigoHuffman(raiz,tab,cod);
    exibeTabela(tab);

    
    //CODIFICA FRASE NOVA
    arq = fopen("frase.txt","r");
    FILE *arq2 = fopen("codigo.dat","wb");
    bits b;
    char palavra[TF],huff[TF];
    while(!feof(arq))
    {
        palavra[0] = '\0';
        lerPalavra(arq,palavra);
        if(palavra[0] != '\0')
        {
            strcpy(huff,buscaPalavra(palavra,tab));
            if(huff == "")
                printf("palavra nao existe!");
            else    
            {
                //errado
                b.b0 = huff[0];
                b.b1 = huff[1];
                b.b2 = huff[2];
                b.b3 = huff[3];
                b.b4 = huff[4];
                b.b5 = huff[5];
                b.b6 = huff[6];
                b.b7 = huff[7];
            }
        }
    }

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