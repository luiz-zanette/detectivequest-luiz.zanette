#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"


int main() {
    No* raiz = NULL; 
    Historico* historico = NULL; 
    NoBST* pistas = NULL; // BST para armazenar APENAS as pistas coletadas
    
    // Inserção de valores na árvore binária (ABB) para construir a casa
    raiz = inserir(raiz, "Hall de Entrada");
    raiz = inserir(raiz, "Sala de Estar");
    raiz = inserir(raiz, "Cozinha");
    raiz = inserir(raiz, "Quarto Principal");
    raiz = inserir(raiz, "Banheiro"); 
    raiz = inserir(raiz, "Escritório");
    raiz = inserir(raiz, "Jardim");
    raiz = inserir(raiz, "Garagem");
    raiz = inserir(raiz, "Sótão");
    raiz = inserir(raiz, "Corredor");
    raiz = inserir(raiz, "Despensa");
    raiz = inserir(raiz, "Lavanderia");

    No* atual = raiz; 
    int escolha;
    
    printf("\nBem-vindo ao jogo de aventura!\n");

    // Adiciona o primeiro cômodo ao histórico e coleta sua pista (se houver)
    historico = adicionarNoHistorico(historico, atual->valor);
    const char* pista_inicial = obterPistaDoComodo(atual->valor);
    if (pista_inicial != NULL) {
        pistas = pistaColetada(pistas, pista_inicial);
        printf("\n[!!! PISTA INICIAL ENCONTRADA !!!]: %s\n", pista_inicial);
    }
    
    exibirComodo(atual);
    printf("===========================================\n");
    
    while (1) {
        
        printf("\nEscolha para onde avançar:\n");
        printf("1. Avançar para a direita\n");
        printf("2. Avançar para a esquerda\n");
        printf("3. Exibir Histórico de Cômodos\n");
        printf("4. Exibir Pistas Coletadas\n");
        printf("5. Dar palpite de suspeito\n");
        printf("0. Sair do Jogo\n");
        printf("Sua escolha: ");
        
        if (scanf("%d", &escolha) != 1) {
            printf("\nEntrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        if (escolha == 3) {
            exibirHistorico(historico);
            continue;
        }

        if (escolha == 4) {
            printf("\n>>> PISTAS COLETADAS (ORDEM ALFABÉTICA) <<<\n");
            if (pistas == NULL) {
                printf("Nenhuma pista coletada ainda.\n");
            } else {
                emOrdem(pistas);
            }
            continue;
        }


        switch (escolha) {
            case 1: // Direita
                if (atual->direita != NULL) {
                    atual = atual->direita;
                    historico = adicionarNoHistorico(historico, atual->valor); 
                    
                    const char* pista = obterPistaDoComodo(atual->valor);
                    if (pista != NULL && !buscarBST(pistas, pista)) { // Verifica se já coletou
                        pistas = pistaColetada(pistas, pista); 
                        printf("\n[!!! PISTA ENCONTRADA !!!]: %s\n", pista);
                    }

                    exibirComodo(atual);
                    printf("===========================================\n");
                } else {
                    printf("\nNão há caminho para a direita. O caminho está bloqueado.\n");
                }
                break;

            case 2: // Esquerda
                if (atual->esquerda != NULL) {
                    atual = atual->esquerda;
                    historico = adicionarNoHistorico(historico, atual->valor);
                    
                    const char* pista = obterPistaDoComodo(atual->valor);
                    if (pista != NULL && !buscarBST(pistas, pista)) { // Verifica se já coletou
                        pistas = pistaColetada(pistas, pista); 
                        printf("\n[!!! PISTA ENCONTRADA !!!]: %s\n", pista);
                    }

                    exibirComodo(atual);
                    printf("===========================================\n");
                } else {
                    printf("\nNão há caminho para a esquerda. O caminho está bloqueado.\n");
                }
                break;

                case 5: // Dar palpite de suspeito
                { 
                    int escolhaSuspeito;
                    printf("\n===================================\n");
                    printf("  ACUSAÇÃO DE SUSPEITO\n");
                    printf("===================================\n");
                    printf("1. Cozinheiro\n");
                    printf("2. Jardineiro\n");
                    printf("3. Governanta\n");
                    printf("4. Motorista\n"); // Suspeito correto
                    printf("5. Mordomo\n");

                    printf("Digite o número do suspeito: ");
                    
                    // Leitura da escolha do suspeito com verificação de erro
                    if (scanf("%d", &escolhaSuspeito) != 1) {
                        printf("\nEntrada inválida. Tente novamente.\n");
                        while (getchar() != '\n'); // Limpa o buffer
                        break;
                    }
                    while (getchar() != '\n'); // Limpa o buffer para o próximo loop

                    // Chama a função de verificação que encerra o jogo se correta
                    if (verificarSuspeito(escolhaSuspeito)) {
                        printf("\nVocê acusou o suspeito correto! Parabéns!\n");
                    }
                }
                break;

            case 0:
                printf("\nSaindo do jogo. Aventura concluída!\n");
                goto end_game; 

            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    }


end_game:
    // Exibir o histórico de salas visitadas
    exibirHistorico(historico);
    // Exibir as pistas coletadas em ordem alfabética
    printf("\n>>> PISTAS COLETADAS FINAIS <<<\n");
    if (pistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        emOrdem(pistas);
    }
    printf("O suspeito do crime foi o Motorista!\n");

    printf("\n#####################################\n");

    // Liberação da memória alocada
    liberar(raiz);
    liberarHistorico(historico); 
    liberarBST(pistas); 
    return 0;
}