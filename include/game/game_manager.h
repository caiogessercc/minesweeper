#pragma once

#include <stdbool.h>

#include "app/settings.h"
#include "game/game_state.h"

/**
 * @brief Cria uma nova partida.
 *
 * Inicializa o estado do jogo utilizando
 * as configurações fornecidas.
 *
 * @param game Estado da partida.
 * @param settings Configurações da aplicação.
 *
 * @return true Se a criação foi concluída.
 * @return false Caso contrário.
 *
 * @note include/game/game_manager.h
 */
bool game_manager_create(
  game_state_t *game,
  const settings_t *settings
);

/**
 * @brief Reinicia uma partida.
 *
 * Mantém as configurações atuais e cria
 * um novo tabuleiro.
 *
 * @param game Estado da partida.
 * @param settings Configurações da aplicação.
 *
 * @return true Se a recriação foi concluída.
 * @return false Caso contrário.
 *
 * @note include/game/game_manager.h
 */
bool game_manager_restart(
  game_state_t *game,
  const settings_t *settings
);

/**
 * @brief Finaliza uma partida.
 *
 * @param game Estado da partida.
 *
 * @note include/game/game_manager.h
 */
void game_manager_destroy(
  game_state_t *game
);