#include <stdio.h>
#include <stdlib.h>  // Librería obligatoria para malloc y free (gestión de memoria dinámica)
#include <string.h>  // Librería para manejar textos (strcpy)

/* * 1. DEFINICIÓN DE LA ESTRUCTURA DEL NODO
 * A diferencia del struct anterior, aquí añadimos PUNTEROS.
 * Un puntero (*) es una variable que guarda la DIRECCIÓN DE MEMORIA de otra variable.
 */
struct NodoAlumno {
    int carnet;
    char nombre[50];
    float notaFinal;
    
    // Punteros hacia los hijos del nodo.
    // 'izquierda' guardará carnets menores, 'derecha' guardará carnets mayores.
    struct NodoAlumno* izquierda; 
    struct NodoAlumno* derecha;   
};

/*
 * 2. FUNCIÓN PARA CREAR UN NODO EN MEMORIA
 * Esta función no usa arreglos fijos. Pide memoria al sistema operativo "al vuelo".
 */
struct NodoAlumno* crearNodo(int carnet, const char* nombre, float nota) {
    // malloc (Memory Allocation) pide un bloque de memoria del tamaño exacto del struct.
    // Retorna la dirección de memoria donde se creó.
    struct NodoAlumno* nuevoNodo = (struct NodoAlumno*)malloc(sizeof(struct NodoAlumno));

    // Usamos la flecha (->) en lugar del punto (.) porque estamos trabajando
    // con un PUNTERO a una estructura, no con la estructura directamente.
    nuevoNodo->carnet = carnet;
    strcpy(nuevoNodo->nombre, nombre);
    nuevoNodo->notaFinal = nota;
    
    // Al nacer, el nodo es una hoja, no tiene hijos conectados aún.
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;

    return nuevoNodo; // Devolvemos la ubicación en memoria de este alumno.
}

/*
 * 3. ALGORITMO RECURSIVO DE INSERCIÓN
 * Va comparando el carnet para decidir si el alumno va a la rama izquierda o derecha.
 */
struct NodoAlumno* insertarNodo(struct NodoAlumno* raiz, int carnet, const char* nombre, float nota) {
    // Caso base: si llegamos a un espacio vacío, ahí colocamos el nuevo nodo.
    if (raiz == NULL) {
        return crearNodo(carnet, nombre, nota);
    }

    // Si el carnet es menor que el actual, nos vamos por la rama izquierda.
    if (carnet < raiz->carnet) {
        raiz->izquierda = insertarNodo(raiz->izquierda, carnet, nombre, nota);
    }
    // Si el carnet es mayor, nos vamos por la rama derecha.
    else if (carnet > raiz->carnet) {
        raiz->derecha = insertarNodo(raiz->derecha, carnet, nombre, nota);
    }

    return raiz; // Retornamos la raíz sin modificar para mantener la conexión.
}

/*
 * 4. ALGORITMO EFICIENTE DE BÚSQUEDA (O(log n))
 * Encuentra a un alumno rapidísimo descartando mitades del árbol.
 */
struct NodoAlumno* buscarNodo(struct NodoAlumno* raiz, int carnetBuscado) {
    // Si llegamos al final y no hay nada, o si encontramos al alumno:
    if (raiz == NULL || raiz->carnet == carnetBuscado) {
        return raiz; 
    }

    // Si el carnet buscado es mayor, descartamos toda la izquierda y buscamos a la derecha.
    if (raiz->carnet < carnetBuscado) {
        return buscarNodo(raiz->derecha, carnetBuscado);
    }

    // Si el carnet buscado es menor, buscamos a la izquierda.
    return buscarNodo(raiz->izquierda, carnetBuscado);
}

/*
 * 5. IMPRESIÓN "IN-ORDER" (Orden Ascendente)
 * Este algoritmo de recorrido es mágico: al ir siempre a la izquierda,
 * luego imprimir el centro, y luego a la derecha, ¡los datos salen ordenados automáticamente!
 */
void imprimirInOrder(struct NodoAlumno* raiz) {
    if (raiz != NULL) {
        imprimirInOrder(raiz->izquierda); // Visita la rama izquierda
        printf("Carnet: %d | Nombre: %s | Nota: %.2f\n", raiz->carnet, raiz->nombre, raiz->notaFinal);
        imprimirInOrder(raiz->derecha);   // Visita la rama derecha
    }
}

/*
 * 6. LIBERACIÓN DE MEMORIA (CRÍTICO EN C)
 * Como C no tiene Garbage Collector, toda memoria pedida con malloc DEBE limpiarse con free.
 */
void liberarArbol(struct NodoAlumno* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz); // Destruye el nodo y devuelve la memoria al sistema operativo
    }
}

// ================= FUNCIÓN PRINCIPAL =================
int main() {
    printf("=== SISTEMA DE ALUMNOS CON ARBOL BINARIO DE BUSQUEDA ===\n\n");

    struct NodoAlumno* raiz = NULL; // El árbol comienza vacío

    // 1. Inserción de datos (Tomando los de su programa anterior y agregando más)
    raiz = insertarNodo(raiz, 25057, "Sebas", 85.5);
    insertarNodo(raiz, 24064, "David", 92.0);
    insertarNodo(raiz, 26031, "Juancho", 78.3);
    insertarNodo(raiz, 21000, "Andres", 95.0); // Nodo extra para probar el árbol
    insertarNodo(raiz, 27000, "Maria", 88.0);

    // 2. Impresión In-Order (Verán que se imprimen de menor a mayor carnet automáticamente)
    printf("--- Lista de Clase (Ordenada por Carnet) ---\n");
    imprimirInOrder(raiz);

    // 3. Demostración del Algoritmo Eficiente de Búsqueda
    printf("\n--- Prueba de Busqueda Eficiente ---\n");
    int carnetABuscar = 26031;
    struct NodoAlumno* resultado = buscarNodo(raiz, carnetABuscar);

    if (resultado != NULL) {
        printf("Alumno encontrado exitosamente: %s (Nota: %.2f)\n", resultado->nombre, resultado->notaFinal);
    } else {
        printf("Alumno con carnet %d NO existe en el sistema.\n", carnetABuscar);
    }

    // 4. Limpieza del desastre (Evitar Memory Leaks)
    liberarArbol(raiz);
    printf("\nMemoria liberada exitosamente. Finalizando programa.\n");

    return 0;
}