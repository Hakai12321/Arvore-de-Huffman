#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "TADLista.c"

int main(){
    FILE *arqTab = fopen("tabela.dat","rb");
    

    int buscaId(char *cod,int *pos,Arvore *raiz);
    char buscaPalavraNoArquivo(int id,FILE *arq,char palavra[TF]);
    char getBit(byte u, int pos);

    byte u;
    Arvore *raiz;
    char byte[9],cod[TF2];
    strcpy(cod,"");
    

    //cria arvore
    raiz = criaArvore(-1,0);
    criaArvoreArquivo(&raiz,arqTab);

    FILE *arqCod = fopen("codigo.dat","rb");

    //le codigo
    while(!feof(arqCod))
    {
        fread(&u.b, sizeof(u.b), 1, arqCod);
        byte[0]=getBit(u,0);
        byte[1]=getBit(u,1);
        byte[2]=getBit(u,2);
        byte[3]=getBit(u,3);
        byte[4]=getBit(u,4);
        byte[5]=getBit(u,5);
        byte[6]=getBit(u,6);
        byte[7]=getBit(u,7);
        byte[8]='\0';
        strcat(cod,byte);
    }
    fclose(arqCod);

    //decodifica
    char palavra[TF],fraseFinal[TF2];
    strcpy(fraseFinal,"");
    int pos=0,id,total;
    total = strlen(cod);
    while(pos<total){
        id = buscaId(cod,&pos,raiz);
        if(buscaPalavraNoArquivo(id,arqTab,palavra))
            strcat(fraseFinal,palavra); 
        else
        {
            printf("Erro!!!");
            pos = TF2;
        }
    }
    printf("%s",fraseFinal);
    fclose(arqTab);
    return 0;   
}


int buscaId(char *cod,int *pos,Arvore *raiz){
    while(cod[*pos]!='\0' && raiz!= NULL && raiz->id == -1)
    {
        if(cod[(*pos)++] == '0')
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    if(raiz!= NULL && raiz->id >=0)
        return raiz->id;
    printf("Erro Na Arvore ou Codigo!!!");
    return -1;
}
char buscaPalavraNoArquivo(int id,FILE *arq,char palavra[TF]){
    Registro reg;
    fseek(arq,0,0);

    do{
        fread(&reg,sizeof(Registro),1,arq);
    }while(!feof(arq) && reg.id!= id);
    if(reg.id == id)
    {
        strcpy(palavra,reg.palavra);
        return 1;
    }
    return 0;
}

char getBit(byte u, int pos){
    char c;
    switch(pos){
        case 0: 
            if(u.b.b0 == 0)
                 c='0';
            else 
                c='1';
            break;

        case 1: 
            if(u.b.b1 == 0)
                 c='0';
            else 
                c='1'; 
            break;

        case 2:
            if(u.b.b2 == 0)
                 c='0';
            else 
                c='1';
             break;

        case 3: 
            if(u.b.b3 == 0)
                 c='0';
            else 
                c='1';
            break;

        case 4:
            if(u.b.b4 == 0)
                 c='0';
            else 
                c='1';
             break;

        case 5: 
            if(u.b.b5 == 0)
                 c='0';
            else 
                c='1';
            break;

        case 6:
            if(u.b.b6 == 0)
                 c='0';
            else 
                c='1';
             break;

        case 7: 
            if(u.b.b7 == 0)
                 c='0';
            else 
                c='1';
            break;
    }
    return c;
}