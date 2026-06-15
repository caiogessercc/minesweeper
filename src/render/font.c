#include <stddef.h>
#include "raylib.h"

#include "render/font.h"

#define FONT_PATH "assets/fonts/Roboto-Regular.ttf"

static Font application_font = { 0 };

/**
 * @brief Converte color_t para Color.
 *
 * @param color Cor abstrata.
 *
 * @return Cor Raylib.
 *
 * @note src/render/font.c
 */
static Color font_to_raylib_color(
  color_t color
) {
  return (Color) {
    .r = color.r,
    .g = color.g,
    .b = color.b,
    .a = color.a
  };
}

/**
 * @brief Inicializa o sistema de fontes.
 *
 * @return true Se a inicialização foi concluída.
 * @return false Caso contrário.
 *
 * @note src/render/font.c
 */
bool font_initialize(void) {
  application_font = LoadFontEx(FONT_PATH, 32, NULL, 0);
  return application_font.texture.id != 0;
}

/**
 * @brief Finaliza o sistema de fontes.
 *
 * @note src/render/font.c
 */
void font_destroy(void) {
  if (application_font.texture.id == 0) { return; }
  UnloadFont(application_font);
  application_font = (Font){ 0 };
}

/**
 * @brief Desenha um texto na tela.
 *
 * @param text Texto a ser desenhado.
 * @param x Posição horizontal.
 * @param y Posição vertical.
 * @param font_size Tamanho da fonte.
 * @param color Cor do texto.
 *
 * @note src/render/font.c
 */
void font_draw_text(
  const char *text,
  float x,
  float y,
  float font_size,
  color_t color
) {
  if (text == NULL) { return; }
  if (application_font.texture.id == 0) { return; }

  DrawTextEx(
    application_font,
    text,
    (Vector2) {
      .x = x,
      .y = y
    },
    font_size,
    1.0f,
    font_to_raylib_color(color)
  );
}

/**
 * @brief Desenha um texto centralizado horizontalmente.
 *
 * @param text Texto a ser desenhado.
 * @param y Posição vertical.
 * @param font_size Tamanho da fonte.
 * @param color Cor do texto.
 *
 * @note src/render/font.c
 */
void font_draw_text_centered(
  const char *text,
  float y,
  float font_size,
  color_t color
) {
  if (text == NULL) { return; }

  float width = font_measure_text(text, font_size);
  float x = (GetScreenWidth() - width) / 2.0f;

  font_draw_text(
    text,
    x,
    y,
    font_size,
    color
  );
}

/**
 * @brief Obtém a largura de um texto.
 *
 * @param text Texto.
 * @param font_size Tamanho da fonte.
 *
 * @return Largura em pixels.
 *
 * @note src/render/font.c
 */
float font_measure_text(
  const char *text,
  float font_size
) {
  if (text == NULL) { return 0.0f; }
  if (application_font.texture.id == 0) { return 0.0f; }

  Vector2 size =
    MeasureTextEx(
      application_font,
      text,
      font_size,
      1.0f
    );

  return size.x;
}