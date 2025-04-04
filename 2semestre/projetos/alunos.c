#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

// struct para armazenar os dados dos alunos
typedef struct {
    int matricula;
    char nome[50];
    float nota;
} Aluno;

void incluirAluno(Aluno alunos[], int *numAlunos);
void editarAluno(Aluno alunos[], int numAlunos);
void consultarAluno(Aluno alunos[], int numAlunos);
void deletarAluno(Aluno alunos[], int *numAlunos);
void imprimirAlunos(Aluno alunos[], int numAlunos);
void salvarDados(Aluno alunos[], int numAlunos);
void carregarDados(Aluno alunos[], int *numAlunos);
void printmenu();

int main() {
    Aluno alunos[MAX];
    int numAlunos = 0;
    int opcao;

    carregarDados(alunos, &numAlunos);

    do {
        
        printmenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirAluno(alunos, &numAlunos);
                break;
            case 2:
                editarAluno(alunos, numAlunos);
                break;
            case 3:
                consultarAluno(alunos, numAlunos);
                break;
            case 4:
                deletarAluno(alunos, &numAlunos);
                break;
            case 5:
                imprimirAlunos(alunos, numAlunos);
                break;
            case 6:
                salvarDados(alunos, numAlunos);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
    } while (opcao != 6);

    return 0;
}

//imprime o menu
void printmenu(){
    printf("\n---------------------------------------------\n");
    printf("| C A D A S T R O   D E   A L U N O S |\n");
    printf("-----------------------------------------------\n");
    printf("1. Incluir\n2. Editar\n3. Consultar\n4. Deletar\n5. Imprimir\n6. Sair\n");
    printf("-----------------------------------------------\n");
}

//adiciona aluno
void incluirAluno(Aluno alunos[], int *numAlunos) {
    if (*numAlunos >= 5) {
        printf("Limite de alunos atingido!\n");
        return;
    }

    printf("Matricula: ");
    scanf("%d", &alunos[*numAlunos].matricula);
    printf("Nome: ");
    scanf(" %[^\n]", alunos[*numAlunos].nome);
    printf("Nota: ");
    scanf("%f", &alunos[*numAlunos].nota);

    (*numAlunos)++;
    printf("Aluno cadastrado com sucesso!\n");
}

//edita os alunos
void editarAluno(Aluno alunos[], int numAlunos) {
    int matricula;
    printf("Digite a matricula do aluno que deseja editar: ");
    scanf("%d", &matricula);

    for (int i = 0; i < numAlunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("Novo nome: ");
            scanf(" %[^\n]", alunos[i].nome);
            printf("Nova nota: ");
            scanf("%f", &alunos[i].nota);
            printf("Aluno editado com sucesso!\n");
            return;
        }
    }

    printf("Aluno nao encontrado!\n");
}

//pesquisa os alunos
void consultarAluno(Aluno alunos[], int numAlunos) {
    int matricula;
    printf("Digite a matricula do aluno que deseja consultar: ");
    scanf("%d", &matricula);

    for (int i = 0; i < numAlunos; i++) {
        if (alunos[i].matricula == matricula) {
            printf("Matricula: %d\n", alunos[i].matricula);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Nota: %.2f\n", alunos[i].nota);
            return;
        }
    }

    printf("Aluno nao encontrado!\n");
}

//deleta alunos existentes
void deletarAluno(Aluno alunos[], int *numAlunos) {
    int matricula;
    printf("Digite a matricula do aluno que deseja deletar: ");
    scanf("%d", &matricula);

    for (int i = 0; i < *numAlunos; i++) {
        if (alunos[i].matricula == matricula) {
            for (int j = i; j < *numAlunos - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*numAlunos)--;
            printf("Aluno deletado com sucesso!\n");
            return;
        }
    }

    printf("Aluno nao encontrado!\n");
}

//mostra os alunos cadastrados
void imprimirAlunos(Aluno alunos[], int numAlunos) {
    if (numAlunos == 0) {
        printf("Nenhum aluno cadastrado!\n");
        return;
    }

    for (int i = 0; i < numAlunos; i++) {
        printf("Matricula: %d, Nome: %s, Nota: %.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].nota);
    }
}

//salva dados e um arquivo FILE
void salvarDados(Aluno alunos[], int numAlunos) {
    FILE *arquivo = fopen("alunos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados!\n");
        return;
    }

    for (int i = 0; i < numAlunos; i++) {
        fprintf(arquivo, "%d %s %.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].nota);
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

//pega o FILE com arquivos para carregar caso exista
void carregarDados(Aluno alunos[], int *numAlunos) {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Criando novo arquivo.\n");
        return;
    }

    while (fscanf(arquivo, "%d %[^\n] %f", &alunos[*numAlunos].matricula, alunos[*numAlunos].nome, &alunos[*numAlunos].nota) != EOF) {
        (*numAlunos)++;
        if (*numAlunos >= 5) break; // Limite de 5 alunos
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}
