#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "game/cell.h"
#include "game/difficulty.h"
#include "game/game_status.h"

/**
 * @brief Representa o estado completo de uma partida.
 *
 * Armazena todas as informações necessárias para
 * execução das regras do jogo, sem dependência
 * de interface gráfica ou plataforma.
 *
 * @note include/game/game_state.h
 */
typedef struct {
  cell_t **cells;
  int32_t row_count;
  int32_t column_count;
  int32_t bomb_count;
  int32_t flag_count;
  bool first_click_done;
  difficulty_t difficulty;
  game_status_t status;
} game_state_t;