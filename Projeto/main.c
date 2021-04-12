#include "tad.h"

int main () {

    ///////////////////////////////
    // Nosso programa começa agora
    //////////////////////////////

    // função que chama o menu principal
    menuPrincipal();

    return 0;
}

/*                                      Busca em cascata!!
                                            /\    /\
    Nosso primeiro menu terá as opções: Buscar produto -> leva a um submenu listando os tipos de produto para seleção
                                                        -> após seleção de um tipo de produto, leva a um subsubmenu com uma lista de produtos daquele tipo para seleção
                                                        -> ao selecionar um produto que é daquele tipo dentre a lista de produtos deste tipo, ele entra em um último menu, um menu^3
                                                        -> neste menu^3 teremos algumas informações do produto disponibilizadas, como preço e quantidade em estoque
                                                        -> Informações e opções de cada produto: nome do produto, preço do produto, quantidade em estoque, exigência de receita sim ou não, ordernar reposição de estoque do produto
                                                        
                            "" "" "" -> pesquisar por produto através de chave de busca (string) - tipo de produto e nome do produto, afunilar busca.
                                                                 \/                   \/                  \/
                                                            Já lança direto o tipo de produto ou o nome do produto
                                                            \/     \/       \/      \/       \/      \/      \/
                                                            Dando o tipo de produto, eu já sei em qual lista procurar, na lista do tipo passado, aí com o nome do produto, eu só faço um search na lista daquele tipo específico procurando pelo nome passado.

                                    ->>>> Cada submenu terá a opção "voltar ao menu principal"


                                    -----> Ao ordernar reposição de estoque, checar se quantidade em estoque é <= 10, se for > 10, não permite reposição


Funcionalidades novas que podem ser boas:

    => Inserir novo tipo de remédio
    => Inserir novo remédio em tipo específico


*/