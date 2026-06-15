# **infinity-morass**
`versión: 1.5.0`

> **IMPORTANTE**
* Se utiliza convención **"camelCase"** para programar la totalidad del programa a lo largo de todos los archivos, por favor tener presente esto al momento de contribuir al proyecto.

* Comando para compilar: `>gcc -I. src/*.c src/tdas/*.c -o prueba`
  
* Comando para establecer UTF-8: `[Console]::OutputEncoding = [System.text.Encoding]::UTF8`

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

* Se mejoró el sistema de navegación del mapa para una experiencia de juego más fluida además de la implementación de una funcionalidad para generar salidas / entradas a los siguientes niveles(mazmorras) de forma aleatoria.

* Se finalizó el sistema de carga de partidas guardadas en el sistema en base al nombre del usuario.

* Se refactorizó la estructura de lista enlazada simple a una lista enlazada doble (**"list.c", "list.h"**)

* Se incluyó el sistema de generación de enemigos **"enemy-gen.c"**.

* Se añadieron nuevas carpetas en las que organizar el proyecto.

* Se refactorizó la implementación de la estructura **"hashmap"** para que se adhiera correctamente a los requisitos del programa.

* Añadido archivo "**MakeFile**" para automatizar compilación del programa; para hacer uso del mismo, abra powershell o su terminal de elección ubicado en el directorio "*infinity-morass*" y utilice el siguiente comando:


  > `mingw32-make`
  
  Con esto realizado, se creará un ejecutable .exe en el directorio donde está ubicado para abrir el programa.
---

* Se implementó versión inicial de la vista de inventario y sub-menú de ajustes (1.5.0)

* Parche (1.5.1): Arreglado bug que causaba que el programa se colgase; preparando un siguiente parche para evitar doble-output de ciertas partes del menú exploración y pérdida total de respuesta a input al abrir el menú de ajustes sobre el mapa.

* Parche (1.5.2): Se arregló el duplicado del menú de exploración y se verificó que los input handlers sean llamados correctamente, pero el programa sigue colgándose y dejando de responder a cualquier tipo de input al entrar al sub-menú de ajustes en el mapa.

## **Distribución de directorios**

> * **`src/`**: Directorio principal del código fuente. Contiene las funcionalides del programa y la lógica central del mismo.
>
---
> * **`main.c`**: Archivo principal del programa. Contiene el bucle de estados en los que se encuentra el jugador y gestiona la transición entre la interfaz del menú principal y los distintos modos de juego interactivos (como `runExplorationMode`). Relega la lógica pesada a los archivos **`game`** para mantener una arquitectura limpia y modular.
>
> * **`engine/`**
>
  >   * **`game.c`**: Implementación de la lógica interna del juego. Contiene los algoritmos de generación procedimental de laberintos (`generateMaze`, `buildSafePath`), las funciones algorítmicas para el recorrido espacial en grafos y el motor de procesamiento de inputs dependiente de la plataforma (`handleWindowsInput`).
>
  >   * **`game.h`**: Cabecera/encabezado de la arquitectura del programa. Concentra la declaración de estructuras de memoria (`Player`, `Enemy`, `State`), enumeraciones de estado (`GameMode`), macros estructurales (como las dimensiones topológicas de la matriz `N`) y expone los prototipos públicos del motor del juego.
>
  >   * **`enemy-gen.c`**: Archivo destinado a la generación y gestión de las entidades *"enemigo"* para su correcta integración en el programa.

> * **`io/`**
>
  >   * **`storage.c`**: Gestor de partidas guardadas del jugador en base a su nombre de usuario: utiliza archivos **.sav** para almacenar el perfil del jugador.
  >
  >   * **`storage.h`**: Encabezado de dicho gestor; contiene prototipos e inclusión de las librerías necesarias para funcionar correctamente.

> * **`ui/`**
>
  >   * **`render.c`**: Archivo dedicado a la visualización y renderización del programa en el terminal correspondiente.
  >
  >   * **`render.h`**: Encabezado de dicho archivo; contiene prototipos e inclusión de las librerías necesarias para funcionar correctamente.



[![Last Commit](https://img.shields.io/github/last-commit/visceralcricket/infinity-morass/main-dev)](https://github.com/visceralcricket/infinity-morass/commits/feature/main-menu) 