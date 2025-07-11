#include <iostream>

#include "controllers/PagamentoController.hpp"
#include "controllers/PedidoController.hpp"
#include "controllers/ProdutoController.hpp"

#include "Pedido.hpp"
#include "Pagamento.hpp"
#include "Produto.hpp"

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <iomanip>

using namespace std;

int main() {
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();

cors.global()
    .methods("POST"_method, "GET"_method, "OPTIONS"_method, "PUT"_method)
    .origin("*")  // pode ser "http://localhost:8000" se quiser restringir
    .headers("Content-Type");

    //erickson

    PedidoController pedidoController;
    PagamentoController pagamentoController;
    ProdutoController produtoController;

    CROW_ROUTE(app, "/")([](){
        return "Bem vindos ao projeto FOODBASE!!!!";
    });

    CROW_ROUTE(app, "/pedido").methods("POST"_method)([&](const crow::request& req) -> crow::response {
        const auto body = crow::json::load(req.body);

        if (!body) {
            std::cerr << "[ERROR] JSON inválido" << std::endl;
            return {400, "JSON inválido"};
        }

        try {
            // ===== Produto =====
            std::string nmProduto = body["pedido"]["produto"]["nmProduto"].s();
            std::string dsProduto = body["pedido"]["produto"]["dsProduto"].s();
            std::string stProduto = body["pedido"]["produto"]["stProduto"].s();
            double vlProduto = body["pedido"]["produto"]["vlProduto"].d();

            Produto produto(nmProduto, dsProduto, vlProduto, stProduto);
            produto = produtoController.salvarProduto(produto);
            std::cout << "[INFO] Produto salvo com ID: " << produto.getCdProduto() << std::endl;

            // ===== Pagamento =====
            std::string tpPagamentoStr = body["pedido"]["pagamento"]["tpPagamento"].s();
            double vlPagamento = body["pedido"]["pagamento"]["vlPagamento"].d();

            TipoPagamentoEnum tipo = toEnum(tpPagamentoStr[0]);
            Pagamento pagamento(tipo, vlPagamento);
            pagamento = pagamentoController.salvarPagamento(pagamento);
            std::cout << "[INFO] Pagamento salvo com ID: " << pagamento.getCdPagamento() << std::endl;

            // ===== Pedido =====
            std::string stPedido = body["pedido"]["stPedido"].s();
            Pedido pedido(&pagamento, &produto, stPedido);
            pedido = pedidoController.salvarPedido(pedido);
            std::cout << "[INFO] Pedido salvo com ID: " << pedido.getCdPedido() << std::endl;

            // ===== Resposta =====
            std::ostringstream ossPagamento, ossProduto;
            ossPagamento << std::fixed << std::setprecision(2) << pagamento.getVlPagamento();
            ossProduto << std::fixed << std::setprecision(2) << produto.getVlProduto();

            crow::json::wvalue resposta;
            resposta["mensagem"] = "Pedido salvo com sucesso!";
            resposta["pedido"]["cdPedido"] = pedido.getCdPedido();
            resposta["pedido"]["stPedido"] = pedido.getStPedido();

            resposta["pedido"]["pagamento"]["cdPagamento"] = pagamento.getCdPagamento();
            resposta["pedido"]["pagamento"]["vlPagamento"] = ossPagamento.str();
            resposta["pedido"]["pagamento"]["tpPagamento"] = std::string(1, toChar(pagamento.getTpPagamento()));

            resposta["pedido"]["produto"]["cdProduto"] = produto.getCdProduto();
            resposta["pedido"]["produto"]["nmProduto"] = produto.getNmProduto();
            resposta["pedido"]["produto"]["dsProduto"] = produto.getDsProduto();
            resposta["pedido"]["produto"]["vlProduto"] = ossProduto.str();
            resposta["pedido"]["produto"]["stProduto"] = produto.getStProduto();

            return crow::response{201, resposta};
            try {
    TipoPagamentoEnum tipo = toEnum(tpPagamentoStr[0]);
} catch (const std::exception& e) {
    std::cerr << "[ERRO] toEnum falhou: " << e.what() << std::endl;
    return crow::response{400, "Tipo de pagamento inválido"};
}

        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Exceção ao salvar pedido: " << e.what() << std::endl;
            return {500, std::string("Erro ao salvar pedido: ") + e.what()};
        }
    });

    CROW_ROUTE(app, "/pedido/<int>").methods("PUT"_method)([&](const crow::request& req, int cdPedido) -> crow::response {
        try {
            auto body = crow::json::load(req.body);
            if (!body) {
                return crow::response(400, "JSON inválido.");
            }

            // valida e xtrai campos do JSON
            std::string stPedido = body["pedido"]["stPedido"].s();

            // objeto pagamento
            int cdPagamento = body["pedido"]["pagamento"]["cdPagamento"].i();
            double vlPagamento = body["pedido"]["pagamento"]["vlPagamento"].d();
            std::string tpPagamentoStr = body["pedido"]["pagamento"]["tpPagamento"].s();

            TipoPagamentoEnum tipo = toEnum(tpPagamentoStr[0]);

            // Criar objetos
            Pagamento pagamento = Pagamento(cdPagamento, tipo, vlPagamento);
            Pedido pedido(cdPedido, &pagamento, stPedido);

            // Atualiza pedido
            pedidoController.atualizarPedido(pedido);

            std::ostringstream ossPagamento, ossProduto;

            crow::json::wvalue resposta;

            ossPagamento << std::fixed << std::setprecision(2) << pedido.getPagamento()->getVlPagamento();

            resposta["pedido"]["cdPedido"] = pedido.getCdPedido();
            resposta["pedido"]["stPedido"] = pedido.getStPedido();

            // pagamento dentro de pedidoo
            resposta["pedido"]["pagamento"]["cdPagamento"] = pedido.getPagamento()->getCdPagamento();
            resposta["pedido"]["pagamento"]["vlPagamento"] = ossPagamento.str();
            resposta["pedido"]["pagamento"]["tpPagamento"] = std::string(1, toChar(pedido.getPagamento()->getTpPagamento()));

            // // produto dentro de pedido
            // resposta["pedido"]["produto"]["cdProduto"] = pedido.getProduto()->getCdProduto();
            // resposta["pedido"]["produto"]["nmProduto"] = pedido.getProduto()->getNmProduto();
            // resposta["pedido"]["produto"]["dsProduto"] = pedido.getProduto()->getDsProduto();
            // resposta["pedido"]["produto"]["stProduto"] = pedido.getProduto()->getStProduto();
            // resposta["pedido"]["produto"]["vlProduto"] = ossProduto.str();
            resposta["pedido"]["mensagem"] = "Pedido atualizado com sucesso!";

            return crow::response{200, resposta};
        } catch (const std::exception& e) {
            return {500, std::string("Erro ao atualizar pedido: ") + e.what()};
        }
    });

    CROW_ROUTE(app, "/pedido/<int>").methods("GET"_method)([&](int cdPedido) -> crow::response {
        crow::json::wvalue resposta;

        Pedido pedido = pedidoController.buscarPedidoPorCd(cdPedido);

        std::ostringstream ossPagamento;
        std::ostringstream ossProduto;

        ossPagamento << std::fixed << std::setprecision(2) << pedido.getPagamento()->getVlPagamento();
        ossProduto << std::fixed << std::setprecision(2) << pedido.getProduto()->getVlProduto();

        resposta["pedido"]["cdPedido"] = pedido.getCdPedido();
        resposta["pedido"]["stPedido"] = pedido.getStPedido();

        // pagamento dentro de pedidoo
        resposta["pedido"]["pagamento"]["cdPagamento"] = pedido.getPagamento()->getCdPagamento();
        resposta["pedido"]["pagamento"]["vlPagamento"] = ossPagamento.str();
        resposta["pedido"]["pagamento"]["tpPagamento"] = std::string(1, toChar(pedido.getPagamento()->getTpPagamento()));

        // produto dentro de pedido
        resposta["pedido"]["produto"]["cdProduto"] = pedido.getProduto()->getCdProduto();
        resposta["pedido"]["produto"]["nmProduto"] = pedido.getProduto()->getNmProduto();
        resposta["pedido"]["produto"]["dsProduto"] = pedido.getProduto()->getDsProduto();
        resposta["pedido"]["produto"]["stProduto"] = pedido.getProduto()->getStProduto();
        resposta["pedido"]["produto"]["vlProduto"] = ossProduto.str();

        return crow::response{200, resposta};
    });

    app.port(18080).multithreaded().run();
}
