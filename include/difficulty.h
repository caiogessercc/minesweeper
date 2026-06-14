#pragma once

#include <stdint.h>

/**
 * @brief Define os níveis de dificuldade disponíveis no jogo.
 *
 * Cada nível determina as dimensões do tabuleiro
 * e a quantidade de bombas geradas.
 *
 * @note include/difficulty.h
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
 * @brief Armazena as configurações de uma dificuldade.
 *
 * Define os parâmetros necessários para inicializar
 * uma partida com um determinado nível de dificuldade.
 *
 * @note include/difficulty.h
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
 * Retorna os parâmetros utilizados para criar
 * o tabuleiro correspondente à dificuldade informada.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Estrutura contendo a configuração da dificuldade.
 *
 * @note include/difficulty.h
 */
difficulty_config_t difficulty_get_config(
  difficulty_t difficulty
);

/**
 * @brief Solicita ao usuário a seleção de uma dificuldade.
 *
 * Exibe as opções disponíveis no terminal e retorna
 * a dificuldade escolhida pelo usuário.
 *
 * @return Dificuldade selecionada.
 *
 * @note include/difficulty.h
 */
difficulty_t difficulty_select(void);

/**
 * @brief Obtém o nome de uma dificuldade.
 *
 * Converte um valor do tipo difficulty_t para sua
 * representação em texto.
 *
 * @param difficulty Dificuldade desejada.
 *
 * @return Nome da dificuldade.
 *
 * @note include/difficulty.h
 */
const char *difficulty_get_name(
  difficulty_t difficulty
);