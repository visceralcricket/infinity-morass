# **infinity-morass**
> *Roguelike de calabozos basado en terminal de texto.*

<img src="https://img.shields.io/badge/version-1.6.5-blue" alt="version">

[![Last Commit](https://img.shields.io/github/last-commit/visceralcricket/infinity-morass/main)](https://github.com/visceralcricket/infinity-morass/commits/main)

## **Premisa**
* **"Infinity-morass"** es un juego roguelike de calabozos basado en terminal de texto donde tu objetivo es claro, conciso e incuestionable: convertirte en el ser más poderoso de estas mazmorras y derrotando a quien sea que ose entrometerse en tu camino — no es como que este infierno tenga algo más que enemigos y estorbos para tí — verdad...?

## **IMPORTANTE**
* Se utiliza convención **"camelCase"** para programar la totalidad del programa a lo largo de todos los archivos, por favor tener presente esto al momento de contribuir al proyecto.

* Comando para compilar: `mingw32-make`
* Ejecutable resultante: `infinity-morass.exe`  
* Comando para establecer UTF-8: `[Console]::OutputEncoding = [System.text.Encoding]::UTF8`

* TDA's utilizados hasta ahora: *"Lista, Mapa, Grafo (implícito)."*

## **Distribución de directorios**

* **`src/`**: Directorio principal del código fuente. Contiene las funcionalidades del programa y la lógica central del mismo.

  * **`main.c`**: Archivo principal del programa. Contiene el bucle de estados en los que se encuentra el jugador y gestiona la transición entre la interfaz del menú principal y los distintos modos de juego interactivos (como `runExplorationMode`). Relega la lógica pesada a los archivos **`game`** para mantener una arquitectura limpia y modular.

  * **`engine/`**
    * **`game.c`**: Lógica interna del juego. Contiene los algoritmos de generación procedimental de laberintos (`generateMaze`, `buildSafePath`), las funciones algorítmicas para el recorrido espacial en grafos y el motor de procesamiento de inputs dependiente de la plataforma (`handleWindowsInput`).

    * **`game.h`**: Cabecera/encabezado de la arquitectura del programa. Concentra la declaración de estructuras de memoria (`Player`, `Enemy`, `State`), enumeraciones de estado (`GameMode`), macros estructurales (como las dimensiones topológicas de la matriz `N`) y expone los prototipos públicos del motor del juego.

    * **`enmap.c`**: Archivo destinado a la generación y tracking de los enemigos para su correcta integración en el programa.
    * **`enmap.h`**: Encabezado del archivo destinado a la generación y mapeo de los enemigos: contiene las definiciones de las entidades **"Enemigo"** y una plantilla genérica para estandarizar la asignación de stats.

  * **`io/`**

    * **`storage.c`**: Gestor de partidas guardadas del jugador en base a su nombre de usuario: utiliza archivos **.sav** para almacenar el perfil del jugador.

    * **`storage.h`**: Encabezado de dicho gestor; contiene prototipos e inclusión de las librerías necesarias para funcionar correctamente.

  * **`ui/`**

    * **`render.c`**: Archivo dedicado a la visualización y renderización del programa en el terminal correspondiente.

    * **`render.h`**: Encabezado de dicho archivo; contiene prototipos e inclusión de las librerías necesarias para funcionar correctamente.

* **`.gitignore`**: Archivo utilizado para excluir ficheros de tipo innecesario a la hora de actualizar el repositorio.

* **`Makefile`**: Archivo utilizado para automatizar la compilación del programa en local con el comando: `mingw32-make` y que crea el ejecutable final: `infinity-morass.exe`

## **Changelog (historial de cambios)**
<small>*Nota: Este changelog está en orden cronológico inverso.*</small>

### **Versión 1.6.0** (18-06-2026)
> Se continuó implementando la funcionalidad de generación, mapeo y tracking de entidades enemigos.

* Parche 1.6.1
  + Se refactorizó la estructura principal de la funcionalidad de generación y mapeo de enemigos, comprimiendo la lógica inicial de comparar nombre a nombre y asignar las estadísticas a una plantilla EnemyTemplate genérica.

  + Se cambiaron los nombres de los archivos **"enemy-gen.c"** a **"engen.c"** para mejor legibilidad y armonía con los nombres del resto de archivos.

* Parche 1.6.2
  + Se modificó la cantidad de salidas por mazmorra para una experiencia de juego más fluida.

* Parche 1.6.3
  + Arreglado bug donde al probar la generación de un enemigo en el mapa el nombre del mismo se quedaba estancado/flotando en el terminal de texto hasta que el jugador entra a ajustes y le da a continuar partida.

  + Se refinó la implementación de la generación de enemigos y además se incluyó un sistema básico para poder visualizar y verificar el correcto procesamiento de la generación y mapeo de los enemigos mediante el TDA Mapa.

  + Actualmente no se pueden generar enemigos múltiples veces por cada mazmorra, sino que una única vez en la primera mazmorra a modo de prueba del sistema.

* Parche 1.6.4
  + Ligeras optimizaciones en la lógica de lectura de input para dispositivos Windows.

  + Se refactorizó la forma en que se guardan los archivos del jugador de tal forma que se escriba cada uno de sus parámetros uno a uno en el archivo .sav para asegurar integridad de los datos y evitar que el programa colapse en caso de que el nombre del usuario pase de un arreglo finito a un puntero.

  + Cambios menores en ciertos flujos de lógica que requerían ajustes para funcionar mejor.

* Parche 1.6.5
  + Removidas funciones de grafos implícitos de las que no se hacían uso puesto que sus funciones estaban cubiertas por otros archivos a lo largo del motor del juego *(src/engine)*

### **Versión 1.5.0** (15-06-2026)

> Se implementó funcionalidad de la vista de inventario y sub-menú de ajustes *in-game* con distintas opciones.

* Parche 1.5.5
  + Mejora de la documentación, organización y redacción del README mediante algunos cambios:

    + Se renombró la sección **"Historial de cambios"** a **"Changelog"** para mayor claridad.

    + Se trasladó la distribución de directorios a la parte superior del archivo.

    + Se afinó formato de la distribución de directorios para que se vea más claro y conciso.

    + Se jerarquizó el Changelog en orden cronológico inverso para dejar los parches y versiones más recientes en la parte superior.

    + Se añadió una pequeña sección para explicar la premisa del juego.

* Parche 1.5.4
  + Ajustes y adiciones menores al formato del README.

* Parche 1.5.3
  + Problemas con cuelgue de programa y sub-menú de ajustes *in-game* solucionados.
  
  + Se añadió la inclusión del archivo **"storage.h"** en **"game.c"** para poder hacer uso de la funcionalidad guardar juego.

  + Se refactorizó ligeramente función **"getCharOption"** en **"extra.c"** para asegurar el procesamiento correcto de input y forzar cierre del programa en caso donde el terminal no sea capaz de leer input del usuario adecuadamente.

* Parche 1.5.2
  + Se arregló el duplicado del menú de exploración y se verificó que los input handlers sean llamados correctamente.

  + Programa continúa colgándose y dejando de responder a cualquier tipo de input al entrar al sub-menú de ajustes en el mapa durante su ejecución.

* Parche 1.5.1
  + Arreglado bug que causaba que el programa se colgase.

  + preparando un siguiente parche para evitar doble-output de ciertas partes del menú exploración y pérdida total de respuesta a input al abrir el menú de ajustes sobre el mapa.


### **Versión 1.4.0** (14-06-2026)
> Refactorización y pulido del programa con nuevas funcionalidades y cambios para la experiencia del usuario (Quality of Life)

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

### **Pre-versión 1.4.0**

* Se crearon **2** archivos nuevos para distribuir el main y dejarlo más limpio:
---
* 
  + **`game.h`** tiene todos los `#include` para las librerías, las definiciones para los movimientos, las teclas que se van a leer para mover al personaje y los prototipos de las entidades.

  + **`game.c`** tiene las entidades en sí, como el `Player`, `Enemy`, `Stats`, las funciones para el grafo y una función para manejar el input en Windows.
---

* El main se relegó únicamente para menús y cosas simples; tiene una versión muy simple de la interfaz del menú principal, por ende más allá de eso faltaría continuar las otras 2 interfaces de navegación y combate.

* Se renombró **`map.c`** y **`map.h`** a **`hashmap.c`** y **`hashmap.h`** para que sea un poco más autoexplicativo.

* Se limpió y afinó el archivo **`extra.c`** para dejar fuera las funciones que no se van a utilizar.
---