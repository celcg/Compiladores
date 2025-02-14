#include "tablaSimbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Inicializa la tabla de símbolos e inserta las palabras reservadas.
 * @param ts Puntero a la tabla de símbolos que se inicializará.
 * @param palabrasReservadas Array de elementos TIPOELEMENTOABB que contiene las palabras reservadas y sus números.
 */
void inicializarTablaSimbolos(TablaSimbolos *ts, ElemTS *palabrasReservadas, int cantidad) {
    // Inicializa la tabla de simbolos como un arbol binario vacío
    crearAbb(ts);

    // Verifica que palabrasReservadas no sea NULL
    if (palabrasReservadas == NULL) {
        printf("Error: palabras reservadas no puede ser NULL\n");
        return;
    }

    // Insertar cada palabra reservada en la tabla de simbolos
    for (int i = 0; i < cantidad; i++) {
        // Verifica que lexema no sea NULL
        if (palabrasReservadas[i].lexema != NULL) {
            insertarEnTablaSimbolos(ts, palabrasReservadas[i]);
        } else {
            printf("Error: lexema NULL en la palabra reservada %d\n", i);
        }
    }

    // Imprimir la tabla de simbolos
    imprimirAbb(*ts);
}

/**
 * Inserta un elemento en la tabla de simbolos
 * @param ts Puntero a la tabla de simbolos
 * @param lexema Lexema del elemento que se va a insertar
 * @param numero Numero asociado al lexema
 */
void insertarEnTablaSimbolos(TablaSimbolos *ts, ElemTS elemento) {
    // Verificar si el lexema es NULL
    if (elemento.lexema == NULL) {
        fprintf(stderr, "Error: El lexema no puede ser NULL.\n");
        return;  // Salir de la función si el lexema es inválido
    }

    // Crear un nuevo elemento ElemTS
    ElemTS nuevoElemento;

    // Reservar memoria para el lexema
    nuevoElemento.lexema = (char *)malloc(strlen(elemento.lexema) + 1);  // +1 para el carácter nulo
    if (nuevoElemento.lexema == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para el lexema.\n");
        return;  // Salir si no se pudo asignar memoria
    }

    // Copiar datos al nuevo elemento
    strcpy(nuevoElemento.lexema, elemento.lexema);
    nuevoElemento.numero = elemento.numero;

    // Insertar el nuevo elemento en el árbol
    insertarElementoAbb(ts, nuevoElemento);
}

/**
 * Destruye la tabla de símbolos, liberando la memoria utilizada
 * por cada elemento (lexemas) y el árbol binario.
 * @param ts Puntero a la tabla de símbolos que se destruirá.
 */
void destruirTablaSimbolos(TablaSimbolos *ts) {
    // Verifica que la tabla no esté vacía
    if (esAbbVacio(*ts)) {
        return;  // Si la tabla está vacía, no hay nada que destruir
    }

    // Llamar a la función de destrucción recursiva del árbol
    destruirAbb(ts);
}

void buscarOInsertarEnTablaSimbolos(TablaSimbolos *ts, ElemTS elemento) {
    // Verificar si el lexema es NULL
    if (elemento.lexema == NULL) {
        fprintf(stderr, "Error: El lexema no puede ser NULL.\n");
        return;  // Salir de la función si el lexema es inválido
    }

    // Crear un nodo para buscar el elemento en el árbol
    ElemTS encontrado;

    // Buscar el elemento en la tabla de símbolos
    buscarNodoAbb(*ts, elemento.lexema, &encontrado);

    // Si el elemento no existe, insertarlo
    if (encontrado.lexema == NULL) {
        // El elemento no se encontró, insertar uno nuevo
        insertarEnTablaSimbolos(ts, elemento);
    } else {
        // El elemento ya existe, imprimir un mensaje de error o advertencia
        printf("El lexema '%s' ya está presente en la tabla de símbolos con número %d.\n", encontrado.lexema, encontrado.numero);
    }
}
