#pragma once

#include <stdbool.h>

#include "game/game_state.h"

/**
 * @brief Inicializa uma partida.
 *
 * Aloca e prepara todas as células do
 * tabuleiro de acordo com a dificuldade
 * configurada.
 *
 * @param game Estado da partida.
 *
 * @return true Se a inicialização foi concluída.
 * @return false Caso contrário.
 *
 * @note include/game/board.h
 */
bool board_initialize(
  game_state_t *game
);

/**
 * @brief Libera os recursos utilizados pela partida.
 *
 * @param game Estado da partida.
 *
 * @note include/game/board.h
 */
void board_destroy(
  game_state_t *game
);

/**
 * @brief Gera bombas preservando uma área segura.
 *
 * @param game Estado da partida.
 * @param safe_row Linha segura.
 * @param safe_column Coluna segura.
 *
 * @note include/game/board.h
 */
void board_generate_bombs(
  game_state_t *game,
  int safe_row,
  int safe_column
);

/**
 * @brief Calcula a quantidade de bombas adjacentes.
 *
 * @param game Estado da partida.
 *
 * @note include/game/board.h
 */
void board_calculate_adjacent_bombs(
  game_state_t *game
);

/**
 * @brief Revela uma célula.
 *
 * @param game Estado da partida.
 * @param row Linha da célula.
 * @param column Coluna da célula.
 *
 * @note include/game/board.h
 */
void board_reveal_cell(
  game_state_t *game,
  int row,
  int column
);

/**
 * @brief Alterna o estado de bandeira de uma célula.
 *
 * @param game Estado da partida.
 * @param row Linha da célula.
 * @param column Coluna da célula.
 *
 * @note include/game/board.h
 */
void board_toggle_flag(
  game_state_t *game,
  int row,
  int column
);

/**
 * @brief Revela todas as bombas do tabuleiro.
 *
 * @param game Estado da partida.
 *
 * @note include/game/board.h
 */
void board_reveal_all_bombs(
  game_state_t *game
);

/**
 * @brief Verifica condição de vitória.
 *
 * @param game Estado da partida.
 *
 * @return true Se o jogador venceu.
 * @return false Caso contrário.
 *
 * @note include/game/board.h
 */
bool board_check_victory(
  const game_state_t *game
);

/**
 * @brief Verifica se a partida terminou.
 *
 * @param game Estado da partida.
 *
 * @return true Se a partida terminou.
 * @return false Caso contrário.
 *
 * @note include/game/board.h
 */
bool board_is_finished(
  const game_state_t *game
);