#include<stdio.h>
#include<ctype.h>

#define TF 50 

struct Arvore{
    int id,frequencia;
    struct Arvore *esq;
    struct Arvore *dir;
};typedef struct Arvore arvore;

struct Tabela{
    int id,frequencia;
    char palavra[TF],huffman[TF];
    struct Tabela *prox;
};typedef struct Tabela tabela;

struct ListaOrdenada{
    arvore *no;
    struct ListaOrdenada *prox;
};typedef struct ListaOrdenada lista;

void insere (lista **cabeca,arvore *no){
    lista *nova = (lista*)malloc(sizeof(lista));
    nova->no = no;
    nova->prox = NULL;
    if(*cabeca == NULL){
        *cabeca = nova;
    }
    else{
        lista *l = *cabeca;
        if(no->frequencia < l->no->frequencia){
            nova->prox = *cabeca;
            *cabeca = nova;
        }
        while(l !=NULL && no->frequencia > l->no->frequencia)
        {
            l = l->prox;
        }
        nova->prox = l->prox;
        l->prox = nova;
    }
}