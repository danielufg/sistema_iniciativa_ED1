#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "personagem.h"

Personagem* criarPersonagem(char nome[50], int nivel, int idDado) {
    Personagem* p = (Personagem*) malloc(sizeof(Personagem));
    if (!p) return NULL;

    if (strlen(nome) < 50 && nivel > 0 && nivel <= 20 && idDado > 0 && idDado <= 6) {
        strcpy(p->nome, nome);
        p->nivel = nivel;
        p->iniciativa = 0;

        switch (idDado) {
            case 1: strcpy(p->dado, "D04"); break;
            case 2: strcpy(p->dado, "D06"); break;
            case 3: strcpy(p->dado, "D08"); break;
            case 4: strcpy(p->dado, "D10"); break;
            case 5: strcpy(p->dado, "D12"); break;
            case 6: strcpy(p->dado, "D20"); break;
        }
    } else {
        free(p);
        return NULL;
    }

    return p;
}

void apagarPersonagem(Personagem** p) {
    if (p && *p) {
        free(*p);
        *p = NULL;
    }
}

int uparNivel(Personagem* p) {
    if (p->nivel == 20) {
        printf("Personagem %s já está no nível máximo.\n", p->nome);
        return -1;
    }
    p->nivel++;
    printf("Personagem %s subiu de nível.\n", p->nome);
    return 1;
}

int converteDado(Personagem* p) {
    char tipo_dado[3];
    tipo_dado[0] = p->dado[1];
    tipo_dado[1] = p->dado[2];
    tipo_dado[2] = '\0';
    return atoi(tipo_dado);
}

int novaRolagem(Personagem* p) {
    int min = 1;
    int max = converteDado(p);
    return (rand() % (max - min + 1)) + min;
}

int calcularIniciativa(Personagem* p) {
    int rolagem = novaRolagem(p);
    p->iniciativa = p->nivel + rolagem;
    return p->iniciativa;
}

void printPersonagem(Personagem* p) {
    printf("Nome: %s\nNivel: %d\nDado: %s\nIniciativa: %d\n",
           p->nome, p->nivel, p->dado, p->iniciativa);
}

int alterarDado(Personagem* p, int idDado) {
    printf("Deseja alterar o dado? (1 = sim / 0 = não): ");
    int c;
    scanf("%d", &c);

    if (c != 1) return -1;

    if (idDado >= 1 && idDado <= 6) {
        switch (idDado) {
            case 1: strcpy(p->dado, "D04"); break;
            case 2: strcpy(p->dado, "D06"); break;
            case 3: strcpy(p->dado, "D08"); break;
            case 4: strcpy(p->dado, "D10"); break;
            case 5: strcpy(p->dado, "D12"); break;
            case 6: strcpy(p->dado, "D20"); break;
        }
        printf("Dado alterado com sucesso.\n");
        return 1;
    }

    printf("ID de dado inválido.\n");
    return 0;
}
