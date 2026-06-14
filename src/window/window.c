#include "window.h"

#define WINDOW_BACKGROUND_R 30
#define WINDOW_BACKGROUND_G 30
#define WINDOW_BACKGROUND_B 30

/**
 * @brief Inicializa a SDL e cria uma nova janela.
 *
 * Cria a janela e o renderer associados ao contexto
 * informado.
 *
 * @param window Contexto da janela.
 * @param config Configuração utilizada na criação.
 *
 * @return true Se a inicialização foi concluída com sucesso.
 * @return false Se ocorreu alguma falha durante a inicialização.
 *
 * @note src/window/window.c
 */
bool window_initialize(
  window_t *window,
  const window_config_t *config
) {
  if (window == NULL || config == NULL) { return false; }
  window->handle = NULL;
  window->renderer = NULL;
  window->is_open = false;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) { return false; }
  window->handle = SDL_CreateWindow(
    config->title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    config->width,
    config->height,
    SDL_WINDOW_SHOWN
  );

  if (window->handle == NULL) {
    SDL_Quit();
    return false;
  }

  window->renderer = SDL_CreateRenderer(
    window->handle,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (window->renderer == NULL) {
    SDL_DestroyWindow(window->handle);
    SDL_Quit();
    return false;
  }

  window->is_open = true;
  return true;
}

/**
 * @brief Processa os eventos da janela.
 *
 * Atualiza o estado interno da janela a partir
 * dos eventos recebidos pela SDL.
 *
 * @param window Contexto da janela.
 *
 * @note src/window/window.c
 * 
 * @deprecated
 * Os eventos da aplicação são processados
 * por input_poll_events().
 */
void window_poll_events(
  window_t *window
) {
  if (window == NULL) { return; }
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      window->is_open = false;
    }
  }
}

/**
 * @brief Atualiza o título da janela.
 *
 * @param window Contexto da janela.
 * @param title Novo título da janela.
 *
 * @note src/window/window.c
 */
void window_set_title(
  window_t *window,
  const char *title
) {
  if (window == NULL || window->handle == NULL || title == NULL) { return; }
  SDL_SetWindowTitle(window->handle, title);
}

/**
 * @brief Limpa o conteúdo atual da janela.
 *
 * Prepara o renderer para o início de um novo frame.
 *
 * @param window Contexto da janela.
 *
 * @note src/window/window.c
 */
void window_clear(
  window_t *window
) {
  if (window == NULL || window->renderer == NULL) { return; }
  SDL_SetRenderDrawColor(
    window->renderer,
    WINDOW_BACKGROUND_R,
    WINDOW_BACKGROUND_G,
    WINDOW_BACKGROUND_B,
    255
  );
  SDL_RenderClear(window->renderer);
}

/**
 * @brief Apresenta o frame renderizado na tela.
 *
 * Exibe o conteúdo atualmente desenhado pelo renderer.
 *
 * @param window Contexto da janela.
 *
 * @note src/window/window.c
 */
void window_present(
  window_t *window
) {
  if (window == NULL || window->renderer == NULL) { return; }
  SDL_RenderPresent(window->renderer);
}

/**
 * @brief Verifica se a janela permanece aberta.
 *
 * @param window Contexto da janela.
 *
 * @return true Se a janela estiver aberta.
 * @return false Se a janela tiver sido encerrada.
 *
 * @note src/window/window.c
 */
bool window_is_open(
  const window_t *window
) {
  if (window == NULL) { return false; }
  return window->is_open;
}

/**
 * @brief Libera os recursos associados à janela.
 *
 * Destrói o renderer, a janela SDL e encerra
 * os subsistemas utilizados.
 *
 * @param window Contexto da janela.
 *
 * @note src/window/window.c
 */
void window_destroy(
  window_t *window
) {
  if (window == NULL) { return; }
  if (window->renderer != NULL) {
    SDL_DestroyRenderer(window->renderer);
    window->renderer = NULL;
  }

  if (window->handle != NULL) {
    SDL_DestroyWindow(window->handle);
    window->handle = NULL;
  }

  SDL_Quit();
  *window = (window_t){ 0 };
  window->is_open = false;
}