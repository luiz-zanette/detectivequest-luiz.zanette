#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore binária
typedef struct No {
    char valor [50]; // Máximo de caracteres
    struct No* esquerda; // Ponteiro para filho esquerdo
    struct No* direita; // Ponteiro para filho direito
} No;

// **********************************************
// NOVO: Estrutura para rastrear o histórico de salas
// Usamos uma lista encadeada simples (FILO ou FIFO, tanto faz aqui,
// pois só queremos a ordem de visitação)
typedef struct Historico {
    char comodo[50];
    struct Historico* proximo;
} Historico;
// **********************************************


// Função para criar um novo nó com alocação dinâmica
No* criarNo(const char* valor) {
    No* novoNo = (No*)malloc(sizeof(No)); 
    if (!novoNo) {
        perror("Erro ao alocar memória"); 
        exit(1); 
    }
    // Uso de strncpy para segurança
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
// Funções para o Histórico

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
// **********************************************


// Função para liberar a memória alocada para a árvore binária
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda); 
        liberar(raiz->direita); 
        free(raiz); 
    }
}

// Função main para alocar os cômodos da casa
int main() {
    No* raiz = NULL; 
    Historico* historico = NULL; // NOVO: Inicia a lista de histórico
    
    // Inserção de valores na árvore binária (ABB)
    raiz = inserir(raiz, "Hall de Entrada");
    raiz = inserir(raiz, "Sala de Estar");
    raiz = inserir(raiz, "Cozinha");
    raiz = inserir(raiz, "Quarto Principal");
    raiz = inserir(raiz, "Banheiro"); 
    raiz = inserir(raiz, "Escritório");
    raiz = inserir(raiz, "Jardim");
    raiz = inserir(raiz, "Garagem");
    raiz = inserir(raiz, "Sótão");

    No* atual = raiz; 
    int escolha;
    
    printf("\nBem-vindo ao jogo de aventura!\n");

    // Adiciona o primeiro cômodo ao histórico
    historico = adicionarNoHistorico(historico, atual->valor);
    
    exibirComodo(atual);
    printf("===========================================\n");
    
    while (1) {
        
        printf("\nEscolha para onde avançar:\n");
        
        printf("1. Avançar para a direita\n");
        printf("2. Avançar para a esquerda\n");

        printf("0. Sair do Jogo\n");
        printf("Sua escolha: ");
        
        // Verifica se a leitura foi bem-sucedida
        if (scanf("%d", &escolha) != 1) {
            printf("\nEntrada inválida. Limpando buffer e tentando novamente.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (escolha) {
            case 1: // Direita
                if (atual->direita != NULL) {
                    atual = atual->direita;
                    //Adiciona o cômodo recém-visitado ao histórico
                    historico = adicionarNoHistorico(historico, atual->valor); 

                    exibirComodo(atual);
                    
                    // Lógica de FIM DE JOGO AUTOMÁTICO (Surpresa)
                    if (atual->esquerda == NULL && atual->direita == NULL) {
                        printf("\n#################################################################\n");
                        printf("FIM DE JOGO: Você chegou a um cômodo sem saídas.\n");
                        printf("#################################################################\n");
                        goto end_game; 
                    }
                } else {
                    // Feedback: O caminho escolhido estava fechado.
                    printf("\nNão há caminho para a direita. O caminho está bloqueado.\n");
                }
                break;

            case 2: // Esquerda
                if (atual->esquerda != NULL) {
                    atual = atual->esquerda;
                    // Adiciona o cômodo recém-visitado ao histórico
                    historico = adicionarNoHistorico(historico, atual->valor);
                    
                    exibirComodo(atual);
                    
                    // Lógica de FIM DE JOGO AUTOMÁTICO (Surpresa)
                    if (atual->esquerda == NULL && atual->direita == NULL) {
                        printf("\n#################################################################\n");
                        printf("FIM DE JOGO: Você chegou a um cômodo sem saídas.\n");
                        printf("#################################################################\n");
                        goto end_game; 
                    }
                } else {
                    // Feedback: O caminho escolhido estava fechado.
                    printf("\nNão há caminho para a esquerda. O caminho está bloqueado.\n");
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
    //Exibir o histórico de salas visitadas
    exibirHistorico(historico);

    // Liberação da memória alocada para a árvore e o histórico
    liberar(raiz);
    liberarHistorico(historico); // NOVO: Libera a memória do histórico
    return 0;
}