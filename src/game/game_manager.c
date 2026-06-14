#include "game_manager.h"
#include "board.h"
#include "difficulty.h"

/**
 * @brief Cria uma nova partida.
 *
 * @param game Estado do jogo.
 * @param difficulty Dificuldade da partida.
 *
 * @return true Se a partida foi criada com sucesso.
 * @return false Se ocorreu falha durante a inicialização.
 *
 * @note src/game/game_manager.c
 */
bool game_manager_create(
  game_state_t *game,
  difficulty_t difficulty
) {
  if (game == NULL) { return false; }
  difficulty_config_t config = difficulty_get_config(difficulty);
  return board_initialize(game, &config);
}

/**
 * @brief Destrói uma partida existente.
 *
 * @param game Estado do jogo.
 *
 * @note src/game/game_manager.c
 */
void game_manager_destroy(
  game_state_t *game
) {
  if (game == NULL) { return; }
  board_destroy(game);
}

/**
 * @brief Reinicia a partida atual.
 *
 * Mantém a dificuldade utilizada anteriormente
 * e cria um novo tabuleiro limpo.
 *
 * @param game Estado do jogo.
 *
 * @return true Se a reinicialização foi concluída com sucesso.
 * @return false Se ocorreu falha durante a recriação.
 *
 * @note src/game/game_manager.c
 */
bool game_manager_restart(
  game_state_t *game
) {
  if (game == NULL) { return false; }

  difficulty_t difficulty = game->difficulty;
  board_destroy(game);
  
  return game_manager_create(game, difficulty);
}