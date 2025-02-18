#include <stdio.h>

#include "analisisSintactico.h"
#include "tablaSimbolos.h"
#include "definiciones.h"

int main(void) {
    int cantidadP;
    // Inicializa la tabla de símbolos

    ElemTS palabrasReservadas[] = {
        {"package", PACKAGE},
        {"import", IMPORT},
        {"func", FUNC},
        {"var", VAR},
        {"for", FOR},
        {"range", RANGE},
        {"return", RETURN},
        {"chan", CHAN},
        {"go", GO},
        {"make", MAKE},
    };
    //Utilizo cantidad P para q la funcion sepa cuantas tiene q recorrer
    cantidadP = sizeof(palabrasReservadas) / sizeof(palabrasReservadas[0]);

    // Inicializa la tabla de símbolos con las palabras reservadas
    inicializarTablaSimbolos(palabrasReservadas, cantidadP);

   // analisisSintactico();
    printf("Tabla de símbolos inicializada con palabras reservadas.\n");

    destruirTablaSimbolos();
    printf("Tabla de símbolos eliminadaAAAs.\n");

    return 0;
}