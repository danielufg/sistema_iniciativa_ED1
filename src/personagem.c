#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "personagem.h"

typedef struct personagem {
	char nome[50];
	int nivel;
	char dado[3];
	int iniciativa;
} Personagem;

/*
 * pelo menos por enquanto, nao vamos usar isso aqui,
 * vai depender da forma que vamos inicializar o personagem
 *
 * #define PERSONAGEM_PADRAO = {"S/N", 0, "S/D", 0};
*/

Personagem* criarPersonagem(char nome[50], int nivel, int idDado) {
	Personagem novo_personagem = malloc((Personagem*) sizeof(Personagem));
	if(strlen(nome)<=50 && nivel>0 && nivel<=20 && idDado>0 && idDado<=6) {
		char dado[3];
		switch(idDado) {
			case 1:
				dado = "D04";
				break;
			case 2:
				dado = "D06";
				break;
			case 3:
				dado = "D08";
				break;
			case 4:
				dado = "D10";
				break;
			case 5:
				dado = "D12";
				break;
			case 6:
				dado = "D20";
				break;
		}
		novo_personagem->nome = nome;
		novo_personagem->nivel = nivel;
		novo_personagem->dado = strcpy(dado);
		novo_personagem->iniciativa = 0;
	}
	return novo_personagem;
}

void apagarPersonagem(Personagem* p) {
	free(p);
	p = NULL;
}

int uparNivel(Personagem* p) {
	if (p->nivel == 20) {
		printf("Personagem já está no nível máximo.");
		return -1;
	} else {
		p->nivel++;
		printf("Personagem %c subiu de nível com sucesso.", &p->nome);
		return 1;
	}
}

int converteDado(Personagem* p) {
	char tipo_dado[2];
	tipo_dado[0] = p->dado[1];
	tipo_dado[1] = p->dado[2];
	int dado = atoi(tipo_dado);
	return dado;
}

int novaRolagem(Personagem* p) {
	int valor_min = 1;
	int valor_max = converteDado(p);
	int rolagem = (rand()%(valor_max-valor_min+1))+valor_min;
	return rolagem;
}

int calcularIniciativa(Personagem* p) {
	p->iniciativa = 0;
	int rolagem = novaRolagem(p);
	int nivel = p->nivel;
	int nova_iniciativa = (nivel+rolagem);
	p->iniciativa = nova_iniciativa;
	return nova_iniciativa;
}

void printPersonagem(Personagem* p) {
	printf("Nome: %s;\nNivel: %d;\nRolagem: %d", p->nome, p->nivel, (p->iniciativa-p->nivel));
}

int alterarDado(Personagem* p, int idDado) {
	printf("Você realmente deseja alterar o dado do personagem?\n");
	printf("Para confirmar, digite 1. Para cancelar, digite 0.");
	int c;
	scanf("%d", &c);
	if(c==1) {
		if(idDado>0 && idDado<=6) {
			char dado[3];
			switch(idDado) {
				case 1:
					dado = "d04";
					break;
				case 2:
					dado = "d06";
					break;
				case 3:
					dado = "d08";
					break;
				case 4:
					dado = "d10";
					break;
				case 5:
					dado = "d12";
					break;
				case 6:
					dado = "d20";
					break;
			}
			p->dado = strcpy(dado);
			printf("Alteração realizada com sucesso.\n");
			return 1;
		}
	} else {
		printf("Nenhuma alteração realizada.\n");
		return -1;
	}
}
