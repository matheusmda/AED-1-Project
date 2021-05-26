#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

// TAD Medicação
typedef struct remedio med;

// TAD Tipo Medicação
typedef struct tipo_remedio tipo;

// TAD Lista - Estrutura de Dados Lista
typedef struct lista lista;

// Função de inicialização da estrutura de dados lista
lista* criaLista();

// Menu com as principais funcionalidades do programa
void menuPrincipal(int contMenuPrincipal, lista* l);