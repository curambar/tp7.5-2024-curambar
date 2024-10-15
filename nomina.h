/*
 * Trabajo Practico 7.5 - EXTRA
 * Leandro Suarez - curambar
 * Programación 1 - Ingenieria en Computación - UNRN Andina
 * Cohorte 2024
 */

#ifndef NOMINA_H
#define NOMINA_H

#define MAX_NOMBRE 99
#define MAX_CALIFICACIONES 4
#include <stdbool.h>

typedef struct
{
	char nombre[MAX_NOMBRE];
	int edad;
} persona_t;

typedef struct
{
	persona_t persona;
	int legajo;
	int calificaciones[MAX_CALIFICACIONES];
} estudiante_t;

/**
 * Crea una persona con los datos provistos
 * @param nombre la cadena conteniendo el nombre
 * @param edad un entero representando la edad de la persona
 * @returns	un persona_t con los datos provistos
 */
persona_t crear_persona(char nombre[], int edad);

/**
 * Compara edades de dos personas
 * @param persona_1 la primer persona a comparar
 * @param persona_2 la segunda persona a comparar
 * @returns	1 si persona_1 es mayor
 * 			-1 si persona_2 es mayor
 * 			0 si son iguales [POST]
 */
int comparar_edad(persona_t persona_1, persona_t persona_2);

/**
 * Imprime los datos de una persona
 * @param persona la persona a imprimir
 *	Imprime nombre- edad [POST]
 */
void imprimir_persona(persona_t persona);

/**
 * Calcula el promedio de edades de un arreglo de personas
 * @param size la cantidad de personas. Debe ser positivo. [PRE]
 * @param personas[] Un arreglo de persona_t, debe tener tamaño 'size' [PRE]
 * @returns	el promedio de las edades.
 */
float promedio_edades(int size, persona_t personas[]);

/**
 * Encuentra la persona con menor edad de un arreglo de personas
 * @param size la cantidad de personas. Debe ser positivo. [PRE]
 * @param personas[] Un arreglo de persona_t, debe tener tamaño 'size' [PRE]
 * @returns	un puntero a la persona_t con menor edad del arreglo.
 */
persona_t* encontrar_mas_joven(int size, persona_t personas[]);

/**
 * Determina si dos persona_t contienen los mismos datos
 * @param p1 la primer persona a comparar
 * @param p2 la segunda persona a comparar
 * @returns	true si los datos coinciden
 * 			false si no. [POST]
 */
bool son_iguales_persona(persona_t p1, persona_t p2);

/**
 * Crea un estudiante_t con los datos provistos
 * @param nombre la cadena conteniendo el nombre
 * @param edad un entero representando la edad de la persona
 * 	Estos dos parametros crean un persona_t [PRE]
 * @param legajo un entero representando el numero de legajo
 * @param calificaciones un arreglo de enteros de MAX_CALIFICACIONES de
 * 	largo. [PRE]
 * @returns	un puntero a estudiante_t con los datos provistos
 */
estudiante_t* crear_estudiante(char nombre[], int edad, int legajo, int calificaciones[]);

/**
 * Libera un estudiante_t
 * @param estudiante un puntero al estudiante_t a liberar
 * 	Si es NULL, no hace nada
 */
void liberar_estudiante(estudiante_t* estudiante);

/**
 * Copia la info de un estudiante_t en otro
 * @param destino un puntero al estudiante_t sobre el que se copiaran los datos
 * @param origen un puntero al estudiante_t desde el que se copiaran los datos
 * 	Si origen es NULL, esta funcion no hace nada
 */
void copiar_estudiante(estudiante_t* destino, estudiante_t* origen);

/**
 * Determina si dos estudiante_t contienen los mismos datos
 * @param e1 el primer estudiante_t a comparar
 * @param e2 el segunda estudiante_t a comparar
 * @returns	true si los datos coinciden
 * 			false si no. [POST]
 */
bool son_iguales_estudiante(estudiante_t* e1, estudiante_t* e2);

/**
 * Imprime los datos de un estudiante
 * @param estudiante el estudiante a imprimir
 *	Imprime:
 * 	Nombre - Edad
 * 	Numero de legajo
 * 	Calificaciones [POST]
 */
void imprimir_estudiante(estudiante_t* estudiante);

/**
 * Calcula el promedio de calificaciones de un estudiante
 * @param estudiante el estudiante a analizar
 * @returns la suma de las calificaciones dividida por MAX_CALIFICACIONES
 * 	o 0 en caso que el estudiante sea NULL [POST]
 */
float calcular_promedio_calificaciones(estudiante_t* estudiante);

/**
 * Cambia las calificaciones de un estudiante por las provistas
 * @param estudiante el estudiante a actualizar
 * @param calificaciones un array de enteros de tamaño MAX_CALIFICACIONES 
 * 	Si el estudiante es NULL no hace nada [POST]
 */
void actualizar_calificaciones(estudiante_t* estudiante, int calificaciones[]);

/**
 * Devuelve el estudiante con mejor promedio
 * @param size el numero de estudiantes en el arreglo. Debe ser un valor positivo
 * 		y debe corresponder con la cantidad de elementos en el arreglo [PRE]
 * @param estudiante el arreglo de estudiantes. Debe contener 'size' elementos [PRE]
 * @returns un puntero al estudiante encontrado.
 */
estudiante_t* encontrar_estudiante_mejor_promedio(int size, estudiante_t** estudiantes);

/**
 * Devuelve el estudiante con menor edad
 * @param size el numero de estudiantes en el arreglo. Debe ser un valor positivo
 * 		y debe corresponder con la cantidad de elementos en el arreglo [PRE]
 * @param estudiante el arreglo de estudiantes. Debe contener 'size' elementos [PRE]
 * @returns un puntero al estudiante encontrado.
 */
estudiante_t* encontrar_estudiante_mas_joven(int size, estudiante_t** estudiantes);

/**
 * Ordena un arreglo de estudiantes por legajo
 * @param size el numero de estudiantes en el arreglo. Debe ser un valor positivo
 * 		y debe corresponder con la cantidad de elementos en el arreglo [PRE]
 * @param estudiante el arreglo de estudiantes. Debe contener 'size' elementos [PRE]
 * 		Hace el ordenamiento mediante qsort, utilizando una funcion de orden auxiliar. [POST]
 */
void ordenar_estudiantes_por_legajo(int size, estudiante_t*** estudiantes);

#endif