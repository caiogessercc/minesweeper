#include <SDL2/SDL.h>

#include "timer.h"

/**
 * @brief Inicializa o cronômetro.
 *
 * @param timer Cronômetro da partida.
 *
 * @note src/game/timer.c
 */
void timer_start(
  game_timer_t *timer
) {
  if (timer == NULL) { return; }
  timer->start_ticks = SDL_GetTicks();
}

/**
 * @brief Reinicia o cronômetro.
 *
 * @param timer Cronômetro da partida.
 *
 * @note src/game/timer.c
 */
void timer_reset(
  game_timer_t *timer
) {
  if (timer == NULL) { return; }
  timer->start_ticks = SDL_GetTicks();
}

/**
 * @brief Obtém o tempo decorrido em segundos.
 *
 * @param timer Cronômetro da partida.
 *
 * @return Quantidade de segundos decorridos.
 *
 * @note src/game/timer.c
 */
uint32_t timer_get_elapsed_seconds(
  const game_timer_t *timer
) {
  if (timer == NULL) { return 0; }
  return (SDL_GetTicks() - timer->start_ticks) / 1000;
}