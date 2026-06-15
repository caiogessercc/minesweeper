#include <stddef.h>

#include "app/settings.h"

/**
 * @brief Configurações padrão da aplicação.
 *
 * @note src/app/settings.c
 */
static const settings_t default_settings = {
  .difficulty = DIFFICULTY_BEGINNER,
  .theme = THEME_CLASSIC,
  .show_fps = false,
  .fullscreen = false
};

/**
 * @brief Inicializa as configurações com os valores padrão.
 *
 * Define o estado inicial das preferências do usuário
 * ao abrir a aplicação pela primeira vez.
 *
 * @param settings Configurações da aplicação.
 *
 * @note src/app/settings.c
 */
void settings_initialize(
  settings_t *settings
) {
  if (settings == NULL) { return; }
  *settings = default_settings;
}