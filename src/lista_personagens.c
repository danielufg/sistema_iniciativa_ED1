#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_personagens.h"
#include "personagem.h"

ListaPersonagens* criarLista() {
    ListaPersonagens* nova = (ListaPersonagens*) malloc(sizeof(ListaPersonagens));
    if (!nova) return NULL;
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->quant_elementos = 0;
    return nova;
}

void destruirLista(ListaPersonagens* l) {
    if (!l) return;
    Elemento* atual = l->primeiro;
    while (atual) {
        Elemento* aux = atual->prox;
        free(atual);
        atual = aux;
    }
    free(l);
}

void destruirListaMantendoPersonagens(ListaPersonagens* l) {
    if (!l) return;
    Elemento* atual = l->primeiro;
    while (atual) {
        Elemento* aux = atual->prox;
        free(atual);
        atual = aux;
    }
    free(l);
}

void destruirListaComPersonagens(ListaPersonagens* l) {
    if (!l) return;
    Elemento* atual = l->primeiro;
    while (atual) {
        Elemento* aux = atual->prox;
        if (atual->personagem) free(atual->personagem);
        free(atual);
        atual = aux;
    }
    free(l);
}

void transferirConteudo(ListaPersonagens* origem, ListaPersonagens* destino) {
    if (!origem || !destino) return;
    Elemento* atual = origem->primeiro;
    while (atual) {
        adicionarPersonagem(atual->personagem, destino);
        atual = atual->prox;
    }
}

Personagem* adicionarPersonagem(Personagem* p, ListaPersonagens* l) {
    if (!p || !l) return NULL;
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    if (!novo) return NULL;

    novo->personagem = p;
    novo->prox = NULL;
    novo->prev = NULL;

    if (!l->primeiro) {
        l->primeiro = novo;
        l->ultimo = novo;
        l->quant_elementos++;
        return p;
    }

    l->ultimo->prox = novo;
    novo->prev = l->ultimo;
    l->ultimo = novo;
    l->quant_elementos++;
    return p;
}

Personagem* removerPersonagem(Personagem* p, ListaPersonagens* l) {
    if(p == NULL || l == NULL || l->primeiro == NULL) {
            return NULL;
    }

    Elemento* atual = l->primeiro;

    while(atual != NULL && strcmp(p->nome, atual->personagem->nome) != 0) {
        atual = atual->prox;
    }

    if(atual == NULL) {
        return NULL;
    }

    Personagem* personagem_real_encontrado = atual->personagem;

    if(atual->prev == NULL) {
        l->primeiro = atual->prox;
        if(l->primeiro) l->primeiro->prev = NULL;
    } else {
        atual->prev->prox = atual->prox;
    }

    if(atual->prox == NULL) {
        l->ultimo = atual->prev;
        if(l->ultimo) l->ultimo->prox = NULL;
    } else {
        atual->prox->prev = atual->prev;
    }
    free(atual);
    l->quant_elementos--;

    return personagem_real_encontrado;
}

typedef struct duas_listas {
    ListaPersonagens* lista1;
    ListaPersonagens* lista2;
} DuasListas;

DuasListas divideLista(ListaPersonagens* P) {
    DuasListas r;
    r.lista1 = criarLista();
    r.lista2 = criarLista();

    if (!P || P->quant_elementos == 0) return r;

    int metade = (P->quant_elementos % 2 == 0)
        ? P->quant_elementos / 2
        : (P->quant_elementos / 2) + 1;

    Elemento* atual = P->primeiro;
    Elemento* anterior = NULL;

    for (int i = 0; i < metade; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    r.lista1->primeiro = P->primeiro;
    r.lista1->ultimo = anterior;
    r.lista1->quant_elementos = metade;

    if (anterior) anterior->prox = NULL;

    r.lista2->primeiro = atual;
    r.lista2->quant_elementos = P->quant_elementos - metade;

    if (atual) atual->prev = NULL;

    Elemento* temp = atual;
    Elemento* ult = NULL;
    while (temp) {
        ult = temp;
        temp = temp->prox;
    }
    r.lista2->ultimo = ult;

    return r;
}

ListaPersonagens* merge(ListaPersonagens* a, ListaPersonagens* b) {
    ListaPersonagens* r = criarLista();
    Elemento* pa = a->primeiro;
    Elemento* pb = b->primeiro;

    while (pa && pb) {
        if (pa->personagem->iniciativa >= pb->personagem->iniciativa) {
            adicionarPersonagem(pa->personagem, r);
            pa = pa->prox;
        } else {
            adicionarPersonagem(pb->personagem, r);
            pb = pb->prox;
        }
    }

    while (pa) {
        adicionarPersonagem(pa->personagem, r);
        pa = pa->prox;
    }

    while (pb) {
        adicionarPersonagem(pb->personagem, r);
        pb = pb->prox;
    }

    return r;
}

ListaPersonagens* ordenarIniciativasMergeSort(ListaPersonagens* p) {

    if (!p || p->quant_elementos <= 1) return p;

    DuasListas partes = divideLista(p);

    ListaPersonagens* e = ordenarIniciativasMergeSort(partes.lista1);
    ListaPersonagens* d = ordenarIniciativasMergeSort(partes.lista2);

    ListaPersonagens* r = merge(e, d);

    destruirListaMantendoPersonagens(e);
    destruirListaMantendoPersonagens(d);

    return r;
}

ListaPersonagens* ordenarIniciativasBubbleSort(ListaPersonagens* p) {

    if (!p || p->quant_elementos <= 1) return p;

    int troca;

    do {
        troca = 0;
        Elemento* atual = p->primeiro;

        while (atual && atual->prox) {

            if (atual->personagem->iniciativa <
                atual->prox->personagem->iniciativa) {

                Personagem* temp = atual->personagem;
                atual->personagem = atual->prox->personagem;
                atual->prox->personagem = temp;

                troca = 1;
            }

            atual = atual->prox;
        }

    } while (troca);

    return p;
}

void printOrdemCombate(ListaPersonagens* l) {
    if (!l) return;
    if (!l->primeiro) return;

    Elemento* atual = l->primeiro;
    int i = 1;

    while (atual) {
        printf("%d) %s - Iniciativa: %d\n",
            i, atual->personagem->nome,
            atual->personagem->iniciativa);
        i++;
        atual = atual->prox;
    }
}
