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
      board[y1 + i][x1 + i] = 3;
    }
    return;
  }

  if (is_vertical) {
    for (int y = y1; y <= y2; y++) {
      board[y][x1] = 3;
    }
    return;
  }

  for (int x = x1; x <= x2; x++) {
    board[y1][x] = 3;
  }
};

void use_cone_ability(int b_size, int board[b_size][b_size], int h_size,
                      int tip_x, int tip_y) {
  if (h_size % 2 == 0)
    return;

  for (int row = 0; row < h_size; row++) {
    int start_x = tip_x - row;

    for (int col = 0; col < row * 2 + 1; col++) {
      int curr_x = start_x + col;
      int curr_y = tip_y + row;

      if (curr_x >= 0 && curr_x < b_size && curr_y >= 0 && curr_y < b_size) {
        board[curr_y][curr_x] = board[curr_y][curr_x] == 3 ? 5 : 1;
      }
    }
  }
}

void use_cross_ability(int b_size, int board[b_size][b_size], int h_size,
                       int center_x, int center_y) {
  if (h_size % 2 == 0)
    return;

  int radius = h_size / 2;

  for (int i = -radius; i <= radius; i++) {
    int curr_y = center_y + i;
    if (curr_y >= 0 && curr_y < b_size && center_x >= 0 && center_x < b_size) {
      board[curr_y][center_x] = board[curr_y][center_x] == 3 ? 5 : 1;
    }
  }

  for (int i = -radius; i <= radius; i++) {
    int curr_x = center_x + i;
    if (curr_x >= 0 && curr_x < b_size && center_y >= 0 && center_y < b_size) {
      board[center_y][curr_x] = board[center_y][curr_x] == 3 ? 5 : 1;
    }
  }
}

void use_octahedron_ability(int b_size, int board[b_size][b_size], int h_size,
                            int center_x, int center_y) {
  if (h_size % 2 == 0)
    return;

  int radius = h_size / 2;

  for (int row = -radius; row <= radius; row++) {
    int width = radius - (row < 0 ? -row : row);

    for (int col = -width; col <= width; col++) {
      int curr_x = center_x + col;
      int curr_y = center_y + row;

      if (curr_x >= 0 && curr_x < b_size && curr_y >= 0 && curr_y < b_size) {
        board[curr_y][curr_x] = board[curr_y][curr_x] == 3 ? 5 : 1;
      }
    }
  }
}

int main() {
  int board_size = 10;
  int ship_size = 3;

  int board[board_size][board_size];
  init_matrix(board_size, board);

  printf("Cone\n");
  place_ship(board_size, board, ship_size, 5, 5, 7, 9);
  place_ship(board_size, board, ship_size, 7, 9, 5, 5);
  place_ship(board_size, board, ship_size, 0, 2, 0, 2);
  place_ship(board_size, board, ship_size, 4, 6, 1, 3);

  use_cone_ability(board_size, board, 3, 5, 2);
  print_matrix(board_size, board);

  printf("\nCruz\n");
  int board1[board_size][board_size];
  init_matrix(board_size, board1);
  place_ship(board_size, board1, ship_size, 5, 5, 7, 9);
  place_ship(board_size, board1, ship_size, 7, 9, 5, 5);
  place_ship(board_size, board1, ship_size, 0, 2, 0, 2);
  place_ship(board_size, board1, ship_size, 4, 6, 1, 3);
  use_cross_ability(board_size, board1, 5, 5, 5);
  print_matrix(board_size, board1);

  printf("\nOcta\n");
  int board2[board_size][board_size];
  init_matrix(board_size, board2);
  place_ship(board_size, board2, ship_size, 5, 5, 7, 9);
  place_ship(board_size, board2, ship_size, 7, 9, 5, 5);
  place_ship(board_size, board2, ship_size, 0, 2, 0, 2);
  place_ship(board_size, board2, ship_size, 4, 6, 1, 3);

  use_octahedron_ability(board_size, board2, 5, 3, 3);
  print_matrix(board_size, board2);
}
