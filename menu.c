#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 41

struct LogsRede {
    char mes[4];
    int dia;
    char horario[9];
    char usuario[15];
    char nomeLog[22];
    char descricao[TAM];
    struct LogsRede *proximo;
};

void lerLogsRede(struct LogsRede *aux);
struct LogsRede* inserir_final(struct LogsRede* cabeca);
int verificar_lista_vazia(struct LogsRede* cabeca);
struct LogsRede* criar_lista(void);
struct LogsRede* remover_lista(struct LogsRede* cabeca, char *desc);
struct LogsRede* liberar_lista(struct LogsRede* cabeca);
void imprimir(struct LogsRede *aux);


void push(node_t * head, char * line) {
    node_t * current = head;

    while(current->next != NULL) {
        current = current->next;
    }

    node_t * new_node = (node_t *) malloc(sizeof(node_t));
    new_node->data = line;
    current->next = new_node;
    new_node->next = NULL;
}

void setup(struct LogsRed *cabeca) {
    // int index;

    // node_t * head = (node_t *)malloc(sizeof(node_t));
    
    // FILE * fp;
    // char * line = NULL;
    // size_t len = 0;
    // ssize_t read;

    // char str[150];

    // fp = fopen("./file", "r");
    
    // if (fp == NULL)
    //     exit(EXIT_FAILURE);

    // while (fgets(str, 150, fp)) {
    //     if(strstr(str, "network")) {
    //         if(head->data == NULL) {
    //             head->data = strdup(str);
    //             head->next = NULL;
    //         } else {
    //             push(cabeca, strdup(str));
    //         }    
    //     }   
    // }
    
    // fclose(fp);
    
    // print_list(head);

    // exit(EXIT_SUCCESS);
}

int main(){
    struct LogsRede *cabeca = (struct LogsRede *)malloc(sizeof(struct LogsRede));
    char descricao[TAM];
    
    int op;

    setup(cabeca);

    printf(" \n Escolha uma das opções abaixo: ");
    printf(" \n 1. Visualizar todos os eventos de rede ");
    printf(" \n 2. Visualizar todos os eventos de rede em ordem decrescente  ");
    printf(" \n 3. Inserir um novo evento de rede ");
    printf(" \n 4. Excluir um evento de rede ");
    printf(" \n 5. Excluir toda a estrutura de eventos de rede. ");
    printf(" \n 6. Informar arquivo de log ");

    printf(" \n Digite o número da opção desejada: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        printf(" \n Opção selecionada 1: ");
        printf(" \n Visualizar todos os eventos de rede:\n\n ");
        imprimir(cabeca);
        break;

    case 2:
        printf(" \n Opção selecionada 2: ");
        printf(" \n Visualizar todos os eventos de rede em ordem decrescente:\n\n ");

        break;

    case 3:
        printf(" \n Opção selecionada 3: ");
        printf(" \n Inserir um novo evento de rede:\n\n ");
        
        
        lerLogsRede(cabeca);

        break;
    case 4:
        printf(" \n Opção selecionada 4: ");
        printf(" \n Excluir um evento de rede:\n\n ");
        cabeca = remover_lista(cabeca, descricao);
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

void lerLogsRede(struct LogsRede *aux) {
    printf("\nMes: ");
    scanf("%s", aux->mes);
    fflush(stdin);
    printf("\nDia: ");
    scanf("%d", &aux->dia);
    fpurge(stdin);

    printf("%d", aux->dia);
    printf("%s", aux->mes);
    // printf("\nHorario: ");
    // scanf("%[^\n]", aux->horario);
    // fflush(stdin);
    // printf("\nUsuario: ");
    // scanf("%[^\n]", aux->usuario);
    // fflush(stdin);
    // printf("\nLog: ");
    // scanf("%[^\n]", aux->nomeLog);
    // fflush(stdin);
    // printf("\nDescricao: ");
    // scanf("%[^\n]", aux->descricao);
    // fflush(stdin);
    // inserir_final(aux);
}

void imprimir(struct LogsRede *cabeca) {
    struct LogsRede *paux;
    for (paux = cabeca; paux != NULL; paux = paux->proximo)
        printf("Mes: %-5s\tDia: %d\tHora: %-11s\tUsuario: %15s\tLog: %-23%\Descricao: %42s\t\n",paux->mes, paux->dia, paux->horario, paux->usuario,paux->nomeLog,paux->descricao);

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
    while (paux != NULL && strcmp(paux->descricao, desc) != 0) {
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
