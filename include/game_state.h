#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "cell.h"
#include "difficulty.h"

/**
 * @brief Representa os possíveis estados de uma partida.
 *
 * @note include/game_state.h
 */
typedef enum {
  GAME_RUNNING,
  GAME_WON,
  GAME_LOST
} game_status_t;

/**
 * @brief Armazena o estado completo de uma partida.
 *
 * Centraliza todas as informações necessárias para
 * execução da lógica do jogo, incluindo o tabuleiro,
 * estatísticas da partida e estado atual.
 *
 * @note include/game_state.h
 */
typedef struct {
  cell_t **cells;
  int32_t row_count;
  int32_t column_count;
  int32_t bomb_count;
  int32_t flag_count;
  bool first_click_done;
  game_status_t status;
  difficulty_t difficulty;
} game_state_t;