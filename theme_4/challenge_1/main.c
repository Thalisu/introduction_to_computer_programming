#include <stdio.h>
void move_tower() {
  // 5 right
  int max = 5;
  for (int i = 0; i < max; i++) {
    printf("Direita\n");
  }
};
void move_bishop() {
  // 5 up right
  int max = 5;
  for (int i = 0; i < max; i++) {
    printf("Cima\nDireita\n");
  }
};
void move_queen() {
  // 8 left
  int max = 8;
  for (int i = 0; i < max; i++) {
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

  return 0;
}