#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "produto.h"
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <optional>

class Inventario {
private:
    // Estrutura proposta pelo exercício:
    std::vector<Produto> produtos_estocados;        //< Todos os produtos em estoque.
    std::set<Categoria> categorias;                 //< Categorias de itens existentes no estoque.
    std::map<Categoria, int> contagem;              //< Quantidade de produtos por categoria.
    std::map<Categoria, double> valor_categoria;    //< Valor total em estoque por categoria.
    std::list<Produto> historico;                   //< Histórico de produtos vendidos.
public:
 //=== Construtores
    /**
    * Construtor padrão. Inicializa o inventário vazio.
    */
    Inventario();
    /**
    * Construtor que inicializa o inventário com uma lista de produtos.
    * 
    * @param ilista Lista de produtos que serão adicionados ao estoque.
    */
    Inventario(const std::vector<Produto>& ilista);

 //=== Métodos de adição, remoção de produtos ao estoque e venda de produto
    /**
    * Adiciona um novo produto ao estoque ou atualiza a quantidade caso o produto já exista.
    * 
    * @param novo_produto Produto a ser adicionado ao estoque.
    */
    void addProduto(const Produto& novo_produto);
    /**
    * Remove um produto do estoque. Caso o produto tenha mais de 1 unidade, a quantidade é decrementada.
    * Caso contrário, o produto é removido completamente.
    * 
    * @param nome Nome do produto a ser removido.
    * @throws std::runtime_error Caso o produto não seja encontrado no estoque.
    */
    void rmvProduto(const std::string& nome);
    /**
    * Registra a venda de um produto. Se o estoque for suficiente, a quantidade do produto será diminuída.
    * 
    * @param produto Nome do produto a ser vendido.
    * @param quantidade Quantidade do produto a ser vendida.
    * @throws std::runtime_error Caso o produto não tenha estoque suficiente ou não seja encontrado.
    */
    void registrarvenda(const std::string& produto, int quantidade);

 //=== Método de atualização das categorias
    /**
    * Atualiza as informações de contagem e valor total de estoque após a adição de um produto.
    * 
    * @param produto Produto adicionado ao estoque.
    */
    void attAddInventario(const Produto& produto);
    /**
    * Atualiza as informações de contagem e valor total de estoque após a remoção de um produto.
    * 
    * @param produto Produto removido do estoque.
    */
    void attRmvInventario(const Produto& produto);
    
 //==- Métodos getters
    /**
    * Retorna a quantidade de produtos de uma determinada categoria.
    * 
    * @param cat Categoria desejada.
    * @return Quantidade de produtos na categoria.
    */
    [[nodiscard]]   int getContagem(const Categoria& cat) const;
    /**
    * Retorna o valor total dos produtos de uma categoria.
    * 
    * @param cat Categoria desejada.
    * @return Valor total dos produtos da categoria.
    */
    [[nodiscard]]   double getValorIndividual(const Categoria& cat) const;
    /**
     * Retorna o valor total de todos os produtos no estoque.
     * 
     * @return Valor total do estoque.
     */
    [[nodiscard]]   double getValorTotal() const;
    /**
    * Retorna a quantidade total de produtos em estoque, somando todos os itens.
    * 
    * @return Quantidade total de produtos.
    */
    [[nodiscard]]   int getQuantidadeProdutos() const;
    
 //=== Métodos de busca de produtos
    /**
    * Lança uma exceção caso um produto não seja encontrado no estoque.
    * 
    * @param nome Nome do produto.
    * @throws std::runtime_error Produto não encontrado.
    */
    void produtoNaoEncontrado(const std::string& nome) const;
    /**
    * Busca um produto no estoque pelo nome.
    * 
    * @param produto_procurado Nome do produto a ser procurado.
    * @return Produto encontrado ou std::nullopt se não encontrado.
    */
    [[nodiscard]]std::optional<Produto> buscarProduto(const std::string& produto_procurado) const;
    
 //=== Métodos de exibição
    /**
    * Exibe todos os produtos do estoque, junto com a quantidade e valor total.
    */
    void exibirEstoque() const;
    /**
    * Exibe um inventário geral, incluindo todas as categorias de produtos, suas quantidades e valores totais.
    */
    void exibirInventario() const;
    /**
    * Exibe todos os produtos de uma categoria específica.
    * 
    * @param categoria Categoria dos produtos a serem exibidos.
    * @throws std::runtime_error Se a categoria não existir no estoque.
    */
    void exibirPorCategoria(const Categoria& categoria) const;
    /**
    * Exibe o histórico de vendas realizadas, mostrando os produtos vendidos e o valor total da venda.
    */
    void exibirHistoricoVenda() const;
};

#endif