#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Configuração da janela gráfica.
 *
 * @note include/engine/graphics.h
 */
typedef struct {
  const char *title;
  int32_t width;
  int32_t height;
  int32_t target_fps;
  bool resizable;
  bool fullscreen;
} graphics_config_t;

/**
 * @brief Informações da superfície gráfica.
 *
 * @note include/engine/graphics.h
 */
typedef struct {
  int32_t width;
  int32_t height;
  float delta_time;
} graphics_state_t;

/**
 * @brief Inicializa o sistema gráfico.
 *
 * @param config Configuração da janela.
 *
 * @return true Se a inicialização foi concluída.
 * @return false Caso contrário.
 *
 * @note include/engine/graphics.h
 */
bool graphics_initialize(
  const graphics_config_t *config
);

/**
 * @brief Finaliza o sistema gráfico.
 *
 * @note include/engine/graphics.h
 */
void graphics_shutdown(void);

/**
 * @brief Inicia a renderização de um frame.
 *
 * @note include/engine/graphics.h
 */
void graphics_begin_frame(void);

/**
 * @brief Finaliza a renderização de um frame.
 *
 * @note include/engine/graphics.h
 */
void graphics_end_frame(void);

/**
 * @brief Verifica se a aplicação deve ser encerrada.
 *
 * @return true Se a aplicação deve encerrar.
 * @return false Caso contrário.
 *
 * @note include/engine/graphics.h
 */
bool graphics_should_close(void);

/**
 * @brief Atualiza informações da superfície gráfica.
 *
 * @note include/engine/graphics.h
 */
void graphics_update(void);

/**
 * @brief Obtém o estado gráfico atual.
 *
 * @return Estado gráfico atual.
 *
 * @note include/engine/graphics.h
 */
const graphics_state_t *graphics_get_state(void);

/**
 * @brief Obtém a largura atual da janela.
 *
 * @return Largura da janela.
 *
 * @note include/engine/graphics.h
 */
int32_t graphics_get_width(void);

/**
 * @brief Obtém a altura atual da janela.
 *
 * @return Altura da janela.
 *
 * @note include/engine/graphics.h
 */
int32_t graphics_get_height(void);

/**
 * @brief Alterna o modo tela cheia.
 *
 * @note include/engine/graphics.h
 */
void graphics_toggle_fullscreen(void);