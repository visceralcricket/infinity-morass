# Variables del compilador
CC = gcc
CFLAGS = -Wall -Wextra -Isrc
TARGET = infinity-morass

# Todos los archivos fuente (.c)
SRCS = src/main.c \
		src/engine/game.c \
		src/engine/enmap.c \
		src/io/storage.c \
		src/ui/render.c \
		src/tdas/extra.c \
		src/tdas/hashmap.c \
		src/tdas/heap.c \
		src/tdas/list.c

# Reemplazar los archivos de extensión .c por .o para crear los archivos objeto
OBJS = $(SRCS:.c = .o)

# Regla principal: compilar todo el programa
all: $(TARGET)

# Regla para enlazar los archivos objeto en el ejecutable (.exe) final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar cada .c en un .o individualmente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar todos los archivos compilados (build limpio)
clean:
	del /Q /S *.o
	del /Q $(TARGET).exe