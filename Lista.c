#include<stdio.h>
#include<ctype.h>

#define TF 100 

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


//ta errado
void criaListaArquivo(lista **cabeca, FILE *arq){
    Registro reg;
    Arvore *arv;
    while(!feof(arq)){
        fread(&reg,sizeof(Registro),1,arq);
        arv = (Arvore*)malloc(sizeof(Arvore));
        arv->id = reg.id;
        arv->dir = NULL;
        arv->esq = NULL;
        insereLista(&(*cabeca),arv);
    }
}

Arvore* removeLista(lista **cabeca){
    Arvore *auxArvore = (*cabeca)->arvore;
    lista *auxLista = *cabeca;
    *cabeca = (*cabeca)->prox;
    free(auxLista);
    return auxArvore;
}

char* buscaPalavra(char palavra[TF],tabela *tab){

}
