CREATE TABLE IF NOT EXISTS produto (
                         cd_produto SERIAL PRIMARY KEY,
                         nm_produto VARCHAR(45),
                         ds_produto VARCHAR(45),
                         vl_produto DECIMAL(4,2),
                         st_produto VARCHAR(45)
);

CREATE TABLE IF NOT EXISTS pagamento (
                           cd_pagamento SERIAL PRIMARY KEY,
                           tp_pagamento VARCHAR(45),
                           vl_pagamento DECIMAL(7,2)
);

CREATE TABLE IF NOT EXISTS pedido (
                        cd_pedido SERIAL PRIMARY KEY,
                        pagamento_cd_pagamento INTEGER,
                        produto_cd_produto INTEGER,
                        st_pedido VARCHAR(45),
                        FOREIGN KEY (pagamento_cd_pagamento) REFERENCES pagamento(cd_pagamento),
                        FOREIGN KEY (produto_cd_produto) REFERENCES produto(cd_produto)
);