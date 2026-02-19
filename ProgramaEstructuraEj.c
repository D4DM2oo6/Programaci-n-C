#include <stdio.h>  // Librería estándar para entrada/salida como printf
#include <string.h> // Librería para poder manipular arreglos de caracteres, o sea textos

// Definir la Estructura de Datos personalizada usando struct
// Esto permite agrupar diferentes tipos de datos primitivos
// Es como una mini clase que solo puede almacenar atributos
struct Alumno {
    int carnet;
    char nombre[50]; // Un arreglo de hasta 50 caracteres para el nombre
    float notaFinal;
};

int main() {
    // Se crea un Array que guardará 3 elementos de tipo struct Alumno
    struct Alumno clase[3];

    // Se llenan los datos del primer alumno en el índice 0
    clase[0].carnet = 25057;
    // En C no se puede hacer nombre = "pepito", se tiene que usar strcpy, que es string copy
    strcpy(clase[0].nombre, "Sebas"); 
    clase[0].notaFinal = 85.5;

    // Se llenan los datos del segundo alumno en el índice 1
    clase[1].carnet = 24064;
    strcpy(clase[1].nombre, "David");
    clase[1].notaFinal = 92.0;

    // Se llenan los datos del tercer alumno en el índice 2
    clase[2].carnet = 26031;
    strcpy(clase[2].nombre, "Juancho");
    clase[2].notaFinal = 78.3;

    // Uso un ciclo for para recorrer el arreglo e imprimir los datos
    printf(" Notas de la Clase \n");
    
    for(int i = 0; i < 3; i++) {
        // %d es para enteros, %s para textos, y %.2f para flotantes con 2 decimales
        printf("Carnet: %d | Nombre: %s | Nota: %.2f\n", clase[i].carnet, clase[i].nombre, clase[i].notaFinal);
    }
    return 0; // Se debe indicar que el programa terminó exitosamente
}