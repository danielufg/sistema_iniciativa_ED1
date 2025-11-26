#include <stdlib.h>
#include <string.h>
#include "personagem.h"

typedef struct elemento {
	Personagem* personagem;
	struct elemento* prox;
	struct elemento* prev;
} Elemento;

typedef struct listapersonagens {
	Elemento* primeiro;
	Elemento* ultimo;
	int quant_elementos;
} ListaPersonagens;

ListaPersonagens* criarLista() {
	ListaPersonagens* nova_lista = (ListaPersonagens*) malloc(sizeof(ListaPersonagens));
	if(nova_lista == NULL) {
		return NULL;
	}
	nova_lista->primeiro = NULL;
	nova_lista->ultimo = NULL;
	nova_lista->quant_elementos = 0;
	return nova_lista;
}

void destruirLista(ListaPersonagens* l) {
	if(l == NULL) {
		return;
	}

	Elemento* atual = l->primeiro;
	while(atual != NULL) {
		Elemento* aux = atual->prox;
		free(atual);
		atual = aux;
	}
	free(l);
}

Personagem* adicionarPersonagem(Personagem* p, ListaPersonagens* l) {
	if(p == NULL || l == NULL) {
		return NULL;
	}

	Elemento* novo_elemento = (Elemento*) malloc(sizeof(Elemento));

	if(novo_elemento == NULL) {
		return NULL;
	}

	novo_elemento->personagem = p;
	novo_elemento->prox = NULL;
	novo_elemento->prev = NULL;

	if(l->primeiro == NULL) {
		l->primeiro = novo_elemento;
		l->ultimo = novo_elemento;
		l->quant_elementos++;
		return p;
	}
	l->ultimo->prox = novo_elemento;
	novo_elemento->prev = l->ultimo;
	l->ultimo = novo_elemento;
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

	// percorreu a lista e nao achou o personagem
	if(atual == NULL) {
		return NULL;
	}

	// o personagem a ser removido era o primeiro
	if(atual->prev == NULL) {
		l->primeiro = atual->prox;
	} else {
		atual->prev->prox = atual->prox;
	}

	// o personagem a ser removido era o ultimo
	if(atual->prox == NULL) {
		l->ultimo = atual->prev;
	} else {
		atual->prox->prev = atual->prev;
	}

	free(atual);
	atual = NULL;
	l->quant_elementos--;

	return p;
}

/*
ListaPersonagens* ordenarIniciativasMergeSort(ListaPersonagens* p) {

}
*/

/*
ListaPersonagens* ordenarIniciativasBubbleSort(ListaPersonagens* p) {

}
*/

void printOrdemCombate(ListaPersonagens* l) {
	if(l == NULL) {
		printf("Lista inválida.");
		return;
	}

	if(l->primeiro == NULL) {
		printf("Não há personagens em combate.\n");
		return;
	}

	Elemento* atual = l->primeiro;
	int i = 1;

	printf("ORDEM DE COMBATE:\n");
	while(atual != NULL) {
		printf("%d) Personagem: %s - Iniciativa: %d;\n", i,
				atual->personagem->nome, atual->personagem->iniciativa);
		i++;
		atual = atual->prox;
	}
	printf("-------------------------------------------\n");
}
