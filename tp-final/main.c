#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "empresa.h"
#include "inversion.h"
#include "cliente.h"

void menuPrincipal();
void menuBroker();
void menuOperarCliente();
void limpiar_pantalla();

int main(){
    int cantidadClientes = 0;
	int cantidadEmpresas = 0;
    int cantidadInversiones = 0;
	int opcionMenuPrincipal, opcionMBroker, opcionOperarCliente, opcionMenuEmpresa, opcionPerfilCliente;
	int opcionPerfilClienteCopia, opcionClienteLogueado, opcionMenuSaldo, opcionMenuInversion,opcionSaldoInsuficiente;
	int confirmarCompra,opcionMenuHistorico, cantidadAccionesVender,cantidadTotalAccionesVender,confirmarBaja;
	int opcionModificarCliente,contClientesInactivos,opcionMenuRendimientos,cantidadTickers;
	cliente nuevo, clienteLogueado, clienteAlta,baseClientes[50];
	float copiaSaldoCliente, cantAccionesComprar, precioCompra, precioEmpresaVenta,precios[30];
	char nombreIng[30], passIng[30], empresaCompraInversion[30], nombreEmpresaIng[30], nombreClienteVer[10], accionEmpresaVender[20], cuilInactivos[20],tickers[30][10];
	bool noLogueado = true;
	bool empresaMalIngresada=true;
	bool comprar=true;
	bool nombreEmpresa=true;
    char fechaActual[]="08/10/2026";
	empresa baseEmpresas[50], accionEmpresaComprar, empresaLogueada;
	inversion baseInversiones[500];

	FILE *archivoClientes;
    archivoClientes=fopen("baseClientes.txt","r");
    if(archivoClientes!=NULL){
        printf("Cargando base de datos de clientes...\n\r");
        // Usamos fscanf para leer los 6 campos de la estructura cliente [3]
        // El formato: Nombre;Email;Cuil;Password;Saldo;Num_Inversiones

        // Mientras fscanf pueda leer 6 elementos (strings separados por ';', un float y un int)
        while(fscanf(archivoClientes, "%[^;];%[^;];%[^;];%[^;];%f;%d; %c\n",
               baseClientes[cantidadClientes].nombre,
               baseClientes[cantidadClientes].email,
               baseClientes[cantidadClientes].cuil,
               baseClientes[cantidadClientes].password,
               &baseClientes[cantidadClientes].saldo_cuenta,
               &baseClientes[cantidadClientes].num_inversiones,
               &baseClientes[cantidadClientes].condicionUser
               ) == 7 && cantidadClientes < 50)
        {
            // Si la lectura es exitosa y no excedemos el límite de 50 clientes
            cantidadClientes++;
        }
        printf("%d clientes cargados exitosamente.\n\r", cantidadClientes);
        fclose(archivoClientes);
    } else {
        printf("No pudo abrirse el archivo base clientes para lectura.\n\r");
    }

// ----------------------
// 2. CARGA DE EMPRESAS
// ----------------------
    FILE *archivoempresa;
    archivoempresa=fopen("baseEmpresas.txt","r");
    if(archivoempresa!=NULL){
        printf("Cargando base de datos de empresas...\n\r");
        // Usamos fscanf para leer los 4 campos de la estructura empresa
        // El formato: id_ticker;nombre;password;precio_actual

        // Mientras fscanf pueda leer 4 elementos (3 strings separados por ';', y un float)
        while(fscanf(archivoempresa, "%[^;];%[^;];%f\n",
               baseEmpresas[cantidadEmpresas].id_ticker,
               baseEmpresas[cantidadEmpresas].nombre,
               &baseEmpresas[cantidadEmpresas].precio_actual
               ) == 3 && cantidadEmpresas < 50)
        {
            // Si la lectura es exitosa y no excedemos el límite de 50 empresas
            cantidadEmpresas++;
        }
        printf("%d empresas cargadas exitosamente.\n\r", cantidadEmpresas);
        fclose(archivoempresa);
    } else {
        printf("No pudo abrirse el archivo base empresas para lectura.\n\r");
    }

// ------------------------
// 3. CARGA DE INVERSIONES
// ------------------------
    FILE *archivoInv;
    archivoInv=fopen("baseInversiones.txt","r");
    if(archivoInv!=NULL){
        printf("Cargando base de datos de inversiones...\n\r");
        // Usamos fscanf para leer los 5 campos de la estructura inversion
        // El formato: id_ticker;cantidad_acciones;precio_compra;fecha;operacion

        // Mientras fscanf pueda leer 5 elementos (string, int, float, string, char)
        while(fscanf(archivoInv, " %[^;];%[^;];%d;%f;%[^;]; %c; %c\n",
                baseInversiones[cantidadInversiones].cuil,
               baseInversiones[cantidadInversiones].id_ticker,
               &baseInversiones[cantidadInversiones].cantidad_acciones,
               &baseInversiones[cantidadInversiones].precio_compra,
               baseInversiones[cantidadInversiones].fecha,
               &baseInversiones[cantidadInversiones].operacion,
               &baseInversiones[cantidadInversiones].condicionActivo
               ) == 7 && cantidadInversiones < 500)
        {
            cantidadInversiones++;
        }
        printf("%d inversiones cargadas exitosamente.\n\r", cantidadInversiones);
        fclose(archivoInv);
    } else {
        printf("No pudo abrirse el archivo base inversiones para lectura.\n\r");
    }
    printf("\n\r\n\r");
	do {
    	menuPrincipal();
    	scanf("%d",&opcionMenuPrincipal);
    	limpiar_pantalla(); ///1
    	switch(opcionMenuPrincipal){
        	case 1:
            	do {
                    menuBroker();                      	///MENU DE BROKER -----------------------------------------------------------
                    scanf("%d",&opcionMBroker);
                    switch (opcionMBroker){
                        case 1:
                            limpiar_pantalla();
                            printf("-----CARGAR EMPRESA NUEVA-----\n\r");
                            baseEmpresas[cantidadEmpresas]=crearEmpresa();
                            cantidadEmpresas++;
                            printf("Empresa creada exitosamente.\n\r\n\r");
                        break;
                        case 2:
                            limpiar_pantalla(); ///1
                            empresaMalIngresada=true;
                            do{
                                printf("-----CAMBIAR EL PRECIO-----\n\r");
                                listaEmpresas(baseEmpresas,cantidadEmpresas);
                                printf("\nIngrese el ID_TICKER de la empresa a la que le va a cambiar el precio:\n\r");
                                scanf("%s",empresaCompraInversion); //se lee compra xq la reutilizamos
                                accionEmpresaComprar=validarEmpresaTicker(baseEmpresas,empresaCompraInversion,cantidadEmpresas);
                                if (strcmp(accionEmpresaComprar.id_ticker, "") == 0) {
                                    printf("\nID_TICKER incorrecto. Intente nuevamente.\n\r\n\r");
                                }
                                else {
                                    empresaMalIngresada=false;
                                }
                                }while(empresaMalIngresada);
                            printf("El nuevo precio es: %.2f\n\r\n\r",cambiarPrecios(accionEmpresaComprar,baseEmpresas,cantidadEmpresas));

                        break;
                        case 3:
                            limpiar_pantalla(); ///1
                            contClientesInactivos=clientesInactivos(baseClientes,cantidadClientes);
                            if(contClientesInactivos>0){
                                do {
                                    printf("Ingrese el CUIL del usuario a dar de alta:\n\r");
                                    scanf("%s",cuilInactivos);
                                    if(validarCuil(cuilInactivos,baseClientes,cantidadClientes)==1){
                                        clienteAlta=darDeAlta(cuilInactivos,baseClientes,cantidadClientes);
                                        printf("%s dado de alta exitosamente.\n\r\n\r",clienteAlta.nombre);
                                        contClientesInactivos=0;
                                    }
                                    else {
                                        printf("Cuil invalido, intentelo nuevamente.\n\r");
                                    }
                                }while(validarCuil(cuilInactivos,baseClientes,cantidadClientes)==0);
                            }
                            else{
                                printf("No hay clientes inactivos.\n\r\n\r");
                            }

                            break;
                        case 4:
                            limpiar_pantalla();//1
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
            	limpiar_pantalla(); ///1
            	switch (opcionOperarCliente){
                	case 1:
                        do {
                            printf("-----OPERAR COMO EMPRESA-----\n\rIngrese el nombre de la empresa:\n\r");
                            scanf("%s",nombreEmpresaIng);
                            empresaLogueada=validarEmpresaNombre(baseEmpresas,nombreEmpresaIng,cantidadEmpresas);
                            if (strcmp(empresaLogueada.nombre,"")==0){
                                printf("\n\rNombre invalido, intente nuevamente.\n\r\n\r");
                            }
                            else{
                                printf("\n\rAcceso exitoso bienvenid@ %s.\n\r\n\r",empresaLogueada.nombre);
                                nombreEmpresa=false;
                            }
                        }while(nombreEmpresa);
                    do{
                    	menuEmpresa();              	///MENU DE EMPRESA ---------------------------------------------
                    	scanf("%d",&opcionMenuEmpresa);
                        limpiar_pantalla(); ///1
                    	switch (opcionMenuEmpresa){
                        	case 1:
                                do{
                                    menuHistorico();
                                    scanf("%d",&opcionMenuHistorico);
                                    switch (opcionMenuHistorico){
                                        case 1:
                                            filtrarIDTICKER(empresaLogueada,baseClientes,cantidadClientes,baseInversiones,cantidadInversiones);
                                            break;
                                        case 2:
                                            limpiar_pantalla(); ///1
                                            mostrarClientes(empresaLogueada,baseClientes,cantidadClientes,baseInversiones,cantidadInversiones);
                                            printf("\n\rIngrese el nombre del cliente para ver sus inversiones\n\r");
                                            scanf("%s",nombreClienteVer);
                                            printf("\n\r");
                                            mostrarAccionCliente(baseClientes,cantidadClientes,empresaLogueada,nombreClienteVer,baseInversiones,cantidadInversiones);
                                            break;
                                        case 3:
                                            limpiar_pantalla(); ///1
                                            break;
                                        default:
                                            printf("Opcion invalida, intente nuevamente.\n\r");
                                    }
                                }while(opcionMenuHistorico!=3);
                            	break;

                        	case 2:
                                mostrarRanking(baseClientes,cantidadClientes,empresaLogueada,baseInversiones,cantidadInversiones);
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
                    	limpiar_pantalla();//1
                    	opcionPerfilClienteCopia = opcionPerfilCliente;
                    	switch (opcionPerfilClienteCopia){
                        	case 1:
                            	printf("-----CREAR USUARIO-----\n\r");
                            	nuevo = crearCliente();
                            	baseClientes[cantidadClientes] = nuevo;
                            	cantidadClientes++;
                            	clienteLogueado = nuevo;
                            	opcionPerfilClienteCopia = 3;
                            	printf("\n\rUsuario creado con exito.\n\r\n\r");
                                	break;
                        	case 2:
                            	do {
                                    printf("-----INICIAR SESION-----\n\r");
                                	printf("Ingrese su usuario:\n\r");
                                	scanf(" %30[^\n]",nombreIng);
                                	printf("Ingrese su password:\n\r");
                                	scanf(" %30[^\n]",passIng);
                                	clienteLogueado = iniciarSesion(baseClientes, nombreIng, passIng,cantidadClientes);
                                    if (strcmp(clienteLogueado.nombre, "") == 0) {
                                        printf("\n\rUsuario o password incorrectos. Intente nuevamente.\n\r\n\r");
                                        }
                                    else {
                                            if (clienteLogueado.condicionUser=='A'){
                                                printf("\n\rBienvenida %s!\n\r\n\r", clienteLogueado.nombre);
                                                clienteLogueado=copiarInversiones(clienteLogueado,baseInversiones,cantidadInversiones); ///Pasamos las inversiones a la estructura de los clientes
                                                noLogueado = false;
                                                opcionPerfilClienteCopia = 3;
                                            }
                                            else {
                                                printf("\n\rEl usuario no existe.\n\r\n\r");
                                                opcionPerfilClienteCopia = 3;
                                                opcionPerfilCliente = 3;
                                            }
                                        }
                            	}while(noLogueado);
                            	break;
                        	case 3:
                        	    limpiar_pantalla();//1
                            	break;
                        	default:
                            	printf("Ingrese una opcion valida\n\r\n\r");
                    	}
                	} while (opcionPerfilClienteCopia!=3);
                	if (opcionPerfilCliente != 3)
                	{
                    	do {
                        	menuClienteLogueado();          	///MENU CLIENTE LOGUEADO ---------------------------------------------
                        	scanf("%d",&opcionClienteLogueado);
                            limpiar_pantalla();//1
                        	switch(opcionClienteLogueado){
                            	case 1:
                                	do {
                                    	menuInversiones ();
                                    	scanf("%d",&opcionMenuInversion);
                                    	switch (opcionMenuInversion){
                                        	case 1:
                                        	    limpiar_pantalla();//1
                                        	    empresaMalIngresada=true;
                                        	    printf("-----COMPRAR ACCION-----\n\r");
                                                printf("Su dinero actual es:$%.2f\n\r\n\r",clienteLogueado.saldo_cuenta);
                                                if(clienteLogueado.saldo_cuenta>0){
                                                    do{
                                                        listaEmpresas(baseEmpresas,cantidadEmpresas);
                                                        printf("\n\rIngrese el ID_TICKER de la empresa a la que le va a comprar\n\r");
                                                        scanf("%s",empresaCompraInversion);
                                                        accionEmpresaComprar=validarEmpresaTicker(baseEmpresas,empresaCompraInversion,cantidadEmpresas);
                                                        if (strcmp(accionEmpresaComprar.id_ticker, "") == 0) {
                                                            printf("\n\rID_TICKER incorrecto. Intente nuevamente.\n\r\n\r");
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
                                                                printf("Compra exitosa! Saldo actual:$%.2f\n\r\n\r",clienteLogueado.saldo_cuenta);
                                                                comprar=false;
                                                                break;
                                                            case 2:
                                                                printf("Operacion cancelada.\n\r\n\r");
                                                                comprar=false;
                                                                break;
                                                            default:
                                                                printf("Ingrese una opcion valida.\n\r\n\r");
                                                            }
                                                        }
                                                    }while(comprar);
                                                }
                                                else{
                                                    printf("Primero debes cargar saldo para realizar una compra.\n\r\n\r");
                                                }
                                                break;
                                        	case 2:
                                        	     limpiar_pantalla();//1
                                        	     empresaMalIngresada=true;
                                        	     printf("-----VENDER ACCION-----\n\r");
                                        	     printf("Su dinero actual es:$%.2f\n\r\n\r",clienteLogueado.saldo_cuenta);
                                                 if (clienteLogueado.num_inversiones>0){
                                                     cantidadTickers = obtenerTickersYPrecios(clienteLogueado, baseEmpresas, cantidadEmpresas, tickers, precios, 30);
                                                     mostrarAccionesCliente(clienteLogueado, tickers, precios, cantidadTickers);
                                                   do{
                                                        printf("\n\rIngrese el ID_TICKER de la inversion que quiere vender:\n\r");
                                                        scanf("%s",empresaCompraInversion);
                                                        accionEmpresaComprar=validarEmpresaTicker(baseEmpresas,empresaCompraInversion,cantidadEmpresas);
                                                        if (strcmp(accionEmpresaComprar.id_ticker, "") == 0) {
                                                            printf("ID_TICKER incorrecto. Intente nuevamente.\n\r");
                                                        }
                                                        else {
                                                            empresaMalIngresada=false;
                                                        }
                                                    }while(empresaMalIngresada);
                                                    strcpy(accionEmpresaVender,accionEmpresaComprar.id_ticker);
                                                    precioEmpresaVenta=obtenerPrecioEmpresa(accionEmpresaVender,tickers,precios,cantidadTickers);
                                                    do{
                                                        printf("Cuantas acciones quiere vender?:\n\r");
                                                        scanf("%d",&cantidadAccionesVender);
                                                        cantidadTotalAccionesVender=validarAcciones(clienteLogueado,accionEmpresaVender);
                                                        if (cantidadAccionesVender>cantidadTotalAccionesVender || cantidadAccionesVender==0){
                                                            printf("Numero invalido, intente nuevamente.\n\r\n\r");
                                                        }
                                                        else{
                                                            clienteLogueado=venderAcciones(clienteLogueado,accionEmpresaVender,cantidadAccionesVender,precioEmpresaVenta,fechaActual);
                                                            printf("Venta Realizada Exitosamente. Saldo en cuenta: $%.2f\n\r\n\r",clienteLogueado.saldo_cuenta);
                                                        }

                                                    }while(cantidadAccionesVender>cantidadTotalAccionesVender || cantidadAccionesVender==0);
                                                 }
                                                 else{
                                                    printf("Primero necesitas realizar una compra de acciones.\n\r\n\r");
                                                 }
                                            	break;
                                        	case 3:
                                        	    limpiar_pantalla();
                                            	break;
                                        	default:
                                            	printf("Ingrese una opcion valida\n\r\n\r");
                                    	}

                                	}while(opcionMenuInversion!=3);
                                	break;
                            	case 2:
                            	    do{
                                        menuRendimientos();
                                        scanf("%d",&opcionMenuRendimientos);
                                        limpiar_pantalla();
                                        switch(opcionMenuRendimientos){
                                            case 1:
                                                printf("-----Rendimientos Diarios-----\n\r\n\r");
                                                cargarTickers(tickers,baseEmpresas,cantidadEmpresas);
                                                cargarPrecios(precios,baseEmpresas,cantidadEmpresas);
                                                valorDiario(precios,tickers,clienteLogueado,cantidadEmpresas,fechaActual);
                                                printf("\n\r");
                                                break;
                                            case 2:
                                                printf("-----Rendimientos Historicos-----\n\r\n\r");
                                                cargarTickers(tickers,baseEmpresas,cantidadEmpresas);
                                                cargarPrecios(precios,baseEmpresas,cantidadEmpresas);
                                                valorHistorico(precios,tickers,clienteLogueado,cantidadEmpresas);
                                                printf("\n\r");
                                                break;
                                            case 3:
                                                limpiar_pantalla();
                                                break;
                                            default:
                                                printf("Ingrese una opcion valida.\n\r\n\r");
                                        }
                            	    }while(opcionMenuRendimientos!=3);
                                	break;
                            	case 3:
                                	do {
                                    	menuGestionSaldo(clienteLogueado);
                                    	scanf("%d",&opcionMenuSaldo);
                                    	limpiar_pantalla();
                                    	switch(opcionMenuSaldo){
                                        	case 1:
                                        	    printf("-----CARGAR SALDO-----\n\r\n\r");
                                             	clienteLogueado=cargarSaldo(clienteLogueado);
                                             	printf("Transaccion exitosa, su saldo nuevo es: $%.2f\n\r\n\r",clienteLogueado.saldo_cuenta);
                                            	break;
                                        	case 2:
                                        	    printf("-----EXTRAER DINERO-----\n\r\n\r");
                                            	if (clienteLogueado.saldo_cuenta<=0){
                                                	printf("Fondos insuficientes, cargue saldo primero.\n\r\n\r");
                                            	}
                                            	else {
                                                	copiaSaldoCliente=clienteLogueado.saldo_cuenta;
                                                	clienteLogueado=extraerSaldo(clienteLogueado);
                                                	if (copiaSaldoCliente!=clienteLogueado.saldo_cuenta){
                                                    	printf("Transaccion exitosa, su saldo nuevo es: $%.2f\n\r\n\r",clienteLogueado.saldo_cuenta);
                                                	}
                                            	}
                                            	break;
                                        	case 3:
                                        	    limpiar_pantalla();
                                            	break;
                                        	default:
                                            	printf("Opcion invalida, intente nuevamente.\n\r\n\r");
                                    	}
                                	} while(opcionMenuSaldo!=3);
                                	break;
                            	case 4:
                                	verPortfolio(clienteLogueado);
                                	break;
                            	case 5:
                            	    do{
                                        menuModificarCliente();
                                        scanf("%d",&opcionModificarCliente);
                                        limpiar_pantalla();//1
                                        switch(opcionModificarCliente){
                                            case 1:
                                                clienteLogueado=cambiarNombre(clienteLogueado,baseClientes,cantidadClientes);
                                                printf("Nombre modificado exitosamente, %s.\n\r\n\r",clienteLogueado.nombre);
                                                break;
                                            case 2:
                                                clienteLogueado=cambiarPassword(clienteLogueado,baseClientes,cantidadClientes);
                                                printf("Password modificada exitosamente, ahora es: %s.\n\r\n\r",clienteLogueado.password);
                                                break;
                                            case 3:
                                                limpiar_pantalla();//1
                                                break;
                                            default:
                                                printf("Opcion invalida, intente nuevamente.\n\r\n\r");
                                        }
                                    }while(opcionModificarCliente!=3);
                                	break;
                            	case 6:
                                	menuConfirmarBaja();
                                	scanf("%d",&confirmarBaja);
                                	if (confirmarBaja == 1 ){
                                        clienteLogueado=darDeBaja(clienteLogueado,baseClientes,cantidadClientes);
                                        printf("Usuario dado de baja con exito.\n\r\n\r");
                                        opcionClienteLogueado=7;
                                	}
                                	else{
                                        printf("Operacion de dar de baja cancelada.\n\r\n\r");
                                	}
                                	break;
                            	case 7:
                                	limpiar_pantalla();//1
                                	break;
                            	default:
                            	printf("Ingrese una opcion valida.\n\r\n\r");
                            	}
                        	} while(opcionClienteLogueado!=7);
                	}
                    	break;
                	case 3:
                    	break;
                	default:
                    	printf("Ingrese una opcion valida\n\r\n\r");
                	}
            	} while(opcionOperarCliente!=3);
            	break;
        	case 3:
            	printf("Cerrando programa ...\n\r");
            	break;
        	default:
            	printf("Ingrese una opcion valida\n\r\n\r");
        	}
	} while(opcionMenuPrincipal!=3);

	return 0;
}

void menuPrincipal(){
    	printf("-----BIENVENIDO AL MENU PRINCIPAL-----\n\r");
    	printf("1-Operar como Broker.\n\r");
    	printf("2-Operar como Cliente.\n\r");
    	printf("3-Salir.\n\r");
        printf("Ingrese una opcion:\n\r");
	}

void menuBroker(){
        printf("------MENU BROKER------\n\r");
    	printf("1-Cargar empresa nueva.\n\r"); //hacer
    	printf("2-Cambiar precios actuales.\n\r");
    	printf("3-Dar de alta (cliente).\n\r");
    	printf("4-Volver al menu principal.\n\r");
    	printf("Ingrese una opcion:\n\r");

}

void menuOperarCliente(){
    printf("------MENU CLIENTE------\n\r");
	printf("1-Operar como empresa.\n\r");
	printf("2-Operar como cliente.\n\r");
	printf("3-Volver al menu principal.\n\r");
	printf("Ingrese una opcion:\n\r");

}

void limpiar_pantalla() { ///preguntar a facu
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
