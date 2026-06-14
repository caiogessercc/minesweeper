#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

#include "font.h"
#include "game_state.h"
#include "theme.h"
#include "timer.h"

/**
 * @brief Configuração visual da HUD.
 *
 * Define posição e fonte utilizadas
 * para renderização das informações da partida.
 *
 * As cores são obtidas dinamicamente
 * através do tema ativo.
 *
 * @note include/hud.h
 */
typedef struct {
  font_t *font;
  int32_t x;
  int32_t y;
} hud_t;

/**
 * @brief Inicializa a HUD.
 *
 * Associa uma fonte e define a posição inicial
 * utilizada para renderização.
 *
 * @param hud HUD da aplicação.
 * @param font Fonte utilizada pela HUD.
 * @param x Posição horizontal inicial.
 * @param y Posição vertical inicial.
 *
 * @note include/hud.h
 */
void hud_initialize(
  hud_t *hud,
  font_t *font,
  int32_t x,
  int32_t y
);

/**
 * @brief Renderiza a quantidade de bombas restantes.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param theme Tema visual utilizado.
 *
 * @note include/hud.h
 */
void hud_render_bombs(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const theme_t *theme
);

/**
 * @brief Renderiza o tempo decorrido da partida.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual utilizado.
 *
 * @note include/hud.h
 */
void hud_render_time(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_timer_t *timer,
  const theme_t *theme
);

/**
 * @brief Renderiza a dificuldade atual.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param theme Tema visual utilizado.
 *
 * @note include/hud.h
 */
void hud_render_difficulty(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const theme_t *theme
);

/**
 * @brief Renderiza o estado atual da partida.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param theme Tema visual utilizado.
 *
 * @note include/hud.h
 */
void hud_render_status(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const theme_t *theme
);

/**
 * @brief Renderiza a HUD completa.
 *
 * Renderiza:
 * - Bombas restantes
 * - Tempo
 * - Dificuldade
 * - Estado da partida
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual utilizado.
 *
 * @note include/hud.h
 */
void hud_render(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const game_timer_t *timer,
  const theme_t *theme
);