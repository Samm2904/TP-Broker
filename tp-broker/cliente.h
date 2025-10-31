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
	} cliente;

///FIRMAS
void menuClienteLogueado();
void menuClienteInversion ();
void menuRendimientos();
void menuGestionSaldo(cliente c);
void menuModificarPerfilCliente();
cliente crearCliente();
cliente cargarSaldo(cliente c);
cliente extraerSaldo(cliente c);
void verPortfolio(cliente c);
cliente iniciarSesion(cliente listaClientes[], char nombreIng[], char passIng[], int cantidadClientes );
void menuInversiones ();
cliente copiarInversiones(cliente c, inversion baseInversiones[], int cantidadInversiones);
void menuSaldoInsuficiente();
void menuConfirmarCompra();
cliente comprarInversion (cliente c, char empresaCompraInversion[],float precioCompra, float cantidadAComprar);





#endif // CLIENTE_H_INCLUDED


