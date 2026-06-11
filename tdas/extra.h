#ifndef EXTRA_H
#define EXTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Necesario para usar _getch
#include <ctype.h> // Necesario para readCharOption
#include "list.h"

// strdup propio para asegurar portabilidad
void *_mystrdup(const char *token);

// Función para limpiar la pantalla
void limpiarPantalla();

void presioneTeclaParaContinuar();

// Leer input de tal forma que los posibles errores en el mismo sean tratados correctamente.
char readCharOption();

// Separador de 40 dashes '-'
void separador1();

// Separador de 40 símbolos igual '='
void separador2();

#endif