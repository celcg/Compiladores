#include "analisisLexico.h"
#include "tablaSimbolos.h"
#include <stdio.h>
#include <string.h>

int obtenerCodigoASCII(char c) {
    return (int)c;
}

ElemTS siguienteCompLexico(void) {
    // CODIGO PARA LEER
    ElemTS compLexico;

    //EJEMPLO LUEGO LO TENGO Q CAMBIAR
    compLexico.numero = 300;
    compLexico.lexema = "package";  // Esto debe ser el lexema real que procesas
    char lexema[]=")";
    if (strcmp(lexema, "(") == 0 || strcmp(lexema, ")") == 0) {
        compLexico.numero = obtenerCodigoASCII(lexema[0]);
        compLexico.lexema = lexema;
    }

    return compLexico;
}
