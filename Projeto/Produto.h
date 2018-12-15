#include "stdio.h"
#include "stdlib.h"

typedef struct{
		float codigo;
		char descricao[50];
		float preco;
		float estoque;
	} tipoProduto;

tipoProduto ConsultarProduto(float codigo);

void inserirProd(tipoProduto produto);

void alterarProd(tipoProduto produto);
