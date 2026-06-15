#pragma once

#include <stdint.h>

/**
 * @brief Representa uma cor RGBA.
 *
 * Estrutura independente de qualquer biblioteca
 * gráfica utilizada pela aplicação.
 *
 * @note include/render/theme.h
 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} color_t;

/**
 * @brief Paleta de cores utilizada por um tema.
 *
 * @note include/render/theme.h
 */
typedef struct {
  color_t background;
  color_t cell_hidden;
  color_t cell_revealed;
  color_t cell_border;
  color_t bomb;
  color_t flag;
  color_t hud_text;
  color_t game_over_text;
  color_t victory_text;
  color_t number_1;
  color_t number_2;
  color_t number_3;
  color_t number_4;
  color_t number_5;
  color_t number_6;
  color_t number_7;
  color_t number_8;
} theme_palette_t;

/**
 * @brief Temas disponíveis.
 *
 * @note include/render/theme.h
 */
typedef enum {
  THEME_CLASSIC = 0,
  THEME_DARK,
  THEME_RETRO,
  THEME_TERMINAL
} theme_type_t;

/**
 * @brief Representa um tema visual completo.
 *
 * @note include/render/theme.h
 */
typedef struct {
  theme_type_t type;
  const char *name;
  theme_palette_t palette;
} theme_t;

/**
 * @brief Obtém um tema visual.
 *
 * @param type Tipo do tema.
 *
 * @return Tema solicitado.
 *
 * @note include/render/theme.h
 */
theme_t theme_get(
  theme_type_t type
);

/**
 * @brief Obtém o nome de um tema.
 *
 * @param type Tipo do tema.
 *
 * @return Nome do tema.
 *
 * @note include/render/theme.h
 */
const char *theme_get_name(
  theme_type_t type
);

/**
 * @brief Obtém a cor associada a uma quantidade
 * de bombas adjacentes.
 *
 * @param theme Tema utilizado.
 * @param bomb_count Quantidade de bombas adjacentes.
 *
 * @return Cor correspondente.
 *
 * @note include/render/theme.h
 */
color_t theme_get_hint_color(
  const theme_t *theme,
  uint8_t bomb_count
);