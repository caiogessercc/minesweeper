#include <stdio.h>
#include <SDL2/SDL.h>

#include "font.h"
#include "render.h"

#define CELL_SIZE 32
#define HUD_HEIGHT 80

/**
 * @brief Renderiza o tabuleiro completo.
 *
 * @note src/render/render.c
 */
static void render_board(
  window_t *window,
  const game_state_t *game,
  const theme_t *theme
);

/**
 * @brief Renderiza uma célula do tabuleiro.
 *
 * @note src/render/render.c
 */
static void render_cell(
  window_t *window,
  const cell_t *cell,
  int row,
  int column,
  const theme_t *theme
);

/**
 * @brief Renderiza o número de bombas adjacentes.
 *
 * @note src/render/render.c
 */
static void render_number(
  window_t *window,
  const SDL_Rect *rect,
  uint8_t value,
  const theme_t *theme
);

/**
 * @brief Renderiza uma bomba.
 *
 * @note src/render/render.c
 */
static void render_bomb(
  window_t *window,
  const SDL_Rect *rect,
  const theme_t *theme
);

/**
 * @brief Renderiza uma bandeira.
 *
 * @note src/render/render.c
 */
static void render_flag(
  window_t *window,
  const SDL_Rect *rect,
  const theme_t *theme
);

/**
 * @brief Renderiza um frame completo da partida.
 *
 * Percorre todas as células do tabuleiro e
 * desenha seu estado atual na janela.
 *
 * @param window Janela utilizada para renderização.
 * @param game Estado atual da partida.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
void render_game(
  window_t *window,
  const game_state_t *game,
  const theme_t *theme
) {
  if (window == NULL || window->renderer == NULL || game == NULL || theme == NULL) { return; }
  render_board(window, game, theme);
}

/**
 * @brief Renderiza o tabuleiro completo.
 *
 * @param window Janela utilizada para renderização.
 * @param game Estado atual da partida.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
static void render_board(
  window_t *window,
  const game_state_t *game,
  const theme_t *theme
) {
  for (int row = 0; row < game->row_count; row++) {
    for (int column = 0; column < game->column_count; column++) {
      render_cell(
        window,
        &game->cells[row][column],
        row,
        column,
        theme
      );
    }
  }
}

/**
 * @brief Renderiza uma célula individual do tabuleiro.
 *
 * Desenha a aparência visual da célula de acordo
 * com seu estado atual, incluindo células reveladas,
 * ocultas, bombas e bandeiras.
 *
 * @param window Janela utilizada para renderização.
 * @param cell Célula a ser desenhada.
 * @param row Índice da linha da célula.
 * @param column Índice da coluna da célula.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
static void render_cell(
  window_t *window,
  const cell_t *cell,
  int row,
  int column,
  const theme_t *theme
) {
  SDL_Rect rect = {
    .x = column * CELL_SIZE,
    .y = (row * CELL_SIZE) + HUD_HEIGHT,
    .w = CELL_SIZE,
    .h = CELL_SIZE
  };

  SDL_Color color;

  if (!cell->is_revealed) {
    color = theme->palette.cell_hidden;
    SDL_SetRenderDrawColor(
      window->renderer,
      color.r,
      color.g,
      color.b,
      color.a
    );

    SDL_RenderFillRect(window->renderer, &rect);

    if (cell->is_flagged) {
      render_flag(window, &rect, theme);
    }
  } else {
    color = theme->palette.cell_revealed;
    SDL_SetRenderDrawColor(
      window->renderer,
      color.r,
      color.g,
      color.b,
      color.a
    );

    SDL_RenderFillRect(window->renderer, &rect);

    if (cell->has_bomb) {
      render_bomb(window, &rect, theme);
    } else if (cell->adjacent_bomb_count > 0) {
      render_number(window, &rect, cell->adjacent_bomb_count, theme);
    }
  }

  color = theme->palette.cell_border;
  SDL_SetRenderDrawColor(
    window->renderer,
    color.r,
    color.g,
    color.b,
    color.a
  );

  SDL_RenderDrawRect(window->renderer, &rect);
}

/**
 * @brief Renderiza uma bandeira.
 *
 * @param window Janela utilizada para renderização.
 * @param rect Área da célula.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
static void render_flag(
  window_t *window,
  const SDL_Rect *rect,
  const theme_t *theme
) {
  theme_draw_flag(
    window->renderer,
    rect,
    theme
  );
}

/**
 * @brief Renderiza uma bomba.
 *
 * @param window Janela utilizada para renderização.
 * @param rect Área da célula.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
static void render_bomb(
  window_t *window,
  const SDL_Rect *rect,
  const theme_t *theme
) {
  theme_draw_bomb(
    window->renderer,
    rect,
    theme
  );
}

/**
 * @brief Renderiza a quantidade de bombas adjacentes.
 *
 * @param window Janela utilizada para renderização.
 * @param rect Área da célula.
 * @param value Quantidade de bombas adjacentes.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
static void render_number(
  window_t *window,
  const SDL_Rect *rect,
  uint8_t value,
  const theme_t *theme
) {
  SDL_Color color = theme_get_number_color(theme, value);
  SDL_SetRenderDrawColor(
    window->renderer,
    color.r,
    color.g,
    color.b,
    color.a
  );

  SDL_Rect number_rect = {
    .x = rect->x + 10,
    .y = rect->y + 10,
    .w = value + 4,
    .h = value + 4
  };

  SDL_RenderFillRect(window->renderer, &number_rect);
}

/**
 * @brief Renderiza a HUD da partida.
 *
 * @param window Janela utilizada para renderização.
 * @param hud Configuração da HUD.
 * @param game Estado atual da partida.
 * @param timer Cronômetro da partida.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
void render_hud(
  window_t *window,
  const hud_t *hud,
  const game_state_t *game,
  const game_timer_t *timer,
  const theme_t *theme
) {
  if (window == NULL || window->renderer == NULL) { return; }
  hud_render(
    window->renderer,
    hud,
    game,
    timer,
    theme
  );
}

/**
 * @brief Renderiza a tela de derrota.
 *
 * @param window Janela utilizada para renderização.
 * @param font Fonte utilizada.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
void render_game_over(
  window_t *window,
  const font_t *font,
  const theme_t *theme
) {
  if (window == NULL || window->renderer == NULL || font == NULL || theme == NULL) { return; }
  font_draw_text(
    window->renderer,
    font,
    "GAME OVER",
    20,
    140,
    theme->palette.game_over_text
  );
}

/**
 * @brief Renderiza a tela de vitória.
 *
 * @param window Janela utilizada para renderização.
 * @param font Fonte utilizada.
 * @param theme Tema visual utilizado na renderização.
 *
 * @note src/render/render.c
 */
void render_victory(
  window_t *window,
  const font_t *font,
  const theme_t *theme
) {
  if (window == NULL || window->renderer == NULL || font == NULL || theme == NULL) { return; }
  font_draw_text(
    window->renderer,
    font,
    "VICTORY",
    20,
    140,
    theme->palette.victory_text
  );
}