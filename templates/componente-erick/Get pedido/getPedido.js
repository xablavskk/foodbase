    document.addEventListener('DOMContentLoaded', () => {
    const btnConsultar = document.getElementById('btnConsultar');
    const resultadoDiv = document.getElementById('resultado');

    btnConsultar.addEventListener('click', async () => {
        const pedidoId = document.getElementById('pedidoId').value.trim();
        if (!pedidoId) {
            alert('Por favor, informe o ID do pedido.');
            return;
        }

        try {
            const res = await fetch(`http://localhost:18080/pedido/${pedidoId}`);
            if (!res.ok) {
                resultadoDiv.style.display = 'none';
                alert(`Erro ao buscar pedido: ${res.status} ${res.statusText}`);
                return;
            }

            const data = await res.json();

            const p = data.pedido;
            document.getElementById('cdPedido').textContent = p.cdPedido || '';
            document.getElementById('stPedido').textContent = p.stPedido || '';

            const prod = p.produto || {};
            document.getElementById('cdProduto').textContent = prod.cdProduto || '';
            document.getElementById('nmProduto').textContent = prod.nmProduto || '';
            document.getElementById('dsProduto').textContent = prod.dsProduto || '';
            document.getElementById('stProduto').textContent = prod.stProduto || '';
            document.getElementById('vlProduto').textContent = prod.vlProduto || '';

            const pag = p.pagamento || {};
            document.getElementById('cdPagamento').textContent = pag.cdPagamento || '';
            document.getElementById('tpPagamento').textContent = pag.tpPagamento || '';
            document.getElementById('vlPagamento').textContent = pag.vlPagamento || '';

            resultadoDiv.style.display = 'block';

        } catch (error) {
            resultadoDiv.style.display = 'none';
            alert('Erro ao buscar pedido: ' + error.message);
        }
    });
});
