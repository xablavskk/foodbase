#pragma once
#include "../controllers/PedidoController.hpp"
#include "../models/Pedido.hpp"
#include &lt;stdexcept&gt;
#include &lt;string&gt;

class PedidoService {
public:
    static Pedido criarPedidoComValidacao(int id, const std::string&amp; nome) {
        if(nome.empty()) {
            throw std::invalid_argument("Nome do pedido não pode ser vazio");
        }
        
        if(id <= 0) {
            throw std::invalid_argument("ID do pedido deve ser maior que zero");
        }
        
        try {
            // Verifica se pedido já existe
            Pedido existente = PedidoRepository::read(id);
            if(existente.getId() != 0) {
                throw std::runtime_error("Pedido com ID " + std::to_string(id) + " já existe");
            }
        } catch(const soci::soci_error&amp; e) {
            // Ignora erros de "não encontrado"
        }
        
        Pedido novoPedido(id, nome);
        PedidoRepository::create(novoPedido);
        return novoPedido;
    }
    
    static Pedido buscarPedidoSeguro(int id) {
        if(id <= 0) {
            throw std::invalid_argument("ID inválido para busca");
        }
        
        Pedido pedido;
        try {
            pedido = PedidoController::read(id);
        } catch(const soci::soci_error&amp; e) {
            throw std::runtime_error("Erro ao acessar banco de dados");
        }
        
        if(pedido.getId() == 0 || pedido.getName().empty()) {
            throw std::runtime_error("Pedido não encontrado");
        }
        return pedido;
    }
};

