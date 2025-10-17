#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct do nó da BST
typedef struct NoBST{
    char valor[50];
    struct NoBST *esquerda; //Nó filho esquerdo
    struct NoBST *direita; //Nó filho direito
} NoBST;

// Cria novo nó na BST
NoBST* criarNoBST(const char* valor) {
    NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere elemento em ordem alfabética na BST
NoBST* inserirBST(NoBST* raiz, const char* valor) {
    if (raiz == NULL) {
        return criarNoBST(valor);
    }
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, valor);
    } else {
        raiz->direita = inserirBST(raiz->direita, valor);
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
        printf("%s\n", raiz->valor);
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

// ****************** Arvore TRIE ******************
#define TAM_ALFABETO 26 // Considerando apenas letras minúsculas a-z

// Estrutura do nó trie
typedef struct NoTrie {
    struct NoTrie* filhos[TAM_ALFABETO];
    bool fimPalavra;
} NoTrie;

// Cria novo nó na trie
NoTrie* criarNoTrie() {
    NoTrie* novo = (NoTrie*)malloc(sizeof(NoTrie));
    novo->fimPalavra = false;
    for (int i = 0; i < TAM_ALFABETO; i++) {
        novo->filhos[i] = NULL;
    }
    return novo;
    }

// Normaliza o índice do caractere (todos para minusculos sem espaços para buscar)
void normalizar(const char* entrada, char* saida) {
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];
        if (c >= 'A' && c <= 'Z') c += 32; // Converte para minúsculo
        if (c >= 'a' && c <= 'z') saida[j++] = c; // Adiciona apenas letras
    }
    saida[j] = '\0'; // Adiciona o terminador de string
}

// Insere palavra na trie
void inserirTrie(NoTrie* raiz, const char* palavra) {
    NoTrie* atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNoTrie();
        }
        atual = atual->filhos[indice];
    }
    atual->fimPalavra = true;
}

// Busca palavra na trie
bool buscarTrie(NoTrie* raiz, const char* palavra) {
    NoTrie* atual = raiz;
    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';
        if (atual->filhos[indice] == NULL) {
            return false;
        }
        atual = atual->filhos[indice];
    }
    return atual != NULL && atual->fimPalavra;
}

// Lista de palavras na Trie (lexicográfica)
void listarPalavras(NoTrie* no, char* buffer, int nivel) {
    if (no->fimPalavra) {
        buffer[nivel] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            listarPalavras(no->filhos[i], buffer, nivel + 1);
        }
    }
}

// libera memória na Trie
void liberarTrie(NoTrie* no) {
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            liberarTrie(no->filhos[i]);
        }
    }
    free(no);
}

// ********** Função main para demonstração **********
int main() {
    // Demonstração da BST
    printf("=== Árvore Binária de Busca (BST) ===\n");
    NoBST* raizBST = NULL;
    raizBST = inserirBST(raizBST, "Pegadas de lama");
    raizBST = inserirBST(raizBST, "Chave Perdida");
    raizBST = inserirBST(raizBST, "Livro sem Capa");
    raizBST = inserirBST(raizBST, "Mapa Antigo");
    raizBST = inserirBST(raizBST, "Espada Enferrujada");

    printf("Elementos em ordem alfabética:\n");
    emOrdem(raizBST);
    printf("\nBuscando 'Mapa Antigo': %s\n", buscarBST(raizBST, "Mapa Antigo") ? "Encontrado" : "Não Encontrado");
    printf("Buscando 'Escudo Quebrado': %s\n", buscarBST(raizBST, "Escudo Quebrado") ? "Encontrado" : "Não Encontrado");

    // liberando memória da BST
    liberarBST(raizBST);

// Demonstração da Trie
    printf("\n=== Árvore TRIE ===\n");
    NoTrie* raizTrie = criarNoTrie();

    // Inserindo palavras na Trie de forma normalizada
    char normalizada[100];
    normalizar("Pegadas de lama", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Chave Perdida", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Livro sem Capa", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Mapa Antigo", normalizada);
    inserirTrie(raizTrie, normalizada);
    normalizar("Espada Enferrujada", normalizada);
    inserirTrie(raizTrie, normalizada);

    printf("Palavras na Trie:\n");
    char buffer[100];
    listarPalavras(raizTrie, buffer, 0);
    printf("\n");
    normalizar("Mapa Antigo", normalizada);
    printf("Buscando 'Mapa Antigo': %s\n", buscarTrie(raizTrie, normalizada) ? "Encontrado" : "Não Encontrado");
    normalizar("Macaco Louco", normalizada);
    printf("Buscando 'Macaco Louco': %s\n", buscarTrie(raizTrie, normalizada) ? "Encontrado" : "Não Encontrado");

    // liberando memória da Trie
    liberarTrie(raizTrie);
    return 0;
}   