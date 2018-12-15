#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "Produto.h"

/*typedef struct{
		int codigo;
		char descricao[50];
		float preco;
		int estoque;
	} tipoProduto;*/
	
	
FILE *pProd;
tipoProduto prod_aux;

void abre_arquivo_prod()
{ 
	pProd = fopen("pProd.dat", "r+b");
	if (pProd == NULL)
		pProd = fopen("pProd.dat", "w+b");
}

tipoProduto ConsultarProduto(float codigo)
{ 
	abre_arquivo_prod();
	rewind(pProd);
	fread(&prod_aux, sizeof(tipoProduto), 1, pProd);
	while (feof(pProd)==0)
	{ 
		if (prod_aux.codigo == codigo){
			fclose(pProd);
			return prod_aux;
		}
		fread(&prod_aux, sizeof(tipoProduto), 1,pProd);
	}
	
	tipoProduto p;
	p.codigo = -1;
	fclose(pProd);
	
	return p;
	
}

int ConsultarPosicao(float codigo)
{ 
	abre_arquivo_prod();
	int p;
	p = 0;
	rewind(pProd);
	fread(&prod_aux, sizeof(tipoProduto), 1, pProd);
	while (feof(pProd)==0)
	{ 
		if (prod_aux.codigo == codigo){
			fclose(pProd);
			return p;
		}
			
		fread(&prod_aux, sizeof(tipoProduto), 1,pProd);
		p++;
	}
	
	fclose(pProd);
	return -1;
	
}

void inserirProd(tipoProduto produto)
{ 
	abre_arquivo_prod();
	fseek(pProd, 0, SEEK_END);
	fwrite(&produto, sizeof(tipoProduto), 1, pProd);
	fclose(pProd);
}

void alterarProd(tipoProduto produto)
{ 
	
	int posicao = ConsultarPosicao(produto.codigo);

	if (posicao == -1){
		
		fclose(pProd);
		return	;
	}		
	else
	{
		abre_arquivo_prod();
		fseek(pProd,posicao*sizeof(tipoProduto), SEEK_SET);
		fwrite(&produto,sizeof(tipoProduto), 1, pProd);
	}
	
	fclose(pProd);
}



