# minesweeper

Minesweeper developed in C, featuring dynamic board generation, safe first-click mechanics, recursive flood-fill cell expansion, multiple difficulty levels, customizable themes, game state management, and structured modular architecture.

---

## Funcionalidades

* geração dinâmica de tabuleiro
* posicionamento aleatório de bombas
* primeiro clique seguro
* cálculo de bombas adjacentes
* expansão recursiva
* sistema de bandeiras
* detecção de vitória
* detecção de derrota
* múltiplos níveis de dificuldade
* múltiplos temas visuais
* sistema de menu
* gerenciamento de cenas
* cronômetro da partida
* arquitetura desacoplada entre engine, jogo e renderização

---

## Dificuldades

| Dificuldade | Tamanho | Bombas |
| ----------- | ------- | ------ |
| Beginner    | 8x8     | 12     |
| Easy        | 10x10   | 10     |
| Medium      | 16x16   | 40     |
| Hard        | 20x20   | 100    |
| Huge        | 32x32   | 220    |
| Extreme     | 16x30   | 280    |

---

## Temas

O jogo possui suporte aos seguintes temas:

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
└── 📂 bin/
└── 📂 assets/
│  └── 📂 fonts/
│    ├── 📄 Roboto-Bold.ttf
│    ├── 📄 Roboto-Regular.ttf
└── 📂 include/
│  └── 📂 app/
│    ├── 📄 app_state.h
│    ├── 📄 scene.h
│    ├── 📄 settings.h
│  └── 📂 engine/
│    ├── 📄 graphics.h
│    ├── 📄 input.h
│    ├── 📄 timer.h
│  └── 📂 game/
│    ├── 📄 board.h
│    ├── 📄 cell.h
│    ├── 📄 difficulty.h
│    ├── 📄 game_manager.h
│    ├── 📄 game_state.h
│    ├── 📄 game_status.h
│  └── 📂 render/
│    ├── 📄 font.h
│    ├── 📄 hud.h
│    ├── 📄 menu.h
│    ├── 📄 render.h
│    ├── 📄 theme.h
└── 📂 src/
│  └── 📂 app/
│    ├── 📄 scene.c
│    ├── 📄 settings.c
│  └── 📂 engine/
│    ├── 📄 graphics.c
│    ├── 📄 input.c
│    ├── 📄 timer.c
│  └── 📂 game/
│    ├── 📄 board.c
│    ├── 📄 difficulty.c
│    ├── 📄 game_manager.c
│  ├── 📄 main.c
│  └── 📂 render/
│    ├── 📄 font.c
│    ├── 📄 hud.c
│    ├── 📄 menu.c
│    ├── 📄 render.c
│    └── 📄 theme.c
```

---

## Controles

### Menu

```text
ENTER      -> iniciar partida
R          -> alterar dificuldade
BACKSPACE  -> alterar tema
ESC        -> sair
```

### Partida

```text
Botão esquerdo -> revelar célula
Botão direito  -> adicionar/remover bandeira
R              -> reiniciar partida
ESC            -> voltar ao menu
```

---

## Tecnologias Utilizadas

* C
* Raylib
* GCC
* Makefile

---

## Como Executar

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

---

## Principais Mudanças da Arquitetura Atual

* remoção completa de SDL2
* remoção completa de SDL2_ttf
* migração para Raylib
* integração do sistema de menu
* integração do sistema de configurações
* integração do sistema de temas
* introdução do Scene Manager
* reorganização da estrutura do projeto
* separação entre App, Engine, Game e Render
* substituição do sistema de janela por Graphics
* substituição do sistema de entrada por Input da Engine
* substituição do sistema de timer por Timer da Engine
* atualização do Makefile para Raylib
* geração do executável em `bin/`

---

## Melhorias Futuras

* animações de células
* efeitos sonoros
* sistema de recordes
* salvamento de configurações
* suporte a resoluções personalizadas
* menu de configurações avançadas
* estatísticas de partidas
* sistema de perfis
* suporte a gamepad
* internacionalização
* testes automatizados
