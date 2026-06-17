# **Información importante sobre los TDAs**

## **Especificaciones**

- El TDA mapa (y su encabezado .h) fueron implementados como una tabla hash para mantener una complejidad temporal óptima a la hora de realizar búsquedas.

- Los archivos extra.c y su encabezado incluyen funciones varias, entre las cuales están:

1. Comando de limpieza de pantalla definido en base al sistema en el que se ejecute el programa (clear->Linux, cls->WIN32) para asegurar portabilidad.

2. Un strdup personalizado (_mystrdup) para asegurar consistencia en todos los sistemas y control total sobre el código.

3. Una función de lectura de opciones representadas como carácteres únicos (readCharOption) que además mantiene un buffer limpio y que no genera conflictos.

4. Incluye 2 separadores de texto:
- separador1(): Separador de 40 dashes '-'
- separador2(): Separador de 40 símbolos igual '='

    * Ambos incluyen un salto de línea al final puesto que están implementados con el comando "puts()".

5. Una función generate_maze para generar un mapa/mazmorra de NxN dimensiones y dificultad entera de 0 a 100.
    * La función de generar un camino asegurado (build_safe_path) y leer se encuentra temporalmente descartada puesto que no ve uso en este proyecto; considerar además eliminar las funciones las cuales no vayan a ver uso.

6. La estructura list.c y su encabezado fueron implementados como una lista enlazada simple (unidireccional), considerar quizás re-implementarla como una lista enlazada doble en el futuro para adecuarse a las necesidades del proyecto.
___