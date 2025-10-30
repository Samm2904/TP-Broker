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

void verHistoricoOperaciones(empresa e, cliente listaClientes[], int cantidadClientes){
  int opEncontradas=0;

  for(int i=0;i<cantidadClientes;i++){
	for(int j=0;j<listaClientes[i].num_inversiones;j++){
    	if(strcmp(e.id_ticker, listaClientes[i].inversiones[j].id_ticker)==0){
      	printf("\nOperación encontrada (Cliente %s):\n\r", listaClientes[i].nombre);
      	printf("- Tipo: %s\n\r", listaClientes[i].inversiones[j].operacion);
      	printf("- Cantidad: %d\n\r", listaClientes[i].inversiones[j].cantidad_acciones);
      	printf("- Precio: $%.2f\n\r", listaClientes[i].inversiones[j].precio_compra);

    	opEncontradas++;
    	}
	}
  }
	if (operacionesEncontradas == 0) {
    	printf("No se encontraron operaciones para el ticker %s.\n\r", e.id_ticker);
 	}
	}

empresa validarEmpresa(empresa e,char nombreEmpresa[]){	///MODIFICAR CON LA BD DE EMPRESAAS PRESENTEEEEEEEEEEEEEEEEEEEEEE
empresa encontrado;
	strcpy(encontrado.nombre,"");

    	for(int i=0;i<"cantidadEmpresas";i++){
        	if(strcmp(listaEmpresas[i].nombre,nombreEmpresaIngresado) == 0) {
                	encontrado=listaEmpresa[i];
                	break;
                	}
            	}

	return encontrado;
}
