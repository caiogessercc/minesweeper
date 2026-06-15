#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Representa uma célula do tabuleiro do Minesweeper.
 *
 * @note include/cell.h
 */
typedef struct {
  bool has_bomb;
  bool is_revealed;
  bool is_flagged;
  uint8_t adjacent_bomb_count;
} cell_t;