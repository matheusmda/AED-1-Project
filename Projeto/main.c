#include "tad.h"

int main () {

    ///////////////////////////////
    // Nosso programa começa agora
    //////////////////////////////

    int contMenuPrincipal = 0;
    lista* l = criaLista();

    // função que chama o menu principal
    menuPrincipal(contMenuPrincipal, l);

    return 0;
}

/*
                                                        
                        Pesquisar medicamento -> pesquisar por produto através de chave de busca (string) - tipo de produto e nome do produto, afunilar busca.
                                                                 \/                   \/                  \/
                                                            Já lança direto o tipo de produto ou o nome do produto
                                                            \/     \/       \/      \/       \/      \/      \/
                                                            Dando o tipo de produto, eu já sei em qual lista procurar, na lista do tipo passado, aí com o nome do produto, eu só faço um search na lista daquele tipo específico procurando pelo nome passado.

                                    ->>>> Cada submenu terá a opção "voltar ao menu principal"


                                    -----> Ao ordernar reposição de estoque, checar se quantidade em estoque é <= 10, se for > 10, não permite reposição


*/