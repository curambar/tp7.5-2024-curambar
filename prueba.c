#include "nomina.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void comparar_edad_test(char mensaje[], persona_t p1, persona_t p2, int esperado)
{
	printf("\n%s\n", mensaje);
	imprimir_persona(p1);
	imprimir_persona(p2);
	int comparacion = comparar_edad(p1, p2);
	printf("Esperado: (%d)\tObtenido: (%d)\n", esperado, comparacion);
	if(esperado == comparacion)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

void promedio_edades_test(char mensaje[], int size, persona_t personas[], float esperado)
{
	printf("\n%s\n", mensaje);
	float promedio = promedio_edades(size, personas);
	printf("Esperado: (%f)\tObtenido: (%f)\n", esperado, promedio);
	if(esperado == promedio)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

void joven_test(char mensaje[], int size, persona_t personas[], persona_t esperado)
{
	printf("\n%s\n", mensaje);
	persona_t *persona = encontrar_mas_joven(size, personas);
	printf("Persona esperada:\n");
	imprimir_persona(esperado);
	printf("Persona encontrada:\n");
	imprimir_persona(*persona);
	if(son_iguales_persona(esperado, *persona))
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

void copiar_estudiante_test(char mensaje[], estudiante_t *origen)
{
	printf("\n%s\n", mensaje);
	int test[] = {0, 0, 0, 0};
	estudiante_t *destino = crear_estudiante("A", 0, 0, test);
	printf("Estudiante ORIGEN:\n");
	imprimir_estudiante(origen);
	copiar_estudiante(destino, origen);
	printf("Estudiante COPIADO:\n");
	imprimir_estudiante(destino);
	if(son_iguales_estudiante(origen, destino))
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
	liberar_estudiante(destino);
}

void promedio_calificaciones_test(char mensaje[], estudiante_t *estudiante, float esperado)
{
	printf("\n%s\n", mensaje);
	printf("Estudiante:\n");
	imprimir_estudiante(estudiante);
	float promedio = calcular_promedio_calificaciones(estudiante);
	float f_min = 1.0E-5;
	printf("Promedio esperado: (%f)\tPromedio calculado: (%f)\n", esperado, promedio);
	if(fabs(esperado - promedio) < f_min)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

void actualizar_calificaciones_test(char mensaje[], estudiante_t *estudiante, int new[])
{
	printf("\n%s\n", mensaje);
	printf("Estudiante:\n");
	imprimir_estudiante(estudiante);
	printf("Nuevas calificaciones:\n");
	for(int i = 0; i < MAX_CALIFICACIONES; i++)
	{
		printf("Calificacion %d = %d\n", i, new[i]);
	}
	actualizar_calificaciones(estudiante, new);
	int compara = memcmp(estudiante->calificaciones, new, sizeof(estudiante->calificaciones));
	if(compara == 0)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

void mejor_promedio_test(char mensaje[], int size, estudiante_t** estudiantes, estudiante_t *esperado)
{
	printf("\n%s\n", mensaje);
	float promedio = calcular_promedio_calificaciones(esperado);
	printf("Estudiante esperado con promedio %f:\n", promedio);
	imprimir_estudiante(esperado);
	estudiante_t *estudiante = encontrar_estudiante_mejor_promedio(size, estudiantes);
	float promedio_encontrado = calcular_promedio_calificaciones(estudiante);
	printf("Estudiante encontrado con promedio %f:\n", promedio_encontrado);
	imprimir_estudiante(estudiante);
	if(son_iguales_estudiante(estudiante, esperado))
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
	printf("Antes de liberar estudiante: %s\n", esperado->persona.nombre);
	liberar_estudiante(estudiante);
	printf("Despues de liberar estudiante: %s\n", esperado->persona.nombre);
}

void menor_edad_test(char mensaje[], int size, estudiante_t** estudiantes, estudiante_t *esperado)
{
	printf("\n%s\n", mensaje);
	printf("Estudiante esperado:\n");
	imprimir_estudiante(esperado);
	estudiante_t *estudiante = encontrar_estudiante_mas_joven(size, estudiantes);
	printf("Estudiante encontrado:\n");
	imprimir_estudiante(estudiante);
	if(son_iguales_estudiante(estudiante, esperado))
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
	liberar_estudiante(estudiante);
}

void ordenar_estudiantes_test(char mensaje[], int size, estudiante_t** estudiantes)
{
	printf("\n%s\n", mensaje);
	printf("Antes de ordenar:\n");
	for(int i = 0; i < size; i++)
	{
		printf("Legajo orden %d = %d (%s)\n", i, estudiantes[i]->legajo, estudiantes[i]->persona.nombre);
	}
	ordenar_estudiantes_por_legajo(size, &estudiantes);
	printf("Despues de ordenar:\n");
	
	bool ordenado = true;
	int base = estudiantes[0]->legajo;
	for(int i = 0; i < size; i++)
	{
		printf("Legajo orden %d = %d (%s)\n", i, estudiantes[i]->legajo, estudiantes[i]->persona.nombre);
		if(estudiantes[i]->legajo > base)
		{
			ordenado = false;
		}
		base = estudiantes[i]->legajo;
	}
	if(ordenado)
	{
		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

int main()
{
	{
		printf("\nProbando comparar_edad_test\n");
		printf("---------------------------\n");
		{
			persona_t p1 = crear_persona("Cacho", 20);
			persona_t p2 = crear_persona("Manuel", 30);
			comparar_edad_test("Persona 2 mayor", p1, p2, -1);
		}
		{
			persona_t p1 = crear_persona("Ana", 40);
			persona_t p2 = crear_persona("Raul", 30);
			comparar_edad_test("Persona 1 mayor", p1, p2, 1);
		}
		{
			persona_t p1 = crear_persona("Beto", 30);
			persona_t p2 = crear_persona("Pocha", 30);
			comparar_edad_test("Misma edad", p1, p2, 0);
		}
	}
	{
		printf("\nProbando promedio_edades_test\n");
		printf("-----------------------------\n");
		{
			persona_t p1 = crear_persona("Cacho", 20);
			persona_t p2 = crear_persona("Manuel", 30);
			persona_t p3 = crear_persona("Julia", 25);
			persona_t personas[] = {p1, p2, p3};
			float promedio = (20.0 + 30.0 + 25.0) / 3.0;
			promedio_edades_test("Arreglo de tres personas", 3, personas, promedio);
		}
		{
			persona_t p1 = crear_persona("Cacho", 20);
			persona_t personas[] = {p1};
			float promedio = 20.0;
			promedio_edades_test("Arreglo de una persona", 1, personas, promedio);
		}
	}
	{
		printf("\nProbando joven_test\n");
		printf("-------------------\n");
		{
			persona_t p1 = crear_persona("Cacho", 40);
			persona_t p2 = crear_persona("Manuel", 20);
			persona_t p3 = crear_persona("Julia", 25);
			persona_t personas[] = {p1, p2, p3};
			joven_test("Arreglo de tres personas de diferentes edades", 3, personas, p2);
		}
		{
			persona_t p1 = crear_persona("Cacho", 20);
			persona_t p2 = crear_persona("Manuel", 20);
			persona_t p3 = crear_persona("Julia", 20);
			persona_t personas[] = {p1, p2, p3};
			joven_test("Arreglo de tres personas de iguales edades", 3, personas, p1);
		}
	}
	{
		printf("\nProbando copiar_estudiante\n");
		printf("--------------------------\n");
		{
			int calif[] = {1, 2, 3, 4};
			estudiante_t *origen = crear_estudiante("Cacho", 20, 0, calif);
			copiar_estudiante_test("Test", origen);
			liberar_estudiante(origen);
		}
	}
	{
		printf("\nProbando calcular_promedio_calificaciones\n");
		printf("-----------------------------------------\n");
		{
			int calif[] = {1, 2, 3, 4};
			float promedio = (1 + 2 + 3 + 4) * 1.0 / 4;
			estudiante_t *estudiante = crear_estudiante("Cacho", 20, 0, calif);
			promedio_calificaciones_test("Test", estudiante, promedio);
			liberar_estudiante(estudiante);
		}
	}
	{
		printf("\nProbando actualizar_calificaciones\n");
		printf("----------------------------------\n");
		{
			int calif[] = {1, 2, 3, 4};
			int new[] = {10, 10, 10, 10};
			estudiante_t *estudiante = crear_estudiante("Cacho", 20, 0, calif);
			actualizar_calificaciones_test("Test", estudiante, new);
			liberar_estudiante(estudiante);
		}
	}
	{
		printf("\nProbando encontrar_estudiante_mejor_promedio\n");
		printf("--------------------------------------------\n");
		{
			int calif_1[] = {1, 2, 3, 4};
			int calif_2[] = {2, 3, 4, 5};
			int calif_3[] = {3, 4, 5, 6};
			estudiante_t **grupo = malloc(3 * sizeof(estudiante_t));
			estudiante_t *e1 = crear_estudiante("Cacho", 20, 1, calif_1);
			estudiante_t *e2 = crear_estudiante("Juana", 20, 2, calif_2);
			estudiante_t *e3 = crear_estudiante("Pocho", 20, 3, calif_3);
			grupo[0] = e1;
			grupo[1] = e2;
			grupo[2] = e3;
			mejor_promedio_test("Test", 3, grupo, e3);
			printf("Luego de volver de la funcion: %s\n", e3->persona.nombre);
			liberar_estudiante(e3);
			liberar_estudiante(e2);
			liberar_estudiante(e1);
			free(grupo);
		}
	}
	{
		printf("\nProbando encontrar_estudiante_mas_joven\n");
		printf("---------------------------------------\n");
		{
			int calif[] = {1, 2, 3, 4};
			estudiante_t **grupo = malloc(3 * sizeof(estudiante_t));
			estudiante_t *e1 = crear_estudiante("Cacho", 30, 1, calif);
			estudiante_t *e2 = crear_estudiante("Juana", 20, 2, calif);
			estudiante_t *e3 = crear_estudiante("Pocho", 25, 3, calif);
			grupo[0] = e1;
			grupo[1] = e2;
			grupo[2] = e3;
			menor_edad_test("Test", 3, grupo, e2);
			liberar_estudiante(e3);
			liberar_estudiante(e2);
			liberar_estudiante(e1);
			free(grupo);
		}
	}
	{
		printf("\nProbando ordenar_estudiantes_por_legajo\n");
		printf("---------------------------------------\n");
		{
			int calif[] = {1, 2, 3, 4};
			estudiante_t **grupo = malloc(4 * sizeof(estudiante_t));
			estudiante_t *e1 = crear_estudiante("Cacho", 30, 4, calif);
			estudiante_t *e2 = crear_estudiante("Juana", 20, 2, calif);
			estudiante_t *e3 = crear_estudiante("Pocho", 25, 1, calif);
			estudiante_t *e4 = crear_estudiante("Pocho", 25, 3, calif);
			grupo[0] = e1;
			grupo[1] = e2;
			grupo[2] = e3;
			grupo[3] = e4;
			ordenar_estudiantes_test("Test", 4, grupo);
			liberar_estudiante(e4);
			liberar_estudiante(e3);
			liberar_estudiante(e2);
			liberar_estudiante(e1);
			free(grupo);
		}
	}
}