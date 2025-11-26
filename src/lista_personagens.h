#ifndef SRC_LISTA_PERSONAGENS_H_
#define SRC_LISTA_PERSONAGENS_H_

typedef struct elemento Elemento;
typedef struct listapersonagens ListaPersonagens;

ListaPersonagens* criarLista();
void destruirLista(ListaPersonagens* l);
Personagem* adicionarPersonagem(Personagem* p, ListaPersonagens* l);
Personagem* removerPersonagem(Personagem* p, ListaPersonagens* l);
ListaPersonagens* ordenarIniciativasMergeSort(ListaPersonagens* l);
ListaPersonagens* ordenarIniciativasBubbleSort(ListaPersonagens* l);
void printOrdemCombate(ListaPersonagens* l);

#endif
