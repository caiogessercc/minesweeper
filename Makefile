PROJECT := minesweeper

SRC_DIR := src
INC_DIR := include

BUILD_DIR := build
BIN_DIR := bin

CC := gcc

CFLAGS := \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-std=c2x \
	-I$(INC_DIR)

RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell pkg-config --libs raylib 2>/dev/null)

CFLAGS += $(RAYLIB_CFLAGS)
LDFLAGS += $(RAYLIB_LIBS)
LDFLAGS += -lm
LDFLAGS += -lX11

SOURCES := $(shell find $(SRC_DIR) -name "*.c")
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

TARGET := $(BIN_DIR)/$(PROJECT)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
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
	rm -rf $(BIN_DIR)

.PHONY: rebuild
rebuild: clean all

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: rebuild

.PHONY: release
release: CFLAGS += -O3
release: rebuild