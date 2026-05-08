#include <stdio.h>
#include <stdlib.h>  // Librería obligatoria para malloc y free, gestión de memoria dinámica
#include <string.h>  // Librería para manejar textos

/* * 1. DEFINICIÓN DE LA ESTRUCTURA DEL NODO
 * A diferencia del struct anterior, aquí añadimos PUNTEROS
 * Un puntero (*) es una variable que guarda la DIRECCIÓN DE MEMORIA de otra variable
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

    return 0;
}