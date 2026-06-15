#pragma once

#include "app/app_state.h"
#include "app/settings.h"
#include "game/game_state.h"

/**
 * @brief Representa uma cena da aplicação.
 *
 * Centraliza o estado global da aplicação,
 * as configurações selecionadas pelo usuário
 * e a partida atualmente carregada.
 *
 * @note include/app/scene.h
 */
typedef struct {
  app_state_t state;
  settings_t settings;
  game_state_t game;
} scene_t;

/**
 * @brief Inicializa uma cena.
 *
 * Configura os estados iniciais da aplicação
 * e aplica as configurações padrão.
 *
 * @param scene Cena a ser inicializada.
 *
 * @note include/app/scene.h
 */
void scene_initialize(
  scene_t *scene
);

/**
 * @brief Reinicia a cena para o menu principal.
 *
 * Mantém as configurações atuais e redefine
 * o estado global da aplicação.
 *
 * @param scene Cena a ser reiniciada.
 *
 * @note include/app/scene.h
 */
void scene_reset(
  scene_t *scene
);

/**
 * @brief Altera o estado atual da aplicação.
 *
 * @param scene Cena da aplicação.
 * @param state Novo estado.
 *
 * @note include/app/scene.h
 */
void scene_set_state(
  scene_t *scene,
  app_state_t state
);

/**
 * @brief Obtém o estado atual da aplicação.
 *
 * @param scene Cena da aplicação.
 *
 * @return Estado atual.
 *
 * @note include/app/scene.h
 */
app_state_t scene_get_state(
  const scene_t *scene
);