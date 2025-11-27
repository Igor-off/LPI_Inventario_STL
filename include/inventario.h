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
    Inventario();
    Inventario(const std::vector<Produto>& ilista);

    //=== Métodos de adição, remoção de produtos ao estoque e venda de produto
    void addProduto(const Produto& novo_produto);
    void rmvProduto(const std::string& nome);
    void vender(const std::string& produto, int quantidade);

    //=== Método de atualização das categorias
    void attAddInventario(const Produto& produto);
    void attRmvInventario(const Produto& produto);
    
    //==- Métodos getters
    [[nodiscard]]   int getContagem(const Categoria& cat) const;
    [[nodiscard]]   double getValorIndividual(const Categoria& cat) const;
    [[nodiscard]]   double getValorTotal() const;
    [[nodiscard]]   int getQuantidadeProdutos() const;
    
    //=== Métodos de busca de produtos
    void produtoNaoEncontrado(const std::string& nome) const;
    //=== Busca por nome
    [[nodiscard]]std::optional<Produto> buscarProduto(const std::string& produto_procurado) const;
    
    //=== Métodos de exibição
    void exibirEstoque() const;
    void exibirInventario() const;
    void exibirPorCategoria(const Categoria& categoria) const;
    void exibirHistoricoVenda() const;
};

#endif