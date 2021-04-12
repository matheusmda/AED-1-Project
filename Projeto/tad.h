#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define max 50

typedef struct remedio med;

typedef struct tipo_remedio tipo;

typedef struct lista lista;

void menuPrincipal(); // menuzão que eu vou sempre voltar pra ele

void menuCascata();

void liberaLista(lista* l); // Eu quero isso aqui? Ou deixo encapsulado no tad.c?

void inserirTipo(lista* l, char tip[max+1]);

void inserirRemedio(lista* l, char rem[max+1], char preco[10+1], int quat_estoque, int exigencia_receita, char tipoMed[max+1]);