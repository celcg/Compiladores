//
// Created by celtia on 13/02/25.
//
#include "analisisSintactico.h"
#include "analisisLexico.h" // Para usar la función siguienteCompLexico
#include <stdio.h>

void analisisSintactico(void) {
    ElemTS compLexico;

    // Bucle que continua hasta que reciba un EOF
    while ((compLexico = siguienteCompLexico()).numero != EOF) {
        // Imprimir lexema y numero
        printf("Lexema: %s, Numero: %d\n", compLexico.lexema, compLexico.numero);
    }

    printf("Fin de archivo (EOF) alcanzado.\n");
}