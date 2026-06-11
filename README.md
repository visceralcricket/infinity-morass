# **infinity-morass**

> **IMPORTANTE**
* Se utiliza convención **"camelCase"** para programar la totalidad del programa a lo largo de todos los archivos, por favor tener presente esto al momento de contribuir al proyecto.

## ***Historial de cambios***

* Se crearon **2** archivos nuevos para distribuir el main y dejarlo más limpio:
---
* 
  + **`game.h`** tiene todos los `#include` para las librerías, las definiciones para los movimientos, las teclas que se van a leer para mover al personaje y los prototipos de las entidades.

  + **`game.c`** tiene las entidades en sí, como el `Player`, `Enemy`, `Stats`, las funciones para el grafo y una función para manejar el input en Windows.
---

* El main se relegó únicamente para menús y cosas simples; tiene una versión muy simple de la interfaz del menú principal, por ende más allá de eso faltaría continuar las otras 2 interfaces de navegación y combate.

* Se renombró **`map.c`** y **`map.h`** a **`hashmap.c`** y **`hashmap.h`** para que sea un poco más autoexplicativo.

* Se limpió y afinó el archivo **`extra.c`** para dejar fuera las funciones que no sirven: `split_string` **NO** debe ser eliminada, primero considerar su potencial uso para la lectura del nombre del jugador y otras posibles utilidades.

---
* Se desplazó la carpeta con los TDAs dentro de la carpeta donde estaban ubicados main, game.c y game.h ("**src/**") para mantener todo el código fuente en un único directorio.

## **Distribución de directorios**

> **`src/`**
> Directorio principal del código fuente. Contiene el orquestador y la lógica central del dominio.
>

> * **`main.c`**: Archivo principal del programa. Contiene el bucle de estados en los que se encuentra el jugador y gestiona la transición entre la interfaz del menú principal y los distintos modos de juego interactivos (como `runExplorationMode`). Relega la lógica pesada a los archivos **`game`** para mantener una arquitectura limpia y modular.
>
> * **`game.h`**: Cabecera/encabezado de la arquitectura del programa. Concentra la declaración de estructuras de memoria (`Player`, `Enemy`, `State`), enumeraciones de estado (`GameMode`), macros estructurales (como las dimensiones topológicas de la matriz `N`) y expone los prototipos públicos del motor del juego.
>
> * **`game.c`**: Implementación de la lógica interna del juego. Contiene los algoritmos de generación procedimental de laberintos (`generateMaze`, `buildSafePath`), las funciones algorítmicas para el recorrido espacial en grafos y el motor de procesamiento de inputs dependiente de la plataforma (`handleWindowsInput`).

[![Last Commit](https://img.shields.io/github/last-commit/visceralcricket/infinity-morass/main-dev)](https://github.com/visceralcricket/infinity-morass/commits/feature/main-menu)