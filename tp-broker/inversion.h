#ifndef INVERSION_H_INCLUDED
#define INVERSION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct inversion{
    	char id_ticker[10];
    	int cantidad_acciones;
    	float precio_compra;
    	char fecha[11];
    	char operacion;

	} inversion;

#endif // INVERSION_H_INCLUDED



