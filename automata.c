//
// Created by celtia on 18/02/25.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEXEMA 100

// Tokens
enum Tokens {
    TOKEN_PALABRA_RESERVADA,
    TOKEN_IDENTIFICADOR,
    TOKEN_NUMERO,
    TOKEN_OPERADOR,
    TOKEN_DELIMITADOR,
    TOKEN_CADENA,
    TOKEN_COMENTARIO,
    TOKEN_ERROR
};

char lexema[MAX_LEXEMA];
int lexema_index = 0;

int es_palabra_reservada(char *lexema) {
    const char *palabras_reservadas[] = {
        "package", "import", "func", "var", "for", "if", "else", "go", "chan", NULL
    };
    for (int i = 0; palabras_reservadas[i] != NULL; i++) {
        if (strcmp(lexema, palabras_reservadas[i]) == 0) {
            return 1; // Es una palabra reservada
        }
    }
    return 0;
}

int analizador_lexico(FILE *fp) {
    int c;
    int estado = 0;

    while ((c = fgetc(fp)) != EOF) {
        switch (estado) {
            case 0: // Estado inicial
                if (isspace(c)) {
                    continue; // Ignorar espacios
                } else if (isalpha(c) || c == '_') {
                    lexema[lexema_index++] = c;
                    estado = 1; // Identificadores o palabras reservadas
                } else if (isdigit(c)) {
                    lexema[lexema_index++] = c;
                    estado = 2; // Números
                } else if (c == '"') {
                    estado = 3; // Cadenas de texto
                } else if (c == '/') {
                    estado = 4; // Comentarios
                } else if (strchr("+-*/=<>:;,{}[]()", c)) {
                    lexema[lexema_index++] = c;
                    if (c == ':' || c == '<') { // Posibles operadores compuestos como := o <-
                        estado = 5;
                    } else {
                        lexema[lexema_index] = '\0';
                        return TOKEN_OPERADOR; // Operadores simples
                    }
                } else {
                    printf("Error léxico: carácter no reconocido '%c'\n", c);
                    return TOKEN_ERROR;
                }
                break;

            case 1: // Identificadores o palabras reservadas
                if (isalnum(c) || c == '_') {
                    lexema[lexema_index++] = c;
                } else {
                    ungetc(c, fp); // Devolver el carácter no usado
                    lexema[lexema_index] = '\0';
                    if (es_palabra_reservada(lexema)) {
                        return TOKEN_PALABRA_RESERVADA;
                    } else {
                        return TOKEN_IDENTIFICADOR;
                    }
                }
                break;

            case 2: // Números
                if (isdigit(c) || c == '.' || c == 'e' || c == 'E' || c == '+' || c == '-') {
                    lexema[lexema_index++] = c;
                } else {
                    ungetc(c, fp); // Devolver el carácter no usado
                    lexema[lexema_index] = '\0';
                    return TOKEN_NUMERO;
                }
                break;

            case 3: // Cadenas de texto
                if (c == '"') {
                    lexema[lexema_index++] = c;
                    lexema[lexema_index] = '\0';
                    return TOKEN_CADENA;
                } else {
                    lexema[lexema_index++] = c;
                }
                break;

            case 4: // Comentarios
                if (c == '/') {
                    while ((c = fgetc(fp)) != '\n' && c != EOF); // Ignorar comentario de una línea
                    estado = 0;
                } else if (c == '*') {
                    while ((c = fgetc(fp)) != EOF) {
                        if (c == '*' && (c = fgetc(fp)) == '/') {
                            break; // Fin del comentario de bloque
                        }
                    }
                    estado = 0;
                } else {
                    printf("Error léxico: '/' inesperado\n");
                    return TOKEN_ERROR;
                }
                break;

            case 5: // Operadores compuestos (como := o <-)
                if (c == '=' || c == '-') {
                    lexema[lexema_index++] = c;
                    lexema[lexema_index] = '\0';
                    return TOKEN_OPERADOR;
                } else {
                    ungetc(c, fp); // Devolver el carácter no usado
                    lexema[lexema_index] = '\0';
                    return TOKEN_DELIMITADOR; // Operador simple
                }
                break;
        }
    }

    return EOF; // Fin del archivo
}
