#include "tad.h"

struct remedio {
    char rem[max+1];
    char preco[10+1];
    int quant_estoque;
    int exigencia_receita; // 0 para não, 1 para sim
    med* next;
    char tipoMed[max+1];
};

struct tipo_remedio {
    char tip[max+1]; // ver depois a possibilidade de fazer um ponteiro para remedio aqui, tendo um "vetor de remédios" de um tipo só
    tipo* next; // dentro de cada tipo eu teria todos os remédios em estoque dentro deste tipo
    med* inicio_lista_de_remedios_deste_tipo;
    int numElem_Meds;
};

struct lista{
    tipo* inicio_listaTipo;
    int numElem_Tipos;
};

void criaEstoquePadraoTipoRemedio(lista* l);
void criaEstoquePadraoRemedio(lista* l);

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
        lista* l = criaLista(); // criaLista em todos os ifs
        criaEstoquePadraoTipoRemedio(l);
        criaEstoquePadraoRemedio(l);
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

lista* criaLista(){
    lista* l = (lista*) malloc(sizeof(lista));
    l->inicio_listaTipo = NULL;
    l->numElem_Tipos = 0;
    
    return l;
}

void criaEstoquePadraoTipoRemedio(lista* l){
    inserirTipo(l, "analgesico");
    inserirTipo(l, "anfetamina");
    inserirTipo(l, "antiacido");
}

void criaEstoquePadraoRemedio(lista* l){
    inserirRemedio(l, "Paracetamol", "12", 80, 0, "analgesico");
    inserirRemedio(l, "Dipirona", "4,50", 15, 0, "analgesico");

    inserirRemedio(l, "Venvanse", "257", 94, 1, "anfetamina");
    inserirRemedio(l, "Ritalina", "40", 50, 1, "anfetamina");

    inserirRemedio(l, "Engov", "5,35", 320, 0, "antiacido");
}

void inserirTipo(lista* l, char tip[max+1]){
    tipo* tipo_de_remedio = (tipo*) malloc(sizeof(tipo));
    strcpy(tipo_de_remedio->tip, tip);
    tipo_de_remedio->inicio_lista_de_remedios_deste_tipo = NULL;
    tipo_de_remedio->numElem_Meds = 0;
    
    if(l->numElem_Tipos == 0){
        l->inicio_listaTipo = tipo_de_remedio;
        l->numElem_Tipos++;
    }
    else{
        ultimoElem();
        penultimoElem();
    }
}

tipo* ultimoElem(){

}

tipo* penultimoElem(){
    
}

void inserirRemedio(lista* l, char rem[max+1], char preco[10+1], int quat_estoque, int exigencia_receita, char tipoMed[max+1]){

}

void menuCascata(){

}

void liberaLista(lista* l){
    tipo* temp = l->inicio_listaTipo;
    while(temp->next != NULL){
        tipo* apagar = temp;
        free(apagar);
        temp = temp->next;
    }
    free(temp);

    l->inicio_listaTipo = NULL;
    l->numElem_Tipos = 0;
    // free(l); ?? 
}