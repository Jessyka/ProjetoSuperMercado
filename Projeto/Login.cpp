#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <string.h>
#include "Login.h"

/*typedef struct{
		char login[50];
		char senha[50];
		int classificacao;
		//Classificacao 01: Adiministrador
		//Classificacao 02: Funcionario Loja
	} tipoLogin;*/
	
	
FILE *pLogin;
tipoLogin login_aux;

void abre_arquivo_login()
{ 
	pLogin = fopen("pLogin.dat", "r+b");
	if (pLogin == NULL)
		pLogin = fopen("pLogin.dat", "w+b");
}

int validarUsuario(char login[50],char senha[50])
{ 
	abre_arquivo_login();
	rewind(pLogin);
	fread(&login_aux, sizeof(tipoLogin), 1, pLogin);
	while (feof(pLogin)==0)
	{ 
		if ((strcmp (login_aux.login, login) == 0) && (strcmp (login_aux.senha, senha) == 0)){
			fclose(pLogin);
			return login_aux.classificacao;
		}
			
		fread(&login_aux, sizeof(tipoLogin), 1,pLogin);
	}
	
	fclose(pLogin);
	return 0;
}

void inserir(tipoLogin login_aux)
{ 
	abre_arquivo_login();
	fseek(pLogin, 0, SEEK_END);
	fwrite(&login_aux, sizeof(tipoLogin), 1, pLogin);
	fclose(pLogin);
}
