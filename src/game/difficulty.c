#include "game/difficulty.h"

/**
 * @brief Tabela estática contendo as configurações para cada nível de dificuldade.
 *
 * Estas configurações definem o tamanho do tabuleiro e a quantidade de bombas
 * para cada um dos 6 modos de jogo suportados.
 *
 * @note src/game/difficulty.c
 */
static const difficulty_config_t difficulty_configs[] = {
  {
    .difficulty = DIFFICULTY_BEGINNER,
    .name = "Beginner",
    .row_count = 8,
    .column_count = 8,
    .bomb_count = 12
  },
  {
    .difficulty = DIFFICULTY_EASY,
    .name = "Easy",
    .row_count = 10,
    .column_count = 10,
    .bomb_count = 10
  },
  {
    .difficulty = DIFFICULTY_MEDIUM,
    .name = "Medium",
    .row_count = 16,
    .column_count = 16,
    .bomb_count = 40
  },
  {
    .difficulty = DIFFICULTY_HARD,
    .name = "Hard",
    .row_count = 20,
    .column_count = 20,
    .bomb_count = 100
  },
  {
    .difficulty = DIFFICULTY_HUGE,
    .name = "Huge",
    .row_count = 32,
    .column_count = 32,
    .bomb_count = 220
  },
  {
    .difficulty = DIFFICULTY_EXTREME,
    .name = "Extreme",
    .row_count = 16,
    .column_count = 30,
    .bomb_count = 280
  }
};

/**
 * @brief Obtém a configuração associada a uma dificuldade.
 *
 * Caso uma dificuldade inválida seja fornecida, retorna por padrão
 * a configuração correspondente ao modo DIFFICULTY_BEGINNER.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Configuração correspondente.
 *
 * @note src/game/difficulty.c
 */
difficulty_config_t difficulty_get_config(
  difficulty_t difficulty
) {
  if (difficulty < DIFFICULTY_BEGINNER || difficulty > DIFFICULTY_EXTREME) {
    return difficulty_configs[DIFFICULTY_BEGINNER];
  }
  return difficulty_configs[difficulty];
}

/**
 * @brief Obtém o nome textual de uma dificuldade.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Ponteiro para a string constante contendo o nome.
 *
 * @note src/game/difficulty.c
 */
const char *difficulty_get_name(
  difficulty_t difficulty
) {
  if (difficulty < DIFFICULTY_BEGINNER || difficulty > DIFFICULTY_EXTREME) {
    return difficulty_configs[DIFFICULTY_BEGINNER].name;
  }
  return difficulty_configs[difficulty].name;
}