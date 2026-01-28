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
    return true;
  }

  if (x2 > max_xy2_value || y2 > max_xy2_value) {
    return true;
  }

  int x_len = (x2 - x1) + 1;
  int y_len = (y2 - y1) + 1;

  bool is_horizontal = (x_len == s_size && y_len == 1);
  bool is_vertical = (y_len == s_size && x_len == 1);

  bool is_diagonal = (x_len == s_size && y_len == s_size);

  if (!is_horizontal && !is_vertical && !is_diagonal) {
    return true;
  }

  return false;
}

void place_ship(int b_size, int board[b_size][b_size], int s_size, int x1,
                int x2, int y1, int y2) {

  if (is_invalid_ship_placement(b_size, s_size, x1, x2, y1, y2)) {
    return;
  }

  int x_len = (x2 - x1) + 1;
  int y_len = (y2 - y1) + 1;

  bool is_diagonal = (x_len == s_size && y_len == s_size);
  bool is_vertical = (y_len == s_size && x_len == 1);

  if (is_diagonal) {
    for (int i = 0; i < s_size; i++) {
      board[y1 + i][x1 + i] = 1;
    }
    return;
  }

  if (is_vertical) {
    for (int y = y1; y <= y2; y++) {
      board[y][x1] = 1;
    }
    return;
  }

  for (int x = x1; x <= x2; x++) {
    board[y1][x] = 1;
  }
};

int main() {
  int board_size = 10;
  int ship_size = 3;

  int board[board_size][board_size];
  init_matrix(board_size, board);

  place_ship(board_size, board, ship_size, 5, 5, 7, 9);
  place_ship(board_size, board, ship_size, 7, 9, 5, 5);
  place_ship(board_size, board, ship_size, 0, 2, 0, 2);
  place_ship(board_size, board, ship_size, 4, 6, 1, 3);

  print_matrix(board_size, board);
}