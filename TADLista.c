#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define TF 100 
#define TF2 50000 

struct Arvore{
    int id,frequencia;
    struct Arvore *esq;
    struct Arvore *dir;
};typedef struct Arvore Arvore;

struct Tabela{
    int id,frequencia;
    char palavra[TF],huffman[TF];
    struct Tabela *prox;
};typedef struct Tabela tabela;
struct Registro{
    int id;
    char palavra[TF],huffman[TF];
};typedef struct Registro Registro;

struct ListaOrdenada{
    Arvore *arvore;
    struct ListaOrdenada *prox;
};typedef struct ListaOrdenada lista;


// criacao de nos
lista* criaNo(Arvore *arvore);
Arvore* criaArvore(int id, int freq);

// manipulacao da lista ordenada
void insereLista(lista **cabeca, Arvore *arv);
void criaListaTabela(lista **cabeca, tabela *tab);
Arvore* removeLista(lista **cabeca);

// consturcao da arvore
void criaArvoreArquivo(Arvore **raiz, FILE *arq);

// leitura e busca
void lerPalavra(FILE *arq, char retorno[TF]);
char* getHuffByPalavra(char palavra[TF], tabela *tab);

lista* criaNo(Arvore* arvore){
    lista *nova = (lista*)malloc(sizeof(lista));
    nova->arvore = arvore;
    nova->prox = NULL;
    return nova;
}

Arvore* criaArvore(int id, int freq){
    Arvore *nova = (Arvore*)malloc(sizeof(Arvore));
    nova->id = id;
    nova->frequencia = freq;
    nova->dir = NULL;
    nova->esq = NULL;
    return nova;
}

void insereLista(lista **cabeca, Arvore *arv){
    lista *nova = criaNo(arv);
    lista *l;

    if (*cabeca == NULL || arv->frequencia < (*cabeca)->arvore->frequencia) {
        nova->prox = *cabeca;
        *cabeca = nova;
    }
    else {
        l = *cabeca;
        while (l->prox != NULL && l->prox->arvore->frequencia <= arv->frequencia) {
            l = l->prox;
        }
        nova->prox = l->prox;
        l->prox = nova;
    }
}

void criaListaTabela(lista **cabeca, tabela *tab){
    while(tab != NULL){
        Arvore *arv;
        arv = criaArvore(tab->id,tab->frequencia);
        insereLista(&(*cabeca),arv);
        tab = tab->prox;
    }
}



//Corrigir
void criaArvoreArquivo(Arvore **raiz, FILE *arq){
    Registro reg;
    Arvore *aux;
    int i;
    do
    {
        fread(&reg,sizeof(Registro),1,arq);
        aux = *raiz;
        for (i = 0; reg.huffman[i] != '\0'; i++) {
            if(reg.huffman[i]=='0')
            {
                if(aux->esq == NULL)
                    aux->esq = criaArvore(-1,0);
                aux = aux->esq;
            }        
            else    
            {
                if(aux->dir == NULL)
                    aux->dir = criaArvore(-1,0);
                aux = aux->dir;
            }
                
        }
        aux->id = reg.id;
    }while(!feof(arq));
}

Arvore* removeLista(lista **cabeca){
    Arvore *auxArvore = (*cabeca)->arvore;
    lista *auxLista = *cabeca;
    *cabeca = (*cabeca)->prox;
    free(auxLista);
    return auxArvore;
}


char isLetra(int c){
    return (c >= 'a' && c <= 'z') || c >= 128;//minusculas ou acentuadas
}

void lerPalavra(FILE *arq, char retorno[TF]){
    int c, i = 0;

    retorno[0] = '\0';
    c = tolower(fgetc(arq));

    while (c != EOF && c!=32 && !isLetra(c))
        c = tolower(fgetc(arq));

    if (c != EOF && c==32) {
        strcpy(retorno, " ");
    }
    else {
        while (c != EOF && isLetra(c)) {
            retorno[i] = c;
            c = tolower(fgetc(arq));
            i++;
        }
        retorno[i] = '\0';
        if (c != EOF)       //se nao acabou volta 1 caracter
            fseek(arq, -1,1);  
    }
}

char* getHuffByPalavra(char palavra[TF], tabela *tab){
    while (tab != NULL && strcmp(palavra, tab->palavra) != 0)
        tab = tab->prox;

    if (tab == NULL)
        return "";
    return tab->huffman;
}



