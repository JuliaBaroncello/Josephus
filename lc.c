#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no{
    char soldado[50];
    int id;
    struct no *prox, *ant;
}No;

int inserir_soldado(No **L, char soldado[]){
    No *novo;
    novo = (No *)malloc(sizeof(No));
    if (novo == NULL){
        return 0;
    }
    strcpy(novo->soldado, soldado);
    novo->prox = NULL;
    novo->ant = NULL;
    novo->id = 0;

    if (*L == NULL){
        *L = novo;
        novo->id = 1;
        novo->prox = novo;
        novo->ant = novo;
    } else{
        novo->prox = *L;
        novo->ant = (*L)->ant;
        novo->ant->prox = novo;
        (*L)->ant = novo;
        novo->id = novo->ant->id+1;
    }
    return 1;
}

void mostrar_soldados(No **L){
    if (*L == NULL){
        printf("Lista vazia.\n");
    } else{
        No *p;
        for (p = *L; p->prox != *L; p = p->prox){
            printf("%i: %s\n", p->id, p->soldado);
        }
        printf("%i: %s\n", p->id, p->soldado);
    }
}

No * sortear_soldado(No **L){
    srand(time(NULL));
    int sorteio = rand()%((*L)->ant->id) + 1;
    printf("Numero do soldado: %i\n", sorteio);
    No *p;
    if (sorteio == (*L)->ant->id){
        //printf("%s foi o soldado selecionado.\n", (*L)->ant->soldado);
        return (*L)->ant;
    }
    for (p = *L; p->prox != *L; p = p->prox){
        if (sorteio == p->id){
            //printf("%s foi o soldado selecionado.\n", p->soldado);
            return p;
        }
    }
}

int remover_soldado(No **selecionado){
    No *p;
    p = *selecionado;
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    printf("%s foi o soldado eliminado\n", p->soldado);
    free(p);
    return 1;
}

No * selecionar_soldado(No **inicial, int n){
    if (*inicial == NULL){
        return NULL;
    }
    if (*inicial == (*inicial)->prox){
        return *inicial;
    }
    No *aux, *proximo;
    aux = *inicial;
    while(aux != aux->prox){
        for (int i = 1; i < n; i++){
            aux = aux->prox;
        }
        proximo = aux->prox;
        remover_soldado(&aux);
        aux = proximo;
    }
    return aux;
}

int sortear_n(No **L){
    srand(time(NULL));
    return (rand()%100) + 1;
}

int menu(){
    int opc;
    //system("clear");
    printf("[0] - Sair\n");
    printf("[1] - Inserir soldado\n");
    printf("[2] - Mostrar soldados\n");
    printf("[3] - Sortear o soldado que iniciará a contagem\n");
    printf("[4] - Apresentar o soldado selecionado (apresente também o número n sorteado e os soldados eliminados)\n\n");

    printf("Escolha uma opção: ");
    scanf("%i", &opc);
    return opc;
}

int main(){
    No *L = NULL;
    No *sorteado = NULL;
    No *selecionado = NULL;
    char nome[50];
    int opc;
    int tam = 0;
    int n;

    while(opc = menu()){
        switch (opc){
            case 1:
                printf("Insira seu nome: ");
                scanf("%s", nome);
                printf("\n");
                if (inserir_soldado(&L, nome)){
                    printf("Soldado %s foi inserido.\n", nome);
                    tam++;
                } else{
                    printf("Soldado não inserido.\n");
                }
                break;

            case 2:
                mostrar_soldados(&L);
                break;
            
            case 3:
                sorteado = sortear_soldado(&L);
                printf("Soldado sorteado: %s\n", sorteado->soldado);
                break;

            case 4:
                n = sortear_n(&L);
                printf("Numero sorteado: %i\n", n);
                selecionado = selecionar_soldado(&sorteado, n);
                printf("Soldado selecionado: id: %i, nome: %s", selecionado->id, selecionado->soldado);
                break;

            default:
                printf("Opção Inválida.\n");
        }
        getchar();
        getchar();
    }
}