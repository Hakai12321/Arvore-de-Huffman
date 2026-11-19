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
void grava(FILE *arq,tabela *tab);


tabela* criaNoTabela(int id, char palavra[TF]);
void insereTabela(tabela **tab, char palavra[TF]);
void criaTabela(tabela **tab, char nomeArquivo[TF]);


void imprimirEspacos(int n);
int contarDigitos(int n);
void exibeTabela(tabela *tab);
void exibeArvore(Arvore *raiz,int nivel,char bit);

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


tabela* criaNoTabela(int id, char palavra[TF]){
    tabela *nova = (tabela*)malloc(sizeof(tabela));
    nova->id = id;
    nova->frequencia = 1;
    strcpy(nova->palavra,palavra);
    nova->huffman[0] = '\0';
    nova->prox = NULL;
    return nova;
}

void insereTabela(tabela **tab, char palavra[TF]){
    tabela *aux = *tab, *ant = NULL;
    int id = 0;

    while(aux != NULL && strcmp(aux->palavra,palavra) != 0){
        ant = aux;
        aux = aux->prox;
        id++;
    }

    if(aux != NULL)
        aux->frequencia++;
    else{
        aux = criaNoTabela(id,palavra);
        if(ant == NULL)
            *tab = aux;
        else
            ant->prox = aux;
    }
}

void criaTabela(tabela **tab, char nomeArquivo[TF]){
    FILE *arq = fopen(nomeArquivo,"r");
    char palavra[TF];

    if(arq == NULL)
        printf("arquivo %s nao encontrado!\n",nomeArquivo);
    else{
        while(!feof(arq)){
            palavra[0] = '\0';
            lerPalavra(arq,palavra);
            if(palavra[0] != '\0')
                insereTabela(&(*tab),palavra);
        }
        fclose(arq);
    }
}

void imprimirEspacos(int n)
{
    int i;
    for(i=0;i<n;i++)
        printf(" ");
}

int contarDigitos(int n)
{
    int qtde = 1;
    while(n >= 10)
    {
        n = n / 10;
        qtde++;
    }
    return qtde;
}

void exibeTabela(tabela *tab)
{
    int qtde = 0;

    printf("\n=========== TABELA DE HUFFMAN ===========\n");
    printf("ID    PALAVRA          FREQ  CODIGO\n");
    while(tab != NULL)
    {
        printf("%d",tab->id);
        imprimirEspacos(6 - contarDigitos(tab->id));

        if(strcmp(tab->palavra," ") == 0)
        {
            printf("[espaco]");
            imprimirEspacos(17 - 8);
        }
        else
        {
            printf("%s",tab->palavra);
            imprimirEspacos(17 - (int)strlen(tab->palavra));
        }

        printf("%d",tab->frequencia);
        imprimirEspacos(6 - contarDigitos(tab->frequencia));
        printf("%s\n",tab->huffman);

        qtde++;
        tab = tab->prox;
    }
    printf("Total de simbolos: %d\n",qtde);
}

void exibeArvore(Arvore *raiz,int nivel,char bit)
{
    int i;
    if(raiz != NULL)
    {
        exibeArvore(raiz->dir,nivel+1,'1');

        for(i=0;i<nivel;i++)
            printf("      ");
        if(nivel > 0)
            printf("%c-- ",bit);

        if(raiz->id < 0)
            printf("(%d)\n",raiz->frequencia);
        else
            printf("[%d]:%d\n",raiz->id,raiz->frequencia);

        exibeArvore(raiz->esq,nivel+1,'0');
    }
}