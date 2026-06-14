#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief Representa uma fonte carregada em memória.
 *
 * Encapsula o recurso SDL_ttf utilizado
 * durante a renderização de textos.
 *
 * @note include/font.h
 */
typedef struct {
  TTF_Font *handle;
  int32_t size;
} font_t;

/**
 * @brief Inicializa o subsistema SDL_ttf.
 *
 * @return true Se a inicialização foi concluída com sucesso.
 * @return false Caso contrário.
 *
 * @note include/font.h
 */
bool font_initialize(void);

/**
 * @brief Finaliza o subsistema SDL_ttf.
 *
 * @note include/font.h
 */
void font_destroy(void);

/**
 * @brief Carrega uma fonte a partir de um arquivo.
 *
 * @param font Estrutura da fonte.
 * @param path Caminho do arquivo .ttf.
 * @param size Tamanho da fonte em pixels.
 *
 * @return true Se a fonte foi carregada.
 * @return false Caso contrário.
 *
 * @note include/font.h
 */
bool font_load(
  font_t *font,
  const char *path,
  int32_t size
);

/**
 * @brief Libera uma fonte carregada.
 *
 * @param font Estrutura da fonte.
 *
 * @note include/font.h
 */
void font_unload(
  font_t *font
);

/**
 * @brief Renderiza um texto na tela.
 *
 * @param renderer Renderer SDL.
 * @param font Fonte utilizada.
 * @param text Texto a ser renderizado.
 * @param x Posição horizontal.
 * @param y Posição vertical.
 * @param color Cor do texto.
 *
 * @note include/font.h
 */
void font_draw_text(
  SDL_Renderer *renderer,
  const font_t *font,
  const char *text,
  int32_t x,
  int32_t y,
  SDL_Color color
);

/**
 * @brief Obtém a largura de um texto.
 *
 * @param font Fonte utilizada.
 * @param text Texto analisado.
 *
 * @return Largura em pixels.
 *
 * @note include/font.h
 */
int32_t font_get_text_width(
  const font_t *font,
  const char *text
);

/**
 * @brief Obtém a altura de um texto.
 *
 * @param font Fonte utilizada.
 *
 * @return Altura em pixels.
 *
 * @note include/font.h
 */
int32_t font_get_text_height(
  const font_t *font
);