#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "personagem.h"
#include "lista_personagens.h"

int main() {
    // Inicializa o gerador de números aleatórios UMA VEZ
    srand(time(0));

    // Cria a lista principal do combate
    ListaPersonagens* listaCombate = criarLista();

    int opcao = 0;
    int metodoOrdenacao = 1; // 1 = Bubble Sort (Padrão), 2 = Merge Sort
    int rodada = 0;

    printf("=== SISTEMA DE COMBATE RPG ===\n");

    while (opcao != 6) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Adicionar Novo Personagem\n");
        printf("2. Remover Personagem\n");
        printf("3. Alterar Metodo de Ordenacao (Atual: %s)\n",
               metodoOrdenacao == 1 ? "Bubble Sort" : "Merge Sort");
        printf("4. ROLAR INICIATIVAS (Iniciar/Atualizar Combate)\n");
        printf("5. Mostrar Ordem de Combate\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        getchar(); // Limpa o \n do buffer do teclado

        switch (opcao) {
            case 1: { // ADICIONAR PERSONAGEM
                char nome[50];
                int nivel, idDado;

                printf("\nNome do Personagem: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove o \n do final da string

                printf("Nivel (1-20): ");
                scanf("%d", &nivel);

                printf("Tipo de Dado (1=D4, 2=D6, 3=D8, 4=D10, 5=D12, 6=D20): ");
                scanf("%d", &idDado);
                getchar(); // Limpa buffer

                Personagem* p = criarPersonagem(nome, nivel, idDado);
                if (p) {
                    adicionarPersonagem(p, listaCombate);
                    printf(">> %s entrou na arena!\n", nome);
                } else {
                    printf(">> Erro ao criar personagem. Verifique os dados.\n");
                }
                break;
            }

            case 2: { // REMOVER PERSONAGEM
                if (listaCombate->quant_elementos == 0) {
                    printf(">> A lista esta vazia.\n");
                    break;
                }
                char nomeRemover[50];
                printf("\nNome do Personagem para remover: ");
                fgets(nomeRemover, 50, stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = 0;

                // Criamos um personagem temporário apenas para passar o nome na busca
                // (Já que sua função removerPersonagem compara pelo nome dentro da struct)
                Personagem temp;
                strcpy(temp.nome, nomeRemover);

                Personagem* removido = removerPersonagem(&temp, listaCombate);

                if (removido) {
                    printf(">> %s foi removido do combate.\n", removido->nome);
                    // Como o personagem foi removido da lista mas ainda existe na memória,
                    // precisamos liberar a memória dele aqui para não ter memory leak.
                    free(removido);
                } else {
                    printf(">> Personagem '%s' nao encontrado.\n", nomeRemover);
                }
                break;
            }

            case 3: { // CONFIGURAR ORDENAÇÃO
                printf("\nEscolha o algoritmo:\n");
                printf("1 - Bubble Sort (Troca de ponteiros, ideal para listas pequenas/estavel)\n");
                printf("2 - Merge Sort (Cria nova lista, mais rapido para listas gigantes)\n");
                printf("Opcao: ");
                int m;
                scanf("%d", &m);
                getchar();
                if (m == 1 || m == 2) {
                    metodoOrdenacao = m;
                    printf(">> Metodo atualizado com sucesso.\n");
                } else {
                    printf(">> Opcao invalida.\n");
                }
                break;
            }

            case 4: { // ROLAR INICIATIVAS (O CORAÇÃO DO SISTEMA)
                if (listaCombate->quant_elementos == 0) {
                    printf(">> Adicione personagens antes de iniciar o combate!\n");
                    break;
                }

                rodada++;
                printf("\n--- RODADA %d: ROLANDO DADOS ---\n", rodada);

                // 1. Atualizar a iniciativa de todos na lista
                Elemento* atual = listaCombate->primeiro;
                while (atual != NULL) {
                    calcularIniciativa(atual->personagem);
                    printf("   Rolagem: %s tirou %d\n",
                           atual->personagem->nome, atual->personagem->iniciativa);
                    atual = atual->prox;
                }

                // 2. Ordenar a lista baseada nos novos valores
                printf(">> Organizando a mesa usando %s...\n",
                       metodoOrdenacao == 1 ? "Bubble Sort" : "Merge Sort");

                if (metodoOrdenacao == 1) {
                    // Bubble Sort altera a lista existente 'in-place' (trocando payloads)
                    ordenarIniciativasBubbleSort(listaCombate);
                } else {
                    // Merge Sort retorna uma NOVA estrutura de lista
                    // Sua implementação do Merge já destrói as listas velhas,
                    // então podemos apenas atualizar o ponteiro principal.
                    listaCombate = ordenarIniciativasMergeSort(listaCombate);
                }

                // 3. Mostrar o resultado imediato
                printOrdemCombate(listaCombate);
                break;
            }

            case 5: { // MOSTRAR ORDEM
            	if(listaCombate->quant_elementos == 0) {
            		printf("Lista Vazia.\n");
            		break;
            	}
                printOrdemCombate(listaCombate);
                break;
            }

            case 6: { // SAIR
                printf(">> Encerrando sistema...\n");
                break;
            }

            default:
                printf(">> Opcao invalida.\n");
        }
    }

    // Limpeza final de memória
    // Usamos a função que libera tanto a lista quanto os Personagens dentro dela
    destruirListaComPersonagens(listaCombate);
    printf("Memoria liberada. Ate a proxima!\n");

    return 0;
}
