/*
 * Trabajo Practico 7.5 - EXTRA
 * Leandro Suarez - curambar
 * Programación 1 - Ingenieria en Computación - UNRN Andina
 * Cohorte 2024
 */

#include "nomina.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*

estudiante_t* crear_estudiante(char nombre[], int edad, int legajo, int calificaciones[]);

void liberar_estudiante(estudiante_t* estudiante);

void copiar_estudiante(estudiante_t* destino, estudiante_t* origen);

float calcular_promedio_calificaciones(estudiante_t* estudiante);

void imprimir_estudiante(estudiante_t* estudiante);

void actualizar_calificaciones(estudiante_t* estudiante, int calificaciones[]);

estudiante_t* encontrar_estudiante_mejor_promedio(estudiante_t** estudiantes, int cantidad);

estudiante_t* encontrar_estudiante_mas_joven(estudiante_t** estudiantes, int cantidad);

void ordenar_estudiantes_por_legajo(estudiante_t** estudiantes, int cantidad);*/


persona_t crear_persona(char nombre[], int edad)
{
	persona_t persona = {0};
	persona.edad = edad;
	strcpy(persona.nombre, nombre);
	return persona;
}

int comparar_edad(persona_t persona_1, persona_t persona_2)
{
	int comparacion = 0;
	if(persona_1.edad > persona_2.edad)
	{
		comparacion = 1;
	}
	else if(persona_1.edad < persona_2.edad)
	{
		comparacion = -1;
	}
	return comparacion;
}

void imprimir_persona(persona_t persona)
{
	printf("%s - Edad %d\n", persona.nombre, persona.edad);
}

float promedio_edades(int size, persona_t personas[])
{
	float promedio = 0.0;
	for(int i = 0; i < size; i++)
	{
		promedio+= personas[i].edad * 1.0 / size;
	}
	return promedio;
}

persona_t *encontrar_mas_joven(int size, persona_t personas[])
{
	persona_t* joven = &personas[0];
	int menor = joven->edad;
	for(int i = 0; i < size; i++)
	{
		if(personas[i].edad < menor)
		{
			joven = &personas[i];
			menor = joven->edad;
		}
	}
	return joven;
}

bool son_iguales_persona(persona_t p1, persona_t p2)
{
	bool iguales = false;
	if(strcmp(p1.nombre, p2.nombre) == 0 && p1.edad == p2.edad)
	{
		iguales = true;
	}
	return iguales;
}

estudiante_t* crear_estudiante(char nombre[], int edad, int legajo, int calificaciones[])
{
	estudiante_t *estudiante = malloc(sizeof(estudiante_t));
	if(estudiante != NULL)
	{
		persona_t persona = crear_persona(nombre, edad);
		estudiante->persona = persona;
		estudiante->legajo = legajo;
		size_t cantidad = MAX_CALIFICACIONES * sizeof(int);
		memcpy(estudiante->calificaciones, calificaciones, cantidad);
	}
	return estudiante;
}

void liberar_estudiante(estudiante_t* estudiante)
{
	if(estudiante != NULL)
	{
		free(estudiante);
	}
}

void copiar_estudiante(estudiante_t* destino, estudiante_t* origen)
{
	if(origen != NULL)
	{
		strcpy(destino->persona.nombre, origen->persona.nombre);
		destino->persona.edad = origen->persona.edad;
		destino->legajo = origen->legajo;
		size_t cantidad = MAX_CALIFICACIONES * sizeof(int);
		memcpy(destino->calificaciones, origen->calificaciones, cantidad);
	}
}

bool son_iguales_estudiante(estudiante_t* e1, estudiante_t* e2)
{
	bool iguales = true;
	persona_t p1 = e1->persona;
	persona_t p2 = e2->persona;
	if(!son_iguales_persona(p1, p2))
	{
		iguales = false;
	}
	else
	{
		int calif = memcmp(e1->calificaciones, e2->calificaciones, sizeof(e1->calificaciones));
		if(e1->legajo != e2->legajo || calif != 0)
		{
			iguales = false;
		}
	}
	return iguales;
}

void imprimir_estudiante(estudiante_t* estudiante)
{
	if(estudiante != NULL)
	{
		imprimir_persona(estudiante->persona);
		printf("Legajo: %d\n", estudiante->legajo);
		for(int i = 0; i < MAX_CALIFICACIONES; i++)
		{
			printf("Calificacion %d: %d\n", i, estudiante->calificaciones[i]);
		}
	}
	else
	{
		printf("ESTUDIANTE NULO");
	}
}

float calcular_promedio_calificaciones(estudiante_t* estudiante)
{
	float promedio = 0;
	if(estudiante != NULL)
	{
		for(int i = 0; i < MAX_CALIFICACIONES; i++)
		{
			promedio+= 1.0 * estudiante->calificaciones[i] / MAX_CALIFICACIONES;
		}
	}
	return promedio;
}

void actualizar_calificaciones(estudiante_t* estudiante, int calificaciones[])
{
	if(estudiante != NULL)
	{
		size_t cantidad = MAX_CALIFICACIONES * sizeof(int);
		memcpy(estudiante->calificaciones, calificaciones, cantidad);
	}
}

estudiante_t* encontrar_estudiante_mejor_promedio(int size, estudiante_t** estudiantes)
{
	estudiante_t *mejor = estudiantes[0];
	float mejor_promedio = calcular_promedio_calificaciones(mejor);
	for(int i = 0; i < size; i++)
	{
		float promedio = calcular_promedio_calificaciones(estudiantes[i]);
		if(promedio > mejor_promedio)
		{
			mejor = estudiantes[i];
			mejor_promedio = promedio;
		}
	}
	return mejor;
}

estudiante_t* encontrar_estudiante_mas_joven(int size, estudiante_t** estudiantes)
{
	estudiante_t *menor = estudiantes[0];
	int menor_edad = menor->persona.edad;
	for(int i = 0; i < size; i++)
	{
		int edad = estudiantes[i]->persona.edad;
		if(edad < menor_edad)
		{
			menor = estudiantes[i];
			menor_edad = edad;
		}
	}
	return menor;
}

/**
 * Funcion auxiliar para comparar estudiantes por legajo
 * @param e1 el primer estudiante_t a comparar
 * @param e2 el segunda estudiante_t a comparar
 * @returns 1 si el legajo de e1 es mayor
 * 			0 si son iguales
 * 			-1 si el legajo de e1 es menor 
 */
int comparar_por_legajo(const void* e1, const void* e2)
{
	int legajo_1 = ((estudiante_t*)e1)->legajo;
	int legajo_2 = ((estudiante_t*)e2)->legajo;
	return (legajo_1 - legajo_2);
}

void ordenar_estudiantes_por_legajo(int size, estudiante_t*** estudiantes)
{
	qsort(*estudiantes, size, sizeof(estudiante_t), comparar_por_legajo);
}