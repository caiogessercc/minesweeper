#include "font.h"

/**
 * @brief Inicializa o subsistema SDL_ttf.
 *
 * @return true Se a inicialização foi concluída com sucesso.
 * @return false Caso contrário.
 *
 * @note src/render/font.c
 */
bool font_initialize(void) { return TTF_Init() == 0; }

/**
 * @brief Finaliza o subsistema SDL_ttf.
 *
 * @note src/render/font.c
 */
void font_destroy(void) { TTF_Quit(); }

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
 * @note src/render/font.c
 */
bool font_load(
  font_t *font,
  const char *path,
  int32_t size
) {
  if (font == NULL || path == NULL) { return false; }
  font->handle = TTF_OpenFont(path, size);
  if (font->handle == NULL) { return false; }
  font->size = size;
  return true;
}

/**
 * @brief Libera uma fonte carregada.
 *
 * @param font Estrutura da fonte.
 *
 * @note src/render/font.c
 */
void font_unload(
  font_t *font
) {
  if (font == NULL || font->handle == NULL) { return; }
  TTF_CloseFont(font->handle);
  font->handle = NULL;
  font->size = 0;
}

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
 * @note src/render/font.c
 */
void font_draw_text(
  SDL_Renderer *renderer,
  const font_t *font,
  const char *text,
  int32_t x,
  int32_t y,
  SDL_Color color
) {
  if (renderer == NULL || font == NULL || font->handle == NULL || text == NULL) { return; }
  SDL_Surface *surface = TTF_RenderText_Blended(font->handle, text, color);
  if (surface == NULL) { return; }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == NULL) {
    SDL_FreeSurface(surface);
    return;
  }

  SDL_Rect destination = {
    .x = x,
    .y = y,
    .w = surface->w,
    .h = surface->h
  };

  SDL_RenderCopy(
    renderer,
    texture,
    NULL,
    &destination
  );

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

/**
 * @brief Obtém a largura de um texto.
 *
 * @param font Fonte utilizada.
 * @param text Texto analisado.
 *
 * @return Largura em pixels.
 *
 * @note src/render/font.c
 */
int32_t font_get_text_width(
  const font_t *font,
  const char *text
) {
  if (font == NULL || font->handle == NULL || text == NULL) { return 0; }

  int width = 0;
  int height = 0;

  TTF_SizeText(
    font->handle,
    text,
    &width,
    &height
  );

  return width;
}

/**
 * @brief Obtém a altura de um texto.
 *
 * @param font Fonte utilizada.
 *
 * @return Altura em pixels.
 *
 * @note src/render/font.c
 */
int32_t font_get_text_height(
  const font_t *font
) {
  if (font == NULL || font->handle == NULL) { return 0; }
  return TTF_FontHeight(font->handle);
}