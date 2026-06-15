#pragma once

#include <stdbool.h>

#include "render/theme.h"

/**
 * @brief Inicializa o sistema de fontes.
 *
 * @return true Se a inicialização foi concluída.
 * @return false Caso contrário.
 *
 * @note include/render/font.h
 */
bool font_initialize(void);

/**
 * @brief Finaliza o sistema de fontes.
 *
 * Libera todos os recursos carregados.
 *
 * @note include/render/font.h
 */
void font_destroy(void);

/**
 * @brief Desenha um texto na tela.
 *
 * @param text Texto a ser desenhado.
 * @param x Posição horizontal.
 * @param y Posição vertical.
 * @param font_size Tamanho da fonte.
 * @param color Cor do texto.
 *
 * @note include/render/font.h
 */
void font_draw_text(
  const char *text,
  float x,
  float y,
  float font_size,
  color_t color
);

/**
 * @brief Desenha um texto centralizado horizontalmente.
 *
 * @param text Texto a ser desenhado.
 * @param y Posição vertical.
 * @param font_size Tamanho da fonte.
 * @param color Cor do texto.
 *
 * @note include/render/font.h
 */
void font_draw_text_centered(
  const char *text,
  float y,
  float font_size,
  color_t color
);

/**
 * @brief Obtém a largura de um texto.
 *
 * @param text Texto.
 * @param font_size Tamanho da fonte.
 *
 * @return Largura em pixels.
 *
 * @note include/render/font.h
 */
float font_measure_text(
  const char *text,
  float font_size
);