#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inversion.h"
#include "cliente.h"

void menuEmpresa();

typedef struct empresa{
    	char id_ticker[10];
    	char nombre[50];
    	float precio_actual;

	} empresa;
void verHistoricoOperaciones(empresa e, cliente listaClientes[], int cantidadClientes);
empresa validarEmpresaNombre(empresa baseEmpresas[],char nombreEmpresaIng[], int cantidadEmpresas);
empresa validarEmpresaTicker(empresa baseEmpresas[],char tickerEmpresaIng[], int cantidadEmpresas);
void listaEmpresas(empresa baseEmpresas[], int cantidadEmpresas);

#endif // EMPRESA_H_INCLUDED








