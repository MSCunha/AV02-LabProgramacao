/*
    UNIVERSIDADE FEDERAL DO MARANHÃO - UFMA
    Laboratório de Programação
    Avaliacao 02
    Matheus Silva Cunha - 2021052782
*/

#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 50
#define MAX_LETTERS 30

int main() {
    char db[MAX_RECORDS][MAX_LETTERS];
    
    //inicializa zerada
    for (int i = 0; i < MAX_RECORDS; i++) {
        db[i][0] = '\0';
    }

    int opt;
    char nameAux[MAX_LETTERS];
    int found, emptyIndex, isDuplicate;
    char newName[MAX_LETTERS];

    //Menu
    do {
        printf("1. Incluir Nome\n2. Buscar Nome\n3. Modificar Nome\n4. Apagar Nome\n5. Listar Todos os Nomes\n0. Sair\n");
        printf("Selecione uma opcao: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                printf("\nNOVO REGISTRO\n");
                printf("Digite o nome: ");
                scanf(" %[^\n]", nameAux); //le ate \n

                //verifica se existe
                isDuplicate = 0;
                for (int i = 0; i < MAX_RECORDS; i++) {
                    //compara se != vazia
                    if (db[i][0] != '\0' && strcmp(db[i], nameAux) == 0) {
                        isDuplicate = 1;
                        break;
                    }
                }

                if (isDuplicate == 1) {
                    printf("Erro: O nome %s ja existe!\n", nameAux);
                } else {
                    emptyIndex = -1;
                    for (int i = 0; i < MAX_RECORDS; i++) {
                        if (db[i][0] == '\0') {
                            emptyIndex = i;
                            break;
                        }
                    }

                    //evita overflow
                    if (emptyIndex == -1) {
                        printf("Erro: O banco de dados esta cheio! Nao e possivel incluir.\n");
                    } else {
                        strcpy(db[emptyIndex], nameAux);
                        printf("Sucesso: [%d] %s\n", emptyIndex, nameAux);
                    }
                }
                break;

            case 2:
                printf("\nBUSCAR REGISTRO\n");
                printf("Digite o nome para pesquisar: ");
                scanf(" %[^\n]", nameAux);

                found = 0;
                //busca linear
                for (int i = 0; i < MAX_RECORDS; i++) {
                    if (db[i][0] != '\0' && strcmp(db[i], nameAux) == 0) {
                        printf("Sucesso: Nome encontrado no indice [%d]\n", i);
                        found = 1;
                        break;
                    }
                }

                if (found == 0) {
                    printf("Nome nao encontrado.\n");
                }
                break;

            case 3:
                printf("\nEDITAR REGISTRO\n");
                printf("Digite o nome que deseja modificar: ");
                scanf(" %[^\n]", nameAux);

                int targetIndex = -1;
                //localizar indice nome antigo
                for (int i = 0; i < MAX_RECORDS; i++) {
                    if (db[i][0] != '\0' && strcmp(db[i], nameAux) == 0) {
                        targetIndex = i;
                        break;
                    }
                }

                if (targetIndex == -1) {
                    printf("Erro: Nome nao encontrado para modificacao.\n");
                } else {
                    printf("Nome localizado no indice [%d]. Digite o novo nome: ", targetIndex);
                    scanf(" %[^\n]", newName);

                    //valida se novo nome existe
                    isDuplicate = 0;
                    for (int i = 0; i < MAX_RECORDS; i++) {
                        //ignora proprio indice e compara
                        if (i != targetIndex && db[i][0] != '\0' && strcmp(db[i], newName) == 0) {
                            isDuplicate = 1;
                            break;
                        }
                    }

                    if (isDuplicate == 1) {
                        printf("Erro: O novo nome '%s' ja existe no sistema! Modificacao cancelada.\n", newName);
                    } else {
                        //substitui apos validacao
                        strcpy(db[targetIndex], newName);
                        printf("Sucesso: Registro atualizado com sucesso!\n");
                    }
                }
                break;

            case 4:
                printf("\nDELETAR REGISTRO\n");
                printf("Digite o nome que deseja apagar: ");
                scanf(" %[^\n]", nameAux);

                found = 0;
                //busca linear
                for (int i = 0; i < MAX_RECORDS; i++) {
                    if (db[i][0] != '\0' && strcmp(db[i], nameAux) == 0) {
                        //redefine primeiro char nulo
                        db[i][0] = '\0';
                        printf("Sucesso: Registro removido do indice [%d].\n", i);
                        found = 1;
                        break;
                    }
                }

                if (found == 0) {
                    printf("Erro: Nome nao encontrado.\n");
                }
                break;

            case 5:
                printf("\nLISTAR REGISTROS\n");
                int activeCount = 0;
                printf("  %2s | %s\n", "INDICE", "NOME");
                printf("------------------------------------\n");

                //percorre matriz busca linhas nao vazias
                for (int i = 0; i < MAX_RECORDS; i++) {
                    //se 1 caractere diferente \0 linha ocupada
                    if (db[i][0] != '\0') {
                        printf("[%-8d] | %s\n", i, db[i]);
                        activeCount++;
                    }
                }

                if (activeCount == 0) {
                    printf("O banco de dados esta completamente vazio.\n");
                } else {
                    printf("------------------------------------\n");
                    printf("Total de registros ativos: %d\n", activeCount);
                }
                break;

            case 0:
		printf("\nENCERRANDO...\n");
                break;

            default:
                printf("\nInvalid option! Try again.\n");
        }

    } while (opt != 0);

    return 0;
}