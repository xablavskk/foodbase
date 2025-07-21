document.addEventListener('DOMContentLoaded', () => {

    /* Configuração dos eventos e associação dos botões */
    const btnConsultar = document.getElementById('btnConsultar');
    const resultadoDiv = document.getElementById('resultado');

    /* Async para lidar com a requisição a api */
    btnConsultar.addEventListener('click', async () => {
        /* Remove os espaços em branco */
        const pedidoId = document.getElementById('pedidoId').value.trim();
        if (!pedidoId) {
            alert('Por favor, informe o ID do pedido.');
            return;
        }
        /*try/catch para ver se API esta ok */
        try {
            const res = await fetch(`http://localhost:18080/pedido/${pedidoId}`);
            if (!res.ok) {
                resultadoDiv.style.display = 'none';
                alert(`Erro ao buscar pedido: ${res.status} ${res.statusText}`);
                return;
            }
        /*Transforma a resposta Json em objeto (data) */
            const data = await res.json();

            /*Distrubuir os dados no HTML*/
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

            /* Pega a descrição do produto e converte para minúsculas para a verificação */
            const dsProduto = String(prod.dsProduto || "").toLowerCase();
            const imagemDiv = document.getElementById('imagem');

            //console.log("Descrição do produto recebida:", dsProduto); 

            /* Com base na descrição, mostra a imagem correspondente */
            if (imagemDiv) {
                if (dsProduto.includes("hambúrguer")) {
                    imagemDiv.innerHTML = `
                <img src="imagens/imagem1.png" alt="hamburguer" width="100">`;
                }

                else if (dsProduto.includes("pizza")) {
                    imagemDiv.innerHTML = `
                <img src="imagens/imagem2.png" alt="pizza" width="100">`;
                }
                /* Se nao for uma resposta esperada, nao mostra nada */
                else {
                    imagemDiv.innerHTML = "";
                }
            }

        } catch (error) {
            resultadoDiv.style.display = 'none';
            alert('Erro ao buscar pedido: ' + error.message);
        }
    });

});
