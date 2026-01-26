#include <stdio.h>
void move_tower() {
  int max = 5;
  for (int i = 0; i < max; i++) {
    printf("Direita\n");
  }
};
void move_bishop() {
  int max = 5;
  for (int i = 0; i < max; i++) {
    printf("Cima\nDireita\n");
  }
};
void move_queen() {
  int max = 8;
  for (int i = 0; i < max; i++) {
    printf("Esquerda\n");
  }
};
void move_knight() {
  int maxY = 2;
  int maxX = 1;

  for (int i = 0; i < maxX; i++) {
    for (int j = 0; j < maxY; j++) {
      printf("Baixo\n");
    }
    printf("Esquerda\n");
  }
};

int main() {
  printf("Torre se move:\n");
  move_tower();
  printf("Bispo se move:\n");
  move_bishop();
  printf("Rainha se move:\n");
  move_queen();
  printf("Cavalo se move:\n");
  move_knight();

  return 0;
}