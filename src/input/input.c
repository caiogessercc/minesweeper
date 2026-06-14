#include "input.h"

/**
 * @brief Inicializa o estado de entrada.
 *
 * @param input Estado da entrada.
 *
 * @note src/input/input.c
 */
void input_initialize(
  input_state_t *input
) {
  if (input == NULL) { return; }
  input->mouse_x = 0;
  input->mouse_y = 0;
  input->left_mouse_pressed = false;
  input->right_mouse_pressed = false;
  input->restart_requested = false;
  input->escape_pressed = false;
  input->quit_requested = false;
}

/**
 * @brief Processa os eventos da SDL.
 *
 * Atualiza o estado do mouse e da aplicação
 * com base nos eventos presentes na fila.
 *
 * @param input Estado da entrada.
 *
 * @note src/input/input.c
 */
void input_poll_events(
  input_state_t *input
) {
  if (input == NULL) { return; }
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        input->quit_requested = true;
        break;
      case SDL_MOUSEMOTION:
        input->mouse_x = event.motion.x;
        input->mouse_y = event.motion.y;
        break;
      case SDL_MOUSEBUTTONDOWN:
        input->mouse_x = event.button.x;
        input->mouse_y = event.button.y;
        if (event.button.button == SDL_BUTTON_LEFT) {
          input->left_mouse_pressed = true;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
          input->right_mouse_pressed = true;
        }
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_r:
            input->restart_requested = true;
            break;
          case SDLK_ESCAPE:
            input->escape_pressed = true;
            break;
          default:
            break;
        }
      break;
      default:
        break;
    }
  }
}

/**
 * @brief Limpa os estados de entrada.
 *
 * Reinicializa os eventos de clique processados
 * durante o frame atual.
 *
 * @param input Estado da entrada.
 *
 * @note src/input/input.c
 */
void input_clear(
  input_state_t *input
) {
  if (input == NULL) { return; }
  input->left_mouse_pressed = false;
  input->right_mouse_pressed = false;
  input->restart_requested = false;
  input->escape_pressed = false;
}