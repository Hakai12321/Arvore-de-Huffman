#define TF 50 

#define TF 50
struct Arvore{
    int id;
    struct Arvore *esq;
    struct Arvore *dir;
};typedef struct Arvore arvore;

struct Tabela{
    int id,frequencia;
    char palavra[TF];
    //huffman
};typedef struct Tabela tabela;


struct ListaOrdenada{
    arvore info;
    struct ListaOrdenada *prox;
};typedef struct ListaOrdenada lista;

void insere (lista **no,)