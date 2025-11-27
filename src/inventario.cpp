#include "inventario.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <optional>
#include <iomanip>

//=== Classe Inventario

 //=== Construtores

    Inventario::Inventario() {}
    Inventario::Inventario(const std::vector<Produto>& ilista) { 
        //  I   -   Percorrer cada produto da lista inicializadora
        //  e, antes de fazer o push_back() para o estoque, verificar
        //  se o produto já ta no estoque, nesse caso apenas somar as quantidades no estoque
        for(const auto& iproduto : ilista) {
            addProduto(iproduto);
        }
    }

 //=== Métodos de adição e remoção de produtos ao estoque

    void Inventario::addProduto(const Produto& novo_produto) {
        //  I   -   Vamos percorrer o estoque de produtos
        //  Caso ja tenha o produto, apenas incrementamos a quantidade e atualizamos o valor total do estoque
        //  Caso contrário, damos um push_back().
        for(auto& produto : produtos_estocados) {
            if(novo_produto == produto) {
                produto.setEstoque( produto.getEstoque() + novo_produto.getEstoque() );
                attAddInventario(novo_produto);
                return;
            }
        }    
        produtos_estocados.push_back(novo_produto);
        categorias.insert(novo_produto.getCategoria());
        attAddInventario(novo_produto);
    }
    void Inventario::rmvProduto(const std::string& nome) {
        //  I   -   Se o estoque estiver vazio, não tem como retirar produto.
        if(produtos_estocados.empty()) {
            throw std::runtime_error(">>> O estoque está vazio, não é possível remover produto.");
        }
        //  II  -   Se tiver algum produto em estoque, percorré-los.
        //  Escolhi percorrer inversamente pois caso o último produto do array for removido
        //  teriamos o equivalente ao pop_back() com complexidade temporal O(1).
        bool encontrado{false};
        for(int i = (produtos_estocados.size() - 1); i >= 0; --i) {  
            if(produtos_estocados[i].getNome() == nome) {
        //  III.I   -   Se a quantidade for igual a 1, removemos o produto do estoque
        //  III.II  -   Se a quantidade for maior que 1, apenas decrementamos a quantidade no estoque
                if(produtos_estocados[i].getEstoque() > 1) {
                    // Subtrair a quantidade
                    produtos_estocados[i].setEstoque((produtos_estocados[i].getEstoque() - 1));
                } else { // Se a  quantidade de item for igual a 1
                    // Tirar esse produto da vector do estoque
                    produtos_estocados.erase(produtos_estocados.begin() + i);
                }
                //  IV  -   Em todos os casos atualizamos o valor total do estoque, set de categorias, mapas de contagem e valor por categora após remoção de um único produto do estoque
                attRmvInventario(produtos_estocados[i]);
                encontrado = true;
                break; // Vamos remover apenas o primeiro elemento encontrado, então usamod break caso a condição seja verdadeira
            }
        }
        if(!encontrado) {
            // Se não achou o produto informar que o produto não faz parte do estoque
            throw std::runtime_error(">>> O produto informado não faz parte do estoque");
        }
    }
    void Inventario::vender(const std::string& nome_do_produto, int quantidade) {
        //  I   -   Procurar o produto no estoque do inventário
        auto produto_a_vender = buscarProduto(nome_do_produto);
        //  II  -   Se encontrou o produto e a quantidade contida for menor ou igual a solicitada, retirá-las
        if(produto_a_vender.has_value()) {
            if(produto_a_vender->getEstoque() >= quantidade) {
                for(int i = 0; i < quantidade; ++i) {
                    rmvProduto(nome_do_produto);
                }
                //  III -   Adicionar os produto a list de histórico de vendas
                Produto h_produto{nome_do_produto, produto_a_vender->getPreco(), produto_a_vender->getCategoria(), quantidade};
                historico.push_back(h_produto);
            } else {
                throw std::runtime_error(">>> Só há " + std::to_string(produto_a_vender->getEstoque()) + " unidades disponíveis no estoque.");
            }
        //  Caso não encontre, tratar excessão
        } else {
            produtoNaoEncontrado(nome_do_produto);
        }
    }

 //=== Métodos de atualização do inventário

    void Inventario::attAddInventario(const Produto& produto) {
        //  I   -   Atualizar mapas de contagem por categoria e valor total por categoria após adição de produto
        contagem[produto.getCategoria()] += produto.getEstoque();
        valor_categoria[produto.getCategoria()] += (produto.getEstoque() * produto.getPreco()); 
    }
    void Inventario::attRmvInventario(const Produto& produto) {
        //  II      -   Atualizar set de categorias dos itens e os mapas de contagem e valor por categoria após remoção
        //  II.I    -   Se tiver apenas um  único item da categoria, limpar os campos
        if(contagem[produto.getCategoria()] == 1) {
            categorias.erase(produto.getCategoria());
            contagem.erase(produto.getCategoria());
            valor_categoria.erase(produto.getCategoria());
        //  II.II   -   Se tiver mais de um item, apenas subtrair o produto  removido
        } else {
            contagem[produto.getCategoria()] -= 1;
            valor_categoria[produto.getCategoria()] -= produto.getPreco();
        }
    }

 //==- Métodos getters

    [[nodiscard]] int Inventario::getContagem(const Categoria& cat) const { return contagem.at(cat); }
    [[nodiscard]] double Inventario::getValorIndividual(const Categoria& cat) const {  return valor_categoria.at(cat); }
    [[nodiscard]] double Inventario::getValorTotal() const {
        double valor_total{0};
        for(const auto& valor : valor_categoria) {
            valor_total += valor.second;
        }
        return valor_total;
    }
    [[nodiscard]] int Inventario::getQuantidadeProdutos() const {
        int quantidade_produtos{0};
        for(const auto& quantidade : contagem) {
            quantidade_produtos += quantidade.second;
        }
        return quantidade_produtos;
    }

 //=== Métodos de busca de produtos
    void Inventario::produtoNaoEncontrado(const std::string& nome) const {
        throw std::runtime_error(">> Produto \"" + nome + "\" não foi encontrado no estoque.");
    }

    [[nodiscard]]std::optional<Produto> Inventario::buscarProduto(const std::string& produto_procurado) const {
        // Percorrer todos os produtos do estoque procurando o produto pelo nome
        for(const auto& produto : produtos_estocados) {
            if(produto.getNome() == produto_procurado) {
                return produto;
            }
        }
        return std::nullopt;
    }

 //=== Métodos de exibição
    void Inventario::exibirEstoque()const {
        //  Cabeçalho do estoque
        std::cout   << std::string(90, '-') << std::endl
                    << std::setw(32) << " " << "Produtos estocados: " << getQuantidadeProdutos() << std::endl
                    << std::setw(27) << " " << "Valor total em estoque: R$ " << std::fixed << std::setprecision(2) << getValorTotal() << std::endl
                    << std::string(90, '-') << std::endl << std::endl;
        // Imprimir produtos no estoque
        size_t i = 1;
        for(const auto& produto : produtos_estocados) {
            std::cout << "[" << i << "] ";
            produto.exibirProduto();
            std::cout   << std::endl
                        << std::string(90, '=') << std::endl;
            ++i;
        }
        std::cout << std::endl;
    }

    void Inventario::exibirInventario() const {
        size_t i = 1;
        std::cout   << std::string(90, '-') << std::endl
                    << std::setw(24) << " " << std::left << "Categorias de itens existentes no estoque" << std::endl 
                    << std::string(90, '-') << std::endl << std::endl;
        for(const auto& categoria : categorias) {
            std::cout   << "[" << i << "] " << std::setw(12) << std::left << categoriaToString(categoria)
                        <<  "possui " << contagem.at(categoria) << " produtos somando R$: " << valor_categoria.at(categoria) << std::endl
                        << std::string(90, '=') << std::endl;
            ++i;
        }
    }

    void Inventario::exibirPorCategoria(const Categoria& categoria) const {
        std::vector<Produto> produtos_por_categoria;
        // I    -   verificar se essa categoria faz parte do set de categorias
        if(categorias.find(categoria) != categorias.end()) {
            // II   -   Se faz parte, pegar todos os produtos no estoque com essa categoria
            for(const auto& produto : produtos_estocados) {
                if(produto.getCategoria() == categoria) {
                    produtos_por_categoria.push_back(produto);
                }
            }
            // Formatação do cabeçalho da impressão
            std::cout   << std::string(90, '-') << std::endl << std::endl   // getContagem retorna par.second que representa a quantidade correspondente ao mapa com chave da categoria
                        << "Produtos da categoria " << categoriaToString(categoria) << ": " << getContagem(categoria) << std::endl
                        << std::string(90, '=') << std::endl;
            // Impressão dos produtos no vector lista filtrada
            for(const auto& produto : produtos_por_categoria) {
                produto.exibirProduto();
                std::cout << std::endl << std::string(90, '=') << std::endl;
            }
            // Imprimir valor total do estoque
            std::cout   << "Valor total em estoque: R$ "     // getValorIndividual retorna par.second que representa o valor correspondente ao mapa com a chave da categoria
                        << std::fixed << std::setprecision(2) << getValorIndividual(categoria) << std::endl << std::endl; 
        } else {
            // Se a categoria não faz parte do estoque no momento, tratar excessão
            throw std::runtime_error(">>> Não há produto com a categoria \"" + categoriaToString(categoria) + "\" no estoque.");
        }
    }

    void Inventario::exibirHistoricoVenda() const {
        double valor_vendas{0};
        std::cout   << std::string(90, '-') << std::endl
                    << std::setw(30) << " " << std::left << "Histórico de vendas" << std::endl
                    << std::string(90, '-') << std::endl << std::endl;
        for(const auto& produto : historico) {
            //  Na venda, a variável estoque se torna a quantidade de itens vendido
            valor_vendas += (produto.getPreco() * produto.getEstoque()); 
            produto.exibirProduto();
            std::cout << std::endl << std::string(90, '=') << std::endl;
        }
        //  II  -   Exibir valor total de vendar
        std::cout << "Valor total de vendas: R$ " << valor_vendas << std::endl;
    }

// Fim das implementações dos métodos da classe Inventario
