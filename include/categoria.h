#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <iostream>
#include <string>
#include <sstream>


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
inline std::ostream& operator<<(std::ostream& os, Categoria cat) {
    os << categoriaToString(cat);
    return os;
}

#endif