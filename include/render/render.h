#pragma once

#include "app/scene.h"
#include "engine/timer.h"
#include "render/theme.h"

/**
 * @brief Renderiza a aplicação.
 *
 * Encaminha a renderização para o sistema
 * apropriado de acordo com o estado atual
 * da aplicação.
 *
 * @param scene Cena atual.
 * @param timer Cronômetro da aplicação.
 * @param theme Tema visual ativo.
 *
 * @note include/render/render.h
 */
void render_application(
  const scene_t *scene,
  const timer_t *timer,
  const theme_t *theme
);

/**
 * @brief Renderiza o tabuleiro da partida.
 *
 * @param scene Cena atual.
 * @param theme Tema visual ativo.
 *
 * @note include/render/render.h
 */
void render_board(
  const scene_t *scene,
  const theme_t *theme
);

/**
 * @brief Renderiza a tela de derrota.
 *
 * @param scene Cena atual.
 * @param theme Tema visual ativo.
 *
 * @note include/render/render.h
 */
void render_game_over(
  const scene_t *scene,
  const theme_t *theme
);

/**
 * @brief Renderiza a tela de vitória.
 *
 * @param scene Cena atual.
 * @param theme Tema visual ativo.
 *
 * @note include/render/render.h
 */
void render_victory(
  const scene_t *scene,
  const theme_t *theme
);