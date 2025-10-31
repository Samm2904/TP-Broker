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



int main()
{
   /// cliente listaClientes[50]; ///Preguntar????
    int cantidadClientes = 0;
	int cantidadEmpresas = 0;
    int cantidadInversiones = 0;
	int opcionMenuPrincipal, opcionMBroker, opcionOperarCliente, opcionMenuEmpresa, opcionPerfilCliente;
	int opcionPerfilClienteCopia, opcionClienteLogueado, opcionMenuSaldo, opcionMenuInversion,opcionSaldoInsuficiente;
	int confirmarCompra;
	cliente nuevo, clienteLogueado;
	float copiaSaldoCliente, cantAccionesComprar, precioCompra;
	char nombreIng[30], passIng[30], empresaCompraInversion[30], nombreEmpresaIng[30];
	bool noLogueado = true;
	bool empresaMalIngresada=true;
	bool comprar=true;
	bool nombreEmpresa=true;
	cliente baseClientes[50]; //en cada BD 20
	empresa baseEmpresas[50], accionEmpresaComprar, empresaLogueada;
	inversion baseInversiones[500];

	FILE *archivoClientes; // Cambiamos el nombre para mayor claridad
    archivoClientes=fopen("baseClientes.txt","r"); // Abrimos el archivo TXT
    if(archivoClientes!=NULL){
        printf("Cargando base de datos de clientes...\n\r");
        // Usamos fscanf para leer los 6 campos de la estructura cliente [3]
        // El formato: Nombre;Email;Cuil;Password;Saldo;Num_Inversiones

        // Mientras fscanf pueda leer 6 elementos (strings separados por ';', un float y un int)
        while(fscanf(archivoClientes, "%[^;];%[^;];%[^;];%[^;];%f;%d\n",
               baseClientes[cantidadClientes].nombre,       // char
               baseClientes[cantidadClientes].email,        // char
               baseClientes[cantidadClientes].cuil,         // char[4]
               baseClientes[cantidadClientes].password,     // char
               &baseClientes[cantidadClientes].saldo_cuenta, // float
               &baseClientes[cantidadClientes].num_inversiones // int
               ) == 6 && cantidadClientes < 50)
        {
            // Si la lectura es exitosa y no excedemos el límite de 50 clientes [1]
            cantidadClientes++;
        }
        printf("%d clientes cargados exitosamente.\n\r", cantidadClientes);
        fclose(archivoClientes);
    } else {
        printf("No pudo abrirse el archivo base clientes para lectura.\n\r");
        // Nota: Aunque el puntero sea NULL, la llamada a fclose(NULL) es inofensiva,
        // pero si usamos un puntero local declarado FILE *archivo, no hace falta cerrarlo
        // si nunca se abrió, por eso eliminamos el fclose(archivo) de aquí.
    }

// -------------------------------------------------------------------------
// 2. CARGA DE EMPRESAS DESDE ARCHIVO DE TEXTO DELIMITADO
// -------------------------------------------------------------------------
    FILE *archivoempresa;
    archivoempresa=fopen("baseEmpresas.txt","r"); // Abrimos el archivo TXT
    if(archivoempresa!=NULL){
        printf("Cargando base de datos de empresas...\n\r");
        // Usamos fscanf para leer los 4 campos de la estructura empresa [5]
        // El formato: id_ticker;nombre;password;precio_actual

        // Mientras fscanf pueda leer 4 elementos (3 strings separados por ';', y un float)
        while(fscanf(archivoempresa, "%[^;];%[^;];%f\n",
               baseEmpresas[cantidadEmpresas].id_ticker,    // char[1]
               baseEmpresas[cantidadEmpresas].nombre,       // char
               &baseEmpresas[cantidadEmpresas].precio_actual // float
               ) == 3 && cantidadEmpresas < 50)
        {
            // Si la lectura es exitosa y no excedemos el límite de 50 empresas [1]
            cantidadEmpresas++;
        }
        printf("%d empresas cargadas exitosamente.\n\r", cantidadEmpresas);
        fclose(archivoempresa);
    } else {
        printf("No pudo abrirse el archivo base empresas para lectura.\n\r");
    }

// -------------------------------------------------------------------------
// 3. CARGA DE INVERSIONES DESDE ARCHIVO DE TEXTO DELIMITADO
// -------------------------------------------------------------------------
    FILE *archivoInv;
    archivoInv=fopen("baseInversiones.txt","r"); // Abrimos el archivo TXT
    if(archivoInv!=NULL){
        printf("Cargando base de datos de inversiones...\n\r");
        // Usamos fscanf para leer los 5 campos de la estructura inversion [6]
        // El formato: id_ticker;cantidad_acciones;precio_compra;fecha;operacion

        // Mientras fscanf pueda leer 5 elementos (string, int, float, string, char)
        while(fscanf(archivoInv, " %[^;];%[^;];%d;%f;%[^;]; %c; %c\n",
                baseInversiones[cantidadInversiones].cuil,
               baseInversiones[cantidadInversiones].id_ticker,        // char[1]
               &baseInversiones[cantidadInversiones].cantidad_acciones, // int
               &baseInversiones[cantidadInversiones].precio_compra,    // float
               baseInversiones[cantidadInversiones].fecha,             // char[2]
               &baseInversiones[cantidadInversiones].operacion,         // char
               &baseInversiones[cantidadInversiones].condicionActivo
               ) == 7 && cantidadInversiones < 500)
        {
            // Si la lectura es exitosa y no excedemos el límite de 500 inversiones [1]
            cantidadInversiones++;
        }
        printf("%d inversiones cargadas exitosamente.\n\r", cantidadInversiones);
        fclose(archivoInv);
    } else {
        printf("No pudo abrirse el archivo base inversiones para lectura.\n\r");
    }

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
                            printf("Ingrese su nombre identificatorio\n\r");
                            scanf("%s",nombreEmpresaIng);
                            empresaLogueada=validarEmpresaNombre(baseEmpresas,nombreEmpresaIng,cantidadEmpresas);
                            if (strcmp(empresaLogueada.nombre,"")==0){
                                printf("Nombre invalido, intente nuevamente\n\r");
                            }
                            else{
                                printf("Acceso exitoso bienvenid@ %s\n\r",empresaLogueada.nombre);
                                nombreEmpresa=false;
                            }
                        }while(nombreEmpresa);

                    do{
                    	menuEmpresa();              	///MENU DE EMPRESA ---------------------------------------------
                    	scanf("%d",&opcionMenuEmpresa);
                    	switch (opcionMenuEmpresa){
                        	case 1:
                            	verHistoricoOperaciones(empresaLogueada,baseClientes,cantidadClientes);
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
                            	baseClientes[cantidadClientes+1] = nuevo; ///TOQUE ACA ANTES ERA LISTACLIENTES[cantclient]
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
                                	clienteLogueado = iniciarSesion(baseClientes, nombreIng, passIng,cantidadClientes);
                                	if (strcmp(clienteLogueado.nombre, "") == 0) {
                                    	printf("Usuario o contraseña incorrectos. Intente nuevamente.\n");
                                	} else {
                                    	printf("Bienvenida %s!\n", clienteLogueado.nombre);
                                        	clienteLogueado=copiarInversiones(clienteLogueado,baseInversiones,cantidadInversiones); ///Pasamos las inversiones a la estructura de los clientes
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

                                            printf("Su dinero actual es:$%.2f\n\r",clienteLogueado.saldo_cuenta);
                                            listaEmpresas(baseEmpresas,cantidadEmpresas);
                                        	do{
                                                printf("Ingrese el ID_TICKER de la empresa a la que le va a comprar\n\r");
                                                scanf("%s",empresaCompraInversion);
                                                accionEmpresaComprar=validarEmpresaTicker(baseEmpresas,empresaCompraInversion,cantidadEmpresas);
                                                if (strcmp(accionEmpresaComprar.id_ticker, "") == 0) {
                                                    printf("ID_TICKER incorrecto. Intente nuevamente.\n");
                                                }
                                                else {
                                                    empresaMalIngresada=false;
                                                }
                                        	}while(empresaMalIngresada);


                                        	do{
                                                printf("Ingrese cuantas acciones desea comprar:\n\r");
                                                scanf("%f",&cantAccionesComprar);
                                                if((cantAccionesComprar*accionEmpresaComprar.precio_actual)>(clienteLogueado.saldo_cuenta)){
                                                   menuSaldoInsuficiente();
                                                   scanf("%d",&opcionSaldoInsuficiente);
                                                   switch (opcionSaldoInsuficiente){
                                                    case 1:
                                                        break;
                                                    case 2:
                                                        comprar = false;
                                                        break;
                                                    default:
                                                        printf("Ingrese una opcion valida.\n\r");
                                                   }
                                                }
                                                else{
                                                    menuConfirmarCompra();
                                                    scanf("%d",&confirmarCompra);
                                                    switch (confirmarCompra){
                                                    case 1:
                                                        precioCompra=accionEmpresaComprar.precio_actual;
                                                        clienteLogueado=comprarInversion(clienteLogueado,empresaCompraInversion,precioCompra,cantAccionesComprar);
                                                        printf("Compra exitosa!\n\r");
                                                        comprar=false;
                                                        break;
                                                    case 2:
                                                        comprar=false;
                                                        break;
                                                    default:
                                                        printf("Ingrese una opcion valida.\n\r");
                                                    }
                                                }

                                        	}while(comprar);
                                            	break;
                                        	case 2:
                                        	     printf("Su dinero actual es:$%.2f\n\r",clienteLogueado.saldo_cuenta);


                                            	break;
                                        	case 3:
                                            	break;
                                        	default:
                                            	printf("Ingrese una opcion valida\n\r");
                                    	}

                                	}while(opcionMenuInversion!=3);
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


}

