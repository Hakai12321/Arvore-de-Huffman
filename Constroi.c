#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "TADLista.c"



void codigoHuffman(Arvore *raiz,tabela  *cabeca,char *cod);
tabela* getCabecaById(tabela *tab,int id);
void codificaFrase(char *frase,FILE *txt,tabela *tab);
void grava(FILE *arq,tabela *tab);
void setBit(byte *u, int pos, int valor);


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

    //CRIA TABELA
    criaTabela(&tab,"FraseBase.txt");

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
    codigoHuffman(raiz,tab,cod);

    //GRAVA TABELA
    FILE *arq = fopen("tabela.dat","wb");
    grava(arq,tab);
    fclose(arq);
    

    //EXIBE TABELA E ARVORE
    int nivel = 0;
    char bit=0;
    
    exibeTabela(tab);
    exibeArvore(raiz,nivel,bit);

    //LE FRASE PARA CODIFICAR
    FILE *txt = fopen("FraseParaCodificar.txt","r");
    if(txt == NULL)
        printf("Arquivo nao existe!");
    char frase[TF2];
    codificaFrase(frase,txt,tab);
    fclose(txt);


    //CODIFICA FRASE
    int total, pos = 0, k,preenche;
    byte u;
    total = strlen(frase);
    arq = fopen("codigo.dat","wb");
    if(!strcmp(getHuffByPalavra(" ",tab),"1"))
        preenche = 255;
    else    
        preenche = 0;
    u.num =preenche;//inicialmente preenchido com 1s ou 0s dependendo do espaco
    for (k = 0; k < total; k++) {
        if(frase[k] == '1')
            setBit(&u, pos, 1);
        if(frase[k] == '0')
            setBit(&u, pos, 0);
        pos++;
        if (pos == 8) {
            fwrite(&u.num, 1, 1, arq);
            u.num = preenche;
            pos = 0;
        }
    }
    if (pos > 0)
        fwrite(&u.num, 1, 1, arq);
    fclose(arq);
    return 0;

}

void codificaFrase(char *frase,FILE *txt,tabela *tab){
    char palavra[TF];
    frase[0] = '\0';
    while (!feof(txt)) 
    {
        palavra[0] = '\0';
        lerPalavra(txt, palavra);
            if (palavra[0] != '\0')
            {
                strcat(frase, getHuffByPalavra(palavra, tab));
                strcat(frase, getHuffByPalavra(" ", tab));
            }               
    }
}

void codigoHuffman(Arvore *raiz,tabela *tab,char *cod){
    if(raiz!= NULL){
        if(raiz->id<0)
        {
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
            {
                insereTabela(&(*tab),palavra);
                insereTabela(&(*tab)," ");
            }
                
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

void setBit(byte *u, int pos, int valor){
    switch(pos){
        case 0: u->b.b7 = valor; 
            break;
        case 1: u->b.b6 = valor; 
            break;
        case 2: u->b.b5 = valor;
             break;
        case 3: u->b.b4 = valor; 
            break;
        case 4: u->b.b3 = valor;
             break;
        case 5: u->b.b2 = valor; 
            break;
        case 6: u->b.b1 = valor;
             break;
        case 7: u->b.b0 = valor; 
            break;
    }
}