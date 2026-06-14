#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

/**
 * @brief Armazena o estado atual dos dispositivos de entrada.
 *
 * Centraliza as informações capturadas dos eventos SDL,
 * incluindo posição do cursor, cliques do mouse e
 * solicitações de encerramento da aplicação.
 *
 * @note include/input.h
 */
typedef struct {
  int32_t mouse_x;
  int32_t mouse_y;
  bool left_mouse_pressed;
  bool right_mouse_pressed;
  bool restart_requested;
  bool escape_pressed;
  bool quit_requested;
} input_state_t;

/**
 * @brief Inicializa o estado de entrada.
 *
 * @param input Estado da entrada a ser inicializado.
 *
 * @note include/input.h
 */
void input_initialize(
  input_state_t *input
);

/**
 * @brief Processa eventos SDL e atualiza o estado da entrada.
 *
 * Consome os eventos presentes na fila da SDL e
 * atualiza o estado do mouse e da aplicação.
 *
 * @param input Estado da entrada a ser atualizado.
 *
 * @note include/input.h
 */
void input_poll_events(
  input_state_t *input
);

/**
 * @brief Limpa os eventos do frame atual.
 *
 * @param input Estado da entrada.
 *
 * @note include/input.h
 */
void input_clear(
  input_state_t *input
);