#include "tad.h"

struct remedio {
    char rem[max+1];
    struct remedio* next;
};

struct tipo_remedio {
    char tip[max+1];
    struct tipo_remedio* next;
};

struct lista{
    med* inicio_listaMed;
    tipo* inicio_listaTipo;
    int numElem_Tipos;
    int numElem_Meds;
};

void criaEstoquePadraoTipoRemedio();
void criaEstoquePadraoRemedio();

void menuPrincipal(){
    printf("=========================================================================================\n");
    printf("\n\t\tSeja bem vindo ao Sistema de Controle de Estoque!\n\n");
    printf("Por favor, selecione a opção desejada:\n\n");
    printf("1 - Buscar Produto.\n");
    printf("2 - Pesquisar Produto.\n");
    printf("3 - Sair.\n");
    printf("=========================================================================================\n");

    int input;
    scanf("%d", &input);

    if(input == 1){
        // chama a função menu cascata
        criaEstoquePadraoTipoRemedio();
        criaEstoquePadraoRemedio();
        menuCascata();
    }
    else if(input == 2){
        // chama a função pesquisar produto via string de busca
    }
    else if(input == 3){
        // encerra o programa
        return;
    }
}

void menuCascata(){

}

void criaEstoquePadraoTipoRemedio(){
    lista* l = criaLista();

}

void criaEstoquePadraoRemedio(){

}

lista* criaLista(){
    lista* l = (lista*) malloc(sizeof(lista));
    l->inicio_listaMed = NULL;
    l->inicio_listaTipo = NULL;
    l->numElem_Meds = 0;
    
    return l;
}

void liberaLista(lista* l){
    lista* apagar;
    med* temp = l->inicio_listaMed;
    while(temp->next != NULL){
        
    }
}

