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
        db/db_config.h
        services/PedidoService.cpp
        services/PedidoService.hpp
        models/Pagamento.cpp
        models/Pagamento.hpp
        enums/TipoPagamentoEnum.hpp
)

target_link_libraries(MVC_Pedido ${PQXX_LIBRARIES})