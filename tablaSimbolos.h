#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "abb.h"

// Prototipos de funciones para la tabla de símbolos
void inicializarTablaSimbolos(ElemTS *palabrasReservadas, int cantidadP);
void insertarEnTablaSimbolos(ElemTS elemento);
void destruirTablaSimbolos();
void buscarOInsertarEnTablaSimbolos(ElemTS elemento);

#endif // TABLASIMBOLOS_H
