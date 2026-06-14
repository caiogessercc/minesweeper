#include <stdio.h>

#include "difficulty.h"
#include "font.h"
#include "game_manager.h"
#include "hud.h"
#include "input.h"
#include "render.h"
#include "timer.h"
#include "window.h"
#include "theme.h"
#include "board.h"

#define CELL_SIZE 32
#define HUD_HEIGHT 120

#define HUD_FONT_PATH "assets/fonts/Roboto-Regular.ttf"
#define TITLE_FONT_PATH "assets/fonts/Roboto-Bold.ttf"

/**
 * @brief Inicializa e executa o loop principal do jogo.
 *
 * Responsável por selecionar a dificuldade,
 * inicializar os subsistemas da aplicação,
 * processar entradas do usuário, atualizar o
 * estado da partida e renderizar os frames
 * até o encerramento do jogo.
 *
 * @return 0 Se a execução foi concluída com sucesso.
 * @return 1 Se ocorreu falha durante a inicialização.
 *
 * @note src/main.c
 */
int main(void) {
  difficulty_t difficulty = difficulty_select();
  difficulty_config_t config = difficulty_get_config(difficulty);
  theme_t theme = theme_get(THEME_CLASSIC);
  game_state_t game = { 0 };

  if (!game_manager_create(&game, difficulty)) {
    fprintf(stderr, "Failed to initialize board.\n");
    return 1;
  }

  window_config_t window_config = {
    .title = config.name,
    .width = config.column_count * CELL_SIZE,
    .height = (config.row_count * CELL_SIZE) + HUD_HEIGHT
  };

  window_t window = { 0 };

  if (!window_initialize(&window, &window_config)) {
    fprintf(stderr, "Failed to initialize window.\n");
    game_manager_destroy(&game);
    return 1;
  }

  if (!font_initialize()) {
    fprintf(stderr, "Failed to initialize SDL_ttf.\n");
    window_destroy(&window);
    game_manager_destroy(&game);
    return 1;
  }

  font_t hud_font = { 0 };
  font_t title_font = { 0 };

  if (!font_load(&hud_font, HUD_FONT_PATH, 20)) { return 1; }
  if (!font_load(&title_font, TITLE_FONT_PATH, 48)) { return 1; }

  hud_t hud = { 0 };
  hud_initialize(&hud, &hud_font, 10, 10);
  input_state_t input = { 0 };
  input_initialize(&input);
  game_timer_t timer = { 0 };
  timer_start(&timer);

  while(window_is_open(&window) && !input.quit_requested) {
    input_poll_events(&input);

    if (input.escape_pressed) { break; }
    if (input.restart_requested) {
      game_manager_restart(&game);
      timer_reset(&timer);
    }

    if (game.status == GAME_RUNNING) {
      if (input.left_mouse_pressed) {
        int row = (input.mouse_y - HUD_HEIGHT) / CELL_SIZE;
        int column = input.mouse_x / CELL_SIZE;
        board_reveal_cell(&game, row, column);
      }
      if (input.right_mouse_pressed) {
        int row = (input.mouse_y - HUD_HEIGHT) / CELL_SIZE;
        int column = input.mouse_x / CELL_SIZE;
        board_toggle_flag(&game, row, column);
      }
    }

    uint32_t elapsed_seconds = timer_get_elapsed_seconds(&timer);
    int remaining_bombs = game.bomb_count - game.flag_count;
    char title[128];

    switch (game.status) {
      case GAME_RUNNING:
        snprintf(
          title,
          sizeof(title),
          "%s | Bombs: %d | Time: %us",
          difficulty_get_name(game.difficulty),
          remaining_bombs,
          elapsed_seconds
        );
        break;
      case GAME_WON:
        snprintf(
          title,
          sizeof(title),
          "%s | Victory | Time: %us",
          difficulty_get_name(game.difficulty),
          elapsed_seconds
        );
        break;
      case GAME_LOST:
        snprintf(
          title,
          sizeof(title),
          "%s | Game Over",
          difficulty_get_name(game.difficulty)
        );
        break;
    }

    window_set_title(&window, title);
    window_clear(&window);
    render_game(&window, &game, &theme);
    render_hud(&window, &hud, &game, &timer, &theme);

    if (game.status == GAME_WON) { render_victory(&window, &title_font, &theme); }
    if (game.status == GAME_LOST) { render_game_over(&window, &title_font, &theme); }

    window_present(&window);
    input_clear(&input);
  }

  font_unload(&title_font);
  font_unload(&hud_font);
  font_destroy();
  window_destroy(&window);
  game_manager_destroy(&game);

  return 0;
}