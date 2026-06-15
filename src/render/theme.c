#include <stddef.h>

#include "render/theme.h"

/**
 * @brief Tema clássico.
 *
 * @note src/render/theme.c
 */
static const theme_t classic_theme = {
  .type = THEME_CLASSIC,
  .name = "Classic",
  .palette = {
    .background = { 30, 30, 30, 255 },
    .cell_hidden = { 120, 120, 120, 255 },
    .cell_revealed = { 200, 200, 200, 255 },
    .cell_border = { 0, 0, 0, 255 },
    .bomb = { 0, 0, 0, 255 },
    .flag = { 220, 0, 0, 255 },
    .hud_text = { 255, 255, 255, 255 },
    .game_over_text = { 220, 0, 0, 255 },
    .victory_text = { 0, 220, 0, 255 },
    .number_1 = { 0, 0, 255, 255 },
    .number_2 = { 0, 128, 0, 255 },
    .number_3 = { 255, 0, 0, 255 },
    .number_4 = { 0, 0, 128, 255 },
    .number_5 = { 128, 0, 0, 255 },
    .number_6 = { 0, 128, 128, 255 },
    .number_7 = { 0, 0, 0, 255 },
    .number_8 = { 128, 128, 128, 255 }
  }
};

/**
 * @brief Tema escuro.
 *
 * @note src/render/theme.c
 */
static const theme_t dark_theme = {
  .type = THEME_DARK,
  .name = "Dark",
  .palette = {
    .background = { 18, 18, 18, 255 },
    .cell_hidden = { 50, 50, 50, 255 },
    .cell_revealed = { 90, 90, 90, 255 },
    .cell_border = { 20, 20, 20, 255 },
    .bomb = { 255, 80, 80, 255 },
    .flag = { 255, 200, 0, 255 },
    .hud_text = { 255, 255, 255, 255 },
    .game_over_text = { 255, 80, 80, 255 },
    .victory_text = { 0, 255, 100, 255 },
    .number_1 = { 80, 180, 255, 255 },
    .number_2 = { 100, 255, 100, 255 },
    .number_3 = { 255, 100, 100, 255 },
    .number_4 = { 180, 120, 255, 255 },
    .number_5 = { 255, 120, 120, 255 },
    .number_6 = { 120, 255, 255, 255 },
    .number_7 = { 255, 255, 255, 255 },
    .number_8 = { 180, 180, 180, 255 }
  }
};

/**
 * @brief Tema retrô.
 *
 * @note src/render/theme.c
 */
static const theme_t retro_theme = {
  .type = THEME_RETRO,
  .name = "Retro",
  .palette = {
    .background = { 20, 30, 20, 255 },
    .cell_hidden = { 50, 80, 50, 255 },
    .cell_revealed = { 120, 180, 120, 255 },
    .cell_border = { 10, 20, 10, 255 },
    .bomb = { 255, 255, 255, 255 },
    .flag = { 255, 220, 0, 255 },
    .hud_text = { 200, 255, 200, 255 },
    .game_over_text = { 255, 120, 120, 255 },
    .victory_text = { 120, 255, 120, 255 },
    .number_1 = { 180, 255, 180, 255 },
    .number_2 = { 120, 255, 120, 255 },
    .number_3 = { 255, 180, 180, 255 },
    .number_4 = { 180, 180, 255, 255 },
    .number_5 = { 255, 120, 120, 255 },
    .number_6 = { 120, 255, 255, 255 },
    .number_7 = { 255, 255, 255, 255 },
    .number_8 = { 180, 180, 180, 255 }
  }
};

/**
 * @brief Tema terminal.
 *
 * @note src/render/theme.c
 */
static const theme_t terminal_theme = {
  .type = THEME_TERMINAL,
  .name = "Terminal",
  .palette = {
    .background = { 0, 0, 0, 255 },
    .cell_hidden = { 10, 40, 10, 255 },
    .cell_revealed = { 0, 0, 0, 255 },
    .cell_border = { 0, 120, 0, 255 },
    .bomb = { 0, 255, 0, 255 },
    .flag = { 0, 255, 0, 255 },
    .hud_text = { 0, 255, 0, 255 },
    .game_over_text = { 255, 0, 0, 255 },
    .victory_text = { 0, 255, 0, 255 },
    .number_1 = { 0, 255, 0, 255 },
    .number_2 = { 0, 255, 0, 255 },
    .number_3 = { 0, 255, 0, 255 },
    .number_4 = { 0, 255, 0, 255 },
    .number_5 = { 0, 255, 0, 255 },
    .number_6 = { 0, 255, 0, 255 },
    .number_7 = { 0, 255, 0, 255 },
    .number_8 = { 0, 255, 0, 255 }
  }
};

/**
 * @brief Obtém um tema visual.
 *
 * @param type Tipo do tema.
 *
 * @return Tema solicitado.
 *
 * @note src/render/theme.c
 */
theme_t theme_get(
  theme_type_t type
) {
  switch (type) {
    case THEME_DARK:
      return dark_theme;
    case THEME_RETRO:
      return retro_theme;
    case THEME_TERMINAL:
      return terminal_theme;
    case THEME_CLASSIC:
    default:
      return classic_theme;
  }
}

/**
 * @brief Obtém o nome de um tema.
 *
 * @param type Tipo do tema.
 *
 * @return Nome do tema.
 *
 * @note src/render/theme.c
 */
const char *theme_get_name(
  theme_type_t type
) {
  return theme_get(type).name;
}

/**
 * @brief Obtém a cor associada a uma quantidade
 * de bombas adjacentes.
 *
 * @param theme Tema utilizado.
 * @param bomb_count Quantidade de bombas adjacentes.
 *
 * @return Cor correspondente.
 *
 * @note src/render/theme.c
 */
color_t theme_get_hint_color(
  const theme_t *theme,
  uint8_t bomb_count
) {
  if (theme == NULL) {
    return (color_t){ 255, 255, 255, 255 };
  }

  switch (bomb_count) {
    case 1: return theme->palette.number_1;
    case 2: return theme->palette.number_2;
    case 3: return theme->palette.number_3;
    case 4: return theme->palette.number_4;
    case 5: return theme->palette.number_5;
    case 6: return theme->palette.number_6;
    case 7: return theme->palette.number_7;
    case 8: return theme->palette.number_8;
    default:
      return theme->palette.hud_text;
  }
}