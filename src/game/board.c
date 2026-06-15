#include <stdlib.h>
#include <stdbool.h>

#include "game/board.h"
#include "game/difficulty.h"

static bool board_is_valid_position(
  const game_state_t *game,
  int row,
  int column
);

static bool board_is_safe_zone(
  int row,
  int column,
  int safe_row,
  int safe_column
);

static int board_count_adjacent_bombs(
  const game_state_t *game,
  int row,
  int column
);

static void board_flood_fill(
  game_state_t *game,
  int row,
  int column
);

/**
 * @brief Verifica se uma posição pertence aos limites do tabuleiro.
 *
 * @note src/game/board.c
 */
static bool board_is_valid_position(
  const game_state_t *game,
  int row,
  int column
) {
  if (game == NULL) { return false; }

  return (
    row >= 0 &&
    row < game->row_count &&
    column >= 0 &&
    column < game->column_count
  );
}

/**
 * @brief Verifica se uma posição pertence à área segura inicial.
 *
 * @note src/game/board.c
 */
static bool board_is_safe_zone(
  int row,
  int column,
  int safe_row,
  int safe_column
) {
  return (
    row >= safe_row - 1 &&
    row <= safe_row + 1 &&
    column >= safe_column - 1 &&
    column <= safe_column + 1
  );
}

/**
 * @brief Conta as bombas adjacentes de uma célula.
 *
 * @note src/game/board.c
 */
static int board_count_adjacent_bombs(
  const game_state_t *game,
  int row,
  int column
) {
  if (game == NULL) { return 0; }

  int count = 0;
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (x == 0 && y == 0) { continue; }

      int neighbor_row = row + y;
      int neighbor_column = column + x;

      if (
        board_is_valid_position(
          game,
          neighbor_row,
          neighbor_column
        ) &&
        game->cells[neighbor_row][neighbor_column].has_bomb
      ) { count++; }
    }
  }

  return count;
}

/**
 * @brief Revela recursivamente células adjacentes.
 *
 * @note src/game/board.c
 */
static void board_flood_fill(
  game_state_t *game,
  int row,
  int column
) {
  if (game == NULL) { return; }

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      int neighbor_row = row + y;
      int neighbor_column = column + x;

      if (!board_is_valid_position( game, neighbor_row, neighbor_column )) { continue; }

      cell_t *neighbor = &game->cells[neighbor_row][neighbor_column];
      if (neighbor->is_revealed || neighbor->is_flagged || neighbor->has_bomb) { continue; }

      neighbor->is_revealed = true;
      if (neighbor->adjacent_bomb_count == 0) {
        board_flood_fill(game, neighbor_row, neighbor_column);
      }
    }
  }
}

/**
 * @brief Inicializa uma partida.
 *
 * @note src/game/board.c
 */
bool board_initialize(
  game_state_t *game
) {
  if (game == NULL) { return false; }

  difficulty_config_t config =
    difficulty_get_config(
      game->difficulty
    );

  game->row_count = config.row_count;
  game->column_count = config.column_count;
  game->bomb_count = config.bomb_count;
  game->flag_count = 0;
  game->first_click_done = false;
  game->status = GAME_RUNNING;

  game->cells =
    malloc(
      game->row_count *
      sizeof(cell_t *)
    );

  if (game->cells == NULL) { return false; }

  for (int row = 0; row < game->row_count; row++) {
    game->cells[row] =
      calloc(
        game->column_count,
        sizeof(cell_t)
      );

    if (game->cells[row] == NULL) {
      for (int allocated_row = 0; allocated_row < row; allocated_row++) {
        free(game->cells[allocated_row]);
      }

      free( game->cells);
      game->cells = NULL;

      return false;
    }
  }

  return true;
}

/**
 * @brief Libera os recursos utilizados pela partida.
 *
 * @note src/game/board.c
 */
void board_destroy(
  game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return; }
  for (int row = 0; row < game->row_count; row++) {
    free(game->cells[row]);
  }

  free(game->cells);

  game->cells = NULL;
  game->row_count = 0;
  game->column_count = 0;
  game->bomb_count = 0;
  game->flag_count = 0;
  game->first_click_done = false;
  game->status = GAME_RUNNING;
}

/**
 * @brief Gera bombas preservando a área segura.
 *
 * @note src/game/board.c
 */
void board_generate_bombs(
  game_state_t *game,
  int safe_row,
  int safe_column
) {
  if (game == NULL || game->cells == NULL) { return; }

  int planted_bombs = 0;
  while (planted_bombs < game->bomb_count) {
    int row = rand() % game->row_count;
    int column = rand() % game->column_count;

    if (board_is_safe_zone(row, column, safe_row, safe_column)) {continue; }
    if (game->cells[row][column].has_bomb) { continue; }

    game->cells[row][column].has_bomb = true;
    planted_bombs++;
  }
}

/**
 * @brief Calcula bombas adjacentes.
 *
 * @note src/game/board.c
 */
void board_calculate_adjacent_bombs(
  game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return; }

  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      if (!game->cells[row][column].has_bomb) {
        game->cells[row][column].adjacent_bomb_count =
            board_count_adjacent_bombs(game, row, column);
      }
    }
  }
}

/**
 * @brief Verifica condição de vitória.
 *
 * @note src/game/board.c
 */
bool board_check_victory(
  const game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return false; }

  int total_safe_cells = (game->row_count * game->column_count) - game->bomb_count;
  int revealed_safe_cells = 0;

  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      const cell_t *cell = &game->cells[row][column];
      if (cell->is_revealed && !cell->has_bomb) { revealed_safe_cells++; }
    }
  }

  return (revealed_safe_cells == total_safe_cells);
}

/**
 * @brief Revela uma célula.
 *
 * @note src/game/board.c
 */
void board_reveal_cell(
  game_state_t *game,
  int row,
  int column
) {
  if (game == NULL || game->status != GAME_RUNNING) { return; }
  if (!board_is_valid_position(game, row, column)) { return; }

  cell_t *cell = &game->cells[row][column];

  if (cell->is_revealed || cell->is_flagged) { return; }
  if (!game->first_click_done) {
    game->first_click_done = true;
    board_generate_bombs(game, row, column);
    board_calculate_adjacent_bombs(game);
  }

  cell->is_revealed = true;

  if (cell->has_bomb) {
    game->status = GAME_LOST;
    board_reveal_all_bombs(game);

    return;
  }

  if (cell->adjacent_bomb_count == 0) {
    board_flood_fill(game, row, column);
  }

  if (board_check_victory(game)) {
    game->status = GAME_WON;
  }
}

/**
 * @brief Alterna o estado da bandeira.
 *
 * @note src/game/board.c
 */
void board_toggle_flag(
  game_state_t *game,
  int row,
  int column
) {
  if ( game == NULL || game->status != GAME_RUNNING) { return; }
  if (!board_is_valid_position(game, row, column)) { return; }

  cell_t *cell = &game->cells[row][column];
  if (cell->is_revealed) { return; }

  if (cell->is_flagged) {
    cell->is_flagged = false;
    game->flag_count--;
  } else {
    cell->is_flagged = true;
    game->flag_count++;
  }
}

/**
 * @brief Revela todas as bombas.
 *
 * @note src/game/board.c
 */
void board_reveal_all_bombs(
  game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return; }

  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      if (game->cells[row][column].has_bomb) {
        game->cells[row][column].is_revealed = true;
      }
    }
  }
}

/**
 * @brief Verifica se a partida terminou.
 *
 * @note src/game/board.c
 */
bool board_is_finished(
  const game_state_t *game
) {
  if (game == NULL) { return true; }
  return (
    game->status == GAME_WON ||
    game->status == GAME_LOST
  );
}