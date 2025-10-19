#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"

// =========================================================================
// FUNÇÕES DA BST (Pistas Coletadas)
// =========================================================================

// Cria novo nó na BST
NoBST* criarNoBST(const char* valor) {
    NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
    if (!novo) {
        perror("Erro ao alocar memória para NoBST");
        exit(1);
    }
    // Copia o valor com segurança
    strncpy(novo->valor, valor, sizeof(novo->valor) - 1);
    novo->valor[sizeof(novo->valor) - 1] = '\0';
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere elemento em ordem alfabética na BST
NoBST* pistaColetada(NoBST* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarNoBST(valor);
    }
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = pistaColetada(raiz->esquerda, valor);
    } else if (strcmp(valor, raiz->valor) > 0) { // Garante que duplicatas não são inseridas
        raiz->direita = pistaColetada(raiz->direita, valor);
    }
    return raiz;
}

// Busca elemento na BST
bool buscarBST(NoBST* raiz, const char* chave) {
    if (raiz == NULL) {
        return false;
    }
    if (strcmp(chave, raiz->valor) == 0) {
        return true;
    }
    if (strcmp(chave, raiz->valor) < 0) {
        return buscarBST(raiz->esquerda, chave);
    } else {
        return buscarBST(raiz->direita, chave);
    }
}

// Percurso em ordem 
void emOrdem(NoBST* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->valor);
        emOrdem(raiz->direita);
    }
}

// Libera memória da BST
void liberarBST(NoBST* raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);
        free(raiz);
    }
}


// =========================================================================
// FUNÇÕES DA ÁRVORE DE CÔMODOS (ABB)
// =========================================================================

// Função para criar um novo nó com alocação dinâmica
No* criarNo(const char* valor) {
    No* novoNo = (No*)malloc(sizeof(No)); 
    if (!novoNo) {
        perror("Erro ao alocar memória para No"); 
        exit(1); 
    }
    strncpy(novoNo->valor, valor, sizeof(novoNo->valor) - 1); 
    novoNo->valor[sizeof(novoNo->valor) - 1] = '\0'; 
    
    novoNo->esquerda = NULL; 
    novoNo->direita = NULL; 
    return novoNo; 
}

// Função para inserir um novo valor na árvore binária de forma recursiva (ABB)
No* inserir(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarNo(valor); 
    }
    // A inserção é baseada na ordem alfabética para construir o caminho.
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, valor); 
    } else if (strcmp(valor, raiz->valor) > 0) {
        raiz->direita = inserir(raiz->direita, valor); 
    }
    return raiz; 
}

void exibirComodo(No* atual) {
    if (atual != NULL) {
        printf("\n===================================\n");
        printf("VOCÊ ESTÁ AGORA NO CÔMODO: %s\n", atual->valor);  
        printf("===================================\n");
    }
}

// Função para liberar a memória alocada para a árvore binária
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda); 
        liberar(raiz->direita); 
        free(raiz); 
    }
}


// =========================================================================
// FUNÇÕES DO HISTÓRICO
// =========================================================================

// Adiciona um novo cômodo ao final da lista de histórico
Historico* adicionarNoHistorico(Historico* cabeca, const char* comodo) {
    Historico* novo = (Historico*)malloc(sizeof(Historico));
    if (!novo) {
        perror("Erro ao alocar memória para histórico");
        exit(1);
    }
    strncpy(novo->comodo, comodo, sizeof(novo->comodo) - 1);
    novo->comodo[sizeof(novo->comodo) - 1] = '\0';
    novo->proximo = NULL;

    if (cabeca == NULL) {
        return novo; // Retorna o primeiro nó
    }

    Historico* temp = cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novo;
    return cabeca; // Retorna a cabeça (raiz) inalterada
}

// Exibe a lista de cômodos visitados
void exibirHistorico(Historico* cabeca) {
    printf("\n>>> CÔMODOS VISITADOS (ORDEM) <<<\n");
    Historico* atual = cabeca;
    int contador = 1;
    while (atual != NULL) {
        printf("%d. %s\n", contador++, atual->comodo);
        if (atual->proximo != NULL) {
            printf("   |\n   v\n");
        }
        atual = atual->proximo;
    }
    printf("#####################################\n");
}

// Libera a memória alocada para o histórico
void liberarHistorico(Historico* cabeca) {
    Historico* atual = cabeca;
    Historico* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}


// =========================================================================
// LÓGICA DO JOGO (PISTAS)
// =========================================================================

// Associa uma pista a um cômodo
const char* obterPistaDoComodo(const char* comodo) {
    if (strcmp(comodo, "Hall de Entrada") == 0) {
        return "A lanterna está no Hall, mas não tem bateria.";
    } else if (strcmp(comodo, "Sala de Estar") == 0) {
        return "Um bilhete amassado: 'A chave está no Oeste'.";
    } else if (strcmp(comodo, "Cozinha") == 0) {
        return "Cheiro forte de café queimado e uma faca faltando.";
    } else if (strcmp(comodo, "Quarto Principal") == 0) {
        return "O armário está revirado; o cofre foi aberto.";
    } else if (strcmp(comodo, "Banheiro") == 0) {
        return "Uma toalha molhada foi usada para limpar algo.";
    } else if (strcmp(comodo, "Escritório") == 0) {
        return "O computador está ligado na tela de um mapa.";
    } else if (strcmp(comodo, "Jardim") == 0) {
        return "Pegadas de lama levam para fora da propriedade.";
    } else if (strcmp(comodo, "Garagem") == 0) {
        return "O carro principal não está, mas o pneu sobressalente sim.";
    } else if (strcmp(comodo, "Sótão") == 0) {
        return "O objeto roubado era um pingente antigo.";
    } else if (strcmp(comodo, "Corredor") == 0) {
        return "Marcas de arranhão profundas no chão de madeira.";
    } else if (strcmp(comodo, "Despensa") == 0) {
        return "Um molho de chaves está pendurado no gancho.";
    } else if (strcmp(comodo, "Lavanderia") == 0) {
        return "Um casaco de chuva ensanguentado foi jogado na máquina.";
    }
    return NULL; // Cômodo sem pista relevante
}