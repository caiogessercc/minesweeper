#include <stddef.h>
#include "raylib.h"

#include "engine/input.h"

/**
 * @brief Inicializa o estado de entrada.
 *
 * @param input Estado da entrada.
 *
 * @note src/engine/input.c
 */
void input_initialize(
  input_state_t *input
) {
  if (input == NULL) { return; }
  input->mouse_x = 0;
  input->mouse_y = 0;
  input->left_mouse_pressed = false;
  input->right_mouse_pressed = false;
  input->escape_pressed = false;
  input->restart_requested = false;
  input->confirm_pressed = false;
  input->back_pressed = false;
  input->quit_requested = false;
}

/**
 * @brief Atualiza o estado da entrada.
 *
 * Coleta os eventos do frame atual
 * utilizando a API da Raylib.
 *
 * @param input Estado da entrada.
 *
 * @note src/engine/input.c
 */
void input_update(
  input_state_t *input
) {
  if (input == NULL) { return; }
  Vector2 mouse_position = GetMousePosition();

  input->mouse_x = (int32_t)mouse_position.x;
  input->mouse_y = (int32_t)mouse_position.y;
  input->left_mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  input->right_mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
  input->escape_pressed = IsKeyPressed(KEY_ESCAPE);
  input->restart_requested = IsKeyPressed(KEY_R);
  input->confirm_pressed = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE);
  input->back_pressed = IsKeyPressed(KEY_BACKSPACE);
  input->quit_requested = WindowShouldClose();
}

/**
 * @brief Limpa eventos instantâneos do frame.
 *
 * @param input Estado da entrada.
 *
 * @note src/engine/input.c
 */
void input_clear(
  input_state_t *input
) {
  if (input == NULL) { return; }
  input->left_mouse_pressed = false;
  input->right_mouse_pressed = false;
  input->escape_pressed = false;
  input->restart_requested = false;
  input->confirm_pressed = false;
  input->back_pressed = false;
  input->quit_requested = false;
}