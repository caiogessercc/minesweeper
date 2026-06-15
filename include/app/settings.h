#pragma once

#include <stdbool.h>

#include "game/difficulty.h"
// TODO: render/theme.h
#include "render/theme.h"

/**
 * @brief Configurações da aplicação.
 *
 * Armazena preferências selecionadas pelo
 * usuário antes do início de uma partida.
 *
 * @note include/app/settings.h
 */
typedef struct {
  difficulty_t difficulty;
  theme_type_t theme;
  bool show_fps;
  bool fullscreen;
} settings_t;

/**
 * @brief Inicializa as configurações com valores padrão.
 *
 * @param settings Configurações da aplicação a serem inicializadas.
 *
 * @note include/app/settings.h
 */
void settings_initialize(
  settings_t *settings
);