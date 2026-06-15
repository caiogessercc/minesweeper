#include <stdio.h>
#include "raylib.h"

#include "engine/timer.h"

/**
 * @brief Inicializa um cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note src/engine/timer.c
 */
void timer_initialize(
  timer_t *timer
) {
  if (timer == NULL) { return; }
  timer->start_time = 0.0;
  timer->elapsed_time = 0.0;
  timer->is_running = false;
}

/**
 * @brief Inicia a contagem do cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note src/engine/timer.c
 */
void timer_start(
  timer_t *timer
) {
  if (timer == NULL) { return; }
  timer->start_time = GetTime();
  timer->elapsed_time = 0.0;
  timer->is_running = true;
}

/**
 * @brief Reinicia o cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note src/engine/timer.c
 */
void timer_restart(
  timer_t *timer
) {
  if (timer == NULL) { return; }
  timer->start_time = GetTime();
  timer->elapsed_time = 0.0;
  timer->is_running = true;
}

/**
 * @brief Interrompe a contagem do cronômetro.
 *
 * @param timer Cronômetro.
 *
 * @note src/engine/timer.c
 */
void timer_stop(
  timer_t *timer
) {
  if (timer == NULL) { return; }
  timer_update(timer);
  timer->is_running = false;
}

/**
 * @brief Atualiza o cronômetro.
 *
 * Deve ser chamada uma vez por frame.
 *
 * @param timer Cronômetro.
 *
 * @note src/engine/timer.c
 */
void timer_update(
  timer_t *timer
) {
  if (timer == NULL) { return; }
  if (!timer->is_running) { return; }
  timer->elapsed_time = GetTime() - timer->start_time;
}

/**
 * @brief Obtém o tempo decorrido em segundos.
 *
 * @param timer Cronômetro.
 *
 * @return Tempo decorrido em segundos.
 *
 * @note src/engine/timer.c
 */
double timer_get_elapsed_time(
  const timer_t *timer
) {
  if (timer == NULL) { return 0.0; }
  return timer->elapsed_time;
}

/**
 * @brief Obtém o tempo decorrido formatado.
 *
 * @param timer Cronômetro.
 * @param buffer Buffer de saída.
 * @param buffer_size Tamanho do buffer.
 *
 * @note src/engine/timer.c
 */
void timer_format(
  const timer_t *timer,
  char *buffer,
  int32_t buffer_size
) {
  if (buffer == NULL || buffer_size <= 0) { return; }
  if (timer == NULL) {
    snprintf(
      buffer,
      (size_t)buffer_size,
      "00:00"
    );
    return;
  }

  int32_t total_seconds = (int32_t)timer->elapsed_time;
  int32_t minutes = total_seconds / 60;
  int32_t seconds = total_seconds % 60;

  snprintf(
    buffer,
    (size_t)buffer_size,
    "%02d:%02d",
    minutes,
    seconds
  );
}