# **infinity-morass**
> *Roguelike de calabozos basado en terminal de texto.*

<img src="https://img.shields.io/badge/version-1.8.7-blue" alt="version">

[![Last Commit](https://img.shields.io/github/last-commit/visceralcricket/infinity-morass/main)](https://github.com/visceralcricket/infinity-morass/commits/main)

## **Premisa**
* **"Infinity-morass"** es un juego roguelike de calabozos basado en terminal de texto donde tu objetivo es claro, conciso e incuestionable: convertirte en el ser más poderoso de estas mazmorras y derrotando a quien sea que ose entrometerse en tu camino — no es como que este infierno tenga algo más que enemigos y estorbos para tí — verdad...?

## **Cómo compilar y ejecutar el programa**

Este proyecto está desarrollado en **C (Estándar C99)**. Para compilarlo de forma local en dispositivos Windows, asegúrese de tener instalado un entorno de desarrollo para C/C++ (como **MinGW-w64** o **MSYS2**) que tenga configuradas en sus variables de entorno tanto el compilador `gcc` como la herramienta de automatización `make`.

### **Instrucciones paso a paso**

1. **Descargar el repositorio:** Descargue el proyecto comprimido como `.zip` desde GitHub y extraiga la carpeta en el directorio de su elección.

2. **Navegar a la raíz:** Abra su terminal de preferencia (PowerShell, CMD o Git Bash) y posiciónese dentro de la carpeta principal del proyecto:
  ```bash
  cd ruta/hacia/infinity-morass
  ```

  * Configurar codificación (Obligatorio en Windows): Para que la terminal dibuje correctamente el arte ASCII, las tildes y los bordes del mapa, ejecute:
  > [Console]::OutputEncoding = [System.text.Encoding]::UTF8

3. **Compilar el proyecto**: Genere el binario ejecutando:
  <pre><code><span style="color: #DCDCAA;">mingw32-make</span></code></pre>
  
<small>**(Una vez finalizado, verá que se ha creado el archivo infinity-morass.exe).**</small>

4. **Iniciar la partida**: Ejecute el binario según su *terminal*

+ En PowerShell / Git Bash:
  > .\infinity-morass.exe

+ En Símbolo del sistema (CMD):
  > infinity-morass.exe

#### **Nota de mantenimiento**
  + Si usted es un desarrollador y desea realizar un rebuild limpio del juego tras modificar las estructuras internas, ejecute:
  <pre><code><span style="color: #DCDCAA;">mingw32-make</span> clean</code></pre>
  para fulminar los archivos tipo objeto (.o) de la memoria caché.

### **IMPORTANTE**
* Se utiliza convención **"camelCase"** para programar la totalidad del programa a lo largo de todos los archivos, por favor tener presente esto al momento de contribuir al proyecto.

* TDA's utilizados: *"Lista, Mapa, Grafo (implícito), Cola de Prioridad."*

## **Distribución de directorios**
<pre><code><i><span style="color: #00fed4ed;">Cómo se organiza el código?</span></i></code></pre>

* <code><b><span style="color: #23c523d4;">src/</span></b></code>: Directorio principal del código fuente. Contiene las funcionalidades clave del programa y la lógica central del mismo.

  * <code><b><span style="color: #009dff;">main.c</span></b></code>: Archivo principal del programa. Contiene el bucle de estados en los que se encuentra el jugador y gestiona la transición entre la interfaz del menú principal y los distintos modos de juego interactivos (como `runExplorationMode`). Relega la lógica pesada a los archivos **`game`** para mantener una arquitectura limpia y modular.

  * <code><b><span style="color: #009dff;">engine/</span></b></code>

    * <code><b><span style="color: #f43009da;">entities.h</span></b></code>: Archivo dedicado completamente a almacenar la memoria para las entidades clave del programa, entre estas se encuentran: Player, Enemy, GameObject, definiciones relacionadas, etc.

    * <code><b><span style="color: #f43009da;">game.c</span></b></code>: Lógica interna del juego. Contiene los algoritmos de generación procedimental de laberintos **(generateMaze, buildSafePath)**, las funciones algorítmicas para el recorrido espacial en grafos y el motor de procesamiento de inputs dependiente de la plataforma **handleWindowsInput**.
    * <code><b><span style="color: #f43009da;">game.h</span></b></code>: Cabecera/encabezado de la arquitectura del programa. Concentra la declaración de macros estructurales (como las dimensiones topológicas de la matriz `N`) y expone los prototipos públicos del motor del juego.

    * <code><b><span style="color: #f43009da;">enmap.c</span></b></code>: Archivo destinado a la generación y tracking de los enemigos para su correcta integración en el programa.
    * <code><b><span style="color: #f43009da;">enmap.h</span></b></code>: Encabezado del archivo destinado a la generación y mapeo de los enemigos: contiene las definiciones de las entidades **"Enemigo"** y una plantilla genérica para estandarizar la asignación de stats.

    * <code><b><span style="color: #f43009da;">combat.c</span></b></code>: Archivo en donde se encuentra implementada la función en donde se gestionan los turnos durante el combate y las acciones del jugador en la misma.
    * <code><b><span style="color: #f43009da;">combat.h</span></b></code>: Encabezado del archivo de la función para el combate del jugador contra los enemigos.

    * <code><b><span style="color: #f43009da;">objmap.c</span></b></code>: Archivo encargado de manejar y gestionar las entidades de tipo objeto y distribuirlos a lo largo de un Mapa de forma ordenada.
    * <code><b><span style="color: #f43009da;">objmap.h</span></b></code>: Encabezado de dicho archivo, encargado de enlazar e incluir las dependencias necesarias para que el sistema funcione correctamente.


  * <code><b><span style="color: #009dff;">io/</span></b></code>

    * <code><b><span style="color: #f43009da;">storage.c</span></b></code>: Gestor de partidas guardadas del jugador en base a su nombre de usuario: utiliza archivos **.sav** para almacenar el perfil del jugador.

    * <code><b><span style="color: #f43009da;">storage.h</span></b></code>: Encabezado de dicho gestor; contiene prototipos e inclusión de las librerías necesarias para funcionar correctamente.

  * <code><b><span style="color: #009dff;">tdas/</span></b></code>
    + Aquí se encuentran las estructuras de los TDAs (Tipos de Datos Abstractos) utilizados en el proyecto, como el montículo *Min-Heap* para el sistema de combate por turnos, la *lista doblemente enlazada* para los inventarios y visualización de objetos, el *mapa hash* para trackear las entidades como enemigos y sus propiedades, etc; más información en la documentación **"TDAS.md"**

  * <code><b><span style="color: #009dff;">ui/</span></b></code>

    * <code><b><span style="color: #f43009da;">render.c</span></b></code>: Archivo dedicado a la visualización y renderización del programa en el terminal correspondiente.

    * <code><b><span style="color: #f43009da;">render.h</span></b></code>: Encabezado de dicho archivo; contiene prototipos e inclusión de las librerías necesarias para funcionar correctamente.

* <code><b><span style="color: #23c523d4;">.gitignore</span></b></code>: Archivo utilizado para excluir ficheros de tipo innecesario a la hora de actualizar el repositorio.

* <code><b><span style="color: #23c523d4;">Makefile</span></b></code>: Archivo utilizado para automatizar la compilación del programa en local con el comando: <code><span style="color: #DCDCAA;">mingw32-make</span></code> y que crea el ejecutable final mencionado en el instructivo del proyecto.

## **Funcionalidades pendientes** 

* A nivel de renderizado / visual
  + Actualmente **NO** hay forma de distinguir las casillas de enemigos comúnes con jefes: sería ideal crear nuevas macros que representen mejor a cada enemigo de forma único o que sean capaces de diferenciar enemigos comúnes de jefes.

  + No se le indica al jugador en qué nivel de la mazmorra se encuentra, es decir, no existe forma de trackear el número que representa la mazmorar actual: en caso de implementarse, considerar que, como la muestra topológica del mapa se guarda junto con el progreso del jugador, el número de la mazmorra que se almacenó en el archivo .sav **también** debe ser considerado de tal forma que el número de mazmorra actual no se reinicie al cargar una partida.

* A nivel de lógica de procedimientos / sistemas
    + Implementar funcionalidad de reiniciar personaje (o al menos los puntos de vida del mismo)

    + ~~Interacciones con objetos generados en el mapa y su posterior guardado en el inventario: actualmente estos no son interactuables ni existe una forma de guardarlos en el inventario.~~ **Resuelto (25-06-2026)**

    + La generación de enemigos no limita jefes por mazmorra, sino que es de forma totalmente aleatoria: integrar métrica que lleve la cuenta de mazmorras recorridas y genere un enemigo jefe cada 4 niveles.

## **Problemas conocidos**

* A nivel de renderizado / visual
  + ...

* A nivel de lógica de procedimientos / sistemas
  + Actualmente, al huir de un enemigo, se muestra que el jugador "derrotó" al enemigo, cuando esto no es correcto, puesto que escapar de un enemigo **≠** derrotar al mismo.

  + Al recoger un objeto en el inventario, las estadísticas afectadas que muestra este mismo (el resúmen de estadísticas afectadas) es poco claro y enrevesado: muestra **todas** las estadísticas que **podría** afectar en vez de simplificarlo al incremento (o decremento) de las estadísticas realmente afectadas.
  Por ejemplo:
  Poción pequeña [CONSUMIBLE]:
    +40HP
  Bomba molotov [CONSUMIBLE]:
    +10 ATK
    -5 SPD

## **Changelog (historial de cambios)**
<small>*Nota: Este changelog está en orden cronológico inverso.*</small>

### **Versión 1.8.0** (20-06-2026) 
> Integración inicial de funcionalidades: modo de juego de combate, sistema de combate, finalización del sistema de guardado/carga de partidas y mejoras de calidad de vida.

* Parche 1.8.7
  + Realizadas mejoras generales de redacción de documentación, limpieza de comentarios innecesarios y refactorizaciones menores de código para mejorar legibilidad y coherencia.

  + Mejorada documentación específica **"TDAS.md"** en la carpeta de **"src/tdas"**

  + Añadidos nuevos macros para eliminar la mayoría (sino toda) existencia de números mágicos tanto en procesos fundamentales del programa como en funcionalidades más finas / de menor impacto.

  + Traducidos comentarios obsoletos que se escribieron en inglés al español para mantener consistencia con el resto del proyecto el cual está escrito en dicho lenguaje.

  + Añadidos comentarios menores a lo largo del código para explicar más a profundidad el funcionamiento de procedimientos y funciones que podrían resultar más complejas o de mayor interés formativo.

  + Inclusión de coloreado de texto con <code><b><span style="color: #ebffa4cb;">HTML</span></b></code> para mayor claridad y facilidad de lectura.

* Parche 1.8.6
  + Añadida la posibilidad de agarrar objetos en el mapa de juego.
  
  + Rolled-back cambios realizados **"heap.c"** y **"combat.c"**: se dejó como Min-Heap y se preservó la resta con **INT_MAX**.

* Parche 1.8.5
  + Implementadas secciones de **"Funcionalidades pendientes"** y **"Problemas conocidos"**

  + Arreglos menores en inclusión de dependencias en **"combat.c, combat.h, enmap.h, game.h, render.h"**

  + Se trasladaron los macros que definen los símbolos de la mazmorra al archivo **"entities.h"** para mantener la separación de responsabilidades adecuada para cada archivo.

* Parche 1.8.4
  + Funcionalidad de guardado y carga de partidas ahora se encuentra finalizada: incluye el nivel/mazmorra donde se encontraba el jugador, los enemigos y objetos que existían en el mismo y la propia posición del jugador antes de cerrar el juego.

  + Depuración de inclusiones incorrectas de archivos de cabecera en **"combat.c"** y **"combat.h"**

  + Arreglado bug de renderizado que provocaba que todo el mapa apareciese completamente vacío a excepción de sus delimitaciones espaciales.

  + Eliminada fuga de memoria en **"main.c"** al sobreescribir la lista del inventario del jugador tras cargar exitosamente una partida.

  + Creación de la nueva entidad **"sessionFloor"** la cual es la encargada de permitir al programa rastrear (tracking) tanto el mapa actual que está navegando el jugador como las entidades que pueblan el mismo además de verificar si el propio mapa fue realmente visitado o si únicamente se generó y el jugador nunca llegó a explorar.

  + Entidades restantes en **"game.h"** como los modos de juego del programa y macros esenciales fueron desplazadas a **"entities.h"** para mantener un mejor orden de los archivos y reducir la naturaleza céntrica del encabezado **"game.h"**

  + Eliminación de entidades innecesarias tipo State y Action heredadas del TDA Grafo Implícito puesto que estas funcionalidades ya se manejan en la función clave **"handleWindowsInput"** la cual modifica inmediatamente la posición del jugador en vez de utilizar un intermediario.

  + Arreglo menor a la documentación: versiones y notas de parches distribuidas en el orden incorrecto.

* Parche 1.8.3
  + heap.c reimplementado como un montículo Min-Heap para eliminar la necesidad de calcular la diferencia de la prioridad encontrada por el montículo e INT_MAX; esto le da más sentido al código y encaja con la lógica de usar la estructura adecuada para el problema adecuado.

  + Creación de función freeGameObject encargada de liberar la memoria de cualquier objeto que se le asigne dentro de los archivos tipo **"combat"**.

* Parche 1.8.2
  + Implementado sistema inicial de generación de objetos en el mapa del videojuego (únicamente visualización, no interacción)
  
  + Implementacion inicial del dropeo de items para los enemigos

* Parche 1.8.1
  + Removido bug presente a partir de la versión 1.7.0, haciendo uso de métodos más robustos para hacer la limpieza del buffer y la lectura de input, todos cambios principalmente concentrados en el archivo **"extra.c"**

  + Refinado de los archivos encargados del renderizado del videojuego para garantizar la integridad y la fidelidad visual del programa tras haber incorporado el nuevo modo de juego de combate y sus respectivas mecánicas.

### **Versión 1.7.0** (20-06-2026)
> Se implemento sistema de combate y menú de combate.

* Parche 1.7.2
  + Se realizaron preparaciones generales para asegurar la correcta integración de las funcionalidades de modo de juego de combate y sus respectivas mecánicas.

* Parche 1.7.1
  + Funciones que no tenían relación con los archivos donde estaban definidas se trasladaron a los archivos correctos
  
  + Removidas múltiples llamadas de librerías innecesarias
  
  + refactorizado nombre de archivo "**combat-system.c**" y su encabezado a "**combat.c**" y "**combat.h**" para tener nombres de archivos más breves y concisos.
  
  + Arreglado bug donde el submenú superpuesto del inventario in-game se mostraba a una altura considerablemente menor de la correcta.

  + Removida verificación temporal del mapeo de enemigos en el TDA Mapa.

* Parche 1.7.0
  + Implementada versión incial de sistema de combate y menú interactivo de combate.

  + En el menú de combate existe un bug donde, al darle a Enter en un momento donde no es necesario, el jugador puede escribir en el lado izquierdo de la pantalla pero sin tener impacto alguno en la experiencia de juego. No afecta a la visualizacion del mapa


### **Versión 1.6.0** (18-06-2026)
> Se continuó implementando la funcionalidad de generación, mapeo y tracking de entidades enemigos.

* Parche 1.6.5
  + Removidas funciones de grafos implícitos de las que no se hacían uso puesto que sus funciones estaban cubiertas por otros archivos a lo largo del motor del juego *(src/engine)*

* Parche 1.6.4
  + Ligeras optimizaciones en la lógica de lectura de input para dispositivos Windows.

  + Se refactorizó la forma en que se guardan los archivos del jugador de tal forma que se escriba cada uno de sus parámetros uno a uno en el archivo .sav para asegurar integridad de los datos y evitar que el programa colapse en caso de que el nombre del usuario pase de un arreglo finito a un puntero.

  + Cambios menores en ciertos flujos de lógica que requerían ajustes para funcionar mejor.

* Parche 1.6.3
  + Arreglado bug donde al probar la generación de un enemigo en el mapa el nombre del mismo se quedaba estancado/flotando en el terminal de texto hasta que el jugador entra a ajustes y le da a continuar partida.

  + Se refinó la implementación de la generación de enemigos y además se incluyó un sistema básico para poder visualizar y verificar el correcto procesamiento de la generación y mapeo de los enemigos mediante el TDA Mapa.

  + Actualmente no se pueden generar enemigos múltiples veces por cada mazmorra, sino que una única vez en la primera mazmorra a modo de prueba del sistema.

* Parche 1.6.2
  + Se modificó la cantidad de salidas por mazmorra para una experiencia de juego más fluida.

* Parche 1.6.1
  + Se refactorizó la estructura principal de la funcionalidad de generación y mapeo de enemigos, comprimiendo la lógica inicial de comparar nombre a nombre y asignar las estadísticas a una plantilla EnemyTemplate genérica.

  + Se cambiaron los nombres de los archivos **"enemy-gen.c"** a **"enmap.c"** para mejor legibilidad y armonía con los nombres del resto de archivos.


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