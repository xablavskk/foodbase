#include <iostream>

#include "controllers/PagamentoController.hpp"
#include "Pedido.hpp"
#include "Pagamento.hpp"
#include "controllers/PedidoController.hpp"
#include <crow.h>
#include <iomanip>

using namespace std;

int main() {
    crow::SimpleApp app;

    PedidoController pedidoController;
    PagamentoController pagamentoController;

    CROW_ROUTE(app, "/")([](){
        return "Bem vindos ao projeto FOODBASE!!!!";
    });

    CROW_ROUTE(app, "/pedido").methods("POST"_method)([&](const crow::request& req) -> crow::response {
        std::cout << "[INFO] Rota /pedido chamada" << std::endl;

        const auto body = crow::json::load(req.body);
        if (!body) {
            std::cerr << "[ERROR] JSON inválido" << std::endl;
            return {400, "JSON inválido"};
        }

        try {
            std::string tpPagamentoStr = body["pagamento"]["tpPagamento"].s();
            double vlPagamento = (body["pagamento"]["vlPagamento"].d());

            std::cout << "[INFO] Tipo de pagamento recebido: " << tpPagamentoStr << std::endl;
            std::cout << "[INFO] Valor do pagamento recebido: " << vlPagamento << std::endl;

            TipoPagamentoEnum tipo = static_cast<TipoPagamentoEnum>(tpPagamentoStr[0]);

            std::cout << "[INFO] tipo do pagamento recebido: " << toChar(tipo) << std::endl;

            Pagamento pagamento = Pagamento(tipo, vlPagamento);
            pagamento = pagamentoController.salvarPagamento(pagamento);

            std::cout << "[INFO] Pagamento salvo com ID: " << pagamento.getCdPagamento() << std::endl;

            std::string stPedido = body["stPedido"].s();
            std::cout << "[INFO] Status do pedido: " << stPedido << std::endl;

            Pedido pedido(&pagamento, stPedido);
            pedido = pedidoController.salvarPedido(pedido, pagamento);

            std::cout << "[INFO] Pedido salvo com ID: " << pedido.getCdPedido() << std::endl;

            crow::json::wvalue resposta;

            resposta["mensagem"] = "Pedido salvo com sucesso!";
            resposta["pedido"]["cdPedido"] = pedido.getCdPedido();
            resposta["pedido"]["stPedido"] = pedido.getStPedido();
            resposta["pagamento"]["cdPagamento"] = pagamento.getCdPagamento();
            resposta["pagamento"]["tpPagamento"] = std::string(1, toChar(pagamento.getTpPagamento()));

            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << pagamento.getVlPagamento();
            resposta["pagamento"]["vlPagamento"] = oss.str();

            return crow::response{resposta};

        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Exceção ao salvar pedido: " << e.what() << std::endl;
            return {500, std::string("Erro ao salvar pedido: ") + e.what()};
        }
    });

    app.port(18080).multithreaded().run();
}
