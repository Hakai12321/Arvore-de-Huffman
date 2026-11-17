#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.c"

int main(){
    FILE *arq = fopen("registro.dat","rb");
    lista *cabeca=NULL;
    tabela *tab=NULL;
    Arvore *arv1,*arv2,*nova,*raiz;
    char cod[TF] = "";
    criaArvoreArquivo(&cabeca,arq);



    fclose(arq);
}