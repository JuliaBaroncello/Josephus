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
    //*novo->soldado = soldado;
    novo->prox = NULL;
    novo->ant = NULL;
    novo->id = 0;

    if (*L == NULL){
        *L = novo;
        novo->id = 1;
        novo->prox = novo;
        novo->ant = novo;
    } else{
        //novo->id = 1;
        //(*L)->id = novo->id+1;
        novo->prox = *L;
        novo->ant = (*L)->ant;
        novo->ant->prox = novo;
        //(*L)->ant = novo;
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

int sortear_soldado(No **L){
    srand(time(NULL));
    int sorteio = rand()%((*L)->ant->id) + 1;
    printf("%i\n", sorteio);
    No *p;
    if (sorteio == (*L)->ant->id){
        printf("%s foi o soldado selecionado.\n", (*L)->ant->soldado);
        return (*L)->ant->id;
    }
    for (p = *L; p->prox != *L; p = p->prox){
        if (sorteio == p->id){
            printf("%s foi o soldado selecionado.\n", p->soldado);
            return p->id;
        }
    }
}

int sortear_n(No **L){
    srand(time(NULL));
    return (rand()%11) + 1;
    //printf("%i\n", rand()%101);
}

No * remover_soldado(No **L, int pos){
    if (*L == NULL){
        return NULL;
    }
    if (*L == (*L)->prox){
        return *L;
    }
    No *p, *q;
    int cont = 1;
    for (p = *L; p->prox != *L; p = p->prox){
        if (cont == pos){
            q = p->ant;
            q->prox = p->prox;
            

        }
        cont++;
    }
}

No * remover_soldado(No **L, int n){
    if (*L == NULL){
        return NULL;
    }
    No *p;
    int pos = 1;
    No *aux;
    int sold = sortear_soldado(&L);
    for (aux = *L; aux->prox != *L; aux = aux->prox){
        if (aux->id == sold){
            *L = aux;
        }
    }
    for (p = aux; p->prox != aux; p = p->prox){
        if (pos == n){

        }
        pos++;
    }
    p = (*L)->ant;
    p->ant->prox = *L;
    (*L)->ant = p->ant;
    free(p);
    return 1;
    /*
    No *p;
    p = *L;
    while(p->prox != *L){
        if (n == p->id){
            No *q;
            q = p;

        }
        p = p->prox;
    }
    */
}

int menu(){
    int opc;
    system("clear");
    printf("[0] - Sair\n");
    printf("[1] - Inserir soldado\n");
    printf("[2] - Mostrar soldados\n");
    printf("[3] - Sortear o soldado que iniciará a contagem\n");
    printf("[4] - Apresentar o soldado selecionado (apresente também o número n sorteado e os soldados eliminados)\n\n");

    printf("Escolha uma opção: ");
    scanf("%i", &opc);
    return opc;
}

/*
[ 3 ] - Sortear o soldado que iniciará a contagem
[ 4 ] - Apresentar o soldado selecionado (apresente também o número n sorteado e os
soldados eliminados)
*/

int main(){
    No *L = NULL;
    char nome[50];
    int opc;
    int tam = 0;

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
                sortear_soldado(&L);
                break;

            case 4:
                int n = sortear_n(&L);
                if (remover_soldado(&L, n)){
                    printf("Soldado removido.\n");
                }
                break;

            default:
                printf("Opção Inválida.\n");
        }
        getchar();
        getchar();
    }

/*
    inserir_soldado(&L, nome);

    printf("Insira seu nome: ");
    fgets(nome, 49, stdin);
    nome[strlen(nome)-1]='\0';

    inserir_soldado(&L, nome);

    printf("Insira seu nome: ");
    fgets(nome, 49, stdin);
    nome[strlen(nome)-1]='\0';

    inserir_soldado(&L, nome);

    mostrar_soldados(&L);*/
}