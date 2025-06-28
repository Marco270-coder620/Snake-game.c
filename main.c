#include <stdio.h>
#include "snake.h"
#include "stats.h"
#include "locale.h"

int main() {
    int escolha;
    setlocale(LC_ALL, "Portuguese");

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Ver Estatísticas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                mostrarEstatisticas();
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}

