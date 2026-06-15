#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Estado atual da entrada do usuário.
 *
 * Centraliza os eventos de mouse e teclado
 * utilizados pela aplicação.
 *
 * @note include/engine/input.h
 */
typedef struct {
  int32_t mouse_x;
  int32_t mouse_y;
  bool left_mouse_pressed;
  bool right_mouse_pressed;
  bool escape_pressed;
  bool restart_requested;
  bool confirm_pressed;
  bool back_pressed;
  bool quit_requested;
} input_state_t;

/**
 * @brief Inicializa o estado de entrada.
 *
 * @param input Estado da entrada.
 *
 * @note include/engine/input.h
 */
void input_initialize(
  input_state_t *input
);

/**
 * @brief Atualiza o estado da entrada.
 *
 * @param input Estado da entrada.
 *
 * @note include/engine/input.h
 */
void input_update(
  input_state_t *input
);

/**
 * @brief Limpa eventos instantâneos do frame.
 *
 * @param input Estado da entrada.
 *
 * @note include/engine/input.h
 */
void input_clear(
  input_state_t *input
);