#include <stdio.h>

void move_bishop() {
  int maxY = 5;
  int maxX = 5;

  for (int i = 0; i < maxY; i++) {
    for (int j = 0; j < 1; j++) {
      printf("Cima\n");
      printf("Direita\n");
    }
  }
}

void move_knight() {
  int y = 2;
  int x = 1;
  int lesser = (y < x) ? y : x;
  int higher = (y > x) ? y : x;
  char *print_lesser = (y < x) ? "Baixo\n" : "Esquerda\n";
  char *print_higher = (y > x) ? "Baixo\n" : "Esquerda\n";

  for (int i = 0, j = 0; i < lesser || j < higher; i++, j++) {
    if (i < lesser) {
      printf("%s", print_lesser);
    }
    if (j < higher && i >= lesser) {
      printf("%s", print_higher);
    }
  }
}

void move_tower() {
  for (int i = 0; i < 5; i++) {
    printf("Direita\n");
  }
}

void move_queen() {
  for (int i = 0; i < 8; i++) {
    printf("Esquerda\n");
  }
}

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