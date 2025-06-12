#ifndef ARVOREBB_H
#define ARVOREBB_H
#include <stdlib.h>
#include <stdio.h>

typedef int tp_item;

typedef struct tp_no{
    struct tp_no *esq;
    tp_item info;
    struct tp_no *dir;
} tp_no;

typedef tp_no * tp_arvore;

tp_arvore inicializa_arvore(){
    return NULL;
}

int arvore_vazia(tp_arvore raiz){
    if(raiz == NULL) return 1;
    else return 0;
}

tp_no * aloca_no(){
    tp_no *no;
    no=(tp_no*)malloc(sizeof(tp_no));
    return no;
}

int insere_no(tp_arvore *raiz, tp_item e){
    tp_no *pai=NULL, *novo, *p=*raiz;
    novo=aloca_no();
    if(!novo) return 0;
    novo->info=e;
    novo->esq=NULL;
    novo->dir=NULL;
    while(p!=NULL){
        pai=p;
        if(e < p->info) p=p->esq;
        else p=p->dir;
    }
    if(pai!=NULL){
        if(e < pai->info) pai->esq=novo;
        else pai->dir=novo;
    }
    else *raiz = novo;
    
    return 1;
}

void pre_ordem(tp_no *p){
    
    if(p!=NULL){
        printf("\n%d\n", p->info);
        pre_ordem(p->esq);
        pre_ordem(p->dir);
    }
}

void em_ordem(tp_no *p){
    
    if(p!=NULL){
        em_ordem(p->esq);
        printf("\n%d\n", p->info);
        em_ordem(p->dir);
    }
}

void pos_ordem(tp_no *p){
    
    if(p!=NULL){
        pos_ordem(p->esq);
        pos_ordem(p->dir);
        printf("\n%d\n", p->info);
    }
}

int qtde_niveis_arvore(tp_arvore raiz){
    if(raiz == NULL) return 0;
    
    int alt_esq = qtde_niveis_arvore(raiz->esq);
    int alt_dir = qtde_niveis_arvore(raiz->dir);
    
    if(alt_esq > alt_dir){
        return alt_esq + 1;
    } else{
        return alt_dir + 1;
    }
}

int qtde_nos(tp_arvore raiz){
    if(raiz == NULL) return 0;
    
    int total_esq = qtde_nos(raiz->esq);
    int total_dir = qtde_nos(raiz->dir);
    
    return (total_esq + total_dir + 1);
}

tp_arvore busca_no_rec(tp_arvore p, tp_item e){
    if(p != NULL){
        if(e < p->info){
            return busca_no_rec(p->esq, e);
        } else if(e > p->info){
            return busca_no_rec(p->dir, e);
        } else{
            return p;
        }
    } else return NULL;
}

int remove_no (tp_arvore *raiz, tp_item e ) {
	tp_no  *p=*raiz, *ant=NULL, *sub, *pai, *filho;
	while (p!=NULL && p->info!=e) {
		ant=p;
		if (e < p->info) p = p->esq;
		else p = p->dir;
	}
	if (p==NULL) return  0; /* não encontrou */
	/* nó tem no máximo um filho */
	if (p->esq==NULL) sub=p->dir;
	else if (p->dir==NULL) sub=p->esq;

		else {
		/* nó tem dois filhos */
			pai=p; sub=p->dir; filho=sub->esq;
			while (filho!=NULL) {
				pai=sub;  sub=filho;  filho=sub->esq;
			}
/* neste ponto, sub é o sucessor em ordem de p */
			if (pai!=p) {
				/*p não é o pai de sub e sub==pai->esq */
				pai->esq=sub->dir;
				/* remove o nó apontado por sub de sua atual 
				 posição e substitui pelo filho direito de rp */
				/* sub ocupa o lugar de p */
				sub->dir=p->dir;
			}
		/*define filho esq de sub para que sub ocupe o lugar de p */
			sub->esq=p->esq;
		}
		/* insere sub na posição ocupada por p */
		if (ant==NULL) *raiz=sub; /* p era raiz */
			
		else
			if (p==ant->esq) ant->esq=sub;

			else ant->dir=sub;
				
		free(p);
	return 1;
}

void destroi_no(tp_no *no){
    if(no==NULL) return;
    destroi_no(no->esq);
    destroi_no(no->dir);
    
    free(no);
    no = NULL;
    return;
}

void destroi_arvore(tp_arvore *raiz){
   if(*raiz==NULL) return;
   destroi_no(*raiz);
  // free(*raiz);
   *raiz=NULL;
}

#endif