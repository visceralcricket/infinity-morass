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

List *split_string(const char *str, const char *delim) {
  List *result = list_create();
  char *token = strtok((char *)str, delim);

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++;
    }

    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1;
    while (*end == ' ' && end > token) {
      *end = '\0';
      end--;
    }

    // Copiar el token en un nuevo string
    char *new_token = _mystrdup(token);

    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token);

    // Obtener el siguiente token
    token = strtok(NULL, delim);
  }

  return result;
}

// Función para limpiar la pantalla
void limpiarPantalla() { system(CLEAR_COMMAND); }

void presioneEnterParaContinuar() {
  puts("Presione Enter para continuar...");
  int c;
  while((c=getchar())!='\n' && c != EOF);
}

// Función principal para generar el laberinto
void generate_maze(int maze[N][N], int difficulty) {
    int safe[N][N] = {0};
    int visited[N][N] = {0};

    // 1. Trazar el camino seguro desde el inicio (0,0) a la meta (N-1, N-1)
    // build_safe_path(0, 0, safe, visited);

    // 2. Rellenar el resto de la matriz basándonos en la dificultad
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (safe[i][j] == 1) {
                // Si es parte del camino seguro, obligatoriamente es espacio libre
                maze[i][j] = 0; 
            } else {
                // Si no es el camino seguro, tiramos un dado de 0 a 99
                // 'difficulty' actúa como el porcentaje de aparición de obstáculos
                int r = rand() % 100;
                if (r < difficulty) {
                    maze[i][j] = 1; // Pared / Obstáculo
                } else {
                    maze[i][j] = 0; // Espacio libre
                }
            }
        }
    }
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
  puts("----------------------------------------");
}

void separador2() {
  puts("========================================");
}