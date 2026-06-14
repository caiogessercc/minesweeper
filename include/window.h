#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>

/**
 * @brief Armazena as configurações utilizadas para criar uma janela.
 *
 * Define as propriedades iniciais da janela SDL,
 * incluindo título e dimensões.
 *
 * @note include/window.h
 */
typedef struct {
  const char *title;
  int32_t width;
  int32_t height;
} window_config_t;

/**
 * @brief Representa uma janela SDL ativa.
 *
 * Armazena os recursos necessários para exibição
 * e renderização da aplicação.
 *
 * @note include/window.h
 */
typedef struct {
  SDL_Window *handle;
  SDL_Renderer *renderer;
  bool is_open;
} window_t;

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
 * @note include/window.h
 */
bool window_initialize(
  window_t *window,
  const window_config_t *config
);

/**
 * @brief Processa os eventos da janela.
 *
 * Atualiza o estado interno da janela com base
 * nos eventos recebidos pela SDL.
 *
 * @param window Contexto da janela.
 *
 * @note include/window.h
 */
void window_poll_events(
  window_t *window
);

/**
 * @brief Atualiza o título da janela.
 *
 * @param window Contexto da janela.
 * @param title Novo título da janela.
 *
 * @note include/window.h
 */
void window_set_title(
  window_t *window,
  const char *title
);

/**
 * @brief Limpa o conteúdo atual da janela.
 *
 * Prepara o renderer para o início de um novo frame.
 *
 * @param window Contexto da janela.
 *
 * @note include/window.h
 */
void window_clear(
  window_t *window
);

/**
 * @brief Apresenta o frame renderizado na tela.
 *
 * Exibe o conteúdo atualmente desenhado pelo renderer.
 *
 * @param window Contexto da janela.
 *
 * @note include/window.h
 */
void window_present(
  window_t *window
);

/**
 * @brief Verifica se a janela permanece aberta.
 *
 * @param window Contexto da janela.
 *
 * @return true Se a janela estiver aberta.
 * @return false Se a janela tiver sido encerrada.
 *
 * @note include/window.h
 */
bool window_is_open(
  const window_t *window
);

/**
 * @brief Libera os recursos associados à janela.
 *
 * Destrói o renderer, a janela SDL e encerra
 * os subsistemas utilizados.
 *
 * @param window Contexto da janela.
 *
 * @note include/window.h
 */
void window_destroy(
  window_t *window
);