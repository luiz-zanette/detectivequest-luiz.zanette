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
    // Comparação para inserção
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
    int comparacao = strcmp(chave, raiz->valor);
    if (comparacao == 0) {
        return true;
    }
    if (comparacao < 0) {
        return buscarBST(raiz->esquerda, chave);
    } else {
        return buscarBST(raiz->direita, chave);
    }
}

// Percurso em ordem (exibe as pistas em ordem alfabética)
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
    // A inserção é baseada na ordem alfabética
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, valor); 
    } else if (strcmp(valor, raiz->valor) > 0) {
        raiz->direita = inserir(raiz->direita, valor); 
    }
    // Ignora duplicatas
    return raiz; 
}

// Exibe o cômodo atual
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
// FUNÇÕES DO HISTÓRICO (Lista Ligada Simples)
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
// PISTAS (Função Simples de Mapeamento)
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

// =========================================================================
// FUNÇÕES DA TABELA HASH (Encadeamento)
// =========================================================================

// Vetor global de ponteiros para início da lista (Tabela Hash)
Nopista* tabela_chaining[TABLE_SIZE]; 

// Função hash simples (soma dos valores ASCII e módulo pelo tamanho da tabela)
int funcao_hash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TABLE_SIZE;
}

// Insere a pista coletada na tabela hash (encadeamento)
void inserirPistaHash(const char* pistaColetada) {
    int indice = funcao_hash(pistaColetada);
    Nopista* novo_Nopista = (Nopista*)malloc(sizeof(Nopista));
    if (!novo_Nopista) {
        perror("Erro ao alocar memória para Nopista");
        exit(1);
    }
    strncpy(novo_Nopista->textoPista, pistaColetada, sizeof(novo_Nopista->textoPista) - 1);
    novo_Nopista->textoPista[sizeof(novo_Nopista->textoPista) - 1] = '\0';

    // Inserção no início da lista (mais simples)
    novo_Nopista->proximo = tabela_chaining[indice];
    tabela_chaining[indice] = novo_Nopista;
}

// Insere a pista do cômodo na tabela hash e a retorna
const char* pistaColetadaHash(const char* valor) {
    const char* pista = obterPistaDoComodo(valor);
    if (pista != NULL) {
        inserirPistaHash(pista);
    }
    return pista;
}

// Busca em encadeamento na lista ligada
Nopista* buscarPistaHash(const char* valor) {
    int indice = funcao_hash(valor);
    Nopista* atual = tabela_chaining[indice];
    while (atual != NULL) {
        if (strcmp(atual->textoPista, valor) == 0) { 
            return atual; // Encontrado
        }
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}

// Obtém a pista coletada associada ao cômodo
const char* obterPistaColetada(const char* valor) {
    const char* pista_original = obterPistaDoComodo(valor);
    if (pista_original == NULL) {
        return NULL;
    }
    
    // Busca a pista (valor) na tabela hash
    Nopista* encontrado = buscarPistaHash(pista_original); 
    if (encontrado != NULL) {
        return encontrado->textoPista;
    }
    return NULL;
}

// Verifica opção do usuário para suspeito correto (Motorista)
bool verificarSuspeito(int escolhaUsuario) {
    const int suspeitoCorreto = 4; // 4. Motorista
    
    // Pistas relevantes ao caso do Motorista
    const char* p1_motorista = "Um casaco de chuva ensanguentado foi jogado na máquina."; // Lavanderia
    const char* p2_motorista = "O carro principal não está, mas o pneu sobressalente sim."; // Garagem
    
    printf("\n--- ACUSAÇÃO DE SUSPEITO ---\n");

    if (escolhaUsuario == suspeitoCorreto) { 
        printf("ACUSAÇÃO CORRETA: O Motorista é o culpado!\n");
        printf("\nDetalhes das Pistas Chave:\n");
        printf("1. %s\n", p1_motorista);
        printf("2. %s\n", p2_motorista);
        printf("\nPARABÉNS! VOCÊ SOLUCIONOU O MISTÉRIO.\n");
        liberarTabelaHash();
        return true;
    } else {
        printf("ACUSAÇÃO INCORRETA. Continue investigando.\n");
        return false;
    }
}

// Libera memória da tabela hash
void liberarTabelaHash() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Nopista* atual = tabela_chaining[i];
        while (atual != NULL) {
            Nopista* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        tabela_chaining[i] = NULL;
    }
}