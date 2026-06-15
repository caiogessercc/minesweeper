#include <stdbool.h>

#include "app/scene.h"
#include "engine/graphics.h"
#include "engine/input.h"
#include "engine/timer.h"
#include "game/game_manager.h"
#include "game/board.h"
#include "render/font.h"
#include "render/menu.h"
#include "render/render.h"
#include "render/theme.h"

/**
 * @brief Configuração padrão da janela.
 *
 * @note src/main.c
 */
static const graphics_config_t graphics_config = {
  .title = "Minesweeper",
  .width = 1280,
  .height = 720,
  .target_fps = 60,
  .fullscreen = false,
  .resizable = true
};

/**
 * @brief Ponto de entrada da aplicação.
 *
 * Responsável por:
 * - Inicializar subsistemas
 * - Executar o loop principal
 * - Gerenciar transições de estado
 * - Encerrar recursos
 *
 * @return Código de saída.
 *
 * @note src/main.c
 */
int main(void) {
  scene_t scene = { 0 };
  scene_initialize(&scene);

  if (!graphics_initialize(&graphics_config)) { return 1; }
  if (!font_initialize()) {
    graphics_shutdown();
    return 1;
  }

  input_state_t input = { 0 };
  input_initialize(&input);
  timer_t timer = { 0 };
  timer_start(&timer);
  bool game_created = false;

  while (!graphics_should_close() && scene.state != APP_STATE_EXIT) {
    graphics_update();
    input_update(&input);
    timer_update(&timer);
    theme_t theme = theme_get(scene.settings.theme);

    switch (scene.state) {
      case APP_STATE_MENU: {
        menu_update(&scene, &input);

        if (scene.state == APP_STATE_PLAYING) {
          if (game_manager_create(&scene.game, &scene.settings)) {
            timer_restart(&timer);
            timer_start(&timer);
            game_created = true;
          } else {
            scene.state = APP_STATE_MENU;
          }
        }
        break;
      }

      case APP_STATE_PLAYING: {
        if (input.escape_pressed) {
          game_manager_destroy(&scene.game);
          game_created = false;
          scene.state = APP_STATE_MENU;
          break;
        }

        if (input.restart_requested) {
          game_manager_restart(&scene.game, &scene.settings);
          timer_restart(&timer);
          timer_start(&timer);
        }

        if (scene.game.status == GAME_RUNNING) {
          if (input.left_mouse_pressed) {
            const int row = (input.mouse_y - 120) / 32;
            const int column = input.mouse_x / 32;
            board_reveal_cell(&scene.game, row, column);
          }

          if (input.right_mouse_pressed) {
            const int row = (input.mouse_y - 120) / 32;
            const int column = input.mouse_x / 32;
            board_toggle_flag(&scene.game, row, column );
          }
        }
        break;
      }
      case APP_STATE_EXIT:
      default:
        break;
    }

    graphics_begin_frame();

    switch (scene.state) {
      case APP_STATE_MENU:
        menu_render(
          &scene,
          &input,
          &theme
        );
        break;
      case APP_STATE_PLAYING:
        if (game_created) {
          render_application(
            &scene,
            &timer,
            &theme
          );
        }
        break;
      case APP_STATE_EXIT:
      default:
        break;
    }

    graphics_end_frame();
    input_clear(&input);
  }

  if (game_created) {
    game_manager_destroy(&scene.game);
  }

  font_destroy();
  graphics_shutdown();

  return 0;
}