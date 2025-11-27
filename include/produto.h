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

    //=== Contrutores
    Produto(std::string n_str = "", double prc = 0., Categoria cat = Categoria::INDEFINIDA, int quantidade = 0);

    //=== Métodos setters
    void setNome(std::string str);
    void setPreco(double prc);
    void setCategoria(Categoria cat);
    void setEstoque(int quantidade);

    //=== Métodos getters
    [[nodiscard]] std::string getNome() const;
    [[nodiscard]] double getPreco() const;
    [[nodiscard]] Categoria getCategoria() const;
    [[nodiscard]] int getEstoque() const;

    //=== Métodos de exibição
    void exibirProduto() const;

    //=== Operadores
    bool operator<(const Produto& outro) const;
    bool operator==(const Produto& outro) const;    // Para o método de remoção de produto
};


#endif