#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <iostream>
#include <string>
#include <sstream>

//!< Categorias pré-definidas e aceitas.
enum class Categoria {
    BEBIDA = 0,
    CARNE,
    FRIO,
    GRAO,
    HORTIFRUTI,
    LATICINIO,
    LIMPEZA,
    MERCEARIA,
    PADARIA,
    INDEFINIDA
};
/**
*   Converte o tipo Categoria em string para impressão.
*   @param cat tipo Categoria a ser convertido
*/
inline std::string categoriaToString(Categoria cat) {
    switch(cat) {
        case Categoria::BEBIDA:        return "bebida";
        case Categoria::CARNE:         return "carne";
        case Categoria::FRIO:          return "frio";
        case Categoria::GRAO:          return "grao";
        case Categoria::HORTIFRUTI:     return "hortifruti";
        case Categoria::LATICINIO:     return "laticinio";
        case Categoria::LIMPEZA:        return "limpeza";
        case Categoria::MERCEARIA:      return "mercearia";
        case Categoria::PADARIA:        return "padaria";
        default:                        return "Indefinida";
    }
}

#endif