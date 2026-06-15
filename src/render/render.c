#include <stddef.h>
#include "raylib.h"

#include "render/render.h"
#include "render/font.h"
#include "render/hud.h"

#define CELL_SIZE 32
#define HUD_HEIGHT 120

/**
 * @brief Converte color_t para Color.
 *
 * @note src/render/render.c
 */
static Color render_color(
  color_t color
) {
  return (Color) {
    color.r,
    color.g,
    color.b,
    color.a
  };
}

/**
 * @brief Renderiza uma célula.
 *
 * @note src/render/render.c
 */
static void render_cell(
  const cell_t *cell,
  int row,
  int column,
  const theme_t *theme
) {
  Rectangle rect = {
    (float)(column * CELL_SIZE),
    (float)((row * CELL_SIZE) + HUD_HEIGHT),
    CELL_SIZE,
    CELL_SIZE
  };

  Color fill =
    cell->is_revealed
      ? render_color(theme->palette.cell_revealed)
      : render_color(theme->palette.cell_hidden);

  DrawRectangleRec(rect, fill);
  DrawRectangleLinesEx(
    rect,
    1.0f,
    render_color(theme->palette.cell_border)
  );

  if (!cell->is_revealed) {
    if (cell->is_flagged) {
      DrawTriangle(
        (Vector2){ rect.x + 8, rect.y + 6 },
        (Vector2){ rect.x + 8, rect.y + 22 },
        (Vector2){ rect.x + 22, rect.y + 14 },
        render_color(theme->palette.flag)
      );
    }
    return;
  }

  if (cell->has_bomb) {
    DrawCircle(
      (int)(rect.x + 16),
      (int)(rect.y + 16),
      8.0f,
      render_color(theme->palette.bomb)
    );
    return;
  }

  if (cell->adjacent_bomb_count > 0) {
    color_t hint =
      theme_get_hint_color(
        theme,
        cell->adjacent_bomb_count
      );

    DrawCircle(
      (int)(rect.x + 16),
      (int)(rect.y + 16),
      6.0f,
      render_color(hint)
    );
  }
}

/**
 * @brief Renderiza a aplicação.
 *
 * @note src/render/render.c
 */
void render_application(
  const scene_t *scene,
  const timer_t *timer,
  const theme_t *theme
) {
  if (scene == NULL || timer == NULL || theme == NULL) { return; }

  render_board(scene, theme);
  hud_render(&scene->game, timer, theme);

  switch (scene->game.status) {
    case GAME_WON:
      render_victory(scene, theme);
      break;
    case GAME_LOST:
      render_game_over(scene, theme);
      break;
    case GAME_RUNNING:
    default:
      break;
  }
}

/**
 * @brief Renderiza o tabuleiro.
 *
 * @note src/render/render.c
 */
void render_board(
  const scene_t *scene,
  const theme_t *theme
) {
  if (scene == NULL || theme == NULL) { return; }
  const game_state_t *game = &scene->game;

  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      render_cell(
        &game->cells[row][column],
        row,
        column,
        theme
      );
    }
  }
}

/**
 * @brief Renderiza tela de derrota.
 *
 * @note src/render/render.c
 */
void render_game_over(
  const scene_t *scene,
  const theme_t *theme
) {
  (void)scene;
  font_draw_text_centered(
    "GAME OVER",
    70.0f,
    42.0f,
    theme->palette.game_over_text
  );
}

/**
 * @brief Renderiza tela de vitória.
 *
 * @note src/render/render.c
 */
void render_victory(
  const scene_t *scene,
  const theme_t *theme
) {
  (void)scene;
  font_draw_text_centered(
    "VICTORY",
    70.0f,
    42.0f,
    theme->palette.victory_text
  );
}