#include <stdbool.h>
#include <stdio.h>

void init_matrix(int size, int matrix[size][size]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = 0;
    }
  }
};

void print_matrix(int size, int matrix[size][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
};

bool is_invalid_ship_placement(int b_size, int s_size, int x1, int x2, int y1,
                               int y2) {
  int max_xy1_value = b_size - s_size;
  int max_xy2_value = b_size - 1;

  if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
    return true;
  }

  if (x2 > b_size || y2 > b_size) {
    return true;
  }

  if (x1 > max_xy1_value || y1 > max_xy1_value) {
    printf("a\n");
    return true;
  }

  if (x2 > max_xy2_value || y2 > max_xy2_value) {
    return true;
  }

  if (((x2 - x1) + 1) != s_size && ((y2 - y1) + 1) != s_size) {
    return true;
  }

  if ((x2 > 0 && y2 != 0) || (y2 > 0 && x2 != 0)) {
    return true;
  }

  return false;
}

void place_ship(int b_size, int board[b_size][b_size], int s_size, int x1,
                int x2, int y1, int y2) {

  if (is_invalid_ship_placement(b_size, s_size, x1, x2, y1, y2)) {
    return;
  }

  bool is_horizontal = y2 == 0;
  printf("isHorizontal = %d\n", is_horizontal);

  if (y2 > 0) {
    for (int y = y1; y <= y2; y++) {
      board[y][x1] = 1;
    }
  } else {
    for (int x = x1; x <= x2; x++) {
      board[y1][x] = 1;
    }
  }
};

int main() {
  int board_size = 10;
  int ship_size = 3;

  int board[board_size][board_size];
  init_matrix(board_size, board);

  place_ship(board_size, board, ship_size, 5, 0, 7, 9);
  place_ship(board_size, board, ship_size, 7, 9, 5, 0);
  print_matrix(board_size, board);
}