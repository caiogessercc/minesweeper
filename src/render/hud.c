#include <stdio.h>

#include "hud.h"
#include "difficulty.h"

/**
 * @brief Inicializa a HUD.
 *
 * @param hud HUD da aplicação.
 * @param font Fonte utilizada pela HUD.
 * @param x Posição horizontal inicial.
 * @param y Posição vertical inicial.
 *
 * @note src/render/hud.c
 */
void hud_initialize(
  hud_t *hud,
  font_t *font,
  int32_t x,
  int32_t y
) {
  if (hud == NULL || font == NULL) { return; }
  hud->font = font;
  hud->x = x;
  hud->y = y;
}

/**
 * @brief Renderiza a quantidade de bombas restantes.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/hud.c
 */
void hud_render_bombs(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const theme_t *theme
) {
  if (renderer == NULL || hud == NULL || game == NULL) { return; }
  char text[64];

  snprintf(
    text,
    sizeof(text),
    "Bombs: %d",
    game->bomb_count - game->flag_count
  );

  font_draw_text(
    renderer,
    hud->font,
    text,
    hud->x,
    hud->y,
    theme->palette.hud_text
  );
}

/**
 * @brief Renderiza o tempo decorrido da partida.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/hud.c
 */
void hud_render_time(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_timer_t *timer,
  const theme_t *theme
) {
  if (renderer == NULL || hud == NULL || timer == NULL) { return; }

  uint32_t elapsed_seconds = timer_get_elapsed_seconds(timer);
  uint32_t minutes = elapsed_seconds / 60;
  uint32_t seconds = elapsed_seconds % 60;
  char text[64];

  snprintf(
    text,
    sizeof(text),
    "Time: %02u:%02u",
    minutes,
    seconds
  );

  font_draw_text(
    renderer,
    hud->font,
    text,
    hud->x,
    hud->y,
    theme->palette.hud_text
  );
}

/**
 * @brief Renderiza a dificuldade atual.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/hud.c
 */
void hud_render_difficulty(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const theme_t *theme
) {
  if (renderer == NULL || hud == NULL || game == NULL) { return; }
  char text[64];

  snprintf(
    text,
    sizeof(text),
    "Difficulty: %s",
    difficulty_get_name(game->difficulty)
  );

  font_draw_text(
    renderer,
    hud->font,
    text,
    hud->x,
    hud->y + 60,
    theme->palette.hud_text
  );
}

/**
 * @brief Renderiza o estado atual da partida.
 *
 * @param renderer Renderer SDL.
 * @param hud Configuração da HUD.
 * @param game Estado do jogo.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/hud.c
 */
void hud_render_status(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const theme_t *theme
) {
  if (renderer == NULL || hud == NULL || game == NULL) { return; }
  const char *status_text = "Running";

  switch (game->status) {
    case GAME_RUNNING:
      status_text = "Running";
      break;
    case GAME_WON:
      status_text = "Victory";
      break;
    case GAME_LOST:
      status_text = "Game Over";
      break;
    default:
      break;
  }

  char text[64];

  snprintf(
    text,
    sizeof(text),
    "Status: %s",
    status_text
  );

  font_draw_text(
    renderer,
    hud->font,
    text,
    hud->x,
    hud->y + 90,
    theme->palette.hud_text
  );
}

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
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/hud.c
 */
void hud_render(
  SDL_Renderer *renderer,
  const hud_t *hud,
  const game_state_t *game,
  const game_timer_t *timer,
  const theme_t *theme
) {
  if (renderer == NULL || hud == NULL || game == NULL || timer == NULL) { return; }
  hud_render_bombs( renderer, hud, game, theme);
  hud_render_time( renderer, hud, timer, theme);
  hud_render_difficulty( renderer, hud, game, theme);
  hud_render_status( renderer, hud, game, theme);
}