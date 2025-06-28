#include <stdio.h>
#include <stdlib.h>

void salvarPontuacao(int pontos) {
    FILE* f = fopen("stats.bin", "ab");
    if (!f) return;
    fwrite(&pontos, sizeof(int), 1, f);
    fclose(f);
}

void mostrarEstatisticas() {
    FILE* f = fopen("stats.bin", "rb");
    if (!f) {
        printf("Sem estatísticas ainda.\n");
        return;
    }
    int p, i = 1;
    printf("\n=== Estatísticas ===\n");
    while (fread(&p, sizeof(int), 1, f)) {
        printf("Jogo %d: %d pontos\n", i++, p);
    }
    fclose(f);
}


