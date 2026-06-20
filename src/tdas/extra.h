#ifndef EXTRA_H
#define EXTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Necesario para usar _getch
#include <ctype.h> // Necesario para readCharOption
#include "list.h"

// ======== Terminal UI formatting (ANSI Codes) ========
#define FORMAT_RESET "\033[0m"
#define FORMAT_BOLD "\033[1m"
#define FORMAT_DIM "\033[2m"

// ======== Text colors ========
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// ======== Cursor repositioning ========
// Establecer coordenadas en las que posicionar el cursor
#define SET_CURSOR_POS(row, col) printf("\033[%d;%dH", (row), (col))
#define MOVE_CURSOR "\033[H"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define CLEAR_LINE_TO_END "\033[K"

// strdup propio para asegurar portabilidad
void *_mystrdup(const char *token);

// Función para limpiar la pantalla
void limpiarPantalla();

void presioneTeclaParaContinuar();

// Leer input de tal forma que los posibles errores en el mismo sean tratados correctamente.
char readCharOption();

// Separador de 2 tabulados + 40 dashes '-'
void separador1();

// Separador de 2 tabulados + 40 símbolos igual '='
void separador2();

#endif