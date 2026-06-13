/*
    UNIVERSIDADE FEDERAL DO MARANHÃO - UFMA
    Laboratório de Programação
    Avaliacao 02
    Matheus Silva Cunha
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
                        printf("Sucesso: Nome gravado com sucesso no indice [%d]!\n", emptyIndex);
                    }
                }
                break;

            case 2:
                printf("\nBUSCAR REGISTRO\n");
                break;

            case 3:
                printf("\nEDITAR REGISTRO\n");
                break;

            case 4:
                printf("\nDELETAR REGISTRO\n");
                break;

            case 5:
                printf("\nLISTAR REGISTROS\n");
                int activeCount = 0;
                printf("%-10s | %s\n", "INDICE", "NOME");
                printf("------------------------------------\n");

                // Percorre matriz busca linhas nao vazias
                for (int i = 0; i < MAX_RECORDS; i++) {
                    // se 1 caractere diferente \0 linha ocupada
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