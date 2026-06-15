#pragma once

#include "engine/timer.h"
#include "game/game_state.h"
#include "render/theme.h"

/**
 * @brief Renderiza o HUD da partida.
 *
 * Exibe informações auxiliares ao jogador,
 * como tempo, dificuldade, bandeiras e
 * estado atual da partida.
 *
 * @param game Estado da partida.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual ativo.
 *
 * @note include/render/hud.h
 */
void hud_render(
  const game_state_t *game,
  const timer_t *timer,
  const theme_t *theme
);