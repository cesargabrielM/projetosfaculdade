#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define LETRAS 26
 
typedef struct tp_no {
    char letra;
    struct tp_no* filhos[LETRAS];
    int eh_folha;
} tp_no;
 
tp_no* cria_no(char letra) {
    tp_no* no = (tp_no*) malloc (sizeof(tp_no));
    int i;
    if (no != NULL) {
    	no->eh_folha = 0;
    	no->letra = letra;
	    for (i=0; i<LETRAS; i++)
    	    no->filhos[i] = NULL;
	}
    return no;
}

tp_no* insere_no_trie(tp_no* raiz, char* palavra) {
    tp_no* no = raiz;
 	int tam = strlen(palavra);
    int i;
    for (i=0; i < tam; i++) {
    	//palavras estão em minúsculo
        int ind = (int) palavra[i] - 'a';
        if (no->filhos[ind] == NULL) {
            no->filhos[ind] = cria_no(palavra[i]);
        }
        no = no->filhos[ind];
    }
    no->eh_folha = 1;
    return raiz;
}
 
int busca_no_trie(tp_no* raiz, char* palavra){
    tp_no* no = raiz;
 	int tam = strlen(palavra); 
 	int i;
    for(i=0; i < tam; i++)
    {
        int pos = palavra[i] - 'a';
        if (no->filhos[pos] == NULL)
            return 0;
        no = no->filhos[pos];
    }
    if (no != NULL && no->eh_folha == 1)
        return 1;
    return 0;
}
 
void imprime_arv_trie(tp_no* raiz) {
    if (!raiz)
        return;
    tp_no* no = raiz;
    printf("%c -> ", no->letra);
    int i;
	for (i=0; i<LETRAS; i++) {
        imprime_arv_trie(no->filhos[i]); 
    }
}

int tem_filhos(tp_no* no) {
    for (int i = 0; i < LETRAS; i++) {
        if (no->filhos[i] != NULL)
            return 1;
    }
    return 0;
}

int remove_no_trie(tp_no** raiz, char* palavra) {
    if (*raiz == NULL)
        return 0;

    // Caso base: fim da palavra
    if (*palavra == '\0') {
        if ((*raiz)->eh_folha) {
            (*raiz)->eh_folha = 0;

            if (!tem_filhos(*raiz)) {
                free(*raiz);
                *raiz = NULL;
                return 1;
            }
            return 0; // Palavra removida, mas o nó ainda tem filhos
        }
        return 0; // Palavra não encontrada como folha
    }
    
int ind = *palavra - 'a';
    if (remove_no_trie(&((*raiz)->filhos[ind]), palavra + 1)) {
        if (!(*raiz)->eh_folha && !tem_filhos(*raiz)) {
            free(*raiz);
            *raiz = NULL;
            return 1;
        }
    }

    return 0;
}