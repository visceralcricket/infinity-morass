# **infinity-morass**

## ***Historial de cambios***

* Se crearon 2 archivos nuevos para distribuir el main y dejarlo más limpio:
---
    + **"game.h"** tiene todos los #include para las librerías, las
    definiciones para los movimientos, las teclas que se van a leer
    para mover al personaje y los prototipos de las entidades.

    + **"game.c"** tiene las entidades en sí, como el Player, Enemy, Stats,
    las funciones para el grafo y una función para manejar el input en Windows
---

* El main se relegó únicamente para menús y cosas simples; tiene una versión muy simple de la interfaz del menú principal, por ende más allá de eso faltaría continuar las otras 2 interfaces de navegación y combate.

* Se renombró **"map.c"** y **"map.h"** a **"hashmap.c"** y **"hashmap.h"** para que sea un poco más autoexplicativo.

* Se limpió y afinó el archivo **"extra.c"** para dejar fuera las funciones que no sirven: split_string **NO** debe ser eliminada, primero considerar su potencial uso para la lectura del nombre del jugador y otras posibles utilidades.

[![Last Commit](https://img.shields.io/github/last-commit/visceralcricket/infinity-morass/main)](https://github.com/visceralcricket/infinity-morass/commits/main)

> Felipe, 09/06/2026
