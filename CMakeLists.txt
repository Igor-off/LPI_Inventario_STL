cmake_minimum_required(VERSION 3.20) # Versão mínima do CMake
project(inventario VERSION 1.0 LANGUAGES CXX) # Nome e versão do projeto
# Definir padrão c++ moderno
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Definir fontes
add_executable(testes
    src/main.cpp
    src/inventario.cpp
    src/produto.cpp
)
# Incluir diretórios de headers
target_include_directories(testes PRIVATE include)