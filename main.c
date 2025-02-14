#include <stdio.h>

#include "analisisSintactico.h"
#include "tablaSimbolos.h"
#include "definiciones.h"

int main(void) {
    TablaSimbolos ts;
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
    //Utilizo cantidad P para q la fun
    cantidadP = sizeof(palabrasReservadas) / sizeof(palabrasReservadas[0]);

    // Inicializa la tabla de símbolos con las palabras reservadas
    inicializarTablaSimbolos(&ts, palabrasReservadas, cantidadP);

   // analisisSintactico();
    printf("Tabla de símbolos inicializada con palabras reservadas.\n");

    destruirTablaSimbolos(&ts);
    printf("Tabla de símbolos eliminada.\n");

    return 0;
}