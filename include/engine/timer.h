#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Representa um cronômetro.
 *
 * Armazena informações de tempo utilizadas
 * pela aplicação ou por sistemas específicos.
 *
 * @note include/engine/timer.h
 */
typedef struct {
  double start_time;
  double elapsed_time;
  bool is_running;
} timer_t;

/**
 * @brief Inicializa um cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note include/engine/timer.h
 */
void timer_initialize(
  timer_t *timer
);

/**
 * @brief Inicia a contagem do cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note include/engine/timer.h
 */
void timer_start(
  timer_t *timer
);

/**
 * @brief Reinicia o cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note include/engine/timer.h
 */
void timer_restart(
  timer_t *timer
);

/**
 * @brief Interrompe a contagem do cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note include/engine/timer.h
 */
void timer_stop(
  timer_t *timer
);

/**
 * @brief Atualiza o cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note include/engine/timer.h
 */
void timer_update(
  timer_t *timer
);

/**
 * @brief Obtém o tempo decorrido em segundos.
 *
 * @param timer Cronômetro.
 *
 * @return Tempo decorrido em segundos.
 *
 * @note include/engine/timer.h
 */
double timer_get_elapsed_time(
  const timer_t *timer
);

/**
 * @brief Obtém o tempo decorrido formatado.
 *
 * @param timer Cronômetro.
 * @param buffer Buffer de saída.
 * @param buffer_size Tamanho do buffer.
 *
 * @note include/engine/timer.h
 */
void timer_format(
  const timer_t *timer,
  char *buffer,
  int32_t buffer_size
);