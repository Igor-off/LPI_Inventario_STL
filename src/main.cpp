#include "inventario.h"

#include <iostream>
#include <iomanip>

#define TESTE_INICIALIZADOR_ESTOQUE 0   //< Testar instância do estoque por lista inicializadora
#define TESTE_ADD_PRODUTO 0             //< Testar método de adição de produto ao estoque 
#define TESTE_REMOVER_PRODUTO 0         //< Testar método de remoção de produto ao estoque
#define TESTE_BUSCA_POR_NOME 0          //< Testar busca de produto por nome do produto
#define TESTE_BUSCA_POR_CATEGORIA 0     //< Testar a busca de produtos por categoria
#define TESTE_VENDA 0                   //< Testar venda de produto

Inventario criarEstoqueTeste();

int main(int arc, char* argv[]) {
#if TESTE_INICIALIZADOR_ESTOQUE    
    //  I   -   Inicialiar o estoque do inventário por meio da lista inicializadora no construtor
    Inventario i1 = criarEstoqueTeste();
    //  II  -   Exibir o estoque para verificar o construtor por lista inicializadora
    i1.exibirEstoque();
    //  III -   Verificar se o set de categorias e os mapas de contagem e valores por categoria atualizam corretamente quando criamos um estoque
    i1.exibirInventario();


#endif  // fim doTESTE_CONSTRUTOR_ESTOQUE

#if TESTE_ADD_PRODUTO
    //  I   -   Adicionar produtos por meio do método de adição de produtos da classe Inventario
    Inventario i2;
    std::cout   << std::string(90, '-') << std::endl
                << std::setw(28) << " " << std::left << "> Testar a primeira adição <" << std::endl;
    Produto p1("banana", 13.99, Categoria::HORTIFRUTI, 30);
    i2.addProduto(p1);
    //  II  -   Exibir o estoque para verificar se realmente adicionou
    i2.exibirEstoque();
    //  III -   Exibir o inventário para conferir o set de categorias e os mapas atualizando corretamente
    i2.exibirInventario();

    std::cout   << std::string(90, '-') << std::endl
                << std::setw(30) << " " << std::left << "> Testar a segunda adição <" << std::endl;
    Produto p2("creme dental", 3.99, Categoria::LIMPEZA, 20);
    i2.addProduto(p2);
    i2.exibirEstoque();
    i2.exibirInventario();

    std::cout   << std::string(90, '-') << std::endl
                << std::setw(30) << " " << std::left << "> Testar a terceira adição <" << std::endl;
    Produto p3("uva", 14.99, Categoria::HORTIFRUTI, 25);
    i2.addProduto(p3);
    i2.exibirEstoque();
    i2.exibirInventario();

#endif // fim doTESTE_CONSTRUTOR_ESTOQUE   

#if TESTE_REMOVER_PRODUTO
    Inventario i3 = criarEstoqueTeste();
    //  I   -   Exibir estoque e as informações do inventário atual antes da remoção
    std::cout   << std::setw(23) << " " << "> Testar primeira remoção de produto <" << std::endl
                << std::string(90, '-') << std::endl
                << "--> [8] file de frango inicia com 15 itens e deve ir para 14 após remoção." << std::endl
                << "--> [19] quinoa deve sumir pois tem apenas 1 item." << std::endl
                << "!!! Como quinoa é o único item da categoria grão, a categoria também deve sumir." << std::endl
                << std::string(90, '-') << std::endl
                << std::setw(30) << " " << "Estoque antes da remoção" << std::endl;
    i3.exibirEstoque();
    i3.exibirInventario();

    //  II  -   Remover produto
    std::string produtoA("quinoa");
    std::string produtoB("frango inteiro");
    try {
        i3.rmvProduto(produtoA);
        i3.rmvProduto(produtoB);
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    //  III  -   Exibir estoque após remoção
    //  Verificar se o set de categorias é atualizado
    //  como grão so possui um único produto, a categoria grão deve ser excluida.
    //  Além disso, os mapas de contagem e valores por categoria devem ser atualizados corretamente.
    std::cout << std::endl << std::setw(30) << " " << "Estoque após da remoção" << std::endl; 
    i3.exibirEstoque();
    i3.exibirInventario();

    //  IV  -   Testar caso da remoção do estoque vazio e o tratamento de erro
    //  Como não fiz um método para limpar o estoque vou criar outro vazio
    std::cout   << std::endl << std::setw(23) << " "  << "> Testar segunda remoção de produto <" << std::endl
                << std::string(90, '-') << std::endl
                <<  std::setw(25) << " "  << "Criando um segundo estoque vazio..." << std::endl
                << std::string(90, '-') << std::endl;
    Inventario i3vazio;
    try {
        i3vazio.rmvProduto(produtoA);
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

#endif  //  fim do TESTE_REMOVER_PRODUTO

#if TESTE_BUSCA_POR_NOME 
    Inventario i4 = criarEstoqueTeste();
    //  I   -   Usar o método buscarProduto() da classe Inventario
    //  Que retorna o Objeto Produto, caso o encontre
    //  ou um std::nullopt da classe optional da biblioteca STL

    //  I.I     -   Produto pertence ao estoque
    std::string produto_buscado("frango inteiro");
    auto resultado = i4.buscarProduto(produto_buscado); 
    if(resultado.has_value()) {
        resultado->exibirProduto();
        std::cout << std::endl;
    } else {
        i4.produtoNaoEncontrado(produto_buscado);
    }

    //  I.II    -   Produto não pertence ao estoque
    produto_buscado = "pessego";
    resultado = i4.buscarProduto(produto_buscado);
    if(resultado.has_value()) {
        resultado->exibirProduto();
    } else {
        i4.produtoNaoEncontrado(produto_buscado);
    }   

#endif // Fim do TESTE_BUSCA

#if TESTE_BUSCA_POR_CATEGORIA
    //  I   -   Criar o estoque e exibir para compararmos
    Inventario i5 = criarEstoqueTeste();
    i5.exibirEstoque();

    //  II      -   Filtrar produtos por categoria usando o método listarPorCategoria() da classe Inventario    
    //  Que retorna um vector com os produtos da mesma categoria encontrados
    //  ou um vector vazio, caso não tenha produtos da categoria indicada
    
    //  Além de imprimir os produtos da categoria indicada
    //  usar os métodos que retornam os valores dos mapas de contagem e de valor individual por categoria
    std::cout   << std::string(90, '-') << std::endl
                << "Testar a filtragem por categoria PADARIA" << std::endl;
    Categoria categoria_teste = Categoria::PADARIA;
    try {
        i5.exibirPorCategoria(categoria_teste);
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    
    std::cout   << std::endl
                << std::string(90, '-') << std::endl
                << "Testar filtragem por categoria não pertencente ao estoque no momento" << std::endl
                << std::string(90, '-') << std::endl;
    categoria_teste = Categoria::FRIO;
    try {
        i5.exibirPorCategoria(categoria_teste);
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
#endif // Fim do TESTE_BUSCA_POR_CATEGORIA   

#if TESTE_VENDA

    //  I   -   Inicializar inventário
    Inventario i6 = criarEstoqueTeste();
    i6.exibirEstoque();

    //  II  -   Vender um produto
    std::string produto_vendido("shampoo");
    int quantidade(10);
    try {
        i6.vender(produto_vendido, quantidade);
        i6.exibirHistoricoVenda();
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    //  III -   Vamos ver se o estoque atualizou corretamente
    std::cout   << std::endl 
                << std::setw(30) << " " << std::left << "Estoque atualizado" << std::endl;
    i6.exibirEstoque();

    //  IV  -   Vamos testar se retirarmos uma quantidade excedente
    quantidade = 20;
    try {
        i6.vender(produto_vendido, quantidade);
        i6.exibirHistoricoVenda();
    } catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

#endif // Fim do TEST_VENDA

    return EXIT_SUCCESS;
}

Inventario criarEstoqueTeste() {
    //  Categoria LIMPEZA
    std::vector<Produto> produtos = {
        //  Construtor Produto("nome", double preço, Categoria)
        //  Categoria LIMPEZA
        {"sabonete", 2.49, Categoria::LIMPEZA, 10},
        {"shampoo", 12.99, Categoria::LIMPEZA, 20},
        {"condicionador", 14.49, Categoria::LIMPEZA, 14},
        {"creme dental", 3.99, Categoria::LIMPEZA, 16},
        //  Categoria PADARIA
        {"pao de forma", 5.40, Categoria::PADARIA, 5},
        {"croissant", 2.99, Categoria::PADARIA, 12},
        {"bolo de cenoura", 15.99, Categoria::PADARIA, 5},
        {"pao de forma", 5.40, Categoria::PADARIA, 5},      //  Alguns eu dupliquei pra testar se incrimenta a quantidade corretamente
        //  Categoria CARNE
        {"frango inteiro", 12.99, Categoria::CARNE, 10},    //  Quando adicionar ao estoque deve ser apenas um produto com quantidade somadas
        {"frango inteiro", 12.99, Categoria::CARNE, 5},     //  Ou seja, em vez de 21 itens, teremos 19
        {"peito de peru", 19.99, Categoria::CARNE, 6},      //  O pão de forma tera (5 + 5) = 10 itens
        {"bife de alcatra", 34.99, Categoria::CARNE, 7},    //  e o file de peito tera (5 + 10) = 15 itens
        //  Categoria HORTIFRUTI
        {"abacaxi", 15.99, Categoria::HORTIFRUTI, 19},
        {"banana", 4.49, Categoria::HORTIFRUTI, 28},
        {"macã", 6.149, Categoria::HORTIFRUTI, 14},
        {"laranja", 5.99, Categoria::HORTIFRUTI, 19},
        //  Categoria LATICINIO
        {"leite", 4.49, Categoria::LATICINIO, 9},
        {"queijo", 29.99, Categoria::LATICINIO, 9},
        {"manteiga", 8.99, Categoria::LATICINIO, 12},
        {"iogurte", 2.99, Categoria::LATICINIO, 12},
        //  Categoria GRAO
        {"quinoa", 16.89, Categoria::GRAO, 1}
    };
    // Construtor Inventario que recebe vector para estoque inicializador
    Inventario inv(produtos);
    return inv;
}