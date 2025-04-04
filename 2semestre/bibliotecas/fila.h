#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#define MAX 100

//tp_item equivale a int
typedef int 
    tp_item; 

//struct que represensa a fila
typedef struct {
    tp_item item[MAX]; // vetor que representa a fila
    int ini, fim; //inicio e fim da fia
    
    /*int tam; --> muitos atores nao usam, pois cria uma redudancia que pode criar uma falha, a maioria
    prefere calcular na hora pois evita falha*/
} tp_fila;

//========funcoes======== 

void inicializaFila(tp_fila *f){
    f->ini = f->fim = MAX - 1;
    //f->tam=0;
}

int filaVazia(tp_fila *f){
    if(f->ini == f->fim) return 1;
    return 0;
}

int proximo(int pos){
    if(pos == MAX-1) return 0;
    return ++pos; /* precisa do ++ antes pois primeiro ira incrementar e depois retornar
    saco use o ++ depois, ele pode primeiro retornar e depois incrementar*/
}

int filaCheia(tp_fila *f){
    if(proximo(f->fim)==f->ini) return 1; // caso o proximo do fim seja o ini, entao a fila esta cheia
    return 0;
}

int insereFila(tp_fila *f, tp_item e){
    if(filaCheia(f)) return 0; // fila esta cheia, nao foi possivel adicionar elementos
    f->fim = proximo(f->fim);
    f->item[f->fim]=e;
    //f->tam++;
    return 1;
}

int removeFila(tp_fila *f, tp_item *e){
    if(filaVazia(f)) return 0;
    f->ini = proximo(f->ini);
    *e = f->item[f->ini];
    //f->tam--;
    return 1;
}

void imprimeFila(tp_fila f){
    tp_item e;

    while(!filaVazia(&f)){
        removeFila(&f, &e);
        printf("\n%d", e);
    }
}

int tamanhoFila(tp_fila *f){
    if (filaVazia(f)) return 0;
    if (f->ini < f->fim) return f->fim - f->ini;
    return MAX - 1 - f->ini + f->fim + 1;
}

#endif