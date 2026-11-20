#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "TADLista.c"

int main(){
    FILE *arq = fopen("tabela.dat","rb");
    

    byte u;
    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;

    //cria arvore
    raiz = criaArvore(-1,0);
    criaArvoreArquivo(&raiz,arq);

    FILE *arqCod = fopen("codigo.dat","rb");

    //le codigo
    while(!feof(arqCod))
    {
        fread()
    }


    fclose(arq);
}