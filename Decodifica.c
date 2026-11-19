#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "TADLista.c"

int main(){
    FILE *arq = fopen("registro.dat","rb");
    FILE *arqCod = fopen("codigo.dat","rb");

    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;
    raiz = criaArvore(-1,0);
    criaArvoreArquivo(&raiz,arq);



    fclose(arq);
}