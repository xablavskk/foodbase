cmake_minimum_required(VERSION 3.10)
project(MVC_Pedido)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(
        ${PQXX_INCLUDE_DIRS}
        config
        core
        models
        controllers
        views
)

add_executable(MVC_Pedido
        main.cpp
        db/Database.cpp
        models/Pedido.cpp
        controllers/PedidoController.cpp
        services/PedidoService.cpp
        services/PedidoService.hpp
        services/PagamentoService.cpp
        services/PagamentoService.hpp
        models/Pagamento.cpp
        enums/TipoPagamentoEnum.hpp
        controllers/PagamentoController.cpp
        resources/EnvLoader.cpp
)

target_link_libraries(MVC_Pedido ${PQXX_LIBRARIES})