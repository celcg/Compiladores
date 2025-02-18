#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////// DEFINICIONES DE TIPOS

/* Definimos el tipo de clave como un puntero a char (string) */
typedef char *TIPOCLAVE;

/* Estructura para los elementos de la tabla de símbolos.
 * Contiene el lexema (puntero a string) y un número asociado.
 */
typedef struct {
	TIPOCLAVE lexema; // Lexema (clave)
	int numero;       // Número asociado al lexema
} ElemTS;

/* Definición de la estructura del árbol binario de búsqueda.
 * Es un puntero a una celda que contiene un elemento y
 * punteros a sus subárboles izquierdo y derecho.
 */
typedef struct celda *TABB;

///////////////////////// DECLARACIÓN DE FUNCIONES

/* Crea un árbol binario de búsqueda vacío */
void crearAbb();

/* Destruye el árbol binario de búsqueda y libera la memoria */
void destruirAbb();

/* Verifica si el árbol binario de búsqueda está vacío */
unsigned esAbbVacio();

/* Comprueba si un elemento pertenece al árbol binario de búsqueda */
unsigned esMiembroAbb(ElemTS E);

/* Inserta un nuevo elemento en el árbol binario de búsqueda */
void insertarElementoAbb(ElemTS E);

/* Elimina un elemento del árbol binario de búsqueda */
void suprimirElementoAbb(ElemTS E);

/* Busca un nodo en el árbol binario de búsqueda dado un lexema */
void buscarNodoAbb(TIPOCLAVE cl, ElemTS *nodo);

/* Modifica un elemento existente en el árbol binario de búsqueda */
//void modificarElementoAbb(ElemTS nodo);

/* Imprime el contenido del árbol binario de búsqueda en orden */
void imprimirAbb();

#endif // ABB_H
