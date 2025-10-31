#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inversion.h"
#include "cliente.h"
#include "empresa.h"

void menuClienteLogueado (){
	printf("Ingreso exitoso.\n\r");
	printf("1-Realizar inversion.\n\r");
	printf("2-Ver rendimientos.\n\r");
	printf("3-Gestion de saldo.\n\r");
	printf("4-Ver portafolio.\n\r");
	printf("5-Moficar perfil.\n\r");
	printf("6-Darse de baja\n\r");
	printf("7-Volver atras\n\r");
	printf("Ingrese su opcion\n\r");

}

void menuClienteInversion (){
	printf("--- Gestor de Inversiones ---\n\r");
	printf("1-Comprar acciones.\n\r");
	printf("2-Vender acciones.\n\r");
	printf("3-Volver atras.\n\r");
	printf("Ingrese su opcion\n\r");
}

void menuRendimientos (){
	printf("--- Rendimientos ---\n\r");
	printf("1-Rendimientos diarios(valor neto).\n\r");
	printf("2-Rendimientos diarios porcentuales.\n\r");
	printf("3-Rendimientos historicos(valor neto).\n\r");
	printf("4-Rendimientos historicos porcentuales.\n\r");
	printf("5-Volver atras.\n\r");
	printf("Ingrese su opcion\n\r");
}

void menuGestionSaldo (cliente c){
	printf("--- Gestion de Saldo ---\n\r");
	printf("Saldo actual: $%.2f \n\r",c.saldo_cuenta);
	printf("1-Cargar saldo.\n\r");
	printf("2-Extraer saldo.\n\r");
	printf("3-Volver atras.\n\r");
	printf("Ingrese su opcion\n\r");
}

void menuModificarPerfilCliente (){
	printf("--- Editar perfil ---\n\r");
	printf("1-Cambiar nombre de usuario.\n\r");
	printf("2-Cambiar email.\n\r");
	printf("3-Cambiar password.\n\r");
	printf("4-Volver atras).\n\r");
	printf("Ingrese su opcion\n\r");
}

cliente crearCliente() {
	cliente clienteNuevo;
	printf("Ingrese nombre: ");
	scanf(" %30[^\n]", clienteNuevo.nombre);
	printf("Ingrese email: ");
	scanf(" %30[^\n]", clienteNuevo.email);
	printf("Ingrese cuil: ");
	scanf(" %30[^\n]", clienteNuevo.cuil);
	printf("Ingrese password: "); ///Preguntar si hay que validar contraseña, es decir una mayuscula, un numero, etc
	scanf(" %30[^\n]", clienteNuevo.password);
	clienteNuevo.saldo_cuenta = 0.0;
	clienteNuevo.num_inversiones = 0;
	return clienteNuevo;
	} // devuelve la copia al llamador

cliente cargarSaldo(cliente c){  ///preguntar si le podemos dejar la c
	float dineroAIngresar;
	do{
    	printf("Cuanto dinero desea ingresar a la cuenta?:\n\r");
    	scanf("%f",&dineroAIngresar);
    	if (dineroAIngresar <= 0) { ///CHEQUEAR VALIDACION DE LETRAS
        	printf("Error: El monto a ingresar debe ser positivo y mayor a cero. Intente de nuevo.\n\r");
    	}
	} while(dineroAIngresar<=0);

	c.saldo_cuenta+=dineroAIngresar;
	return c;
}

cliente extraerSaldo(cliente c ){
	float dineroAExtraer;

	do{
    	printf("Ingrese el saldo a extraer:\n\r");
    	scanf("%f",&dineroAExtraer);
    	if (dineroAExtraer>c.saldo_cuenta){
        	printf("Error: Fondos insuficientes.\n\r");
    	}
    	if (dineroAExtraer<=0){
        	printf("Error: No se puede extraer montos menores o iguales a $0.\n\r");
    	}
	} while(dineroAExtraer<=0 && dineroAExtraer>c.saldo_cuenta);

	if(dineroAExtraer>0 && dineroAExtraer<=c.saldo_cuenta){
   	c.saldo_cuenta-=dineroAExtraer;
	}
	return c;
}

void verPortfolio(cliente c){
	int i=0;
	if (c.num_inversiones==0){
    	printf("Aun no tienes inversiones.\n\r");
	}
	else {
     	do {
    	printf("Inversion N°%d:\n\r",i+1);
    	printf("Id Ticker:%s\n\r",c.inversiones[i].id_ticker);
    	printf("Cantidad de acciones:%d\n\r",c.inversiones[i].cantidad_acciones);
    	printf("Precio de compra:%.2f\n\r",c.inversiones[i].precio_compra);
    	printf("Fecha de compra:%s\n\r",c.inversiones[i].fecha);
    	i++;
	} while(i<c.num_inversiones);
	}
}

cliente iniciarSesion(cliente listaClientes[], char nombreIng[], char passIng[], int cantidadClientes ){
	cliente encontrado;
	strcpy(encontrado.nombre,"");
	strcpy(encontrado.password,"");

    	for(int i=0;i<cantidadClientes;i++){
        	if(strcmp(listaClientes[i].nombre,nombreIng) == 0 && (strcmp(listaClientes[i].password,passIng)) ==0) {
                	encontrado=listaClientes[i];
                	break;
                	}
            	}

	return encontrado;
}


//{}

void menuInversiones (){
	printf("--- Gestor de Inversiones ---\n\r");
	printf("1-Comprar acciones.\n\r");
	printf("2-Vender acciones.\n\r");
	printf("3-Volver atras.\n\r");
	printf("Ingrese su opcion\n\r");
}

cliente copiarInversiones(cliente c, inversion baseInversiones[], int cantidadInversiones){
    int j=0;
        for(int i=0;i<cantidadInversiones;i++){
            if (strcmp(baseInversiones[i].cuil, c.cuil)==0){
                    c.inversiones[j]=baseInversiones[i];
                    j++;
                }
            if (j==c.num_inversiones)
                break;
        }
    return  c;
}

cliente comprarInversion (cliente c, char empresaCompraInversion[],float precioCompra, float cantidadAComprar){
    int indice=c.num_inversiones;

    c.inversiones[indice].cantidad_acciones=cantidadAComprar;
    strcpy(c.inversiones[indice].cuil,c.cuil);
    strcpy(c.inversiones[indice].cuil,"08/10/2026");
    strcpy(c.inversiones[indice].cuil,empresaCompraInversion);
    strcpy(c.inversiones[indice].cuil,"C");
    c.inversiones[indice].precio_compra=precioCompra;
    c.saldo_cuenta-=precioCompra;
    c.num_inversiones++;
    return c;
}

void menuSaldoInsuficiente(){
    printf("Saldo insuficiente.\n\r");
    printf("Que quiere hacer?:\n\r");
    printf("1 - Reintentar compra.\n\r");
    printf("2 - Cancelar compra.\n\r");
    printf("Ingrese su opcion:\n\r");
}

void menuConfirmarCompra(){
    printf("Saldo suficiente, desea confirmar la compra?\n\r");
    printf("1-Confirmar compra.\n\r");
    printf("2-Cancelar compra.\n\r");
    printf("Ingrese una opcion:\n\r");
}

