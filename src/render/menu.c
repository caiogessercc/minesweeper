#include <stddef.h>

#include "render/menu.h"
#include "app/app_state.h"
#include "game/difficulty.h"
#include "render/font.h"
#include "render/theme.h"

/**
 * @brief Obtém a próxima dificuldade disponível.
 *
 * @param difficulty Dificuldade atual.
 *
 * @return Próxima dificuldade.
 *
 * @note src/render/menu.c
 */
static difficulty_t menu_next_difficulty(
  difficulty_t difficulty
) {
  switch (difficulty) {
    case DIFFICULTY_BEGINNER:
      return DIFFICULTY_EASY;
    case DIFFICULTY_EASY:
      return DIFFICULTY_MEDIUM;
    case DIFFICULTY_MEDIUM:
      return DIFFICULTY_HARD;
    case DIFFICULTY_HARD:
      return DIFFICULTY_HUGE;
    case DIFFICULTY_HUGE:
      return DIFFICULTY_EXTREME;
    case DIFFICULTY_EXTREME:
    default:
      return DIFFICULTY_BEGINNER;
  }
}

/**
 * @brief Obtém o próximo tema disponível.
 *
 * @param theme Tema atual.
 *
 * @return Próximo tema.
 *
 * @note src/render/menu.c
 */
static theme_type_t menu_next_theme(
  theme_type_t theme
) {
  switch (theme) {
    case THEME_CLASSIC:
      return THEME_DARK;
    case THEME_DARK:
      return THEME_RETRO;
    case THEME_RETRO:
      return THEME_TERMINAL;
    case THEME_TERMINAL:
    default:
      return THEME_CLASSIC;
  }
}

/**
 * @brief Atualiza a lógica do menu.
 *
 * @param scene Cena atual da aplicação.
 * @param input Estado atual da entrada.
 *
 * @note src/render/menu.c
 */
void menu_update(
  scene_t *scene,
  const input_state_t *input
) {
  if (scene == NULL || input == NULL) { return; }
  if (scene->state != APP_STATE_MENU) { return; }

  if (input->confirm_pressed) {
    scene->state = APP_STATE_PLAYING;
  }

  if (input->restart_requested) {
    scene->settings.difficulty =
      menu_next_difficulty(
        scene->settings.difficulty
      );
  }

  if (input->back_pressed) {
    scene->settings.theme =
      menu_next_theme(
        scene->settings.theme
      );
  }

  if (input->escape_pressed) {
    scene->state = APP_STATE_EXIT;
  }
}

/**
 * @brief Renderiza o menu principal.
 *
 * @param scene Cena atual da aplicação.
 * @param input Estado atual da entrada.
 * @param theme Tema visual ativo.
 *
 * @note src/render/menu.c
 */
void menu_render(
  scene_t *scene,
  const input_state_t *input,
  const theme_t *theme
) {
  (void)input;
  if (scene == NULL || theme == NULL) { return; }
  if (scene->state != APP_STATE_MENU) { return; }

  font_draw_text_centered(
    "MINESWEEPER",
    80.0f,
    48.0f,
    theme->palette.hud_text
  );

  font_draw_text_centered(
    "Press ENTER to Start",
    180.0f,
    24.0f,
    theme->palette.hud_text
  );

  font_draw_text_centered(
    "Press R to Change Difficulty",
    230.0f,
    20.0f,
    theme->palette.hud_text
  );

  font_draw_text_centered(
    difficulty_get_name(scene->settings.difficulty),
    260.0f,
    24.0f,
    theme->palette.victory_text
  );

  font_draw_text_centered(
    "Press BACKSPACE to Change Theme",
    320.0f,
    20.0f,
    theme->palette.hud_text
  );

  font_draw_text_centered(
    theme_get_name(scene->settings.theme),
    350.0f,
    24.0f,
    theme->palette.victory_text
  );

  font_draw_text_centered(
    "ESC - Exit",
    430.0f,
    20.0f,
    theme->palette.game_over_text
  );
}