#include <stddef.h>

#include "app/scene.h"
#include "app/settings.h"

/**
 * @brief Reinicializa o estado interno da partida.
 *
 * @param scene Cena da aplicação.
 *
 * @note src/app/scene.c
 */
static void scene_reset_game(
  scene_t *scene
) {
  scene->game.cells = NULL;
  scene->game.row_count = 0;
  scene->game.column_count = 0;
  scene->game.bomb_count = 0;
  scene->game.flag_count = 0;
  scene->game.first_click_done = false;
  scene->game.difficulty = scene->settings.difficulty;
  scene->game.status = GAME_RUNNING;
}

/**
 * @brief Inicializa uma cena.
 *
 * Configura os estados iniciais da aplicação
 * e aplica as configurações padrão.
 *
 * @param scene Cena a ser inicializada.
 *
 * @note src/app/scene.c
 */
void scene_initialize(
  scene_t *scene
) {
  if (scene == NULL) { return; }
  settings_initialize(&scene->settings);
  scene->state = APP_STATE_MENU;
  scene_reset_game(scene);
}

/**
 * @brief Reinicia a cena para o menu principal.
 *
 * Mantém as configurações atuais e redefine
 * o estado global da aplicação.
 *
 * @param scene Cena a ser reiniciada.
 *
 * @note src/app/scene.c
 */
void scene_reset(
  scene_t *scene
) {
  if (scene == NULL) { return; }
  scene->state = APP_STATE_MENU;
  scene_reset_game(scene);
}

/**
 * @brief Altera o estado atual da aplicação.
 *
 * @param scene Cena da aplicação.
 * @param state Novo estado.
 *
 * @note src/app/scene.c
 */
void scene_set_state(
  scene_t *scene,
  app_state_t state
) {
  if (scene == NULL) { return; }
  scene->state = state;
}

/**
 * @brief Obtém o estado atual da aplicação.
 *
 * @param scene Cena da aplicação.
 *
 * @return Estado atual.
 *
 * @note src/app/scene.c
 */
app_state_t scene_get_state(
  const scene_t *scene
) {
  if (scene == NULL) { return APP_STATE_EXIT; }
  return scene->state;
}