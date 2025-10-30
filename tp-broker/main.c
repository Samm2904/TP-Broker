#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "empresa.h"
#include "inversion.h"
#include "cliente.h"


///FIRMAS
void menuPrincipal();
void menuBroker();
void menuOperarCliente();
void menuPerfilCliente();

cliente listaClientes[50]; ///Preguntar????
int cantidadClientes = 0;

int main()
{
	int opcionMenuPrincipal, opcionMBroker, opcionOperarCliente, opcionMenuEmpresa, opcionPerfilCliente, opcionPerfilClienteCopia, opcionClienteLogueado, opcionMenuSaldo, opcionMenuInversion;
	cliente nuevo, clienteLogueado;
	float copiaSaldoCliente;
	char nombreIng[30], passIng[30], empresaCompraInversion[30];
	bool noLogueado = true;

	do {
    	menuPrincipal();
    	scanf("%d",&opcionMenuPrincipal);
    	switch(opcionMenuPrincipal){
        	case 1:
            	do {
            	menuBroker();                      	///MENU DE BROKER -----------------------------------------------------------
            	scanf("%d",&opcionMBroker);
            	switch (opcionMBroker){
                	case 1:
                	//Funcion alta empresas
                	break;
                	case 2:
                	//Funcion cambiar precios
                	break;
                	case 3:
                	//modiFicar perfil empresa
                	break;
                	case 4:
                	break;
                	default:
                    	printf("Ingrse una opcion valida\n\r");
                	}
            	} while (opcionMBroker!=4);
            	break;
        	case 2:
            	do{
            	menuOperarCliente();
            	scanf("%d",&opcionOperarCliente);
            	switch (opcionOperarCliente){
                	case 1:
                    	do {
                    	menuEmpresa();              	///MENU DE EMPRESA ---------------------------------------------
                    	scanf("%d",&opcionMenuEmpresa);
                    	switch (opcionMenuEmpresa){
                        	case 1:
                            	/*do {
                            	printf("Ingrese su ticker identificatorio\n\r");
                            	}while();
                            	verHistoricoOperaciones();
                            	*/
                            	///FIJARSE COIMO VERIFICAR LA EMPRESA PARA PODER PASARLA COMO PARAMETRO
                            	break;

                        	case 2:
                        	//funcion ranking clientes
                            	break;
                        	case 3:
                            	break;
                        	default:
                            	printf("Ingrse una opcion valida\n\r");
                        	}
                    	}while(opcionMenuEmpresa!=3);
                    	break;
                	case 2:
                	do {
                    	menuPerfilCliente();
                    	scanf("%d",&opcionPerfilCliente);
                    	opcionPerfilClienteCopia = opcionPerfilCliente;
                    	switch (opcionPerfilClienteCopia){
                        	case 1:
                            	printf("Cree su cuenta:\n\r");
                            	nuevo = crearCliente();
                            	listaClientes[cantidadClientes] = nuevo;
                            	cantidadClientes++;
                            	clienteLogueado = nuevo;
                            	opcionPerfilClienteCopia = 3;
                                	break;
                        	case 2:
                            	do {
                                	printf("Ingrese su usuario:\n\r");
                                	scanf(" %30[^\n]",nombreIng);
                                	printf("Ingrese su contraseña:\n\r");
                                	scanf(" %30[^\n]",passIng);
                                	clienteLogueado = iniciarSesion(listaClientes, nombreIng, passIng,cantidadClientes);
                                	if (strcmp(clienteLogueado.nombre, "") == 0) {
                                    	printf("Usuario o contraseña incorrectos. Intente nuevamente.\n");
                                	} else {
                                    	printf("Bienvenida %s!\n", clienteLogueado.nombre);
                                        	noLogueado = false;
                                        	opcionPerfilClienteCopia = 3;
                                	}
                            	}while(noLogueado);
                            	break;
                        	case 3:
                            	break;
                        	default:
                            	printf("Ingrese una opcion valida\n\r");
                    	}
                	} while (opcionPerfilClienteCopia!=3);

                	if (opcionPerfilCliente != 3)
                	{
                    	do {
                        	menuClienteLogueado();          	///MENU CLIENTE LOGUEADO ---------------------------------------------
                        	scanf("%d",&opcionClienteLogueado);
                        	switch(opcionClienteLogueado){
                            	case 1:
                                	do {
                                    	menuInversiones ();
                                    	scanf("%d",&opcionMenuInversion);
                                    	switch (opcionMenuInversion){
                                        	case 1:
                                        	printf("Ingrese el nombre de la empresa a la que le va a comprar\n\r");
                                        	scanf("%s",empresaCompraInversion);

                                        	//compra
                                            	break;
                                        	case 2:
                                            	//vender
                                            	break;
                                        	case 3:
                                            	break;
                                        	default:
                                            	printf("Ingrese una opcion valida\n\r");
                                    	}

                                	}while(opcionMenuInversion!=3)
                                	break;
                            	case 2:
                                	///ver rendimientos
                                	break;
                            	case 3:
                                	do {
                                    	menuGestionSaldo(clienteLogueado);
                                    	scanf("%d",&opcionMenuSaldo);
                                    	switch(opcionMenuSaldo){
                                        	case 1:
                                             	clienteLogueado=cargarSaldo(clienteLogueado);
                                             	printf("Transaccion exitosa, su saldo nuevo es: %.2f\n\r",clienteLogueado.saldo_cuenta);
                                            	break;
                                        	case 2:
                                            	if (clienteLogueado.saldo_cuenta<=0){
                                                	printf("Fondos insuficientes, cargue saldo primero.\n\r");
                                            	}
                                            	else {
                                                	copiaSaldoCliente=clienteLogueado.saldo_cuenta;
                                                	clienteLogueado=extraerSaldo(clienteLogueado);
                                                	if (copiaSaldoCliente!=clienteLogueado.saldo_cuenta){
                                                    	printf("Transaccion exitosa, su saldo nuevo es: %.2f\n\r",clienteLogueado.saldo_cuenta);
                                                	}
                                            	}
                                            	break;
                                        	case 3:
                                            	break;
                                        	default:
                                            	printf("Opcion invalida, intente nuevamente.\n\r");
                                    	}
                                	} while(opcionMenuSaldo!=3);
                                	break;
                            	case 4:
                                	verPortfolio(clienteLogueado);
                                	break;
                            	case 5:
                                	/// modificar perfil
                                	break;
                            	case 6:
                                	///darse d baja
                                	break;
                            	case 7:
                                	//cerrar sesion
                                	break;
                            	default:
                            	printf("Ingrese una opcion valida.\n\r");
                            	}
                        	} while(opcionClienteLogueado!=7);
                	}
                    	break;
                	case 3:
                    	break;
                	default:
                    	printf("Ingrese una opcion valida\n\r");
                	}
            	} while(opcionOperarCliente!=3);
            	break;
        	case 3:
            	printf("Cerrando programa ...\n\r");
            	break;
        	default:
            	printf("Ingrese una opcion valida\n\r");
        	}
	} while(opcionMenuPrincipal!=3);

	return 0;
}

void menuPrincipal(){
    	printf("Bienvenido al menu principal.\n\r");
    	printf("1-Operar como Broker.\n\r");
    	printf("2-Operar como Cliente.\n\r");
    	printf("3-Salir.\n\r");
	}

void menuBroker(){
    	printf("1-Dar de alta (empresas).\n\r");
    	printf("2-Cambiar precios actuales.\n\r");
    	printf("3-Modificar perfil empresas.\n\r");
    	printf("4-Volver al menu principal.\n\r");
    	printf("Ingrese una opcion:\n\r");

}

void menuOperarCliente(){
	printf("1-Operar como empresa.\n\r");
	printf("2-Operar como cliente.\n\r");
	printf("3-Volver al menu principal.\n\r");
	printf("Ingrese una opcion:\n\r");

}

void menuPerfilCliente(){
	printf("1- Crear cuenta.\n\r");
	printf("2-Iniciar sesion.\n\r");
	printf("3-Volver al menu principal.\n\r");
	printf("Ingrese una opcion:\n\r");

}
