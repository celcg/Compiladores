#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "abb.h"

// Reutiliza TIPOELEMENTOABB definido en Abb.h
typedef TABB TablaSimbolos;
typedef TIPOELEMENTOABB ElemTS;
// Prototipos de funciones para la tabla de símbolos
void inicializarTablaSimbolos(TablaSimbolos *ts, ElemTS *palabrasReservadas, int cantidadP);
void insertarEnTablaSimbolos(TablaSimbolos *ts, ElemTS elemento);
void destruirTablaSimbolos(TablaSimbolos *ts);
void buscarOInsertarEnTablaSimbolos(TablaSimbolos *ts, ElemTS elemento);

#endif // TABLASIMBOLOS_H
