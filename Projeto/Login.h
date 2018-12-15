#include "stdio.h"
#include "stdlib.h"

typedef struct{
		char login[50];
		char senha[50];
		int classificacao;
		//Classificacao 01: Adiministrador
		//Classificacao 02: Funcionario Loja
	} tipoLogin;
	

int validarUsuario(char login[50],char senha[50]);

void inserir(tipoLogin login_aux);
