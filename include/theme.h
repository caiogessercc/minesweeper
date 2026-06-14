#pragma once

#include <stdint.h>

#include <SDL2/SDL.h>

/**
 * @brief Temas visuais disponíveis.
 *
 * @note include/theme.h
 */
typedef enum {
  THEME_CLASSIC = 0,
  THEME_DARK,
  THEME_LIGHT,
  THEME_RETRO
} theme_type_t;

/**
 * @brief Paleta de cores utilizada por um tema.
 *
 * @note include/theme.h
 */
typedef struct {
  SDL_Color background;
  SDL_Color cell_hidden;
  SDL_Color cell_revealed;
  SDL_Color cell_border;
  SDL_Color bomb;
  SDL_Color flag;
  SDL_Color number_1;
  SDL_Color number_2;
  SDL_Color number_3;
  SDL_Color number_4;
  SDL_Color number_5;
  SDL_Color number_6;
  SDL_Color number_7;
  SDL_Color number_8;
  SDL_Color hud_text;
  SDL_Color victory_text;
  SDL_Color game_over_text;
} theme_palette_t;

/**
 * @brief Representa um tema visual completo.
 *
 * @note include/theme.h
 */
typedef struct {
  theme_type_t type;
  const char *name;
  theme_palette_t palette;
} theme_t;

/**
 * @brief Obtém um tema visual.
 *
 * @param type Tema desejado.
 *
 * @return Configuração completa do tema.
 *
 * @note include/theme.h
 */
theme_t theme_get(
  theme_type_t type
);

/**
 * @brief Obtém a cor correspondente a um número.
 *
 * @param theme Tema utilizado.
 * @param value Número de bombas adjacentes.
 *
 * @return Cor associada ao número.
 *
 * @note include/theme.h
 */
SDL_Color theme_get_number_color(
  const theme_t *theme,
  uint8_t value
);

/**
 * @brief Desenha uma bomba.
 *
 * @param renderer Renderer SDL.
 * @param rect Área da célula.
 * @param theme Tema utilizado.
 *
 * @note include/theme.h
 */
void theme_draw_bomb(
  SDL_Renderer *renderer,
  const SDL_Rect *rect,
  const theme_t *theme
);

/**
 * @brief Desenha uma bandeira.
 *
 * @param renderer Renderer SDL.
 * @param rect Área da célula.
 * @param theme Tema utilizado.
 *
 * @note include/theme.h
 */
void theme_draw_flag(
  SDL_Renderer *renderer,
  const SDL_Rect *rect,
  const theme_t *theme
);