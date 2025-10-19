#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef FUNCOES_H
#define FUNCOES_H

// Declaração das structs
// Definição da estrutura do nó da árvore binária (COMODOS)
typedef struct No {
    char valor [50]; // Nome do cômodo
    struct No* esquerda; // Ponteiro para filho esquerdo
    struct No* direita; // Ponteiro para filho direito
} No;

// Struct do nó da BST (PISTAS COLETADAS)
typedef struct NoBST{
    char valor[100]; // Aumentado para acomodar frases de pista
    struct NoBST *esquerda; 
    struct NoBST *direita; 
} NoBST;

// Estrutura para rastrear o histórico de salas
typedef struct Historico {
    char comodo[50];
    struct Historico* proximo;
} Historico;

// =========================================================================
// Declaração das funções usadas em BST
NoBST* criarNoBST(const char* valor);
NoBST* pistaColetada(NoBST* raiz, const char* valor);
bool buscarBST(NoBST* raiz, const char* chave);
void emOrdem(NoBST* raiz);
void liberarBST(NoBST* raiz);

// Declaração das funções usadas em Árvore Binária
No* criarNo(const char* valor);
No* inserir(No* raiz, const char* valor);
void exibirComodo(No* atual);
void liberar(No* raiz);

// Declaração das funções usadas em Histórico
Historico* adicionarNoHistorico(Historico* cabeca, const char* comodo);
void exibirHistorico(Historico* cabeca);
void liberarHistorico(Historico* cabeca);

// Declaração da função para obter pista do cômodo
const char* obterPistaDoComodo(const char* comodo);

#endif