#pragma once

#include "game_state.h"
#include "hud.h"
#include "theme.h"
#include "timer.h"
#include "window.h"

/**
 * @brief Renderiza um frame completo da partida.
 *
 * Responsável por desenhar todos os elementos visuais
 * do jogo a partir do estado atual da partida,
 * incluindo células, bombas, bandeiras, números e
 * demais componentes da interface.
 *
 * @param window Janela utilizada para renderização.
 * @param game Estado atual da partida.
 * @param theme Tema visual utilizado.
 *
 * @note include/render.h
 */
void render_game(
  window_t *window,
  const game_state_t *game,
  const theme_t *theme
);

/**
 * @brief Renderiza a interface da partida.
 *
 * Exibe informações auxiliares ao jogador:
 * - Bombas restantes
 * - Tempo decorrido
 * - Dificuldade
 * - Estado atual da partida
 *
 * @param window Janela de renderização.
 * @param hud Configuração da HUD.
 * @param game Estado atual da partida.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual utilizado.
 *
 * @note include/render.h
 */
void render_hud(
  window_t *window,
  const hud_t *hud,
  const game_state_t *game,
  const game_timer_t *timer,
  const theme_t *theme
);

/**
 * @brief Renderiza a tela de derrota.
 *
 * @param window Janela de renderização.
 * @param font Fonte utilizada na renderização.
 * @param theme Tema visual utilizado.
 *
 * @note include/render.h
 */
void render_game_over(
  window_t *window,
  const font_t *font,
  const theme_t *theme
);

/**
 * @brief Renderiza a tela de vitória.
 *
 * @param window Janela de renderização.
 * @param font Fonte utilizada na renderização.
 * @param theme Tema visual utilizado.
 *
 * @note include/render.h
 */
void render_victory(
  window_t *window,
  const font_t *font,
  const theme_t *theme
);