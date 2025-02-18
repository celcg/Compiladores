 #include "abb.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////////// ESTRUCTURAS DE DATOS
TABB Arbol;

struct celda {
    ElemTS info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIONES


/////////////////////////////////////////////////////////////
/////////////////////////// INICIO PARTE MODIFICABLE

/*Extraer la clave de una celda */
//Si es orden alfabetico
TIPOCLAVE _clave_elem(ElemTS *E) {
    return E->lexema;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(TIPOCLAVE cl1, TIPOCLAVE cl2) {
    return strcmp(cl1, cl2);
}


/* Si tipoelem tiene alguna estructura que necesite 
 * destruirse ha de hacerse aqui. El uso de esta funcion
 * permite hacer mas eficiente la destruccion del arbol.*/
void _destruir_elem(ElemTS *E) {
    free(E->lexema); // Liberar memoria
}


/////////////////////////// FIN PARTE MODIFICABLE
/////////////////////////////////////////////////////////////

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crearAbb() {
    Arbol = NULL;
}

void destruirAbbRec(TABB *A) {
    if (*A != NULL) {
        destruirAbbRec(&(*A)->izq);
        destruirAbbRec(&(*A)->der);
        _destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    }
}
void destruirAbb() {
    if (Arbol != NULL) {
        destruirAbbRec(&Arbol);
    }
}


//OPERACIONES DE INFORMACIÓN

unsigned esAbbVacio() {
    return Arbol == NULL;
}
unsigned _esAbbVacio(TABB A) {
    return A == NULL;
}

TABB izqAbb(TABB A) {
    return A->izq;
}

TABB derAbb(TABB A) {
    return A->der;
}

void leerElementoAbb(TABB A, ElemTS *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int comparar_clave_elem(TIPOCLAVE cl, ElemTS E) {
    return _comparar_claves(cl, _clave_elem(&E));
}
//Función privada para informar si una clave está en el árbol

unsigned es_miembro_clave(TABB A, TIPOCLAVE cl) {
    if (A == NULL) {  // Si la celda actual es NULL, el árbol está vacío en ese punto
        return 0;
    }
    int comp = comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        return 1;
    }
    if (comp > 0) { // cl > A->info
        return es_miembro_clave(derAbb(A), cl);
    }
    // cl < A->info
    return es_miembro_clave(izqAbb(A), cl);
}

//Funciones públicas

unsigned esMiembroAbb(ElemTS E) {
    return es_miembro_clave(Arbol, _clave_elem(&E));
}


void buscarNodoAbbRec(TABB A, TIPOCLAVE cl, ElemTS *nodo) {
    if (A == NULL) {  // Si llegamos a un nodo vacío, terminamos la búsqueda
        return;
    }

    int comp = comparar_clave_elem(cl, A->info);

    if (comp == 0) {  // Si encontramos el nodo, lo almacenamos
        *nodo = A->info;
        return;
    }

    // Si la clave es menor, buscamos en el subárbol izquierdo
    if (comp < 0) {
        buscarNodoAbbRec(A->izq, cl, nodo);
    } else {  // Si la clave es mayor, buscamos en el subárbol derecho
        buscarNodoAbbRec(A->der, cl, nodo);
    }
}

void buscarNodoAbb(TIPOCLAVE cl, ElemTS *nodo) {
    if (Arbol != NULL) {
        buscarNodoAbbRec(Arbol, cl, nodo);  // Llamamos a la función recursiva
    }
}

//OPERACIONES DE MODIFICACIÓN

/* Funcion recursiva para insertar un nuevo nodo 
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */


void insertarElementoAbbRec(TABB *A, ElemTS E) {
    if (*A == NULL) {  // Si el árbol o subárbol es vacío, insertamos el nuevo nodo
        *A = (TABB) malloc(sizeof(struct celda));
        (*A)->info = E;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }

    TIPOCLAVE cl = _clave_elem(&E);
    int comp = comparar_clave_elem(cl, (*A)->info);

    // Si la clave es mayor, insertamos en el subárbol derecho
    if (comp > 0) {
        insertarElementoAbbRec(&(*A)->der, E);
    } else {  // Si la clave es menor o igual, insertamos en el subárbol izquierdo
        insertarElementoAbbRec(&(*A)->izq, E);
    }
}
void insertarElementoAbb(ElemTS E) {
    insertarElementoAbbRec(&Arbol, E);  // Llamamos a la función recursiva con el árbol global
}



/* Funcion privada que devuelve mínimo de subárbol dcho */
 ElemTS _suprimir_min(TABB * A) {//Se devuelve el elemento más a la izquierda
    TABB aux;
    ElemTS ele;
    if (esAbbVacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}
void suprimirElementoAbbRec(TABB *A, ElemTS E) {
    TABB aux;

    if (*A == NULL) {  // Si el árbol o subárbol es vacío, terminamos
        return;
    }

    TIPOCLAVE cl = _clave_elem(&E);
    int comp = comparar_clave_elem(cl, (*A)->info);

    if (comp < 0) {  // Si la clave es menor, buscamos en el subárbol izquierdo
        suprimirElementoAbbRec(&(*A)->izq, E);
    } else if (comp > 0) {  // Si la clave es mayor, buscamos en el subárbol derecho
        suprimirElementoAbbRec(&(*A)->der, E);
    } else {  // Si encontramos el nodo a eliminar
        if (esAbbVacio((*A)->izq) && esAbbVacio((*A)->der)) {  // No tiene hijos
            _destruir_elem(&((*A)->info));
            free(*A);
            *A = NULL;
        } else if (esAbbVacio((*A)->izq)) {  // Solo tiene hijo derecho
            aux = *A;
            *A = (*A)->der;
            _destruir_elem(&aux->info);
            free(aux);
        } else if (esAbbVacio((*A)->der)) {  // Solo tiene hijo izquierdo
            aux = *A;
            *A = (*A)->izq;
            _destruir_elem(&aux->info);
            free(aux);
        } else {  // Tiene ambos hijos, reemplazamos por el mínimo del subárbol derecho
            _destruir_elem(&(*A)->info);  // Eliminamos la info pero no el nodo
            (*A)->info = _suprimir_min(&(*A)->der);  // Suprimimos el mínimo del subárbol derecho
        }
    }
}

void suprimirElementoAbb(ElemTS E) {
    suprimirElementoAbbRec(&Arbol, E);  // Llamamos a la función recursiva con el árbol global
}


/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.*/
void _modificar(TABB A, TIPOCLAVE cl, ElemTS nodo) {
    if (esAbbVacio(A)) {
        return;
    }
    int comp = comparar_clave_elem(cl, A->info);
    if (comp == 0) {
        A->info = nodo;
    } else if (comp < 0) {
        _modificar(A->izq, cl, nodo);
    } else {
        _modificar(A->der, cl, nodo);
    }
}


/* Permite modificar el nodo extrayendo del mismo la clave */
void modificarElementoAbb(TABB A, ElemTS nodo) {
    TIPOCLAVE cl = _clave_elem(&nodo);
    _modificar(A, cl, nodo);
}



void imprimirAbbRec(TABB A) {
    if (A != NULL) {
        // Primero recorre el subárbol izquierdo
        imprimirAbbRec(izqAbb(A));

        // Luego imprime el elemento actual
        ElemTS elem;
        leerElementoAbb(A, &elem);
        printf("Lexema: %s, Numero: %d\n", elem.lexema, elem.numero);

        // Finalmente recorre el subárbol derecho
        imprimirAbbRec(derAbb(A));
    }
}

void imprimirAbb() {
    imprimirAbbRec(Arbol);
}