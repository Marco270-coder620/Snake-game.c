#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "snake.h"
#include "stats.h"

#define TAM 10

typedef struct Parte {
    int x, y;
    struct Parte* prox;
} Parte;

Parte* criarParte(int x, int y) {
    Parte* nova = (Parte*)malloc(sizeof(Parte));
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}

void liberarCobra(Parte* cabeca) {
    while (cabeca) {
        Parte* temp = cabeca;
        cabeca = cabeca->prox;
        free(temp);
    }
}

int colidiu(Parte* cobra, int x, int y, char mapa[TAM][TAM]) {
    if (mapa[x][y] == '#') return 1;
    Parte* p = cobra;
    while (p) {
        if (p->x == x && p->y == y) return 1;
        p = p->prox;
    }
    return 0;
}

void desenharMapa(char mapa[TAM][TAM], Parte* cobra) {
    char temp[TAM][TAM];
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            temp[i][j] = mapa[i][j];

    Parte* p = cobra;
    while (p) {
        temp[p->x][p->y] = 'O';
        p = p->prox;
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c", temp[i][j]);
        }
        printf("\n");
    }
}

void carregarFase(int fase, char mapa[TAM][TAM]) {
    char nome[20];
    sprintf(nome, "fase%d.txt", fase);
    FILE* f = fopen(nome, "r");
    if (!f) {
        perror("Erro ao abrir o arquivo");
        printf("Arquivo: %s\n", nome);
        exit(1);
    }
    for (int i = 0; i < TAM; i++) {
        fscanf(f, "%s", mapa[i]);
    }
    fclose(f);
}

void iniciarJogo() {
    char mapa[TAM][TAM];
    int pontuacao = 0;

    for (int fase = 1; fase <= 5; fase++) {
        system("cls");
        printf("\nIniciando Fase %d...\n", fase);
        carregarFase(fase, mapa);

        // Inicializa cobra no centro
        Parte* cobra = criarParte(5, 5);

        int dx = 0, dy = 1; // Direção inicial: direita
        char comando;
        int fim = 0;

        // Contador de comidas
        int totalComida = 0;
        int comidaComida = 0;

        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (mapa[i][j] == '*') {
                    totalComida++;
                }
            }
        }

        while (!fim) {
            system("cls");
            desenharMapa(mapa, cobra);
            printf("Pontuação: %d\n", pontuacao);
            comando = getch();

            switch (comando) {
                case 'w': dx = -1; dy = 0; break;
                case 's': dx = 1; dy = 0; break;
                case 'a': dx = 0; dy = -1; break;
                case 'd': dx = 0; dy = 1; break;
                case 'x': fim = 1; continue; // Sair
            }

            int novoX = cobra->x + dx;
            int novoY = cobra->y + dy;

            if (novoX < 0 || novoX >= TAM || novoY < 0 || novoY >= TAM || colidiu(cobra, novoX, novoY, mapa)) {
                printf("\nVocê perdeu! Fim de jogo.\n");
                fim = 1;
                break;
            }

            Parte* nova = criarParte(novoX, novoY);
            nova->prox = cobra;
            cobra = nova;

            if (mapa[novoX][novoY] == '*') {
                pontuacao += 10;
                mapa[novoX][novoY] = '.';
                comidaComida++;

                if (comidaComida == totalComida) {
                    printf("\nParabéns! Você completou a fase %d!\n", fase);
                    fim = 1;
                    break;
                }
            } else {
                // Remove cauda
                Parte* p = cobra;
                while (p->prox && p->prox->prox)
                    p = p->prox;
                free(p->prox);
                p->prox = NULL;
            }
        }

        liberarCobra(cobra);
        printf("Pressione qualquer tecla para continuar...\n");
        getch();
    }

    salvarPontuacao(pontuacao);
    printf("Sua pontuação total foi: %d\n", pontuacao);
    printf("Pontuação salva!\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch();
}

