#include <iostream>

#include "controllers/PagamentoController.hpp"
#include "Pedido.hpp"
#include "ProdutoController.hpp"
#include "controllers/PedidoController.hpp"

using namespace std;

void mostrarMenuOpcao() {
    cout<<"\n===== MENU PEDIDO =====\n";
    cout << "1 - PRODUTO\n";
    cout << "2 - PEDIDO\n";
    cout << "3 - Sair\n";
    cout << "Escolha: ";
}

void mostrarMenu() {
    cout << "\n===== MENU PEDIDO =====\n";
    cout << "1 - Criar Pedido\n";
    cout << "2 - Buscar Pedido por ID\n";
    cout << "3 - Atualizar Pedido\n";
    cout << "4 - Deletar Pedido\n";
    cout<< "6 - Consultar pagamento\n";
    cout << "5 - Sair\n";
    cout << "Escolha: ";
}

void mostrarMenuProduto() {
    cout << "\n===== MENU PRODUTO =====\n";
    cout<<"1 - Criar Produto\n";
    cout<<"2 - Buscar Produto por ID\n";
    cout<<"3 - Atualizar Produto\n";
    cout<<"4 - Deletar Produto\n";
    cout<<"5 - Sair\n";
}

int main() {
    PedidoController controller;
    PagamentoController pagamentoController;
    ProdutoController produtoController;

    int opcaoMenu;
    int opcaoProduto;
    int opcao;


    do {
        mostrarMenuProduto();
        cin>> opcaoProduto;
        if (opcaoProduto == 1) {
            int produtoId;
            string nome, descricao, status;
            double valorProduto;
            cout << "ID: ";
            cin >> produtoId;
            cin.ignore();
            cout << "Nome: ";
            getline(cin, nome);
            cout<< "Descricao: ";
            getline(cin, descricao);
            cout<< "Valor: ";
            cin >> valorProduto;
            cin.ignore();
            cout<< "Status: ";
            getline(cin, status);
            Produto produto(produtoId, nome, descricao, valorProduto, status);
            produto = produtoController.salvarProduto(produto);
            cout<< "Produto cadastrado com sucesso!\n";
        }else if (opcaoProduto == 2) {
            int produtoId;
            cout<< "ID: ";
            cin>> produtoId;
            cin.ignore();
            Produto produto = produtoController.buscarProdutoPorId(produtoId);
            if (produto.getId() != -1) {
                cout << "ID: " << produto.getId() << " | Nome: " << produto.getName() << "\n";
                } else {
                cout << "Pedido não encontrado.\n";
                }
        }else if (opcaoProduto == 3) {
            int id;
            string nome, descricao, status;
            double valor;

            cout << "ID do produto: ";
            cin >> id;
            cin.ignore();

            cout << "Novo nome: ";
            getline(std::cin, nome);

            cout << "Nova descrição: ";
            getline(std::cin, descricao);

            cout << "Novo valor: ";
            cin >> valor;
            cin.ignore();

            cout << "Novo status: ";
            getline(std::cin, status);

            Produto produto(id, nome, descricao, valor, status);

            try {
                produtoController.atualizarProduto(produto); // Chama o método no controller
                cout << "Produto atualizado com sucesso.\n";
            } catch (const std::exception& e) {
                cerr << "Erro: " << e.what() << '\n';
            }
        }else if (opcaoProduto == 4) {
            int id;
            cout << "ID do produto a ser deletado: ";
            cin >> id;
            cin.ignore();

            try {
                produtoController.deletarProduto(id); // Chama o método no controller
                cout << "Produto deletado com sucesso.\n";
            } catch (const std::exception& e) {
                cerr << "Erro: " << e.what() << '\n';
            }
        }


    }while (opcaoProduto != 5);

    // do {
    //     cin>> opcao;
    //     if (opcao == 1) {
    //         int id;
    //         string nome;
    //         cout << "ID: ";
    //         cin >> id;
    //         cin.ignore();
    //         cout << "Nome: ";
    //         getline(cin, nome);
    //         Pedido pedido(id, nome);
    //         pedido = controller.salvarPedido(pedido);
    //         cout << "Pedido salvo!\n";
    //
    //     } else if (opcao == 2) {
    //         int id;
    //         cout << "ID: ";
    //         cin >> id;
    //         cin.ignore();
    //         Pedido pedido = controller.buscarPedidoPorId(id);
    //         if (pedido.getId() != -1) {
    //             cout << "ID: " << pedido.getId() << " | Nome: " << pedido.getName() << "\n";
    //         } else {
    //             cout << "Pedido não encontrado.\n";
    //         }
    //
    //     } else if (opcao == 3) {
    //         int id;
    //         // string nome;
    //         // cout << "ID do pedido para atualizar: ";
    //         // cin >> id;
    //         // cin.ignore();
    //         // cout << "Novo nome: ";
    //         // getline(cin, nome);
    //         // Pedido pedido(id, nome);
    //         // controller.atualizarPedido(pedido);
    //         cout << "Pedido atualizado!\n";
    //
    //     } else if (opcao == 4) {
    //         int id;
    //         // cout << "ID do pedido para deletar: ";
    //         // cin >> id;
    //         // cin.ignore();
    //         // controller.deletarPedido(id);
    //         cout << "Pedido deletado!\n";
    //
    //     } else if (opcao == 6) {
    //         cout << "Consultando pagamentos...\n";
    //         std::vector<Pagamento> pagamentos = pagamentoController.buscarTodosPagamentos();
    //
    //         for (const auto& pagamento : pagamentos) {
    //             cout << "ID: " << pagamento.getCdPagamento() << " | Tipo: " << toChar(pagamento.getTpPagamento())<<endl;
    //         }
    //     }
    //     else if (opcao == 5) {
    //         cout << "Saindo...\n";
    //     } else {
    //         cout << "Opção inválida!\n";
    //     }
    //
    // } while (opcao != 5);

    return 0;
}
