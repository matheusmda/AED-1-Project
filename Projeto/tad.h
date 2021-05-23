#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

typedef struct remedio med;

typedef struct tipo_remedio tipo;

typedef struct lista lista;

lista* criaLista();

void menuPrincipal(int contMenuPrincipal, lista* l); // menuzão que eu vou sempre voltar pra ele