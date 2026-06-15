#include <stddef.h>
#include "raylib.h"

#include "engine/graphics.h"

/**
 * @brief Estado gráfico global.
 *
 * @note src/engine/graphics.c
 */
static graphics_state_t graphics_state = { 0 };

/**
 * @brief Inicializa o sistema gráfico.
 *
 * @param config Configuração da janela.
 *
 * @return true Se a inicialização foi concluída.
 * @return false Caso contrário.
 *
 * @note src/engine/graphics.c
 */
bool graphics_initialize(
  const graphics_config_t *config
) {
  if (config == NULL) { return false; }
  if (config->resizable) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  }

  InitWindow(
    config->width,
    config->height,
    config->title
  );

  if (!IsWindowReady()) { return false; }
  SetTargetFPS(config->target_fps);
  if (config->fullscreen) { ToggleFullscreen(); }

  graphics_state.width =  GetScreenWidth();
  graphics_state.height = GetScreenHeight();
  graphics_state.delta_time = 0.0f;

  return true;
}

/**
 * @brief Finaliza o sistema gráfico.
 *
 * @note src/engine/graphics.c
 */
void graphics_shutdown(void) {
  if (!IsWindowReady()) { return; }
  CloseWindow();
}

/**
 * @brief Inicia a renderização de um frame.
 *
 * @note src/engine/graphics.c
 */
void graphics_begin_frame(void) {
  BeginDrawing();
  ClearBackground(
    (Color){
      .r = 30,
      .g = 30,
      .b = 30,
      .a = 255
    }
  );
}

/**
 * @brief Finaliza a renderização de um frame.
 *
 * @note src/engine/graphics.c
 */
void graphics_end_frame(void) { EndDrawing(); }

/**
 * @brief Verifica se a aplicação deve ser encerrada.
 *
 * @return true Se a aplicação deve encerrar.
 * @return false Caso contrário.
 *
 * @note src/engine/graphics.c
 */
bool graphics_should_close(void) {
  if (!IsWindowReady()) { return true; }
  return WindowShouldClose();
}

/**
 * @brief Atualiza informações da superfície gráfica.
 *
 * @note src/engine/graphics.c
 */
void graphics_update(void) {
  graphics_state.width = GetScreenWidth();
  graphics_state.height = GetScreenHeight();
  graphics_state.delta_time = GetFrameTime();
}

/**
 * @brief Obtém o estado gráfico atual.
 *
 * @return Estado gráfico atual.
 *
 * @note src/engine/graphics.c
 */
const graphics_state_t *graphics_get_state(void) {
  return &graphics_state;
}

/**
 * @brief Obtém a largura atual da janela.
 *
 * @return Largura da janela.
 *
 * @note src/engine/graphics.c
 */
int32_t graphics_get_width(void) {
  return graphics_state.width;
}

/**
 * @brief Obtém a altura atual da janela.
 *
 * @return Altura da janela.
 *
 * @note src/engine/graphics.c
 */
int32_t graphics_get_height(void) {
  return graphics_state.height;
}

/**
 * @brief Alterna o modo tela cheia.
 *
 * @note src/engine/graphics.c
 */
void graphics_toggle_fullscreen(void) {
  if (!IsWindowReady()) { return; }

  ToggleFullscreen();

  graphics_state.width = GetScreenWidth();
  graphics_state.height = GetScreenHeight();
  graphics_state.delta_time = GetFrameTime();
}