#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inversion.h"
#include "cliente.h"
#include "empresa.h"

void menuClienteLogueado (){
	printf("-----MENU-----\n\r");
	printf("1-Realizar inversion.\n\r");
	printf("2-Ver rendimientos.\n\r");
	printf("3-Gestion de saldo.\n\r");
	printf("4-Ver portafolio.\n\r");
	printf("5-Modificar perfil.\n\r");
	printf("6-Darse de baja.\n\r");
	printf("7-Volver atras.\n\r");
	printf("Ingrese su opcion.\n\r");

}

void menuClienteInversion (){
	printf("---GESTOR DE INVERSIONES---\n\r");
	printf("1-Comprar acciones.\n\r");
	printf("2-Vender acciones.\n\r");
	printf("3-Volver atras.\n\r");
	printf("Ingrese su opcion\n\r");
}

void menuRendimientos (){
	printf("---RENDIMEINTOS---\n\r");
	printf("1-Rendimientos diarios.\n\r");
	printf("2-Rendimientos historicos.\n\r");
	printf("3-Volver atras.\n\r");
	printf("Ingrese su opcion:\n\r");
}

void menuGestionSaldo (cliente c){
	printf("---GESTION DE SALDO---\n\r");
	printf("Saldo actual: $%.2f \n\r",c.saldo_cuenta);
	printf("1-Cargar saldo.\n\r");
	printf("2-Extraer saldo.\n\r");
	printf("3-Volver atras.\n\r");
	printf("Ingrese su opcion\n\r");
}

void menuPerfilCliente(){
    printf("-----MENU CLIENTE-----\n\r");
	printf("1-Crear cuenta.\n\r");
	printf("2-Iniciar sesion.\n\r");
	printf("3-Volver al menu principal.\n\r");
	printf("Ingrese una opcion:\n\r");

}

cliente crearCliente() {
	int tieneArroba = 0;

	cliente clienteNuevo;
	printf("Ingrese su nombre: ");
	scanf(" %30[^\n]", clienteNuevo.nombre);
	do{
        printf("Ingrese su email: ");
        scanf(" %30[^\n]", clienteNuevo.email);
        for (int i = 0; clienteNuevo.email[i] != '\0'; i++) {
            if (clienteNuevo.email[i] == '@') {
                tieneArroba = 1;
            }
        }
        if (tieneArroba<1) {
            printf("Email invalido: debe contener '@'. Intente nuevamente.\n");
        }
    } while (tieneArroba<1);

	printf("Ingrese su cuil: ");
	scanf(" %30[^\n]", clienteNuevo.cuil);
	printf("Ingrese su password: ");
	scanf(" %30[^\n]", clienteNuevo.password);
	clienteNuevo.saldo_cuenta = 0.0;
	clienteNuevo.num_inversiones = 0;
	return clienteNuevo;
	}

cliente cargarSaldo(cliente c){
	float dineroAIngresar;
	do{
    	printf("Cuanto dinero desea ingresar a la cuenta?:\n\r");
    	scanf("%f",&dineroAIngresar);
    	if (dineroAIngresar <= 0) {
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
        	printf("Error: Fondos insuficientes.\n\r\n\r");
    	}
    	if (dineroAExtraer<=0){
        	printf("Error: No se puede extraer montos menores o iguales a $0.\n\r\n\r");
    	}
	} while(dineroAExtraer<=0 && dineroAExtraer>c.saldo_cuenta);
	if(dineroAExtraer>0 && dineroAExtraer<=c.saldo_cuenta){
   	c.saldo_cuenta-=dineroAExtraer;
	}
	return c;
}

void verPortfolio(cliente c){
	int i=0;
	printf("---PORTAFOLIO---\n\r\n\r");
	if (c.num_inversiones==0){
    	printf("Aun no tienes inversiones.\n\r\n\r");
	}
	else {
     	do {
    	printf("Inversion N-%d:\n\r",i+1);
    	printf("Id Ticker:%s\n\r",c.inversiones[i].id_ticker);
    	printf("Cantidad de acciones:%d\n\r",c.inversiones[i].cantidad_acciones);

    	if(c.inversiones[i].operacion == 'V'){
            printf("Precio de venta:%.2f\n\r",c.inversiones[i].precio_compra);
            printf("Fecha de venta:%s\n\r",c.inversiones[i].fecha);
    	}
    	else{
            printf("Precio de compra:%.2f\n\r",c.inversiones[i].precio_compra);
            printf("Fecha de compra:%s\n\r",c.inversiones[i].fecha);
    	}
        printf("\n\r");
    	i++;
	} while(i<c.num_inversiones);
	}
}

cliente iniciarSesion(cliente listaClientes[], char nombreIng[], char passIng[], int cantidadClientes ){
	cliente encontrado;
	strcpy(encontrado.nombre,"");
	strcpy(encontrado.password,"");
	encontrado.condicionUser='A';

    	for(int i=0;i<cantidadClientes;i++){
        	if(strcmp(listaClientes[i].nombre,nombreIng) == 0 && (strcmp(listaClientes[i].password,passIng)) ==0) {
                	encontrado=listaClientes[i];
                	break;
                	}
            	}
	return encontrado;
}

void menuInversiones (){
	printf("---GESTOR DE INVERSIONES---\n\r");
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
    strcpy(c.inversiones[indice].fecha,"08/10/2026");
    strcpy(c.inversiones[indice].id_ticker,empresaCompraInversion);
    c.inversiones[indice].operacion='C';
    c.inversiones[indice].condicionActivo='A';
    c.inversiones[indice].precio_compra=precioCompra;
    c.saldo_cuenta-=precioCompra*cantidadAComprar;
    c.num_inversiones++;
    return c;
}

void menuSaldoInsuficiente(){
    printf("\n\rSaldo insuficiente.\n\r");
    printf("Que quiere hacer?:\n\r");
    printf("1 - Reintentar compra.\n\r");
    printf("2 - Cancelar compra.\n\r");
    printf("Ingrese su opcion:\n\r");
}

void menuConfirmarCompra(){
    printf("\n\rConfirmar la compra?\n\r");
    printf("1-Confirmar compra.\n\r");
    printf("2-Cancelar compra.\n\r");
    printf("Ingrese una opcion:\n\r");
}

void mostrarAccionesCliente(cliente clienteLogueado, char tickers[][10], float precios[], int cantidadTickers) {
    int cantidades[30] = {0};

    for (int i = 0; i < clienteLogueado.num_inversiones; i++) {
        if (clienteLogueado.inversiones[i].condicionActivo == 'A') {
            for (int j = 0; j < cantidadTickers; j++) {
                if (strcmp(clienteLogueado.inversiones[i].id_ticker, tickers[j]) == 0) {
                    cantidades[j] += clienteLogueado.inversiones[i].cantidad_acciones;
                    break;
                }
            }
        }
    }
    printf("Acciones activas del cliente:\n\r\n\r");
    for (int i = 0; i < cantidadTickers; i++) {
        printf(" %s | %d acciones | Precio actual: $%.2f\n\r", tickers[i], cantidades[i], precios[i]);
    }
    if (cantidadTickers == 0) {
        printf("No se encontraron acciones activas para mostrar.\n\r\n\r");
    }
}

int validarAcciones(cliente c, char accionEmpresaVender[]){
    int cantidadAcciones=0;

    for (int i=0;i<c.num_inversiones;i++){
        if(strcmp(c.inversiones[i].id_ticker,accionEmpresaVender)==0){
            if(c.inversiones[i].condicionActivo=='A'){
                cantidadAcciones+=c.inversiones[i].cantidad_acciones;
            }
        }
    }
    return cantidadAcciones;
}

cliente venderAcciones(cliente c, char ticker[10], int cantidadAVender, float precioVenta, char fecha[11]) {
    int restante = cantidadAVender;

    for (int i = 0; i < c.num_inversiones && restante > 0; i++) {
        if (c.inversiones[i].condicionActivo == 'A' &&
            strcmp(c.inversiones[i].id_ticker, ticker) == 0) {
            if (c.inversiones[i].cantidad_acciones <= restante) {
                restante -= c.inversiones[i].cantidad_acciones;
                c.inversiones[i].condicionActivo = 'I';
            } else {
                restante = 0;
            }
        }
    }
    // Registrar nueva inversión de tipo venta
    if (c.num_inversiones < 500) {
        int k = c.num_inversiones;
        strcpy(c.inversiones[k].cuil, c.inversiones[0].cuil);
        strcpy(c.inversiones[k].id_ticker, ticker);
        c.inversiones[k].cantidad_acciones = cantidadAVender;
        c.inversiones[k].precio_compra = precioVenta;
        strcpy(c.inversiones[k].fecha, fecha);
        c.inversiones[k].operacion = 'V';
        c.inversiones[k].condicionActivo = 'I';
        c.saldo_cuenta += cantidadAVender * precioVenta;
        c.num_inversiones++;

    }
    return c;
}

cliente darDeBaja(cliente c, cliente baseClientes[],int cantidadClientes){
    c.condicionUser='B';

    for (int i = 0; i < cantidadClientes; i++) {
    if (strcmp(baseClientes[i].nombre, c.nombre) == 0 &&
        strcmp(baseClientes[i].password, c.password) == 0) {
        baseClientes[i].condicionUser='B';
        break;
    }
}
    return c;
}

void menuConfirmarBaja(){
    printf("Confirmar baja de usuario?:\n\r");
    printf("1-Confirmar.\n\r");
    printf("2-Cancelar.\n\r");
}

void menuModificarCliente(){
    printf("---MODIFICAR PERFIL---\n\r");
    printf("1-Modificar Nombre.\n\r");
    printf("2-Modificar Password.\n\r");
    printf("3-Volver atras.\n\r");
    printf("Ingrese una opcion:\n\r");
}

cliente cambiarNombre(cliente c, cliente baseCliente[], int cantidadClientes){

    for(int i=0;i<cantidadClientes;i++){
        if (strcmp(c.nombre,baseCliente[i].nombre)==0 && strcmp(c.password,baseCliente[i].password)==0){
        printf("Ingrese el nuevo nombre:\n\r");
            scanf(" %30[^\n]", c.nombre);
            strcpy(baseCliente[i].nombre,c.nombre);
        }
    }
    return c;
}

cliente cambiarPassword(cliente c, cliente baseCliente[], int cantidadClientes){
    for(int i=0;i<cantidadClientes;i++){
        if (strcmp(c.nombre,baseCliente[i].nombre)==0 && strcmp(c.password,baseCliente[i].password) == 0){
            printf("Ingrese la nueva password:\n\r");
            scanf(" %30[^\n]", c.password);
            strcpy(baseCliente[i].password,c.password);
        }
    }
    return c;
}

cliente darDeAlta(char cuilADarDeAlta[], cliente baseClientes[], int cantidadClientes){
    cliente dadoDeAlta;

    for (int i=0;i<cantidadClientes;i++){
        if(strcmp(cuilADarDeAlta,baseClientes[i].cuil)==0){
            baseClientes[i].condicionUser='A';
            dadoDeAlta=baseClientes[i];
        }
    }
    return dadoDeAlta;
}

int clientesInactivos(cliente baseClientes[],int cantidadClientes){
    int inactivos=0;

    for(int i=0;i<cantidadClientes;i++){
            if(baseClientes[i].condicionUser=='B'){
                printf("Nombre:%s CUIL:%s\n\r",baseClientes[i].nombre, baseClientes[i].cuil);
                inactivos++;
            }
    }

    return inactivos;
}

int validarCuil(char cuil[],cliente baseClientes[],int cantClientes){
   int valido=0;
    for (int i=0;i<cantClientes;i++){
        if(strcmp(cuil,baseClientes[i].cuil)==0){
            valido=1;
        }
    }
    return valido;
}

void valorDiario(float precios[], char tickers[][10], cliente c, int cantidadempresas, char fecha[]) {
    float precioMasBarato;
    float precioMasCaro;
    float totalGananciaEmpresa;
    float totalPorcentajeEmpresa;
    int encontrado;
    float sumaGanancias = 0;
    float sumaCostos = 0;
    float porcentajeTotal = 0;
    int inversionesFecha = 0;

    if (c.num_inversiones > 0) {
        for (int i = 0; i < cantidadempresas; i++) {
            precioMasBarato = 10000000.0;
            precioMasCaro = -1.0;
            encontrado = 0;
            for (int j = 0; j < c.num_inversiones; j++) {
                if (strcmp(tickers[i], c.inversiones[j].id_ticker) == 0 && c.inversiones[j].condicionActivo == 'A' && strcmp(c.inversiones[j].fecha, fecha) == 0) {
                    encontrado = 1;
                    inversionesFecha++;
                    if (c.inversiones[j].precio_compra < precioMasBarato) {
                        precioMasBarato = c.inversiones[j].precio_compra;
                    }
                    if (c.inversiones[j].precio_compra > precioMasCaro) {
                        precioMasCaro = c.inversiones[j].precio_compra;
                    }
                }
            }
            if (encontrado) {
                totalGananciaEmpresa = precioMasCaro - precioMasBarato;
                if (precioMasBarato > 0 && precioMasBarato != 10000000.0) {
                    totalPorcentajeEmpresa = (totalGananciaEmpresa / precioMasBarato) * 100;
                } else {
                    totalPorcentajeEmpresa = 0;
                }
                printf("NOMBRE | PRECIO ACTUAL | VALOR HISTORICO  | %% HISTORICO\n\r");
                printf(" %s |  $%.2f   |  $%.2f   |  %.2f %%\n\r",
                       tickers[i], precios[i], totalGananciaEmpresa, totalPorcentajeEmpresa);
                sumaGanancias += totalGananciaEmpresa;
                sumaCostos += precioMasBarato;
            }
        }
        if (inversionesFecha > 0) {
            if (sumaCostos > 0) {
                porcentajeTotal = (sumaGanancias / sumaCostos) * 100;
            } else {
                porcentajeTotal = 0;
            }
            printf("Ganancia total (todas las empresas del %s): $%.2f || %.2f%% \n\r",
                   fecha, sumaGanancias, porcentajeTotal);
        } else {
            printf("No tienes inversiones activas en la fecha %s.\n\r", fecha);
        }
    } else {
        printf("Aun no tienes inversiones registradas.\n\r");
    }
}

void valorHistorico(float precios[], char tickers[][10], cliente c, int cantidadempresas) {
    float precioMasBarato = 10000000;
    float totalGananciaEmpresa;
    float totalPorcentajeEmpresa;
    int encontrado;
    float sumaGanancias=0;
    float sumaCostos=0;
    float porcentajeTotal=0;

    if (c.num_inversiones > 0) {
        printf("NOMBRE   | PRECIO ACTUAL | VALOR HISTORICO  | %% HISTORICO\n\r");
        for (int i = 0; i < cantidadempresas; i++) {
            precioMasBarato = 10000000;
            encontrado = 0;
            for (int j = 0; j < c.num_inversiones; j++) {
                if (strcmp(tickers[i], c.inversiones[j].id_ticker) == 0 && c.inversiones[j].condicionActivo == 'A') {
                    encontrado = 1;
                    if (precioMasBarato > c.inversiones[j].precio_compra) {
                        precioMasBarato = c.inversiones[j].precio_compra;
                    }
                }
            }
            if (encontrado) {
                totalGananciaEmpresa=(precios[i]-precioMasBarato);
                totalPorcentajeEmpresa=((totalGananciaEmpresa/precios[i])*100);
                printf(" %s | $%.2f  | $%.2f  | %.2f %%\n\r",tickers[i],precios[i],totalGananciaEmpresa,totalPorcentajeEmpresa);
                sumaGanancias += totalGananciaEmpresa;
                sumaCostos += precioMasBarato;
            }
        }
        porcentajeTotal = (sumaGanancias / sumaCostos) * 100;
        printf("Ganancia total(todas las empresas): $%.2f || %.2f%% \n\r\n\r",sumaGanancias,porcentajeTotal);
    }
    else{
        printf("Aun no tienes inversiones historicas.\n\r\n\r");
    }
}
