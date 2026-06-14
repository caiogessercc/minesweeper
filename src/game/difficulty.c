#include <stdio.h>

#include "difficulty.h"

/**
 * @brief Configurações disponíveis de dificuldade.
 *
 * Contém os parâmetros utilizados para inicializar
 * cada nível de dificuldade do jogo.
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
  }, // 18%
  {
    .difficulty = DIFFICULTY_EASY,
    .name = "Easy",
    .row_count = 10,
    .column_count = 10,
    .bomb_count = 10
  }, // 10%
  {
    .difficulty = DIFFICULTY_MEDIUM,
    .name = "Medium",
    .row_count = 16,
    .column_count = 16,
    .bomb_count = 40
  }, // 15%
  {
    .difficulty = DIFFICULTY_HARD,
    .name = "Hard",
    .row_count = 20,
    .column_count = 20,
    .bomb_count = 100
  }, // 25%
  {
    .difficulty = DIFFICULTY_HUGE,
    .name = "Huge",
    .row_count = 30,
    .column_count = 30,
    .bomb_count = 220
  }, // 24%
  {
    .difficulty = DIFFICULTY_EXTREME,
    .name = "Extreme",
    .row_count = 16,
    .column_count = 30,
    .bomb_count = 280
  } // 58%
};

/**
 * @brief Obtém a configuração associada a uma dificuldade.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Configuração correspondente à dificuldade informada.
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
 * @brief Solicita ao usuário a seleção de uma dificuldade.
 *
 * Exibe as dificuldades disponíveis e retorna
 * a opção escolhida pelo usuário.
 *
 * @return Dificuldade selecionada.
 *
 * @note src/game/difficulty.c
 */
difficulty_t difficulty_select(void) {
  int32_t option = 0;

  printf("\n");
  printf("===========\n");
  printf("MINESWEEPER\n");
  printf("===========\n");
  printf("\n");
  printf("1 - Beginner (12 bombs)\n");
  printf("2 - Easy     (10 bombs)\n");
  printf("3 - Medium   (40 bombs)\n");
  printf("4 - Hard     (100 bombs)\n");
  printf("5 - Huge     (220 bombs)\n");
  printf("6 - Extreme  (280 bombs)\n");
  printf("\n");
  printf("Select difficulty:\n");

  while (scanf("%d", &option) != 1 || option < 1 || option > 6) {
    while (getchar() != '\n');
    printf("Invalid option. Try again: ");
  }

  return (difficulty_t)(option - 1);
}

/**
 * @brief Obtém o nome de uma dificuldade.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Nome da dificuldade.
 *
 * @note src/game/difficulty.c
 */
const char *difficulty_get_name(
  difficulty_t difficulty
) {
  if (difficulty < DIFFICULTY_BEGINNER || difficulty > DIFFICULTY_EXTREME) {
    return "Unknown";
  }

  return difficulty_configs[difficulty].name;
}