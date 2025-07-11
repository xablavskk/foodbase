    document.addEventListener('DOMContentLoaded', () => {
    const form = document.getElementById('pedidoForm');
    const respostaEl = document.getElementById('resposta');

    form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const payload = {
            pedido: {
                produto: {
                    nmProduto: document.getElementById('nmProduto').value,
                    dsProduto: document.getElementById('dsProduto').value,
                    stProduto: document.getElementById('stProduto').value,
                    vlProduto: parseFloat(document.getElementById('vlProduto').value)
                },
                pagamento: {
                    tpPagamento: document.getElementById('tpPagamento').value,
                    vlPagamento: parseFloat(document.getElementById('vlPagamento').value)
                },
                stPedido: document.getElementById('stPedido').value
            }
        };

        try {
            console.log("Enviando payload:", JSON.stringify(payload, null, 2));

            const response = await fetch('http://localhost:18080/pedido', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(payload)
            });

            const contentType = response.headers.get("content-type");
            let data;

            if (contentType && contentType.includes("application/json")) {
                data = await response.json();
            } else {
                data = await response.text();
            }

            if (!response.ok) {
                respostaEl.textContent = `Erro ${response.status}:\n${data}`;
            } else {
                respostaEl.textContent = typeof data === 'string'
                    ? data
                    : JSON.stringify(data, null, 2);
            }
        } catch (error) {
            respostaEl.textContent = 'Erro na requisição: ' + error.message;
        }
    });
});
