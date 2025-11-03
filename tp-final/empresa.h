#ifndef EMPRESA_H_INCLUDED
#define EMPRESA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inversion.h"
#include "cliente.h"

typedef struct empresa{
    	char id_ticker[10];
    	char nombre[50];
    	float precio_actual;
	} empresa;

void menuEmpresa();
void filtrarIDTICKER(empresa e, cliente baseClientes[], int cantidadClientes, inversion baseInversiones[], int cantidadInversiones);
empresa validarEmpresaNombre(empresa baseEmpresas[],char nombreEmpresaIng[], int cantidadEmpresas);
empresa validarEmpresaTicker(empresa baseEmpresas[],char tickerEmpresaIng[], int cantidadEmpresas);
void listaEmpresas(empresa baseEmpresas[], int cantidadEmpresas);
void menuHistorico();
void mostrarClientes(empresa e, cliente baseClientes[], int cantidadClientes, inversion baseInversiones[], int cantidadInversiones) ;
void mostrarAccionCliente(cliente baseCliente[], int cantidadClientes,empresa e,char nombreClienteVer[], inversion baseInversiones[], int cantidadInversiones);
void mostrarRanking(cliente baseClientes[],int cantidadClientes, empresa e, inversion baseIneversiones[], int cantidadInversiones);
int obtenerTickersYPrecios(cliente clienteLogueado, empresa baseEmpresas[], int cantidadEmpresas, char tickers[][10], float precios[], int cantidadTickersMax);
float obtenerPrecioEmpresa(char accionEmpresaVender[10], char tickers[][10], float precios[], int cantidadTickers) ;
float cambiarPrecios(empresa empresaACambiar, empresa baseEmpresas[],int cantidadEmpresas);
empresa crearEmpresa();
void cargarTickers(char tickers[][10], empresa baseEmpresas[], int cantidadEmpresas);
void cargarPrecios(float precios[],empresa baseEmpresas[], int cantidadEmpresas);

#endif // EMPRESA_H_INCLUDED
