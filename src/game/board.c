#include <stdlib.h>
#include <time.h>

#include "board.h"

/**
 * @brief Verifica se uma posição pertence aos limites do tabuleiro.
 *
 * @note src/game/board.c
 */
static bool board_is_valid_position(
  const game_state_t *game,
  int row,
  int column
);

/**
 * @brief Conta as bombas adjacentes de uma célula.
 *
 * @note src/game/board.c
 */
static int board_count_adjacent_bombs(
  const game_state_t *game,
  int row,
  int column
);

/**
 * @brief Revela recursivamente células adjacentes sem bombas.
 * 
 * @note src/game/board.c
 */
static void board_flood_fill(
  game_state_t *game,
  int row,
  int column
);

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
);

/**
 * @brief Inicializa o tabuleiro da partida.
 *
 * @param game Estado do jogo.
 * @param config Configuração da dificuldade.
 *
 * @return true Se a inicialização foi concluída com sucesso.
 * @return false Se ocorreu falha durante a alocação.
 *
 * @note src/game/board.c
 */
bool board_initialize(
  game_state_t *game,
  const difficulty_config_t *config
) {
  if (game == NULL || config == NULL) { return false; }

  game->row_count = config->row_count;
  game->column_count = config->column_count;
  game->bomb_count = config->bomb_count;
  game->flag_count = 0;
  game->first_click_done = false;
  game->status = GAME_RUNNING;
  game->difficulty = config->difficulty;

  game->cells = calloc(
    game->row_count,
    sizeof(cell_t *)
  );

  if (game->cells == NULL) { return false; }

  for (int row = 0; row < game->row_count; row++) {
    game->cells[row] = calloc(
      game->column_count,
      sizeof(cell_t)
    );

    if (game->cells[row] == NULL) {
      board_destroy(game);
      return false;
    }
  }

  return true;
}

/**
 * @brief Libera os recursos alocados pelo tabuleiro.
 *
 * @param game Estado do jogo.
 *
 * @note src/game/board.c
 */
void board_destroy(
  game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return; }
  for (int row = 0; row < game->row_count; row++) { free(game->cells[row]); }
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
 * @brief Distribui bombas preservando uma área segura.
 *
 * @param game Estado do jogo.
 * @param safe_row Linha segura.
 * @param safe_column Coluna segura.
 *
 * @note src/game/board.c
 */
void board_generate_bombs_safe(
  game_state_t *game,
  int safe_row,
  int safe_column
) {
  if (game == NULL || game->cells == NULL) { return; }

  static bool seed_initialized = false;

  if (!seed_initialized) {
    srand((unsigned int)time(NULL));
    seed_initialized = true;
  }

  int available_cells = game->row_count * game->column_count;

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      int row = safe_row + y;
      int column = safe_column + x;
      if (board_is_valid_position(game, row, column)) { available_cells--; }
    }
  }

  if (game->bomb_count > available_cells) {
    game->status = GAME_LOST;
    return;
  }

  int placed_bombs = 0;

  while (placed_bombs < game->bomb_count) {
    int row = rand() % game->row_count;
    int column = rand() % game->column_count;

    if (board_is_safe_zone(row, column, safe_row, safe_column)) { continue; }
    if (game->cells[row][column].has_bomb) { continue; }

    game->cells[row][column].has_bomb = true;
    placed_bombs++;
  }
}

/**
 * @brief Calcula o número de bombas adjacentes para cada célula.
 *
 * @param game Estado do jogo.
 *
 * @note src/game/board.c
 */
void board_calculate_adjacent_bombs(
  game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return; }
  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      cell_t *cell = &game->cells[row][column];

      if (cell->has_bomb) { continue; }

      cell->adjacent_bomb_count =
        (uint8_t)board_count_adjacent_bombs(
          game,
          row,
          column
        );
    }
  }
}

/**
 * @brief Revela uma célula do tabuleiro.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha.
 * @param column Índice da coluna.
 *
 * @note src/game/board.c
 */
void board_reveal_cell(
  game_state_t *game,
  int row,
  int column
) {
  if (game->status != GAME_RUNNING) { return; }
  if (!board_is_valid_position(game, row, column)) { return; }

  if (!game->first_click_done) {
    board_generate_bombs_safe(game, row, column);
    board_calculate_adjacent_bombs(game);
    game->first_click_done = true;
  }

  cell_t *cell = &game->cells[row][column];

  if (cell->is_revealed) { return; }
  if (cell->is_flagged) { return; }

  cell->is_revealed = true;

  if (cell->has_bomb) {
    board_reveal_all_bombs(game);
    game->status = GAME_LOST;
  
    return;
  }

  if (cell->adjacent_bomb_count == 0) {
    board_flood_fill(game, row, column);
  }

  if (board_check_victory(game)) { game->status = GAME_WON; }
}

/**
 * @brief Alterna o estado de bandeira de uma célula.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha.
 * @param column Índice da coluna.
 *
 * @note src/game/board.c
 */
void board_toggle_flag(
  game_state_t *game,
  int row,
  int column
) {
  if (game->status != GAME_RUNNING) { return; }
  if (!board_is_valid_position(game, row, column)) { return; }
  cell_t *cell = &game->cells[row][column];

  if (cell->is_revealed) { return; }
  cell->is_flagged = !cell->is_flagged;

  if (cell->is_flagged) {
    game->flag_count++;
  } else {
    game->flag_count--;
  }
}

/**
 * @brief Revela todas as bombas do tabuleiro.
 *
 * @param game Estado do jogo.
 *
 * @note src/game/board.c
 */
void board_reveal_all_bombs(
  game_state_t *game
) {
  if (game == NULL) { return; }

  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      if (game->cells[row][column].has_bomb) {
        game->cells[row][column].is_revealed = true;
      }
    }
  }
}

/**
 * @brief Verifica se a condição de vitória foi atingida.
 *
 * @param game Estado do jogo.
 *
 * @return true Se o jogador venceu.
 * @return false Caso contrário.
 *
 * @note src/game/board.c
 */
bool board_check_victory(
  const game_state_t *game
) {
  if (game == NULL || game->cells == NULL) { return false; }

  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      const cell_t *cell = &game->cells[row][column];
      if (!cell->has_bomb && !cell->is_revealed) { return false; }
    }
  }

  return true;
}

/**
 * @brief Verifica se a partida terminou.
 *
 * @param game Estado do jogo.
 *
 * @return true Se a partida terminou.
 * @return false Se a partida continua em andamento.
 *
 * @note src/game/board.c
 */
bool board_is_game_over(
  const game_state_t *game
) {
  if (game == NULL) { return true; }
  return game->status != GAME_RUNNING;
}

/**
 * @brief Verifica se uma posição é válida dentro do tabuleiro.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha.
 * @param column Índice da coluna.
 *
 * @return true Se a posição for válida.
 * @return false Caso contrário.
 *
 * @note src/game/board.c
 */
static bool board_is_valid_position(
  const game_state_t *game,
  int row,
  int column
) {
  if (game == NULL) { return false; }
  return  row >= 0 &&
          row < game->row_count &&
          column >= 0 &&
          column < game->column_count;
}

/**
 * @brief Conta a quantidade de bombas adjacentes a uma célula.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha da célula.
 * @param column Índice da coluna da célula.
 *
 * @return Quantidade de bombas adjacentes.
 *
 * @note src/game/board.c
 */
static int board_count_adjacent_bombs(
  const game_state_t *game,
  int row,
  int column
) {
  int bomb_count = 0;

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (x == 0 && y == 0) { continue; }

      int neighbor_row = row + y;
      int neighbor_column = column + x;

      if (!board_is_valid_position(game, neighbor_row, neighbor_column)) { continue; }
      if (game->cells[neighbor_row][neighbor_column].has_bomb) { bomb_count++; }
    }
  }

  return bomb_count;
}

/**
 * @brief Revela recursivamente células vazias adjacentes.
 *
 * Utilizado para expandir regiões sem bombas
 * próximas quando uma célula com valor zero
 * é revelada.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha inicial.
 * @param column Índice da coluna inicial.
 *
 * @note src/game/board.c
 */
static void board_flood_fill(
  game_state_t *game,
  int row,
  int column
) {
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      int neighbor_row = row + y;
      int neighbor_column = column + x;

      if (!board_is_valid_position(game, neighbor_row, neighbor_column)) { continue; }
      cell_t *neighbor = &game->cells[neighbor_row][neighbor_column];
      if (neighbor->is_revealed || neighbor->is_flagged || neighbor->has_bomb) { continue; }
      neighbor->is_revealed = true;
      if (neighbor->adjacent_bomb_count == 0) {
        board_flood_fill(
          game,
          neighbor_row,
          neighbor_column
        );
      }
    }
  }
}

/**
 * @brief Verifica se uma posição pertence à área segura inicial.
 *
 * @param row Linha analisada.
 * @param column Coluna analisada.
 * @param safe_row Linha segura.
 * @param safe_column Coluna segura.
 *
 * @return true Se a posição estiver na área protegida.
 * @return false Caso contrário.
 *
 * @note src/game/board.c
 */
static bool board_is_safe_zone(
  int row,
  int column,
  int safe_row,
  int safe_column
) {
  return
    abs(row - safe_row) <= 1 &&
    abs(column - safe_column) <= 1;
}