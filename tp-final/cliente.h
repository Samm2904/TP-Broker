#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inversion.h"

typedef struct cliente{
    	char nombre[50], email[50], cuil[15], password[20];
    	float saldo_cuenta;
    	inversion inversiones[500];
    	int num_inversiones;
    	char condicionUser;
	} cliente;

void menuClienteLogueado();
void menuClienteInversion ();
void menuRendimientos();
void menuGestionSaldo(cliente c);
void menuPerfilCliente();
cliente crearCliente();
cliente cargarSaldo(cliente c);
cliente extraerSaldo(cliente c);
void verPortfolio(cliente c);
cliente iniciarSesion(cliente listaClientes[], char nombreIng[], char passIng[], int cantidadClientes);
void menuInversiones ();
cliente copiarInversiones(cliente c, inversion baseInversiones[], int cantidadInversiones);
void menuSaldoInsuficiente();
void menuConfirmarCompra();
cliente comprarInversion (cliente c, char empresaCompraInversion[],float precioCompra, float cantidadAComprar);
void mostrarAccionesCliente(cliente clienteLogueado, char tickers[][10], float precios[], int cantidadTickers);
int validarAcciones(cliente c, char accionEmpresaVender[]);
cliente venderAcciones(cliente c, char ticker[10], int cantidadAVender, float precioVenta, char fecha[11]);
cliente darDeBaja(cliente c, cliente baseClientes[],int cantidadClientes);
void menuConfirmarBaja();
void menuModificarCliente();
cliente cambiarNombre(cliente c, cliente baseCliente[], int cantidadClientes);
cliente cambiarPassword(cliente c, cliente baseCliente[], int cantidadClientes);
cliente darDeAlta(char cuilADarDeAlta[], cliente baseClientes[], int cantidadClientes);
int clientesInactivos(cliente baseClientes[],int cantidadClientes);
int validarCuil(char cuil[],cliente baseClientes[],int cantClientes);
void valorDiario(float precios[], char tickers[][10], cliente c, int cantidadempresas, char fecha[]);
void valorHistorico(float precios[],char tickers[][10],cliente c, int cantidadempresas);
void mostrarTickersYPrecios(char tickers[][10], float precios[], int cantidadTickers) ;

#endif // CLIENTE_H_INCLUDED
