PROJECT := minesweeper

SRC_DIR := src
INC_DIR := include

BUILD_DIR := build
TEST_DIR := tests

CC := gcc

CFLAGS := \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-std=c2x \
	-I$(INC_DIR)

SDL_CFLAGS := $(shell sdl2-config --cflags 2>/dev/null)
SDL_LIBS := $(shell sdl2-config --libs 2>/dev/null)

TTF_CFLAGS := $(shell pkg-config --cflags SDL2_ttf 2>/dev/null)
TTF_LIBS := $(shell pkg-config --libs SDL2_ttf 2>/dev/null)

CFLAGS += $(SDL_CFLAGS)
CFLAGS += $(TTF_CFLAGS)

LDFLAGS += $(SDL_LIBS)
LDFLAGS += $(TTF_LIBS)

SOURCES := $(shell find $(SRC_DIR) -name "*.c")
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

TARGET := $(TEST_DIR)/$(PROJECT)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(TEST_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TEST_DIR)

.PHONY: rebuild
rebuild: clean all

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: rebuild

.PHONY: release
release: CFLAGS += -O3
release: rebuild