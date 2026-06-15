#include <stdio.h>

#include "render/hud.h"
#include "engine/graphics.h"
#include "engine/timer.h"
#include "game/difficulty.h"
#include "render/font.h"

/**
 * @brief Renderiza o HUD da partida.
 *
 * @param game Estado da partida.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual ativo.
 *
 * @note src/render/hud.c
 */
void hud_render(
  const game_state_t *game,
  const timer_t *timer,
  const theme_t *theme
) {
  if (game == NULL || timer == NULL || theme == NULL) { return; }

  char bombs_text[64];
  char time_text[64];
  char difficulty_text[64];
  char status_text[64];

  snprintf(
    bombs_text,
    sizeof(bombs_text),
    "Bombs: %d",
    game->bomb_count - game->flag_count
  );

  timer_format(
    timer,
    time_text,
    sizeof(time_text)
  );

  snprintf(
    difficulty_text,
    sizeof(difficulty_text),
    "Difficulty: %s",
    difficulty_get_name(game->difficulty)
  );

  const char *status = "Running";

  switch (game->status) {
    case GAME_WON:
      status = "Victory";
      break;
    case GAME_LOST:
      status = "Game Over";
      break;
    case GAME_RUNNING:
    default:
      status = "Running";
      break;
  }

  snprintf(
    status_text,
    sizeof(status_text),
    "Status: %s",
    status
  );

  float x = 16.0f;
  float y = 16.0f;
  float line_height = 28.0f;

  font_draw_text(
    bombs_text,
    x,
    y,
    20.0f,
    theme->palette.hud_text
  );

  font_draw_text(
    time_text,
    x,
    y + line_height,
    20.0f,
    theme->palette.hud_text
  );

  font_draw_text(
    difficulty_text,
    x,
    y + (line_height * 2.0f),
    20.0f,
    theme->palette.hud_text
  );

  font_draw_text(
    status_text,
    x,
    y + (line_height * 3.0f),
    20.0f,
    theme->palette.hud_text
  );
}