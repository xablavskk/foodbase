#include <iostream>
#include "Pedido.hpp"
#include "controllers/PedidoController.hpp"

using namespace std;

void mostrarMenu() {
    cout << "\n===== MENU PEDIDO =====\n";
    cout << "1 - Criar Pedido\n";
    cout << "2 - Buscar Pedido por ID\n";
    cout << "3 - Atualizar Pedido\n";
    cout << "4 - Deletar Pedido\n";
    cout << "5 - Sair\n";
    cout << "Escolha: ";
}

int main() {
    PedidoController controller;
    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            int id;
            string nome;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "Nome: ";
            getline(cin, nome);
            Pedido pedido(pedido);
            pedido = controller.salvarPedido(pedido);
            cout << "Pedido salvo!\n";

        } else if (opcao == 2) {
            int id;
            cout << "ID: ";
            cin >> id;S
            cin.ignore();
            Pedido pedido = controller.buscarPedidoPorCd(cd_pedido);
            if (pedido.getCdPedido() != -1) {
                cout << "ID: " << pedido.getCdPedido();// << " | Nome: " << pedido.getName() << "\n";
            } else {
                cout << "Pedido não encontrado.\n";
            }

        } else if (opcao == 3) {
            int id;
            // string nome;
            // cout << "ID do pedido para atualizar: ";
            // cin >> id;
            // cin.ignore();
            // cout << "Novo nome: ";
            // getline(cin, nome);
            // Pedido pedido(id, nome);
            // controller.atualizarPedido(pedido);
            cout << "Pedido atualizado!\n";

        } else if (opcao == 4) {
            int id;
            // cout << "ID do pedido para deletar: ";
            // cin >> id;
            // cin.ignore();
            // controller.deletarPedido(id);
            cout << "Pedido deletado!\n";

        } else if (opcao == 5) {
            cout << "Saindo...\n";
        } else {
            cout << "Opção inválida!\n";
        }

    } while (opcao != 5);

    return 0;
}
