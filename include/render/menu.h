#pragma once

#include <stdbool.h>

#include "app/scene.h"
#include "engine/input.h"
#include "render/theme.h"

/**
 * @brief Renderiza o menu principal.
 *
 * Responsável pela interface de seleção
 * de dificuldade, tema e início da partida.
 *
 * @param scene Cena atual da aplicação.
 * @param input Estado atual da entrada.
 * @param theme Tema visual ativo.
 *
 * @note include/render/menu.h
 */
void menu_render(
  scene_t *scene,
  const input_state_t *input,
  const theme_t *theme
);

/**
 * @brief Atualiza a lógica do menu.
 *
 * Processa navegação, seleção de opções
 * e mudanças de estado da aplicação.
 *
 * @param scene Cena atual da aplicação.
 * @param input Estado atual da entrada.
 *
 * @note include/render/menu.h
 */
void menu_update(
  scene_t *scene,
  const input_state_t *input
);