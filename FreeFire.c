/*
============================================================
    Sistema de Inventário — Nível Novato
    Desenvolvido conforme as regras do desafio do nível novato.
    
    O nível novato exige:
    - Uso de struct para representar itens (nome, tipo, quantidade)
    - Lista sequencial com capacidade para 10 itens
    - Funções de inserir, remover, listar e buscar
    - Uso de busca sequencial
    - Interface simples e orientativa
    - Documentação e código limpo para fácil manutenção

    Este arquivo implementa todas as funcionalidades solicitadas.
============================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ITENS 10

// --------------------------------------------------------
// Struct Item: armazena os dados de cada item da mochila
// --------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens
Item inventario[MAX_ITENS];
int totalItens = 0;

// Remove \n de fgets
void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Deixa minúsculo (para busca case-insensitive)
void minusculo(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

// --------------------------------------------------------
// Função: inserirItem()
// Permite cadastrar um novo item no inventário
// --------------------------------------------------------
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️  A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== Cadastro de Item ===\n");

    getchar(); // limpa buffer

    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    removerQuebraLinha(novo.nome);

    printf("Tipo do item (arma, municao, cura, etc): ");
    fgets(novo.tipo, 20, stdin);
    removerQuebraLinha(novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    inventario[totalItens] = novo;
    totalItens++;

    printf("\n✅ Item cadastrado com sucesso!\n");
}

// --------------------------------------------------------
// Função: removerItem()
// Remove um item do inventário pelo nome
// --------------------------------------------------------
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️  A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");

    getchar();
    fgets(nomeRemover, 30, stdin);
    removerQuebraLinha(nomeRemover);

    char nomeRemoverLower[30];
    strcpy(nomeRemoverLower, nomeRemover);
    minusculo(nomeRemoverLower);

    int encontrado = -1;

    for (int i = 0; i < totalItens; i++) {
        char temp[30];
        strcpy(temp, inventario[i].nome);
        minusculo(temp);

        if (strcmp(temp, nomeRemoverLower) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n❌ Item não encontrado!\n");
        return;
    }

    for (int i = encontrado; i < totalItens - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    totalItens--;
    printf("\n🗑️  Item removido com sucesso!\n");
}

// --------------------------------------------------------
// Função: listarItens()
// Mostra todos os itens cadastrados
// --------------------------------------------------------
void listarItens() {
    printf("\n====== Itens na Mochila ======\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", inventario[i].nome);
        printf("Tipo: %s\n", inventario[i].tipo);
        printf("Quantidade: %d\n", inventario[i].quantidade);
    }
}

// --------------------------------------------------------
// Função: buscarItem()
// Busca um item pelo nome usando busca sequencial
// --------------------------------------------------------
void buscarItem() {
    if (totalItens == 0) {
        printf("\n⚠️  A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");

    getchar();
    fgets(nomeBusca, 30, stdin);
    removerQuebraLinha(nomeBusca);

    char nomeBuscaLower[30];
    strcpy(nomeBuscaLower, nomeBusca);
    minusculo(nomeBuscaLower);

    for (int i = 0; i < totalItens; i++) {
        char temp[30];
        strcpy(temp, inventario[i].nome);
        minusculo(temp);

        if (strcmp(temp, nomeBuscaLower) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Tipo: %s\n", inventario[i].tipo);
            printf("Quantidade: %d\n", inventario[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item não encontrado!\n");
}

// --------------------------------------------------------
// Função principal: menu do sistema
// --------------------------------------------------------
int main() {
    int opcao;

    do {
        printf("\n==============================\n");
        printf("  Sistema de Inventário - Nível Novato\n");
        printf("==============================\n");
        printf("1. Cadastrar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n❌ Opção inválida! Tente novamente.\n");

            while (getchar() != '\n'); // limpa buffer

            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}
