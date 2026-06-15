#pragma once

/**
 * @brief Estados possíveis de uma partida.
 *
 * @note include/game/game_status.h
 */
typedef enum {
  GAME_RUNNING = 0,
  GAME_WON,
  GAME_LOST
} game_status_t;