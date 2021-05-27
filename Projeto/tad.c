#include "tad.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                TADS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
};

struct lista{
    tipo* inicio_listaTipo;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                               FUNÇÕES LOCAIS - ENCAPSULADAS ~ PRIVATE.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BACK-END
void criaEstoquePadraoTipoRemedio(lista* l);
void criaEstoquePadraoRemedio(lista* l);
void inserirTipo(lista* l, char tip[max+1]);
void inserirMedicamento(lista* l, char nome_med[max+1], char preco[10+1], int quant_estoque, int exigencia_receita, char tipoMed[max+1]);
tipo* ultimoElemTipo(lista* l);
tipo* NoTipoEspecifico(lista* l, char tipoMed[max+1]);
int tipoExiste(lista* l, char tipoMed[max+1]);
void inserirMed_na_lista(tipo* tipo_de_remedio, med* medicacao);
med* ultimoElemMed(tipo* tipo_de_remedio, med* medicacao);
void liberaLista(lista* l);
void deletarMedicamento(lista* l, med* medicacao, tipo* tipo_de_remedio);
void retirarDuplicata(lista* l, char tipoMed[max+1], char nome_med[max+1]);

// FRONT-END
void menuCascata(lista* l, int contMenuPrincipal);
void submenu(lista* l, tipo* tipo_de_remedio, int contMenuPrincipal);
void menuInfo(lista* l, med* medicacao, int contMenuPrincipal);
void pesquisarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void removerMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void adicionarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void alterarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void alterarMedicamentoSucesso(lista* l, int contMenuPrincipal, char nome_med[max+1]);
void repoRecusada(lista* l, med* medicacao, int contMenuPrincipal);
void repoSucesso(lista* l, med* medicacao, int contMenuPrincipal);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                      IMPLEMENTAÇÃO DAS FUNÇÕES.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                        FRONT-END  -  Função do Menu Principal do Programa.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuPrincipal(int contMenuPrincipal, lista* l){
    contMenuPrincipal++;
    system("clear");
    printf("=========================================================================================\n");
    printf("\n\t\tSeja bem vindo ao Sistema de Controle de Estoque!\n");
    printf("\t\t-------------------------------------------------\n\n\n");
    printf(" Por favor, selecione a opção desejada:\n\n");
    printf(" 1 - Buscar Medicamento.\n");
    printf(" 2 - Pesquisar Medicamento.\n");
    printf(" 3 - Remover Medicamento.\n");
    printf(" 4 - Adicionar Novo Medicamento.\n");
    printf(" 5 - Alterar Medicamento.\n");
    printf(" 6 - Sair.\n");
    printf("=========================================================================================\n");
    printf("Opção: ");

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
        system("clear");
        printf("Digite o nome do medicamento que deseja pesquisar:\n\n");
        printf("--> ");
        scanf("%s", nome_med);
        pesquisarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 3){
        char nome_med[max+1];
        system("clear");
        printf("Digite o nome do medicamento que deseja remover:\n\n");
        printf("--> ");
        scanf("%s", nome_med);
        removerMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 4){
        char nome_med[max+1];
        system("clear");
        printf("Digite o nome do medicamento que deseja adicionar:\n\n");
        printf("--> ");
        scanf("%s", nome_med);
        adicionarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 5){
        char nome_med[max+1];
        system("clear");
        printf("Digite o nome do medicamento que deseja alterar:\n\n");
        printf("--> ");
        scanf("%s", nome_med);
        alterarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 6){
        liberaLista(l);
        system("clear");
        printf("\n\n\t\t--------- SISTEMA ENCERRADO ---------\n\n\n\n\n");
        printf("Muito Obrigado! :)\n\n");
        return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                      Função para inicializar a lista.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
lista* criaLista(){
    lista* l = (lista*) malloc(sizeof(lista));
    l->inicio_listaTipo = NULL;
    
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     BACK-END  -  Função para criar nosso "Estoque Atual" ou "Estoque existente" -> TIPOS.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void criaEstoquePadraoTipoRemedio(lista* l){
    inserirTipo(l, "Analgesico");
    inserirTipo(l, "Anfetamina");
    inserirTipo(l, "Antiacido");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                BACK-END  -  Função Local para criar nosso "Estoque Atual" ou "Estoque existente" -> MEDICAMENTOS.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void criaEstoquePadraoRemedio(lista* l){
    inserirMedicamento(l, "Paracetamol", "12,00", 80, 0, "Analgesico");
    inserirMedicamento(l, "Dipirona", "4,50", 9, 0, "Analgesico");

    inserirMedicamento(l, "Venvanse", "257,00", 94, 1, "Anfetamina");
    inserirMedicamento(l, "Ritalina", "40,00", 50, 1, "Anfetamina");

    inserirMedicamento(l, "Engov", "5,35", 320, 0, "Antiacido");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 BACK-END  -  Função para inserir um nó (tipo) na lista de Tipos de medicamentos.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inserirTipo(lista* l, char tip[max+1]){
    tipo* novo_tipo = (tipo*) malloc(sizeof(tipo));
    strcpy(novo_tipo->tip, tip);
    novo_tipo->inicio_lista_med = NULL;
    novo_tipo->next = NULL;
    
    if(l->inicio_listaTipo == NULL){
        l->inicio_listaTipo = novo_tipo;
    }
    else{
        tipo* ultimo = ultimoElemTipo(l);
        ultimo->next = novo_tipo;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                BACK-END  -  Função para retornar último elemento da lista de tipos de remédio.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tipo* ultimoElemTipo(lista* l){
    tipo* tempTipo = l->inicio_listaTipo;
    while(tempTipo->next != NULL){
        tempTipo = tempTipo->next;
    }
    return tempTipo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       BACK-END  -  Função para inserir um Remedio em sua lista especifica de acordo com seu Tipo.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inserirMedicamento(lista* l, char nome_med[max+1], char preco[10+1], int quant_estoque, int exigencia_receita, char tipoMed[max+1]){
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
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    BACK-END  -  Função auxiliar da função inserirMedicamento usada para inserir remedio na sua respectiva lista.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inserirMed_na_lista(tipo* tipo_de_remedio, med* medicacao){
    if(tipo_de_remedio->inicio_lista_med == NULL){
        tipo_de_remedio->inicio_lista_med = medicacao;
    }
    else{
        med* tempMed = ultimoElemMed(tipo_de_remedio, medicacao);
        tempMed->next = medicacao;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                    BACK-END  -  Função auxiliar da função inserirMed_na_lista para retornar o último elemento da lista de medicamentos do tipo especificado.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
med* ultimoElemMed(tipo* tipo_de_remedio, med* medicacao){
    med* tempMed = tipo_de_remedio->inicio_lista_med;
    while(tempMed->next != NULL){
        tempMed = tempMed->next;
    }
    return tempMed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                              BACK-END  -  Função para retornar 1 se o tipo especificado de medicamento existe e 0 caso não exista no sistema.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                            BACK-END  -  Função para retornar o nó do tipo de medicamento especificado.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
tipo* NoTipoEspecifico(lista* l, char tipoMed[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    while(strcmp(tempTipo->tip, tipoMed) != 0 && tempTipo != NULL){
        tempTipo = tempTipo->next;
    }
    if(tempTipo == NULL){
        printf("\n\t\t**MEDICAMENTO ESPECIFICADO NÃO EXISTE EM ESTOQUE**\n\n\n\n");
        printf("Digite 1 para continuar a execução do programa\n\n");
        printf("--> ");
        int input;
        scanf("%d", &input);
        if(input == 1){
            return NULL;
        }
    }
    else if(strcmp(tempTipo->tip, tipoMed) == 0){
        return tempTipo;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          FRONT-END  -  Menu que disponibiliza lista de tipos de remédio para seleção.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuCascata(lista* l, int contMenuPrincipal){
    system("clear");
    tipo* tempTipo = l->inicio_listaTipo;
    printf("Selecione o tipo de medicação desejado:\n\n");
    int i;
    for(i = 1;tempTipo != NULL;i++){
        printf("%d - %s\n", i, tempTipo->tip);
        tempTipo = tempTipo->next;
    }
    printf("\n0 - Voltar ao Menu Principal\n");
    printf("=========================================\n");
    printf("Opção: ");

    int input;
    scanf("%d", &input);
    
    if(input == 0){
        menuPrincipal(contMenuPrincipal, l);
    }

    tempTipo = l->inicio_listaTipo;
    for(i = 1;tempTipo != NULL;i++){
        if(i == input){
            submenu(l, tempTipo, contMenuPrincipal);
        }
        tempTipo = tempTipo->next;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 FRONT-END  -  Menu que disponibiliza lista de remédios (do tipo selecionado no menu anterior) para seleção.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void submenu(lista* l, tipo* tipo_de_remedio, int contMenuPrincipal){
    system("clear");
    med* tempMed = tipo_de_remedio->inicio_lista_med;
    printf("Selecione o %s desejado:\n\n", tipo_de_remedio->tip);
    int i;
    for(i = 1;tempMed != NULL;i++){
        printf("%d - %s\n", i, tempMed->nome_med);
        tempMed = tempMed->next;
    }
    if(tipo_de_remedio->inicio_lista_med == NULL){
        printf("\n--> Não há nenhum medicamento do tipo '%s' em estoque no momento!\n", tipo_de_remedio->tip);
        printf("-------------------------------------------------------------------------\n\n\n");
    }
    printf("\n0 - Voltar ao Menu Principal\n");
    printf("=========================================\n");
    printf("Opção: ");

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         FRONT-END  -  Menu que disponibiliza informações e opções do medicamento selecionado.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuInfo(lista* l, med* medicacao, int contMenuPrincipal){
    system("clear");
    printf("\t\tInformações e Opções do medicamento:\n\n\n");
    printf("\t  %s\n", medicacao->nome_med);
    printf("--------------------------------\n");
    printf("Preço: R$%s\n", medicacao->preco);
    printf("Quantidade em Estoque: %d\n", medicacao->quant_estoque);
    printf("Tipo de Medicamento: %s\n", medicacao->tipoMed);
    if(medicacao->exigencia_receita == 1){
        printf("Exige Receita Médica? - SIM\n");
    }
    else{
        printf("Exige Receita Médica? - NÃO\n");
    }
    printf("--------------------------------\n\n\n");
    printf("1 - Solicitar Reposição de Estoque\n");
    printf("0 - Voltar ao Menu Principal\n");
    printf("=====================================\n");
    printf("Opção: ");

    int input, entrada;
    scanf("%d", &input);

    if(input == 0){
        menuPrincipal(contMenuPrincipal, l);
    }
    if(input == 1){
        if(medicacao->quant_estoque > 10){
            repoRecusada(l, medicacao, contMenuPrincipal);
        }
        else{
            system("clear");
            printf("Por favor, digite a quantidade de '%s' que deseja adicionar ao estoque:\n\n", medicacao->nome_med);
            printf("--> ");

            int input;
            scanf("%d", &input);
            medicacao->quant_estoque += input;
            repoSucesso(l, medicacao, contMenuPrincipal);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             FRONT-END  -  Função auxiliar da função menuInfo usada para tela de Reposição Recusada.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void repoRecusada(lista* l, med* medicacao, int contMenuPrincipal){
    system("clear");
    printf("\n\t\t\t\t***REPOSIÇÃO RECUSADA***\n\n");
    printf("-----------------------------------------\n");
    printf("A resposição de estoque só é permitida\ncaso a quantidade do medicamento\nem estoque seja 10 ou menos!\n");
    printf("-----------------------------------------\n\n");
    printf("2 - Voltar as informações do medicamento buscado\n");
    printf("0 - Voltar ao Menu Principal\n");
    printf("=====================================\n");
    printf("Opção: ");
    int entrada;
    scanf("%d", &entrada);
    if(entrada == 2){
        menuInfo(l, medicacao, contMenuPrincipal);
    }
    else if(entrada == 0){
        menuPrincipal(contMenuPrincipal, l);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       FRONT-END  -  Função auxiliar da função repoAceita para tela de medicamento reestocado com sucesso!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void repoSucesso(lista* l, med* medicacao, int contMenuPrincipal){
    system("clear");
    printf("\n\t\t\t\t***MEDICAMENTO REESTOCADO!***\n\n\n\nNova quantidade em estoque: %d\n", medicacao->quant_estoque);
    printf("-------------------------------\n\n\n");
    printf("==================================================\n");
    printf(" 2 - Voltar as informações do medicamento buscado\n");
    printf(" 0 - Voltar ao Menu Principal\n");
    printf("==================================================\n");
    printf("Opção: ");
    
    int entrada;
    scanf("%d", &entrada);

    if(entrada == 2){
        menuInfo(l, medicacao, contMenuPrincipal);
    }
    else if(entrada == 0){
        menuPrincipal(contMenuPrincipal, l);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 FRONT-END  -  Função para pesquisar produto diretamente via string de busca.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        printf("\n\t\t***MEDICAMENTO PESQUISADO NÃO EXISTE EM ESTOQUE***\n\n\n\n");
        printf("Medicamento Pesquisado: %s\n", nome_med);
        printf("-------------------------------\n\n\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("==============================\n");
        printf("\nOpção: ");
        int input;
        scanf("%d", &input);
        if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         FRONT-END  -  Função para remover medicamento do estoque.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
                printf("\n\t\t --- MEDICAMENTO REMOVIDO COM SUCESSO!! ---\n\n\n\n");
                printf("Medicamento Removido: %s\n", nome_med);
                printf("-------------------------------\n\n\n");
                printf("0 - Voltar ao Menu Principal\n");
                printf("==============================\n");
                printf("\nOpção: ");
                int input;
                scanf("%d", &input);
                if(input == 0){
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
        printf("\n\t\t***MEDICAMENTO SOLICITADO PARA REMOÇÃO NÃO EXISTE EM ESTOQUE***\n\n\n\n");
        printf("Medicamento Solicitado: %s\n", nome_med);
        printf("-------------------------------\n\n\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("==============================\n");
        printf("\nOpção: ");
        int input;
        scanf("%d", &input);
        if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                             BACK-END  -  Função para efetivamente deletar medicamento na lista (Função auxiliar da função acima - removerMedicamento).
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void deletarMedicamento(lista* l, med* medicacao, tipo* tipo_de_remedio){
    med* tempMed = tipo_de_remedio->inicio_lista_med;

    if(medicacao == tipo_de_remedio->inicio_lista_med){
        if(tempMed->next == NULL){
            free(medicacao);
            tipo_de_remedio->inicio_lista_med = NULL;
            return;
        }
        else{
            tipo_de_remedio->inicio_lista_med = medicacao->next;
            free(medicacao);
            return;
        }
    }
    else{
        while(tempMed->next != medicacao){
            tempMed = tempMed->next;
        }
        
        tempMed->next = medicacao->next;
        free(medicacao);
        return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          FRONT-END  -  Função para adicionar novo medicamento ao estoque.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void adicionarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    int aux = 0;

    while(tempTipo != NULL){
        while(tempMed != NULL){
            if(strcmp(nome_med, tempMed->nome_med) == 0){
                aux = 1;
                system("clear");
                printf("\n\t--> MEDICAMENTO SOLICITADO PARA ADIÇÃO JÁ EXISTE EM ESTOQUE! <--\n\n\n\n");
                printf("Medicamento Solicitado: %s\n", nome_med);
                printf("-------------------------------\n\n\n");
                printf("0 - Voltar ao Menu Principal\n");
                printf("==============================\n");
                printf("\nOpção: ");
                int input;
                scanf("%d", &input);
                if(input == 0){
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
        printf("Por favor, insira os seguintes campos: \n\n");

        printf("----------------------------------\n");
        printf("Preço: ");
        char preco[11];
        scanf("%s", preco);
        printf("\n");

        printf("Quantidade de medicamentos: ");
        int quant_estoque;
        scanf("%d", &quant_estoque);
        printf("\n");

        printf("-----------------------\n");
        printf("1 caso SIM, 0 caso NÃO\n");
        printf("-----------------------\n");
        printf("Exigência de Receita*: ");
        int exigencia_receita;
        scanf("%d", &exigencia_receita);
        printf("\n\n");

        printf("Tipo de medicamento: ");
        char tipoMed[max+1];
        scanf("%s", tipoMed);
        printf("\n\n");

        inserirMedicamento(l, nome_med, preco, quant_estoque, exigencia_receita, tipoMed);

        system("clear");
        printf("\n\t\t--> Novo medicamento inserido em estoque com sucesso!! <--\n\n\n\n");
        printf("Medicamento Inserido: %s\n", nome_med);
        printf("---------------------------------\n\n\n");
        printf("2 - Ver informações do remédio adicionado\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("===========================================\n");
        int input;
        scanf("%d", &input);

        if(input == 2){
            pesquisarMedicamento(l, contMenuPrincipal, nome_med);
        }
        else if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  FRONT-END  -  Função para alterar dados de um medicamento já existente no estoque.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alterarMedicamento(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    int aux = 0; // variável auxiliar usada pra impedir que a função tente acessar um local de memória não alocado

    while(tempTipo != NULL){
        while(tempMed != NULL){
            if(strcmp(nome_med, tempMed->nome_med) == 0){
                aux = 1;
                system("clear");
                printf("Por favor, selecione o campo do medicamento que deseja alterar: \n\n");

                printf("1 - Nome\n");
                printf("2 - Preço\n");
                printf("3 - Quantidade em estoque\n");
                printf("4 - Exigência de receita médica\n");
                printf("5 - Tipo de medicamento\n");
                printf("0 - Voltar ao Menu Principal\n");
                printf("========================================\n\n");
                printf("Opção: ");

                int campo;
                scanf("%d", &campo);

                if(campo == 1){
                    system("clear");
                    printf("Por favor, digite o novo nome do medicamento:\n\n");
                    printf("--> ");
                    char nome[max+1];
                    scanf("%s", nome);
                    strcpy(tempMed->nome_med, nome);

                    alterarMedicamentoSucesso(l, contMenuPrincipal, tempMed->nome_med);
                }
                else if(campo == 2){
                    system("clear");
                    printf("Por favor, digite o novo preço do medicamento:\n\n");
                    printf("--> ");
                    char preco[11];
                    scanf("%s", preco);
                    strcpy(tempMed->preco, preco);

                    alterarMedicamentoSucesso(l, contMenuPrincipal, tempMed->nome_med);
                }
                else if(campo == 3){
                    system("clear");
                    printf("Por favor, digite a nova quantidade em estoque:\n\n");
                    printf("--> ");
                    int quant_estoque;
                    scanf("%d", &quant_estoque);
                    tempMed->quant_estoque = quant_estoque;

                    alterarMedicamentoSucesso(l, contMenuPrincipal, tempMed->nome_med);
                }
                else if(campo == 4){
                    system("clear");
                    printf("Por favor, digite o nova exigência do medicamento em relação a receita médica:\n\n");
                    printf("-----------------------\n");
                    printf("1 caso SIM, 0 caso NÃO\n");
                    printf("-----------------------\n");
                    printf("Exigência de Receita: ");
                    int exigencia_receita;
                    scanf("%d", &exigencia_receita);
                    tempMed->exigencia_receita = exigencia_receita;

                    alterarMedicamentoSucesso(l, contMenuPrincipal, tempMed->nome_med);
                }
                else if(campo == 5){
                    system("clear");
                    printf("Por favor, digite o novo tipo do medicamento:\n\n");
                    printf("--> ");
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
                    inserirMed_na_lista(tempTipo, tempMed); // Colocando o medicamento na lista que ele deve passar a pertencer!!

                    // Retirar a duplicata do medicamento do antigo tipo a qual pertencia!
                    retirarDuplicata(l, stringAuxTipoMed, tempMed->nome_med);

                    alterarMedicamentoSucesso(l, contMenuPrincipal, tempMed->nome_med);
                }
                else if(campo == 0){
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
        printf("\n\t\t***MEDICAMENTO PESQUISADO NÃO EXISTE EM ESTOQUE***\n\n\n\n");
        printf("Medicamento Pesquisado: %s\n", nome_med);
        printf("-------------------------------\n\n\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("==============================\n");
        printf("\nOpção: ");
        int input;
        scanf("%d", &input);
        if(input == 0){
            menuPrincipal(contMenuPrincipal, l);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             FRONT-END  -  Função auxiliar da função alterarMedicamento para tela de sucesso.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alterarMedicamentoSucesso(lista* l, int contMenuPrincipal, char nome_med[max+1]){
    system("clear");
    printf("\n\t\t--> Medicamento alterado com sucesso!! <--\n\n\n\n");
    printf("Medicamento Alterado: %s\n", nome_med);
    printf("---------------------------------\n\n\n");
    printf("2 - Ver informações do remédio alterado\n");
    printf("0 - Voltar ao Menu Principal\n");
    printf("=========================================\n");

    int input;
    scanf("%d", &input);

    if(input == 2){
        pesquisarMedicamento(l, contMenuPrincipal, nome_med);
    }
    else if(input == 0){
        menuPrincipal(contMenuPrincipal, l);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                 BACK-END  -  Função auxiliar da função alterarMedicamento usada para retirar medicamento duplicado em dois tipos diferentes (duas listas diferentes).
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void retirarDuplicata(lista* l, char tipoMed[max+1], char nome_med[max+1]){
    tipo* tempTipo = l->inicio_listaTipo;
    med* tempMed = tempTipo->inicio_lista_med;
    med* auxMed;

    while(tempTipo != NULL){
        if(strcmp(tempTipo->tip, tipoMed) == 0){
            if(strcmp(tempTipo->inicio_lista_med->nome_med, nome_med) == 0){
                if(tempTipo->inicio_lista_med->next == NULL){
                    tempTipo->inicio_lista_med = NULL;
                    return;
                }
                else{
                    auxMed = tempTipo->inicio_lista_med;
                    tempTipo->inicio_lista_med = tempTipo->inicio_lista_med->next; // THIS
                    auxMed->next = NULL;
                    return;
                }
            }
            while(tempMed != NULL){
                if(strcmp(tempMed->next->nome_med, nome_med) == 0){
                    auxMed = tempMed->next;
                    tempMed->next = tempMed->next->next;
                    auxMed->next = NULL;
                    return;
                }
                tempMed = tempMed->next;
            }
        }
        tempTipo = tempTipo->next;
        if(tempTipo == NULL) break;
        tempMed = tempTipo->inicio_lista_med;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                BACK-END  -  Função para desalocar memória.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                 Fim do programa!!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                       Desenvolvedor: Matheus Diniz Alencar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////