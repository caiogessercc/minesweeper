# minesweeper

Minesweeper developed in C, featuring dynamic board generation, safe first-click mechanics, recursive flood-fill cell expansion, multiple difficulty levels, customizable themes, game state management, and structured modular architecture.

---

## Funcionalidades

* Geração dinâmica de tabuleiro
* Posicionamento aleatório de bombas
* Primeiro clique seguro
* Cálculo de bombas adjacentes
* Expansão recursiva de células vazias
* Sistema de bandeiras
* Detecção de vitória
* Detecção de derrota
* Cronômetro da partida
* HUD com informações em tempo real
* Múltiplos níveis de dificuldade
* Temas visuais personalizáveis
* Interface gráfica com SDL2

---

## Dificuldades

| Dificuldade | Tamanho | Bombas |
| ----------- | ------- | ------ |
| Beginner    | 8x8     | 12     |
| Easy        | 10x10   | 10     |
| Medium      | 16x16   | 40     |
| Hard        | 20x20   | 100    |
| Huge        | 30x30   | 220    |
| Extreme     | 16x30   | 280    |

---

## Temas

O jogo possui os seguintes temas visuais:

* Classic
* Dark
* Light
* Retro

---

## Estrutura do Projeto

```markdown
. 📂 minesweeper
├── 📄 Makefile
├── 📄 README.md
└── 📂 assets/
│  └── 📂 fonts/
│    ├── 📄 Roboto-Bold.ttf
│    ├── 📄 Roboto-Regular.ttf
└── 📂 include/
│  ├── 📄 board.h
│  ├── 📄 cell.h
│  ├── 📄 difficulty.h
│  ├── 📄 font.h
│  ├── 📄 game_manager.h
│  ├── 📄 game_state.h
│  ├── 📄 hud.h
│  ├── 📄 input.h
│  ├── 📄 render.h
│  ├── 📄 theme.h
│  ├── 📄 timer.h
│  ├── 📄 window.h
└── 📂 src/
│  └── 📂 game/
│    ├── 📄 board.c
│    ├── 📄 difficulty.c
│    ├── 📄 game_manager.c
│    ├── 📄 timer.c
│  └── 📂 input/
│    ├── 📄 input.c
│  ├── 📄 main.c
│  └── 📂 render/
│    ├── 📄 font.c
│    ├── 📄 hud.c
│    ├── 📄 render.c
│    ├── 📄 theme.c
│  └── 📂 window/
│    └── 📄 window.c
```

---

## Controles

| Ação                       | Tecla                   |
| -------------------------- | ----------------------- |
| Revelar célula             | Botão esquerdo do mouse |
| Adicionar/remover bandeira | Botão direito do mouse  |
| Reiniciar partida          | R                       |
| Sair do jogo               | ESC                     |

---

## Como executar

### Requisitos

* GCC
* SDL2
* SDL2_ttf
* Make

### Compilar

```bash
make
```

### Executar

```bash
make run
```

### Limpar arquivos gerados

```bash
make clean
```
