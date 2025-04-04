#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gravar_arq(FILE *arquivo, char nome[50], int n){
    
    arquivo = fopen("listanomes.txt", n > 0 ? "a" : "w");
    
    if (arquivo){
        printf("Arquivo criado/aberto\n");
    }
    else {
        printf("\n----Erro ao criar/abrir o arquivo----\n");
        return;
    }
    
    fprintf(arquivo, "%s\n", nome);
    
    printf("----------Escrita do arquivo encerrada----------\n");
    
    fclose(arquivo);
}

void ler_arq(FILE *arquivo){
    arquivo = fopen("listanomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[200]; // Buffer para armazenar cada linha
    while (fgets(linha, sizeof(linha), arquivo)){
        printf(" %s\n", linha); // Exibe cada linha
    }

    fclose(arquivo);
}


int main()
{
    int escolha;
    char nomes[50];
    FILE *arquivo;
    int contador = 0;
    
    while(escolha!=3){
        printf("\n=====MENU=====\n");
        printf("Esolha uma das opcoes abaixo:\n\n");
        printf("(1) Gravar nomes    (2) Ler nomes    (3) Sair\n\n");
        scanf("%d", &escolha);
        
        switch(escolha){
            case 1:
                printf("Digite o Nome a ser adicionado: ");
                scanf(" %s", nomes);
                gravar_arq(arquivo, nomes, contador);
                contador++;
                break;
                
            case 2:
                ler_arq(arquivo);
                break;
            
        }  
        
    }
    
    printf("Programa finalizado!\n\n");

    return 0;
}