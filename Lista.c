#include<stdio.h>
#include<ctype.h>
#include<string.h>
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


// criacao de nos
lista* criaNo(Arvore *arvore);
Arvore* criaArvore(int id, int freq);

// manipulacao da lista ordenada
void insereLista(lista **cabeca, Arvore *arv);
void criaListaTabela(lista **cabeca, tabela *tab);
Arvore* removeLista(lista **cabeca);

// consturcao da arvore
void insereFinal(Arvore **raiz, int id);
void insereEsq(Arvore **raiz);
void insereDir(Arvore **raiz);
void criaArvoreArquivo(lista **cabeca, FILE *arq);

// leitura e busca
void lerPalavra(FILE *arq, char retorno[TF]);
char* buscaPalavra(char palavra[TF], tabela *tab);

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


void insereFinal(Arvore **raiz,int id);
{

}
void insereEsq(Arvore **raiz);
{
    
}
void insereDir(Arvore **raiz);
{
    
}

//Corrigir
void criaArvoreArquivo(lista **cabeca, FILE *arq){
    Registro reg;
    Arvore *raiz,*aux;
    int i;
    while(!feof(arq)){
        fread(&reg,sizeof(Registro),1,arq);
        aux = raiz;
        for(i=0;i<strlen(reg.huffman);i++){
            if(reg.huffman[i]==0)
                insereEsq(&aux);
            else    
                insereDir(&aux);
        }
        aux->id = reg.id;
    }
}

Arvore* removeLista(lista **cabeca){
    Arvore *auxArvore = (*cabeca)->arvore;
    lista *auxLista = *cabeca;
    *cabeca = (*cabeca)->prox;
    free(auxLista);
    return auxArvore;
}


void lerPalavra(FILE *arq,char retorno[TF]) {
    char palavra[TF];
    int c, i = 0;

    c = tolower(fgetc(arq));

    while (c != EOF &&  c != 32 && (c < 'a' || c > 'z'))
        c = fgetc(arq);
    
    if(c==32)
        strcpy(retorno," ");
    else{
        while (!feof(arq) && c >= 'a' && c <= 'z') 
        {
            palavra[i++] = c;
            c = tolower(fgetc(arq));
        }
        palavra[i] = '\0';
        if(palavra[0]!='\0')
            strcpy(retorno,palavra);
    }
}

char* buscaPalavra(char palavra[TF], tabela *tab){
    while (tab != NULL && strcmp(palavra, tab->palavra) != 0)
        tab = tab->prox;

    if (tab == NULL)
        return "";
    return tab->huffman;
}



