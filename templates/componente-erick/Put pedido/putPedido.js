    document.getElementById('formAtualizar').addEventListener('submit', async (e) => {
    e.preventDefault();

    const cdPedido = parseInt(document.getElementById('cdPedido').value);
    const cdPagamento = parseInt(document.getElementById('cdPagamento').value);
    const tpPagamento = document.getElementById('tpPagamento').value;
    const vlPagamento = parseFloat(document.getElementById('vlPagamento').value);
    const stPedido = document.getElementById('stPedido').value;

    const payload = {
        pedido: {
            pagamento: {
                cdPagamento: cdPagamento,
                tpPagamento: tpPagamento,
                vlPagamento: vlPagamento
            },
            stPedido: stPedido
        }
    };

    try {
        const response = await fetch(`http://localhost:18080/pedido/${cdPedido}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(payload)
        });

        const contentType = response.headers.get("content-type");
        let data = contentType && contentType.includes("application/json")
            ? await response.json()
            : await response.text();

        const respostaEl = document.getElementById('resposta');
        if (!response.ok) {
            respostaEl.textContent = `Erro ${response.status}:\n${JSON.stringify(data)}`;
        } else {
            respostaEl.textContent = typeof data === 'string' ? data : JSON.stringify(data, null, 2);
        }
    } catch (error) {
        document.getElementById('resposta').textContent = 'Erro na requisição: ' + error.message;
    }
});
