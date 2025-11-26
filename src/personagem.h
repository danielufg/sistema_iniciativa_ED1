#ifndef SRC_PERSONAGEM_H_
#define SRC_PERSONAGEM_H_

typedef struct personagem Personagem;

Personagem* criarPersonagem(char nome[50], int nivel, int idDado);
void apagarPersonagem(Personagem** p);
int uparNivel(Personagem* p);
int novaRolagem(Personagem* p);
int calcularIniciativa(Personagem* p);
void printPersonagem(Personagem* p);
int alterarDado(Personagem* p, int idDado);

#endif
