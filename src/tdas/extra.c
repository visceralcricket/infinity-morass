#include "extra.h"
/* +++
Este bloque de código se modificó para hacer que el programa sea portable y funcione
correctamente en la Powershell de windows, puesto que el comando para limpiar la pantalla
es "cls" y el "clear" actual parece no funcionar correctamente.
--- */
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

#define MAX_LINEA 16

// Función para limpiar la pantalla
void limpiarPantalla() { system(CLEAR_COMMAND); }

void limpiarInputPendiente() {
  while(_kbhit()) _getch();
}

void presioneTeclaParaContinuar() {
  printf("Presione cualquier tecla para continuar.");
  fflush(stdout);

  limpiarInputPendiente();
  
  _getch();
}

// Se lee únicamente 1 carácter y en caso de no ser válido se retorna carácter nulo
char readCharOption() {

  char linea[MAX_LINEA];

  // return '\0'; modificado a exit(0);
  if(!fgets(linea, sizeof(linea), stdin)) exit(0);

  if(strchr(linea, '\n') == NULL) {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
  }

  return linea[0];
}

// Separadores
void separador1() {
  puts("\t\t" FORMAT_DIM "----------------------------------------" FORMAT_RESET);
}

void separador2() {
  puts("\t\t" FORMAT_BOLD "========================================" FORMAT_RESET);
}