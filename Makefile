# Forzar a Make a usar CMD de Windows, evitando conflictos con sh.exe de Git Bash
SHELL = cmd.exe

CC = gcc
CFLAGS = -Wall -Wextra -Isrc
TARGET = infinity-morass

# Todos los archivos fuente (.c)
SRCS = src/main.c \
		src/engine/game.c \
		src/engine/enmap.c \
		src/engine/combat.c \
		src/engine/objmap.c \
		src/engine/player.c \
		src/io/storage.c \
		src/ui/render.c \
		src/tdas/extra.c \
		src/tdas/hashmap.c \
		src/tdas/heap.c \
		src/tdas/list.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla limpia, absoluta e infalible
clean:
	del /Q /S *.o
	del /Q $(TARGET).exe