#ifndef EMPRESA_H_INCLUDED
#define EMPRESA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void menuEmpresa();

typedef struct empresa{
    	char id_ticker[10];
    	char nombre[50],password[20];
    	float precio_actual;

	} empresa;
void verHistoricoOperaciones(empresa e, cliente listaClientes[], int cantidadClientes);
empresa validarEmpresa(empresa e,char nombreEmpresaIngresado[]); ///MODIFICAR CON LA BD DE EMPRESAAS PRESENTEEEEEEEEEEEEEEEEEEEEEE

#endif // EMPRESA_H_INCLUDED




