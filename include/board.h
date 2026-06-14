#pragma once

#include <stdbool.h>

#include "game_state.h"
#include "difficulty.h"

/**
 * @brief Inicializa o estado do jogo e aloca o tabuleiro.
 *
 * Configura os dados da partida a partir da dificuldade
 * selecionada e realiza a alocação dinâmica das células.
 *
 * @param game Estado do jogo a ser inicializado.
 * @param config Configuração da dificuldade utilizada.
 *
 * @return true Se a inicialização foi concluída com sucesso.
 * @return false Se ocorreu falha de alocação ou parâmetros inválidos.
 *
 * @note include/board.h
 */
bool board_initialize(
  game_state_t *game,
  const difficulty_config_t *config
);

/**
 * @brief Libera todos os recursos associados ao tabuleiro.
 *
 * Remove a memória alocada dinamicamente para as células
 * e invalida os ponteiros utilizados pelo estado do jogo.
 *
 * @param game Estado do jogo a ser destruído.
 *
 * @note include/board.h
 */
void board_destroy(
  game_state_t *game
);

/**
 * @brief Distribui bombas aleatoriamente pelo tabuleiro.
 *
 * Posiciona a quantidade de bombas definida pela
 * configuração da dificuldade atual.
 *
 * @param game Estado do jogo.
 *
 * @note include/board.h
 */
void board_generate_bombs(
  game_state_t *game
);

/**
 * @brief Distribui bombas preservando uma área segura.
 *
 * Garante que a célula selecionada no primeiro clique
 * e suas posições adjacentes não contenham bombas.
 *
 * @param game Estado do jogo.
 * @param safe_row Linha segura.
 * @param safe_column Coluna segura.
 *
 * @note include/board.h
 */
void board_generate_bombs_safe(
  game_state_t *game,
  int safe_row,
  int safe_column
);

/**
 * @brief Calcula a quantidade de bombas adjacentes.
 *
 * Percorre todas as células do tabuleiro e calcula
 * quantas bombas existem nas posições vizinhas.
 *
 * @param game Estado do jogo.
 *
 * @note include/board.h
 */
void board_calculate_adjacent_bombs(
  game_state_t *game
);

/**
 * @brief Revela uma célula do tabuleiro.
 *
 * Caso a célula possua valor zero, células
 * vizinhas poderão ser reveladas automaticamente.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha da célula.
 * @param column Índice da coluna da célula.
 *
 * @note include/board.h
 */
void board_reveal_cell(
  game_state_t *game,
  int row,
  int column
);

/**
 * @brief Alterna o estado de bandeira de uma célula.
 *
 * Adiciona ou remove uma bandeira da posição informada.
 *
 * @param game Estado do jogo.
 * @param row Índice da linha da célula.
 * @param column Índice da coluna da célula.
 *
 * @note include/board.h
 */
void board_toggle_flag(
  game_state_t *game,
  int row,
  int column
);

/**
 * @brief Revela todas as bombas do tabuleiro.
 *
 * Utilizada quando a partida termina em derrota,
 * permitindo exibir todas as bombas ao jogador.
 *
 * @param game Estado do jogo.
 *
 * @note include/board.h
 */
void board_reveal_all_bombs(
  game_state_t *game
);

/**
 * @brief Verifica se a partida foi vencida.
 *
 * @param game Estado atual do jogo.
 *
 * @return true Se a condição de vitória foi atingida.
 * @return false Caso contrário.
 *
 * @note include/board.h
 */
bool board_check_victory(
  const game_state_t *game
);

/**
 * @brief Verifica se a partida terminou.
 *
 * @param game Estado atual do jogo.
 *
 * @return true Se a partida terminou.
 * @return false Se a partida ainda está em andamento.
 *
 * @note include/board.h
 */
bool board_is_game_over(
  const game_state_t *game
);