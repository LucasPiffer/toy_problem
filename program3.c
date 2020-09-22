#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAM 150

struct LogsRede {
    char * linha;
    int number;

    struct LogsRede *proximo;
};

void push(struct LogsRede* cabeca, char * linha);
char * lerLogsRede(void);
struct LogsRede* inserir_final(struct LogsRede* cabeca);
int verificar_lista_vazia(struct LogsRede* cabeca);
struct LogsRede* criar_lista(void);
struct LogsRede* remover_lista(struct LogsRede* cabeca, int *number);
struct LogsRede* liberar_lista(struct LogsRede* cabeca);
void imprimir(struct LogsRede *aux);


 void push(struct LogsRede* cabeca, char * linha) {
     struct LogsRede* current = cabeca;
     int i = cabeca->number + 1;

     while(current->proximo != NULL) {
        current = current->proximo;
        i++;
    }

    struct LogsRede * novo_logsRede = (struct LogsRede *) malloc(sizeof(struct LogsRede));

    novo_logsRede->linha = linha;
    novo_logsRede->number = i;
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

    fp = fopen("./file", "r"); //./file
    //fp = fopen("./xyz", "r"); //./file

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while (fgets(str, 150, fp)) {
        if(strstr(str, "NetworkManager")) {
            if(cabeca->linha == NULL) {
                cabeca->linha = strdup(str);
                cabeca->number = 1;
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
    printf(" \n 2. Inserir um novo evento de rede ");
    printf(" \n 3. Excluir um evento de rede ");
    printf(" \n 4. Excluir toda a estrutura de eventos de rede. ");
    printf(" \n 5. Sair do programa ");

    printf(" \n Digite o número da opção desejada: ");
    scanf("%d", &op);

    return op;
}

int main(){
    struct LogsRede *cabeca = (struct LogsRede *)malloc(sizeof(struct LogsRede));
    char descricao[TAM];
    int number;

    setup(cabeca);
    printf("\n\n");

    int op = askUser();

    switch (op)
    {
    case 1:
        printf(" \n Opção selecionada 1: ");
        if(cabeca==NULL){
            printf("Lista está vazia!!!");
            op = askUser();
        }else{
            printf(" \n Visualizar todos os eventos de rede:\n\n ");
            imprimir(cabeca);
            printf("\n\n");
        op = askUser();
        
        }
    break;

    case 2:
        printf(" \n Opção selecionada 3: ");
        printf(" \n Inserir um novo evento de rede:\n\n ");

        char userLine[TAM];
        strcpy(userLine, lerLogsRede());

        printf("%s", userLine);

        push(cabeca, userLine);

        imprimir(cabeca);

        op = askUser();

        break;

    case 3:
        printf(" \n Opção selecionada 4: ");
        printf(" \n Excluir um evento de rede:\n\n ");
        imprimir(cabeca);

        printf("Qual nodo voce deseja excluir? ");
        scanf("%d", &number); 
        cabeca = remover_lista(cabeca, &number);
        printf("\n\n");
        op = askUser();
        break;

    case 4:
        printf(" \n Opção selecionada 5: ");
        printf(" \n Excluir toda a estrutura de eventos de rede:\n\n ");
        cabeca = liberar_lista(cabeca);
        printf("\nLista eliminada com sucesso!!!\n");
        op = askUser();
        break;
    case 5:
        exit(0);
    default:
        printf(" \n Você digitou uma opção inválida!");
    }

    return 0;
}

struct LogsRede* criar_lista(void) {
    return NULL;
};

 char * lerLogsRede(void) {
    
    char * descricao = malloc(3 * sizeof(char));

    printf("Digite o novo log no seguinte formato:\n");
    printf("mes -   dia - hora -     usuario -          log -                     descricao");
    printf("Sep     20  16:06:45 sisop-VirtualBox NetworkManager[610]: <info> manager: startup complete");
    scanf("%s", descricao);
    
    return descricao;
}

void imprimir(struct LogsRede *cabeca) {
    struct LogsRede *paux;
    for (paux = cabeca; paux != NULL; paux = paux->proximo)
        printf("%d: %s\n",paux->number, paux->linha);

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
        int i = cabeca->number + 1;
    }
    return cabeca;
}

int verificar_lista_vazia(struct LogsRede* cabeca) {
    return (cabeca == NULL);
}

struct LogsRede* remover_lista(struct LogsRede* cabeca, int *number) {
    struct LogsRede *paux = cabeca;
    struct LogsRede *anterior_paux = NULL;
    while (paux != NULL && paux->number, number){
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
    return 0;
    ;
} 