#pragma once

/**
 * @brief Estados possíveis da aplicação.
 *
 * Controla o fluxo principal entre menus,
 * partida e encerramento da aplicação.
 *
 * @note include/app/app_state.h
 */
typedef enum {
  APP_STATE_MENU = 0,
  APP_STATE_PLAYING,
  APP_STATE_GAME_WON,
  APP_STATE_GAME_LOST,
  APP_STATE_EXIT
} app_state_t;