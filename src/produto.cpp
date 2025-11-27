#include "produto.h"
#include <iostream>
#include <iomanip>

//=== Implementações dos métodos da classe Produto
 //=== Cobstrutores
    Produto::Produto(std::string n_str, double prc, Categoria c_str, int quant) 
    : nome(n_str), preco(prc), categoria(c_str), estoque(quant) {/*STUB*/}

    //=== Métodos setters
    void Produto::setNome(std::string n_str) { nome = n_str; }
    void Produto::setPreco(double prc) { preco = prc; }
    void Produto::setCategoria(Categoria catg) { categoria = catg; }
    void Produto::setEstoque(int quantidade) { estoque=  quantidade; }

 //=== Métodos getters
    [[nodiscard]] std::string Produto::getNome() const { return nome; }
    [[nodiscard]] double Produto::getPreco() const { return preco; }
    [[nodiscard]] Categoria Produto::getCategoria() const { return categoria; }
    [[nodiscard]] int Produto::getEstoque() const { return estoque; }

 //=== Métodos de exibição
    void Produto::exibirProduto() const {
        std::cout   << "Produto: " << nome 
                    << " | custa: R$ " << std::setprecision(2) << preco 
                    << " | categoria: " << categoriaToString(categoria)
                    << " | quantidade: " << estoque;
    }

 //=== Métodos operadores
    //  Necessário para ordenar por categoria em listas TAD que vamos usar no inventário
    bool Produto::operator<(const Produto& outro) const {
        return (categoria < outro.categoria);
    }
    //  Necessário para comparação e remoção do produto
    bool Produto::operator==(const Produto& outro) const { 
        return  nome == outro.nome &&
                categoria == outro.categoria &&
                preco == outro.preco;
    }