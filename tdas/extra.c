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

#define MAX_LINE_LENGTH 4096
#define MAX_FIELDS      128
#define MAX_LINEA 16

// strdup propio para asegurar portabilidad
void *_mystrdup(const char *token) {
  size_t length = strlen(token)+1;
  char *newToken = (char *) malloc(length);
  if(!newToken) return NULL;

  memcpy(newToken, token, length);
  return newToken;
}

// Función para limpiar la pantalla
void limpiarPantalla() { system(CLEAR_COMMAND); }

void presioneTeclaParaContinuar() {
  puts("Presione cualquier tecla para continuar...");
  int c;
  while((c=getchar())!='\n' && c != EOF);
}

// Se lee únicamente 1 carácter y en caso de no ser válido se retorna carácter nulo
char readCharOption() {
  char linea[MAX_LINEA];
  if(!fgets(linea, sizeof(linea), stdin)) return '\0';
  if(strchr(linea, '\n') == NULL) {
    int c;
    while((c=getchar())!='\n' && c != EOF);
  }

  int i=0;
  while(linea[i] && isspace((unsigned char) linea[i])) i++;

  return linea[i] ? linea[i] : '\0';
}

// Separadores
void separador1() {
  puts("\t----------------------------------------");
}

void separador2() {
  puts("\t========================================");
}