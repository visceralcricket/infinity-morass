# **Información importante sobre los TDAs**

## **Especificaciones**

* El TDA mapa (y su encabezado .h) fueron implementados como una tabla hash para mantener una complejidad temporal óptima a la hora de realizar búsquedas e inserciones.

* Los archivos extra.c y su encabezado incluyen funciones varias, entre las cuales están:

    1. Comando de limpieza de pantalla definido en base al sistema en el que se ejecute el programa 
    ```powershell
    (clear->Linux, cls->WIN32)
    ```
    > para asegurar portabilidad.

    2. Una función de lectura de opciones representadas como carácteres únicos (readCharOption) que además mantiene un buffer limpio y que no genera conflictos.

    3. Incluye 2 separadores de texto:
        + separador1(): Separador de 40 dashes '-' con formato dim (tenue)
        
        + separador2(): Separador de 40 símbolos igual '=' con formato **bold**

        + Ambos incluyen 2 tabulados al inicio y un salto de línea al final puesto que están implementados con el comando "puts()"

* La estructura list.c y su encabezado fueron **inicialmente** implementados como una lista enlazada simple (unidireccional), actualmente están implementadas como una lista doblemente enlazada para adecuarse a las necesidades del proyecto.
___