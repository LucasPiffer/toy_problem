#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 150

struct LogsRede {
    char * linha;
    
    struct LogsRede *proximo;
};

void push(struct LogsRede* cabeca, char * linha);
char * lerLogsRede(void);
struct LogsRede* inserir_final(struct LogsRede* cabeca);
int verificar_lista_vazia(struct LogsRede* cabeca);
struct LogsRede* criar_lista(void);
struct LogsRede* remover_lista(struct LogsRede* cabeca, char *desc);
struct LogsRede* liberar_lista(struct LogsRede* cabeca);
void imprimir(struct LogsRede *aux);


 void push(struct LogsRede* cabeca, char * linha) {
     struct LogsRede* current = cabeca;

     while(current->proximo != NULL) {
        current = current->proximo;
    }

    struct LogsRede * novo_logsRede = (struct LogsRede *) malloc(sizeof(struct LogsRede));
    
    novo_logsRede->linha = linha;
    current->proximo = novo_logsRede;
    novo_logsRede->proximo = NULL;
}


void setup(struct LogsRede *cabeca) {
     int index;

    FILE * fp;
    char * linha = NULL;
    size_t len = 0;
    ssize_t read;

    char str[150];

    fp = fopen("./xyz", "r"); //./file

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while (fgets(str, 150, fp)) {
        if(strstr(str, "network")) {
            if(cabeca->linha == NULL) {
                cabeca->linha = strdup(str);
                cabeca->proximo = NULL;
            } else {
                push(cabeca, strdup(str));
            }
        }
    }

    fclose(fp);
}


int askUser() {
    int op;

    printf(" \n Escolha uma das opções abaixo: ");
    printf(" \n 1. Visualizar todos os eventos de rede ");
    printf(" \n 2. Visualizar todos os eventos de rede em ordem decrescente  ");
    printf(" \n 3. Inserir um novo evento de rede ");
    printf(" \n 4. Excluir um evento de rede ");
    printf(" \n 5. Excluir toda a estrutura de eventos de rede. ");
    printf(" \n 6. Informar arquivo de log ");

    printf(" \n Digite o número da opção desejada: ");
    scanf("%d", &op);

    return op;
}

int main(){
    struct LogsRede *cabeca = (struct LogsRede *)malloc(sizeof(struct LogsRede));
    char descricao[TAM];
    
    setup(cabeca);
    printf("\n\n");
    
    int op = askUser();

    switch (op)
    {
    case 1:
        printf(" \n Opção selecionada 1: ");
        printf(" \n Visualizar todos os eventos de rede:\n\n ");
        imprimir(cabeca);
        printf("\n\n");
        op = askUser();
        break;

    case 2:
        printf(" \n Opção selecionada 2: ");
        printf(" \n Visualizar todos os eventos de rede em ordem decrescente:\n\n ");
        printf("\n\n");
        op = askUser();

        break;
    case 3:
        printf(" \n Opção selecionada 3: ");
        printf(" \n Inserir um novo evento de rede:\n\n ");
        
        char userLine[TAM];
        strcpy(userLine, lerLogsRede());
        
        push(cabeca, userLine);
    
        imprimir(cabeca);

        break;
    case 4:
        printf(" \n Opção selecionada 4: ");
        printf(" \n Excluir um evento de rede:\n\n ");
        cabeca = remover_lista(cabeca, descricao);
        printf("\n\n");
        int op = askUser();
        break;
    case 5:
        printf(" \n Opção selecionada 5: ");
        printf(" \n Excluir toda a estrutura de eventos de rede:\n\n ");
        cabeca = liberar_lista(cabeca);
        break;
    default:
        printf(" \n Você digitou uma opção inválida!");
    }

    return 0;
}

struct LogsRede* criar_lista(void) {
    return NULL;
};

 char * lerLogsRede(void) {
    char mes[4];
    char dia[3];
    char horario[9];
    char nomeLog[22];
    char descricao[TAM];
    
    printf("\nMes: ");
    scanf("%s", mes);
    fpurge(stdin);
    printf("\nDia: ");
    scanf("%s", dia);
    fpurge(stdin);
    printf("\nHorario: ");
    scanf("%s", horario);
    fpurge(stdin);
    printf("\nLog: ");
    scanf("%s", nomeLog);
    fpurge(stdin);
    printf("\nDescrição: ");
    scanf("%s", descricao);
    fpurge(stdin);

    char *cat;

    asprintf(&cat, "%s - %s", mes, horario);

    return cat;
}

void imprimir(struct LogsRede *cabeca) {
    struct LogsRede *paux;
    for (paux = cabeca; paux != NULL; paux = paux->proximo)
        printf("Descricão: %-151s",paux->linha);

}
//Inserir no final da lista
struct LogsRede* inserir_final(struct LogsRede* cabeca) {
    struct LogsRede *paux, *anterior_paux = NULL;
    struct LogsRede* novo = (struct LogsRede*) malloc(sizeof(struct LogsRede));
   // lerLogsRede(novo);
    novo->proximo = NULL;
    if (verificar_lista_vazia(cabeca))
        cabeca = novo;
    else {
        paux = cabeca;
        while (paux != NULL) {
            anterior_paux = paux;
            paux = paux->proximo;
        }
        anterior_paux->proximo = novo;
    }
    return cabeca;
}

int verificar_lista_vazia(struct LogsRede* cabeca) {
    return (cabeca == NULL);
}

struct LogsRede* remover_lista(struct LogsRede* cabeca, char *desc) {
    struct LogsRede *paux = cabeca;
    struct LogsRede *anterior_paux = NULL;
    
    while (paux != NULL && strcmp(paux->linha, desc) != 0) {
        anterior_paux = paux;
        paux = paux->proximo;
    }
    if (paux == NULL)
        return NULL;
    if (anterior_paux == NULL)
        cabeca = paux->proximo;
    else
        anterior_paux->proximo = paux->proximo;
    free(paux);
    return cabeca;
}

struct LogsRede* liberar_lista(struct LogsRede* cabeca) {
    struct LogsRede *paux = cabeca, *aux = NULL;
    while (paux != NULL) {
        aux = paux->proximo;
        free(paux);
        paux = aux;
    }
    return NULL;
}