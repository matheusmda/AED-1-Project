#include "tad.h"

struct remedio {
    char nome_med[max+1];
    char preco[10+1];
    int quant_estoque;
    int exigencia_receita; // 0 para não, 1 para sim
    med* next;
    char tipoMed[max+1];
};

struct tipo_remedio {
    char tip[max+1];
    tipo* next;
    med* inicio_lista_med;
    int numElem_Meds;
};

struct lista{
    tipo* inicio_listaTipo;
    int numElem_Tipos; // eu tiraria isso daqui
};

// FUNÇÕES LOCAIS - ENCAPSULADAS ~ PRIVATE
void criaEstoquePadraoTipoRemedio(lista* l);
void criaEstoquePadraoRemedio(lista* l);
void inserirTipo(lista* l, char tip[max+1]);
void inserirRemedio(lista* l, char nome_med[max+1], char preco[10+1], int quant_estoque, int exigencia_receita, char tipoMed[max+1]);
tipo* ultimoElemTipo(lista* l);
tipo* NoTipoEspecifico(lista* l, char tipoMed[max+1]);
int tipoExiste(lista* l, char tipoMed[max+1]);
void inserirMed_na_lista(tipo* tipo_de_remedio, med* medicacao);
med* ultimoElemMed(tipo* tipo_de_remedio, med* medicacao);
void liberaLista(lista* l);
void menuCascata(lista* l, int contMenuPrincipal);
void submenu(lista* l, tipo* tipo_de_remedio, int contMenuPrincipal);
void menuInfo(lista* l, med* medicacao, int contMenuPrincipal);
void pesquisarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void removerMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void deletarMedicamento(lista* l, med* medicacao, tipo* tipo_de_remedio);
void adicionarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void alterarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void retirarDuplicata(lista* l, char tipoMed[max+1], char nome_med[max+1]);

// Função do Menu Principal do Programa
void menuPrincipal(int contMenuPrincipal, lista* l){
    contMenuPrincipal++;
    system("clear");
    printf("=========================================================================================\n");
    printf("\n\t\tSeja bem vindo ao Sistema de Controle de Estoque!\n\n");
    printf("Por favor, selecione a opção desejada:\n\n");
    printf("1 - Buscar Medicamento.\n");
    printf("2 - Pesquisar Medicamento.\n");
    printf("3 - Remover Medicamento.\n");
    printf("4 - Adicionar Novo Medicamento.\n");
    printf("5 - Alterar Medicamento.\n");
    printf("6 - Sair.\n");
    printf("=========================================================================================\n");

    int input;
    scanf("%d", &input);

    if(contMenuPrincipal == 1){
        criaEstoquePadraoTipoRemedio(l);
        criaEstoquePadraoRemedio(l);
    }

    if(input == 1){
        menuCascata(l, contMenuPrincipal);
    }
    else if(input == 2){
        char nome_med[max+1];
        printf("Digite o nome do medicamento que deseja pesquisar:\n");
        scanf("%s", nome_med);
        pesquisarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 3){
        char nome_med[max+1];
        printf("Digite o nome do medicamento que deseja remover:\n\n");
        scanf("%s", nome_med);
        removerMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 4){
        char nome_med[max+1];
        printf("Digite o nome do medicamento que deseja adicionar:\n\n");
        scanf("%s", nome_med);
        adicionarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 5){
        char nome_med[max+1];
        printf("Digite o nome do medicamento que deseja alterar:\n\n");
        scanf("%s", nome_med);
        alterarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 6){
        liberaLista(l);
        system("clear");
        printf("\n\n\t\t--------- SISTEMA ENCERRADO ---------\n\n\n");
        printf("Muito Obrigado! :)\n");
        return;
    }
}

// Função para inicializar a lista
lista* criaLista(){
    lista* l = (lista*) malloc(sizeof(lista));
    l->inicio_listaTipo = NULL;
    l->numElem_Tipos = 0; // simplesmente deixaria de existir
    
    return l;
}

// Função Local para criar nosso "Estoque Atual" ou "Estoque existente"
void criaEstoquePadraoTipoRemedio(lista* l){
    inserirTipo(l, "analgesico");
    inserirTipo(l, "anfetamina");
    inserirTipo(l, "antiacido");
}

// Função Local para criar nosso "Estoque Atual" ou "Estoque existente"
void criaEstoquePadraoRemedio(lista* l){
    inserirRemedio(l, "Paracetamol", "12,00", 80, 0, "analgesico");
    inserirRemedio(l, "Dipirona", "4,50", 9, 0, "analgesico");

    inserirRemedio(l, "Venvanse", "257,00", 94, 1, "anfetamina");
    inserirRemedio(l, "Ritalina", "40,00", 50, 1, "anfetamina");

    inserirRemedio(l, "Engov", "5,35", 320, 0, "antiacido");
}

// Função local para inserir um nó na lista de Tipos de medicamentos
void inserirTipo(lista* l, char tip[max+1]){
    tipo* novo_tipo = (tipo*) malloc(sizeof(tipo));
    strcpy(novo_tipo->tip, tip);
    novo_tipo->inicio_lista_med = NULL;
    novo_tipo->numElem_Meds = 0;
    novo_tipo->next = NULL;
    
    if(l->numElem_Tipos == 0){ // trocaria por l->inicio_listaTipo == NULL
        l->inicio_listaTipo = novo_tipo;
        l->numElem_Tipos++; // deixaria de existir
    }
    else{
        tipo* ultimo = ultimoElemTipo(l);
        ultimo->next = novo_tipo;
        l->numElem_Tipos++; // deixaria de existir
    }
}

// Função local para retornar último elemento da lista de tipos de remédio
tipo* ultimoElemTipo(lista* l){
    tipo* tempTipo = l->inicio_listaTipo;
    while(tempTipo->next != NULL){
        tempTipo = tempTipo->next;
    }
    return tempTipo;
}

// Função local para inserir um Remedio em sua lista especifica de acordo com seu Tipo
void inserirRemedio(lista* l, char nome_med[max+1], char preco[10+1], int quant_estoque, int exigencia_receita, char tipoMed[max+1]){
    med* novo_med = (med*) malloc(sizeof(med));
    strcpy(novo_med->nome_med, nome_med);
    strcpy(novo_med->preco, preco);
    novo_med->quant_estoque = quant_estoque;
    novo_med->exigencia_receita = exigencia_receita;
    strcpy(novo_med->tipoMed, tipoMed);

    int check = tipoExiste(l, tipoMed);
    if(check == 0){
        inserirTipo(l, tipoMed);
    }

    tipo* tempTipo = NoTipoEspecifico(l, tipoMed);
    inserirMed_na_lista(tempTipo, novo_med);
    tempTipo->numElem_Meds++;
}

// Função local auxiliar da função inserirRemedio usada para inserir remedio na sua respectiva lista
void inserirMed_na_lista(tipo* tipo_de_remedio, med* medicacao){
    if(tipo_de_remedio->inicio_lista_med == NULL){
        tipo_de_remedio->inicio_lista_med = medicacao;
    }
    else{
        med* tempMed = ultimoElemMed(tipo_de_remedio, medicacao);
        tempMed->next = medicacao;
    }
}

// Função local auxiliar da função inserirMed_na_lista para retornar o último elemento da lista de medicamentos do tipo especificado
med* ultimoElemMed(tipo* tipo_de_remedio, med* medicacao){
    med* tempMed = tipo_de_remedio->inicio_lista_med;
    while(tempMed->next != NULL){
        tempMed = tempMed->next;
    }
    return tempMed;
}

// Função local para retornar 1 se o tipo especificado de medicamento existe e 0 caso não exista no sistema.
int tipoExiste(lista* l, char tipoMed[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    while(strcmp(tempTipo->tip, tipoMed) != 0 && tempTipo->next != NULL){
        tempTipo = tempTipo->next;
    }
    if(strcmp(tempTipo->tip, tipoMed) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

// Função local para retornar o nó do tipo de medicamento especificado
tipo* NoTipoEspecifico(lista* l, char tipoMed[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    for(int i = 0;strcmp(tempTipo->tip, tipoMed) != 0 && i < l->numElem_Tipos && tempTipo->next ;i++){ // ARRUMAR ESSE TREM AQUI!! PRA NÃO PRECISAR USAR MAIS numElem!!
        tempTipo = tempTipo->next;
    }
    if(strcmp(tempTipo->tip, tipoMed) == 0){
        return tempTipo;
    }
    else{
        printf("Tipo de medicamento especificado não existe em estoque!\n");
        return NULL;
    }
}

// Menu que disponibiliza lista de tipos de remédio para seleção
void menuCascata(lista* l, int contMenuPrincipal){
    system("clear");
    tipo* tempTipo = l->inicio_listaTipo;
    printf("Selecione o tipo de medicação desejado:\n");
    int i;
    for(i = 1;tempTipo != NULL;i++){
        printf("%d - %s\n", i, tempTipo->tip);
        tempTipo = tempTipo->next;
    }
    printf("0 - Voltar ao Menu Principal\n");

    int input;
    scanf("%d", &input);

    tempTipo = l->inicio_listaTipo;
    for(i = 1;tempTipo != NULL;i++){
        if(i == input){
            submenu(l, tempTipo, contMenuPrincipal);
        }
        tempTipo = tempTipo->next;
    }
}

// Menu que disponibiliza lista de remédios (do tipo selecionado no menu anterior) para seleção
void submenu(lista* l, tipo* tipo_de_remedio, int contMenuPrincipal){
    system("clear");
    med* tempMed = tipo_de_remedio->inicio_lista_med;
    printf("Selecione o %s desejado:\n", tipo_de_remedio->tip);
    int i;
    for(i = 1;tempMed != NULL;i++){
        printf("%d - %s\n", i, tempMed->nome_med);
        tempMed = tempMed->next;
    }
    if(tipo_de_remedio->inicio_lista_med == NULL){
        printf("\n--> Não há nenhum medicamento do tipo %s em estoque no momento!\n\n", tipo_de_remedio->tip);
    }
    printf("0 - Voltar ao Menu Principal\n");

    int input;
    scanf("%d", &input);

    if(input == 0){
        menuPrincipal(contMenuPrincipal, l);
    }
    tempMed = tipo_de_remedio->inicio_lista_med;
    for(i = 1;tempMed != NULL;i++){
        if(i == input){
            menuInfo(l, tempMed, contMenuPrincipal);
        }
        tempMed = tempMed->next;
    }
}

// Menu que disponibiliza informações e opções do medicamento selecionado
void menuInfo(lista* l, med* medicacao, int contMenuPrincipal){
    system("clear");
    printf("\t\tInformações e Opções do medicamento:\n\n");
    printf("Medicamento: %s\n", medicacao->nome_med);
    printf("Preço: R$%s\n", medicacao->preco);
    printf("Quantidade em Estoque: %d\n", medicacao->quant_estoque);
    printf("Tipo de medicamento: %s\n", medicacao->tipoMed);
    if(medicacao->exigencia_receita == 1){
        printf("Exige Receita Médica? - SIM\n");
    }
    else{
        printf("Exige Receita Médica? - NÃO\n");
    }
    printf("\n");
    printf("1 - Solicitar Reposição de Estoque\n");
    printf("0 - Voltar ao Menu Principal\n\n");

    int input, entrada;
    scanf("%d", &input);

    if(input == 0){
        menuPrincipal(contMenuPrincipal, l);
    }
    if(input == 1){
        if(medicacao->quant_estoque > 10){
            system("clear");
            printf("\n\t\t\t\t***REPOSIÇÃO RECUSADA!***\n\n");
            printf("A resposição de estoque só é permitida caso a quantidade do medicamento em estoque seja 10 ou menos!\n\n");
            printf("2 - Voltar as informações do medicamento buscado\n");
            printf("0 - Voltar ao Menu Principal\n\n");
            scanf("%d", &entrada);
            if(entrada == 2){
                menuInfo(l, medicacao, contMenuPrincipal);
            }
            else if(entrada == 0){
                menuPrincipal(contMenuPrincipal, l);
            }         
        }
        else{
            system("clear");
            printf("Por favor, digite quantos medicamentos deseja reestocar:\n\n");
            scanf("%d", &input);
            medicacao->quant_estoque = medicacao->quant_estoque + input;
            system("clear");
            printf("\n\t\t\t\t***MEDICAMENTO REESTOCADO!***\n\nNova quantidade em estoque: %d\n", medicacao->quant_estoque);
            printf("2 - Voltar as informações do medicamento buscado\n");
            printf("0 - Voltar ao Menu Principal\n");
            
            scanf("%d", &entrada);
            if(entrada == 2){
                menuInfo(l, medicacao, contMenuPrincipal);
            }
            else if(entrada == 0){
                menuPrincipal(contMenuPrincipal, l);
            }
        }
    }
}

// Função para pesquisar produto diretamente via string de busca
void pesquisarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    int aux = 0;

    while(tempTipo != NULL){
        while(tempMed != NULL){
            if(strcmp(nome_med, tempMed->nome_med) == 0){
                aux = 1;
                menuInfo(l, tempMed, contMenuPrincipal);
                break;
            }
            tempMed = tempMed->next;
        }
        if(aux == 1) break;
        tempTipo = tempTipo->next;
        if(tempTipo == NULL) break;
        tempMed = tempTipo->inicio_lista_med;
    }

    if(aux == 0){
        system("clear");
        printf("\n\t--> MEDICAMENTO BUSCADO NÃO EXISTE EM ESTOQUE! <--\n\n\n");
        printf("0 - Voltar ao Menu Principal\n\n");
        int input;
        scanf("%d", &input);
        if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
        else{
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

// Função para remover medicamento do estoque
void removerMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    int aux = 0;
    while(tempTipo != NULL){
        while(tempMed != NULL){
            if(strcmp(nome_med, tempMed->nome_med) == 0){
                aux = 1;
                deletarMedicamento(l, tempMed, tempTipo);
                system("clear");
                printf("\n\t --- MEDICAMENTO RETIRADO COM SUCESSO!! ---\n\n\n");
                printf("0 - Voltar ao Menu Principal\n\n");
                int input;
                scanf("%d", &input);
                if(input == 0){
                    menuPrincipal(contMenuPrincipal, l);
                }
                else{
                    menuPrincipal(contMenuPrincipal, l);
                }
                break;
            }
            tempMed = tempMed->next;
        }
        if(aux == 1) break;
        tempTipo = tempTipo->next;
        if(tempTipo == NULL) break;
        tempMed = tempTipo->inicio_lista_med;
    }

    if(aux == 0){
        system("clear");
        printf("\n\t--> MEDICAMENTO BUSCADO NÃO EXISTE EM ESTOQUE! <--\n\n\n");
        printf("0 - Voltar ao Menu Principal\n\n");
        int input;
        scanf("%d", &input);
        if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
        else{
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

// Função para efetivamente deletar medicamento na lista (Função auxiliar da função acima - removerMedicamento)
void deletarMedicamento(lista* l, med* medicacao, tipo* tipo_de_remedio){
    med* tempMed = tipo_de_remedio->inicio_lista_med;

    while(tempMed->next != medicacao){
        if(tempMed == medicacao){
            free(medicacao);
            tipo_de_remedio->inicio_lista_med = NULL;
            return;
        }
        tempMed = tempMed->next;
    }
    tempMed->next = medicacao->next;
    free(medicacao);
}

// Função para adicionar novo medicamento ao estoque
void adicionarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    int aux = 0;

    while(tempTipo != NULL){
        while(tempMed != NULL){
            if(strcmp(nome_med, tempMed->nome_med) == 0){
                aux = 1;
                system("clear");
                printf("\n\t--> MEDICAMENTO BUSCADO JÁ EXISTE EM ESTOQUE! <--\n\n\n");
                printf("0 - Voltar ao Menu Principal\n\n");
                int input;
                scanf("%d", &input);
                if(input == 0){
                    menuPrincipal(contMenuPrincipal, l);
                }
                else{
                    menuPrincipal(contMenuPrincipal, l);
                }
                break;
            }
            tempMed = tempMed->next;
        }
        if(aux == 1) break;
        tempTipo = tempTipo->next;
        if(tempTipo == NULL) break;
        tempMed = tempTipo->inicio_lista_med;
    }

    if(aux == 0){
        system("clear");
        printf("\nPor favor, insira os seguintes campos: \n\n\n");
        printf("*O campo 'Exigência de Receita' deve ser preenchido com 0 para não e 1 para sim\n\n\n");

        printf("Preço: ");
        char preco[11];
        scanf("%s", preco);
        printf("\n");

        printf("Quantidade de medicamentos: ");
        int quant_estoque;
        scanf("%d", &quant_estoque);
        printf("\n");

        printf("Exigência de Receita*: ");
        int exigencia_receita;
        scanf("%d", &exigencia_receita);
        printf("\n");

        printf("Tipo de medicamento: ");
        char tipoMed[max+1];
        scanf("%s", tipoMed);
        printf("\n\n");

        inserirRemedio(l, nome_med, preco, quant_estoque, exigencia_receita, tipoMed);

        system("clear");
        printf("===================================================================================\n");
        printf("\n\t\t-----Novo medicamento inserido em estoque com sucesso!!-----\n\n\n");
        printf("2 - Ver informações do remédio adicionado\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("===================================================================================\n");
        int input;
        scanf("%d", &input);

        if(input == 2){
            pesquisarMedicamento(l, contMenuPrincipal, nome_med);
        }
        else if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
        else{
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

// Função para alterar dados de um medicamento já existente no estoque
void alterarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    int aux = 0;

    while(tempTipo != NULL){
        while(tempMed != NULL){
            if(strcmp(nome_med, tempMed->nome_med) == 0){
                aux = 1;
                system("clear");
                printf("===================================================================================\n");
                printf("\nPor favor, selecione o campo do medicamento que deseja alterar: \n\n\n");

                printf("1 - Nome\n");
                printf("2 - Preço\n");
                printf("3 - Quantidade em estoque\n");
                printf("4 - Exigência de receita médica\n");
                printf("5 - Tipo de medicamento\n");
                printf("===================================================================================\n");

                int campo;
                scanf("%d", &campo);

                if(campo == 1){
                    printf("Nome do medicamento: ");
                    char nome[max+1];
                    scanf("%s", nome);
                    strcpy(tempMed->nome_med, nome);
                }
                else if(campo == 2){
                    printf("Preço: ");
                    char preco[11];
                    scanf("%s", preco);
                    strcpy(tempMed->preco, preco);
                }
                else if(campo == 3){
                    printf("Quantidade de medicamentos: ");
                    int quant_estoque;
                    scanf("%d", &quant_estoque);
                    tempMed->quant_estoque = quant_estoque;
                }
                else if(campo == 4){
                    printf("*O campo 'Exigência de Receita' deve ser preenchido com 0 para não e 1 para sim\n\n\n");
                    printf("Exigência de Receita: ");
                    int exigencia_receita;
                    scanf("%d", &exigencia_receita);
                    tempMed->exigencia_receita = exigencia_receita;
                }
                else if(campo == 5){
                    printf("Tipo de medicamento: ");
                    char tipoMed[max+1];
                    scanf("%s", tipoMed);
                    int existe = tipoExiste(l, tipoMed);
                    if(existe == 0){
                        inserirTipo(l, tipoMed);
                    }

                    // Vou usar essa string auxiliar para retirar o medicamento da lista em que ele está
                    char stringAuxTipoMed[max+1];
                    strcpy(stringAuxTipoMed, tempMed->tipoMed);

                    strcpy(tempMed->tipoMed, tipoMed);
                    tipo* tempTipo = NoTipoEspecifico(l, tipoMed);
                    inserirMed_na_lista(tempTipo, tempMed); // Colocando o medicamento na lista em qual ele deve passar a pertencer!!
                    tempTipo->numElem_Meds++;

                    // Retirar a duplicata do medicamento do antigo tipo a qual pertencia!
                    retirarDuplicata(l, stringAuxTipoMed, tempMed->nome_med);
                }
                else{
                    printf("\n\t\t***OPÇÃO INVÁLIDA!!***\n");
                    printf("\nPor favor, digite uma opção válida!!\n\n");
                    printf("Digite 1 para tentar novamente: ");
                    int input;
                    scanf("%d", &input);
                    if(input == 1){
                        alterarMedicamento(l, contMenuPrincipal, nome_med);
                    }
                    else{
                        alterarMedicamento(l, contMenuPrincipal, nome_med);
                    }
                }

                system("clear");
                printf("=============================================================================\n");
                printf("\n\t\t-----Medicamento alterado com sucesso!!-----\n\n\n");
                printf("2 - Ver informações do remédio alterado\n");
                printf("0 - Voltar ao Menu Principal\n");
                printf("=============================================================================\n");
                int input;
                scanf("%d", &input);

                if(input == 2){
                    pesquisarMedicamento(l, contMenuPrincipal, tempMed->nome_med);
                }
                else if(input == 0){
                    menuPrincipal(contMenuPrincipal, l);
                }
                else{
                    menuPrincipal(contMenuPrincipal, l);
                }

            }
            tempMed = tempMed->next;
        }
        if(aux == 1) break;
        tempTipo = tempTipo->next;
        if(tempTipo == NULL) break;
        tempMed = tempTipo->inicio_lista_med;
    }

    if(aux == 0){
        system("clear");
        printf("\n\t--> MEDICAMENTO BUSCADO NÃO EXISTE EM ESTOQUE! <--\n\n\n");
        printf("0 - Voltar ao Menu Principal\n\n");
        int input;
        scanf("%d", &input);
        if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
        else{
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

// Função auxiliar da função alterarMedicamento usada para retirar medicamento duplicado em dois tipos diferentes!!
void retirarDuplicata(lista* l, char tipoMed[max+1], char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;

    while(tempTipo != NULL){
        if(strcmp(tempTipo->tip, tipoMed) == 0){
            while(tempMed != NULL){
                if(strcmp(tempMed->nome_med, nome_med) == 0){
                    deletarMedicamento(l, tempMed, tempTipo);
                    return;
                }
                tempMed = tempMed->next;
            }
        }
        tempTipo = tempTipo->next;
    }
}

// Função para desalocar memória
void liberaLista(lista* l){
    if(l->inicio_listaTipo == NULL){
        return;
    }
    

    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;

    while(tempTipo != NULL){
        while(tempMed != NULL){
            med* apagarMed = tempMed;
            tempMed = tempMed->next;
            free(apagarMed);
        }
        tipo* apagarTipo = tempTipo;
        tempTipo = tempTipo->next;
        free(apagarTipo);
        if(tempTipo == NULL) break;
        tempMed = tempTipo->inicio_lista_med;
    }

    free(l);
}