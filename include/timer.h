#pragma once

#include <stdint.h>

/**
 * @brief Responsável por controlar o tempo de uma partida.
 *
 * Armazena o instante inicial da partida e
 * calcula o tempo decorrido em segundos.
 *
 * @note include/timer.h
 */
typedef struct {
  uint32_t start_ticks;
} game_timer_t;

/**
 * @brief Inicializa o cronômetro.
 *
 * @param timer Cronômetro da partida.
 *
 * @note include/timer.h
 */
void timer_start(
  game_timer_t *timer
);

/**
 * @brief Reinicia o cronômetro.
 *
 * @param timer Cronômetro da partida.
 *
 * @note include/timer.h
 */
void timer_reset(
  game_timer_t *timer
);

/**
 * @brief Obtém o tempo decorrido em segundos.
 *
 * @param timer Cronômetro da partida.
 *
 * @return Quantidade de segundos decorridos.
 *
 * @note include/timer.h
 */
uint32_t timer_get_elapsed_seconds(
  const game_timer_t *timer
);