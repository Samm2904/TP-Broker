#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "empresa.h"


void menuEmpresa(){
	printf("Bienvenido al menu empresa.\n\r");
	printf("1- Ver historico de operaciones.\n\r");
	printf("2-Ver ranking de clientes.\n\r");
	printf("3-Volver al menu principal.\n\r");
	printf("Ingrese una opcion:\n\r");
}

void verHistoricoOperaciones(empresa e, cliente baseClientes[], int cantidadClientes){
  int opEncontradas=0;
  for(int i=0;i<cantidadClientes;i++){
	for(int j=0;j<baseClientes[i].num_inversiones;j++){
    	if(strcmp(e.id_ticker,baseClientes[i].inversiones[j].id_ticker)==0){
      	printf("Operación encontrada (Cliente %s):\n\r", baseClientes[i].nombre);
      	printf("- Tipo: %c\n\r", baseClientes[i].inversiones[j].operacion);
      	printf("- Cantidad: %d\n\r", baseClientes[i].inversiones[j].cantidad_acciones);
      	printf("- Precio: $%.2f\n\r", baseClientes[i].inversiones[j].precio_compra);
      	printf("- Fecha: %s\n\r",baseClientes[i].inversiones[j].fecha);
    	opEncontradas++;
    	}
	}
  }
	if (opEncontradas == 0) {
    	printf("No se encontraron operaciones para el ticker %s.\n\r", e.id_ticker);
 	}

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


