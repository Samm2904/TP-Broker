#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "empresa.h"

void menuEmpresa(){
	printf("-----MENU EMPRESA-----\n\r");
	printf("1-Ver historico de operaciones.\n\r");
	printf("2-Ver ranking de clientes.\n\r");
	printf("3-Volver al menu principal.\n\r");
	printf("Ingrese una opcion:\n\r");
}

void filtrarIDTICKER(empresa e, cliente baseClientes[], int cantidadClientes, inversion baseInversiones[], int cantidadInversiones){
  int opEncontradas=0;
  for(int i=0;i<cantidadInversiones;i++){
    if(strcmp(e.id_ticker,baseInversiones[i].id_ticker)==0){
        for(int j=0;j<cantidadClientes;j++){
                if(strcmp(baseInversiones[i].cuil,baseClientes[j].cuil)==0){
                    printf("Operacion encontrada (Cliente %s):\n\r", baseClientes[j].nombre);
                }
        }
    printf("- Tipo: %c\n\r", baseInversiones[i].operacion);
    printf("- Cantidad: %d\n\r", baseInversiones[i].cantidad_acciones);
    printf("- Precio: $%.2f\n\r", baseInversiones[i].precio_compra);
    printf("- Fecha: %s\n\r",baseInversiones[i].fecha);
    printf("\n\r\n\r");
    opEncontradas++;
    	}
	}
	if (opEncontradas == 0) {
    	printf("No se encontraron operaciones para el ticker %s.\n\r", e.id_ticker);
 	}
}

void mostrarClientes(empresa e, cliente baseClientes[], int cantidadClientes, inversion baseInversiones[], int cantidadInversiones) {
    char nombresClientes[30][50];
    int cantidadNombres = 0;

    for (int i = 0; i < cantidadInversiones; i++) {
        if (strcmp(e.id_ticker, baseInversiones[i].id_ticker) == 0) {
            for (int j = 0; j < cantidadClientes; j++) {
                if (strcmp(baseInversiones[i].cuil, baseClientes[j].cuil) == 0) {
                    bool yaExiste = false;
                    for (int k = 0; k < cantidadNombres; k++) {
                        if (strcmp(nombresClientes[k], baseClientes[j].nombre) == 0) {
                            yaExiste = true;
                            break;
                        }
                    }
                    if (!yaExiste && cantidadNombres < 30) {
                        strcpy(nombresClientes[cantidadNombres], baseClientes[j].nombre);
                        cantidadNombres++;
                    }
                }
            }
        }
    }
    if (cantidadNombres == 0) {
        printf("No se encontraron clientes con operaciones en %s\n\r", e.nombre);
    }
    printf("--- Clientes con operaciones en %s ---\n\r", e.nombre);
    for (int i = 0; i < cantidadNombres; i++) {
        printf("- %s\n\r", nombresClientes[i]);
    }
    printf("\n\r");
}

void listaEmpresas(empresa baseEmpresas[], int cantidadEmpresas){
    printf("| NOMBRE | ID_TICKER |  PRECIO\n\r");
    for(int i=0;i<cantidadEmpresas;i++){
        printf("%s: %s         $%.2f\n\r",baseEmpresas[i].nombre,baseEmpresas[i].id_ticker,baseEmpresas[i].precio_actual);
    }
}

empresa validarEmpresaNombre(empresa baseEmpresas[],char nombreEmpresaIng[], int cantidadEmpresas){
    empresa encontrado;
    strcpy(encontrado.nombre,"");

    	for(int i=0;i<cantidadEmpresas;i++){
        	if(strcmp(baseEmpresas[i].nombre,nombreEmpresaIng) == 0) {
                	encontrado=baseEmpresas[i];
                	break;
                	}
            	}

	return encontrado;
}

empresa validarEmpresaTicker(empresa baseEmpresas[],char tickerEmpresaIng[], int cantidadEmpresas){
    empresa encontrado;
    strcpy(encontrado.id_ticker,"");

    	for(int i=0;i<cantidadEmpresas;i++){
        	if(strcmp(baseEmpresas[i].id_ticker,tickerEmpresaIng) == 0) {
                	encontrado=baseEmpresas[i];
                	break;
                	}
            	}

	return encontrado;
}

void menuHistorico(){
        printf("-----MENU HISTORICO-----\n\r");
        printf("1-Filtrar por ID_TICKER.\n\r");
        printf("2-Filtrar por cliente.\n\r");
        printf("3-Volver atras.\n\r");
        printf("Ingrese una opcion:\n\r");
}

void mostrarAccionCliente(cliente baseCliente[], int cantidadClientes, empresa e,char nombreClienteVer[], inversion baseInversiones[], int cantidadInversiones){
    int k=1;
    bool esta=false;
    cliente encontrado;
    for(int i=0;i<cantidadClientes;i++){
        if(strcmp(nombreClienteVer, baseCliente[i].nombre)==0){
            strcpy(encontrado.cuil,baseCliente[i].cuil);
            esta=true;
            break;
        }
    }
    for(int i=0;i<cantidadInversiones;i++){
        if (strcmp(encontrado.cuil,baseInversiones[i].cuil)==0){
            if (strcmp(e.id_ticker, baseInversiones[i].id_ticker)==0 ){
                    printf("- Accion numero:%d\n\r",k);
                    printf("- Tipo: %c\n\r", baseInversiones[i].operacion);
                    printf("- Cantidad: %d\n\r", baseInversiones[i].cantidad_acciones);
                    printf("- Precio: $%.2f\n\r", baseInversiones[i].precio_compra);
                    printf("- Fecha: %s\n\r",baseInversiones[i].fecha);
                    printf("\n\r\n\r");
                    k++;

            }
        }
    }
    if(!esta){
        printf("Usuario no encontrado.\n\r\n\r");
    }
    }

void mostrarRanking(cliente baseClientes[], int cantidadClientes, empresa e, inversion baseInversiones[], int cantidadInversiones) {
    char nombresClientes[30][50];
    int totalesAcciones[30] = {0};
    int cantidadNombres = 0;
    char tempNombre[50];
    int tempAcciones=0;

    for (int i = 0; i < cantidadInversiones; i++) {
        if (strcmp(e.id_ticker, baseInversiones[i].id_ticker) == 0 && baseInversiones[i].condicionActivo == 'A') {
            for (int j = 0; j < cantidadClientes; j++) {
                if (strcmp(baseInversiones[i].cuil, baseClientes[j].cuil) == 0) {
                    bool yaExiste = false;
                    for (int k = 0; k < cantidadNombres; k++) {
                        if (strcmp(nombresClientes[k], baseClientes[j].nombre) == 0) {
                            yaExiste = true;
                            break;
                        }
                    }
                    if (!yaExiste && cantidadNombres < 30) {
                        strcpy(nombresClientes[cantidadNombres], baseClientes[j].nombre);
                        cantidadNombres++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < cantidadInversiones; i++) {
        if (strcmp(e.id_ticker, baseInversiones[i].id_ticker) == 0 && baseInversiones[i].condicionActivo == 'A') {
            for (int k = 0; k < cantidadNombres; k++) {
                for (int j = 0; j < cantidadClientes; j++) {
                    if (strcmp(nombresClientes[k], baseClientes[j].nombre) == 0 &&
                        strcmp(baseClientes[j].cuil, baseInversiones[i].cuil) == 0) {
                        totalesAcciones[k] += baseInversiones[i].cantidad_acciones;
                    }
                }
            }
        }
    }
    for (int i = 0; i < cantidadNombres - 1; i++) {
        for (int j = i + 1; j < cantidadNombres; j++) {
            if (totalesAcciones[i] < totalesAcciones[j]) {
                tempAcciones = totalesAcciones[i];
                totalesAcciones[i] = totalesAcciones[j];
                totalesAcciones[j] = tempAcciones;
                strcpy(tempNombre, nombresClientes[i]);
                strcpy(nombresClientes[i], nombresClientes[j]);
                strcpy(nombresClientes[j], tempNombre);
            }
        }
    }
    printf("----Ranking de clientes de %s----\n\r", e.nombre);
    for (int i = 0; i < cantidadNombres; i++) {
        printf("- %s: %d acciones.\n\r", nombresClientes[i], totalesAcciones[i]);
    }
    printf("\n\r");
}

int obtenerTickersYPrecios(cliente clienteLogueado, empresa baseEmpresas[], int cantidadEmpresas, char tickers[][10], float precios[], int cantidadTickersMax) {
    int cantidadTickers = 0;
    char tickerActual[10];

    for (int i = 0; i < clienteLogueado.num_inversiones; i++) {
        if (clienteLogueado.inversiones[i].condicionActivo == 'A') {
            strcpy(tickerActual, clienteLogueado.inversiones[i].id_ticker);
            bool yaExiste = false;
            for (int j = 0; j < cantidadTickers; j++) {
                if (strcmp(tickers[j], tickerActual) == 0) {
                    yaExiste = true;
                    break;
                }
            }
            if (!yaExiste && cantidadTickers < cantidadTickersMax) {
                strcpy(tickers[cantidadTickers], tickerActual);
                for (int k = 0; k < cantidadEmpresas; k++) {
                    if (strcmp(baseEmpresas[k].id_ticker, tickerActual) == 0) {
                        precios[cantidadTickers] = baseEmpresas[k].precio_actual;
                        break;
                    }
                }
                cantidadTickers++;
            }
        }
    }
    return cantidadTickers;
}

float obtenerPrecioEmpresa(char accionEmpresaVender[10], char tickers[][10], float precios[], int cantidadTickers) {
   int k=0;
   for (int i = 0; i < cantidadTickers; i++) {
        if (strcmp(tickers[i], accionEmpresaVender) == 0) {
            k=i;
        }
    }
    return precios[k];
}

float cambiarPrecios(empresa empresaACambiar, empresa baseEmpresas[],int cantidadEmpresas){
    float precioActualizado;

    for(int i=0;i<cantidadEmpresas;i++){
        if (strcmp(empresaACambiar.id_ticker,baseEmpresas[i].id_ticker)==0){
            do{
                printf("Ingrese el precio actualizado:\n\r");
                scanf("%f",&precioActualizado);
            }while(precioActualizado<=0);
            baseEmpresas[i].precio_actual=precioActualizado;
        }
    }
    return precioActualizado;
}

empresa crearEmpresa() {
	empresa empresaNueva;

	printf("Ingrese nombre:\n\r");
	scanf(" %30[^\n]", empresaNueva.nombre);
	printf("Ingrese ID_TICKER:\n\r");
	scanf(" %30[^\n]", empresaNueva.id_ticker);
	printf("Ingrese precio:\n\r");
	scanf(" %f", &empresaNueva.precio_actual);
	return empresaNueva;
}

void cargarTickers(char tickers[][10], empresa baseEmpresas[], int cantidadEmpresas){
 int cont=0;
    for(int i=0;i<cantidadEmpresas;i++){
        strcpy(tickers[i],baseEmpresas[i].id_ticker);
        cont++;
    }
    /*
     printf("=== Tickers ===\n\r");
    for (int i = 0; i < cont ; i++) {
        printf("Ticker %d: %s \n\r", i+1, tickers[i]);
    }
    */
}

void cargarPrecios(float precios[],empresa baseEmpresas[], int cantidadEmpresas){
int cont=0;
        for(int i=0;i<cantidadEmpresas;i++){
        precios[i]=baseEmpresas[i].precio_actual;
        cont++;
    }

    /*
     printf("=== Precios ===\n\r");
    for (int i = 0; i < cont ; i++) {
        printf("Precios %d: %.2f \n\r", i+1, precios[i]);
    }
    */
}
