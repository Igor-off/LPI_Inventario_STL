#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"
#include <string>

class Produto {
private:
    std::string nome;       //< Nome do produto.
    double preco;           //< Preço do produto.
    Categoria categoria;    //< Categoria do produto.
    int estoque;            //< Quantidade de itens no estoque.

public:
 //=== Construtores
    /**
    * @param n_str Nome do produto (padrão: string vazia).
    * @param prc Preço do produto (padrão: 0.0).
    * @param cat Categoria do produto (padrão: Categoria::INDEFINIDA).
    * @param quantidade Quantidade de produtos no estoque (padrão: 0).
    */
    Produto(std::string n_str = "", double prc = 0., Categoria cat = Categoria::INDEFINIDA, int quantidade = 0);

 //=== Métodos setters
    /**
    * Define o nome do produto.
    * 
    * @param str Nome do produto.
    */
    void setNome(std::string str);
    /**
    * Define o preço do produto.
    * 
    * @param prc Preço do produto.
    */
    void setPreco(double prc);
    /**
    * Define a categoria do produto.
    * 
    * @param cat Categoria do produto.
    */
    void setCategoria(Categoria cat);
    /**
    * Define a quantidade de itens do produto no estoque.
    * 
    * @param quantidade Quantidade de itens em estoque.
    */
    void setEstoque(int quantidade);

 //=== Métodos getters
    /**
    * Retorna o nome do produto.
    * 
    * @return Nome do produto.
    */
    [[nodiscard]] std::string getNome() const;
    /**
    * Retorna o preço do produto.
    * 
    * @return Preço do produto.
    */
    [[nodiscard]] double getPreco() const;
    /**
    * Retorna a categoria do produto.
    * 
    * @return Categoria do produto.
    */
    [[nodiscard]] Categoria getCategoria() const;

    /**
    * Retorna a quantidade de itens do produto no estoque.
    * 
    * @return Quantidade de itens no estoque.
    */
    [[nodiscard]] int getEstoque() const;

 //=== Métodos de exibição
    /**
    * Exibe as informações do produto, incluindo nome, preço, categoria e quantidade no estoque.
    */
    void exibirProduto() const;

 //=== Operadores
    /**
    * Operador de comparação "menor que" para comparação de produtos. 
    * Compara o nome dos produtos.
    * 
    * @param outro Outro produto a ser comparado.
    * @return true se o nome do produto for lexicograficamente menor que o nome do outro produto, false caso contrário.
    */
    bool operator<(const Produto& outro) const;

    /**
    * Operador de comparação "igual a" para comparação de produtos.
    * Verifica se os dois produtos têm o mesmo nome e a mesma categoria.
    * 
    * @param outro Outro produto a ser comparado.
    * @return true se os produtos forem iguais, ou seja, se o nome e a categoria forem os mesmos, false caso contrário.
    */
    bool operator==(const Produto& outro) const;    // Para o método de remoção de produto
};

#endif
