#pragma once

#include <stdint.h>

/**
 * @brief Níveis de dificuldade disponíveis.
 *
 * Define os modos de jogo suportados pela
 * aplicação.
 *
 * @note include/game/difficulty.h
 */
typedef enum {
  DIFFICULTY_BEGINNER = 0,
  DIFFICULTY_EASY,
  DIFFICULTY_MEDIUM,
  DIFFICULTY_HARD,
  DIFFICULTY_HUGE,
  DIFFICULTY_EXTREME
} difficulty_t;

/**
 * @brief Configuração de uma dificuldade.
 *
 * Armazena os parâmetros necessários para
 * criação de uma partida.
 *
 * @note include/game/difficulty.h
 */
typedef struct {
  difficulty_t difficulty;
  const char *name;
  int32_t row_count;
  int32_t column_count;
  int32_t bomb_count;
} difficulty_config_t;

/**
 * @brief Obtém a configuração associada a uma dificuldade.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Configuração correspondente.
 *
 * @note include/game/difficulty.h
 */
difficulty_config_t difficulty_get_config(
  difficulty_t difficulty
);

/**
 * @brief Obtém o nome textual de uma dificuldade.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Nome da dificuldade.
 *
 * @note include/game/difficulty.h
 */
const char *difficulty_get_name(
  difficulty_t difficulty
);