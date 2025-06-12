#ifndef LISTASE_H
#define LISTASE_H
#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

//tp_no é um apelino da struct para que o compilador possa reconhecer o tipo da struct
typedef struct tp_no{
    tp_item info; //conteudo do no
    struct tp_no *prox; //aponta pro proximo no
}tp_listase;


//FUNCOES

//função que apenas retorna NULL
//para não da erro, a fução tera de ser o mesmo tipo do ponteiro inicial
tp_listase * inicializa_listase(){
    return NULL;
}

//verifica se a lista esta vazia
int listase_vazia(tp_listase *lista){
    if(lista==NULL) return 1; // retorna 1, a lista esta vazia
    return 0;// a lista nao esta vazia
}

//aloca a lista para um novo no
tp_listase * aloca_listase(){
    tp_listase *novo_no; // cria um novo no
    novo_no=(tp_listase*) malloc(sizeof(tp_listase)); //alocamento de memoria para o novo no
    return novo_no; //retorna o novo no
}

//insere o conteudo da lista em seu fim
int insere_listase_no_fim(tp_listase **lista, tp_item e){ //tem como parametro o ponteiro de ponteiro da lista e o elemento adicionado
    tp_listase *novo_no, *atu; //cria ponteiros auxiliares para novo no e lista atual
    novo_no=aloca_listase(); //aloca o novo no
    if(novo_no==NULL) return 0; //retorna falso se o novo no for nulo
    
    novo_no -> info = e; //novo no coleta o elemento
    novo_no -> prox = NULL; //novo no aponta para nulo
    //finaliza o encadeamento do no 
    if(listase_vazia(*lista)) *lista = novo_no; //se for o primeiro no, entra aqui
    else{
        atu = *lista; //diz a lista atual
        while(atu->prox!=NULL){
            atu=atu->prox; //aponta para o ultimo no
        }
        atu->prox=novo_no;
    }
    return 1;
}

int insere_listase_no_inicio(tp_listase **lista, tp_item e){
    tp_listase *novo_no;
    
    novo_no=aloca_listase();
    if(novo_no==NULL) return 0;
    
    novo_no->info=e;
    
    novo_no->prox= *lista;
    *lista=novo_no;
    
    return 1;
}

void imprime_listase(tp_listase *lista){
    tp_listase *atu;
    atu=lista;
    while (atu!=NULL){
        printf("%d\n", atu->info);
        atu=atu->prox;
    }
}

int remove_listase(tp_listase **lista, tp_item e){
    tp_listase * ant, *atu;
    atu=*lista;
    ant=NULL;
    while((atu!=NULL)&&(atu->info!=e)){
        ant=atu;
        atu = atu->prox;
    }
    if(atu==NULL) return 0;
    if(ant==NULL) *lista=atu->prox;
    else ant->prox=atu->prox;
    
    free(atu);
    atu=NULL;
    return 1;
}

tp_listase *busca_listase(tp_listase *lista, tp_item e){
    tp_listase *atu;
    atu=lista;
    while((atu!=NULL)&&(atu->info!=e)){
        atu=atu->prox;
    }
    if (atu==NULL) return NULL;
    return atu;
}

int tamanho_listase(tp_listase *lista){
    int cont = 0;
    tp_listase *atu;
    atu = lista;
    while(atu != NULL){
        cont++;
        atu = atu->prox;
    }
    return cont;
}

void destroi_listase(tp_listase **lista){
    tp_listase *atu;
    atu=*lista;
    while(atu!=NULL){
        *lista=atu->prox;
        free(atu);
        atu=*lista;
    }
    *lista=NULL;
    
}


#endif