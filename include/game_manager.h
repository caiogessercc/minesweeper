#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "difficulty.h"
#include "game_state.h"

/**
 * @brief Cria uma nova partida.
 *
 * Inicializa o estado do jogo com base na
 * dificuldade informada e prepara o tabuleiro
 * para o primeiro clique do jogador.
 *
 * @param game Estado do jogo.
 * @param difficulty Dificuldade da partida.
 *
 * @return true Se a criação foi concluída com sucesso.
 * @return false Se ocorreu falha durante a inicialização.
 *
 * @note include/game_manager.h
 */
bool game_manager_create(
  game_state_t *game,
  difficulty_t difficulty
);

/**
 * @brief Destrói uma partida existente.
 *
 * Libera todos os recursos associados ao
 * estado atual do jogo.
 *
 * @param game Estado do jogo.
 *
 * @note include/game_manager.h
 */
void game_manager_destroy(
  game_state_t *game
);

/**
 * @brief Reinicia a partida utilizando a mesma dificuldade.
 *
 * Destrói o estado atual e cria um novo
 * tabuleiro mantendo a dificuldade da
 * partida anterior.
 *
 * @param game Estado do jogo.
 *
 * @return true Se a reinicialização foi concluída com sucesso.
 * @return false Se ocorreu falha durante a recriação da partida.
 *
 * @note include/game_manager.h
 */
bool game_manager_restart(
  game_state_t *game
);