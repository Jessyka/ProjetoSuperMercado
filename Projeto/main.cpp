#include <windows.h>
#include "Login.h"
#include "Produto.h"
#include <string.h>
#include <cstdlib> 
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND handleforwindow1,UINT message,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK WndAdmin(HWND handleforwindow2,UINT message,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK WndLoja(HWND handleforwindow2,UINT message,WPARAM wParam,LPARAM lParam);

void createwindowAdmin(WNDCLASSEX& wc,HWND& hwnd,HINSTANCE hInst,int nShowCmd);
void limparWindowAdmin();

void createwindowLoja(WNDCLASSEX& wc,HWND& hwnd,HINSTANCE hInst,int nShowCmd);
void limparWindowLoja();


void LoadGrid1(HWND hgrid);

bool windowAdminStart=false;
bool windowLojaStart=false;
bool windowLogin=true;

bool verificarRegistroTelaAdmin, verificarRegistroTelaLogin,
    verificarRegistroTelaLoja=false;
    
    
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	//Janela Login
	WNDCLASSEX wc; 
	HWND hwnd; 
	
	//Janela Admin
	WNDCLASSEX wcAdmin; 
	HWND hwndAdmin; 
	
	//Janela Loja
	WNDCLASSEX wcLoja; 
	HWND hwndLoja; 
		
	MSG msg; 
	bool endprogram=false;

	//Janela Login
	if(verificarRegistroTelaLogin == false){
	
		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpfnWndProc	 = WndProc; 
		wc.hInstance	 = hInstance;
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		wc.lpszClassName = "WindowClass";
		wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
		wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); 
	}
	
	if(!RegisterClassEx(&wc))
    {
        int nResult=GetLastError();
        MessageBox(hwnd, "Erro ao instaciar WNDCLASSEX", "AVISO", MB_OK);
    }
    else{
	
        verificarRegistroTelaLogin = true;
    } 

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Super Mercado IF",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		500, 
		200, 
		NULL,NULL,hInstance,NULL);
	//Fim Janela Login
	
	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	 
	while (endprogram==false) {
        if (GetMessage(&msg,NULL,0,0)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if(windowLojaStart==true){
        	createwindowLoja(wcLoja,hwndLoja,hInstance,nCmdShow);
		}
		if(windowAdminStart==true){
        	createwindowAdmin(wcAdmin,hwndAdmin,hInstance,nCmdShow);
		}
		if(windowLogin==false){
        	DestroyWindow(hwnd);
		}
        if (windowLojaStart==false && windowLogin==false && windowAdminStart==false) {
            endprogram=true;
        }
    }
	return msg.wParam;
}

/*Variaveis da tela Login*/
HWND TextBoxLogin;
HWND TextBoxSenha;

char login[50];
char senha[50];
static HWND labelLogin;
static HWND labelSenha;

////////////////////////

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch(Message) {
		
		case WM_CREATE: {	
				
			labelLogin = CreateWindow("STATIC", "Login:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
				10, 10, 50, 20, hwnd, NULL, NULL, NULL);
			TextBoxLogin = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
				70, 10, 300, 20, hwnd, NULL, NULL, NULL);
			labelLogin = CreateWindow("STATIC", "Senha:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
				10, 40, 50, 20, hwnd, NULL, NULL, NULL);
			TextBoxSenha = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
				70, 40, 300, 20, hwnd, NULL, NULL, NULL);			
   			
   			
			CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
				385, 10, 70, 50, hwnd, (HMENU) 1, NULL, NULL);
			
			break;
		}
		case WM_COMMAND:{
			switch (LOWORD(wParam)){
				case 1:{
					int gwtstat = 0;
					
					gwtstat = GetWindowText(TextBoxLogin, &login[0], 50);
					gwtstat = GetWindowText(TextBoxSenha, &senha[0], 50);
					
					int retorno = validarUsuario(login, senha);
					
					switch(retorno){
						case 1:{
							//Acesso Admin
							windowAdminStart = true;
							windowLogin = false;
							break;
						}
						case 2:{
							//Acesso Loja
							windowLojaStart = true;
							windowLogin = false;
							break;
						}
						default:{
							MessageBox(hwnd, "Usuario nao encontrado!", "AVISO", MB_OK);
							break;
						}
					}
					break;
				}
			}
			break;
		}			
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/*Variaveis das telas Admin*/

HWND TextBoxUserLogin;
HWND TextBoxUserSenha;

HWND TextBoxProdCodigo;
HWND TextBoxProdDescricao;
HWND TextBoxProdPreco;
HWND TextBoxProdQuantidade;
HWND ButtonSalvar;

HWND labelAux1;
HWND labelAux2;
HWND labelAux3;
HWND labelAux4;

HWND labelAux5;

HWND labelAux6;
HWND labelAux7;
HWND labelAux8;
HWND hGrpButtons;

////////////////////////////

void createwindowAdmin(WNDCLASSEX &wc,HWND &hwnd,HINSTANCE hInst,int nShowCmd) {
	
    if (verificarRegistroTelaAdmin==false) {
    	
    	ZeroMemory(&wc,sizeof(WNDCLASSEX));
    	wc.cbClsExtra=NULL;
    	wc.cbSize=sizeof(WNDCLASSEX);
    	wc.cbWndExtra=NULL;
    	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
    	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    	wc.hIcon=NULL;
    	wc.hIconSm=NULL;
    	wc.hInstance=hInst;
    	wc.lpfnWndProc=(WNDPROC)WndAdmin;
    	wc.lpszClassName="Admin";
    	wc.lpszMenuName=NULL;
    	wc.style=CS_HREDRAW|CS_VREDRAW;

    if(!RegisterClassEx(&wc)){
        int nResult=GetLastError();
        MessageBox(hwnd, "Erro ao instaciar window", "AVISO", MB_OK);
    }
    else{	
        verificarRegistroTelaAdmin=true;
    } 
    
    hwnd=CreateWindowEx(NULL,
            wc.lpszClassName,
            "Administrado - Super Mercado IF",
            WS_OVERLAPPEDWINDOW,
            200, 170, 640, 400, NULL, NULL, hInst, NULL);
	}
	
	ShowWindow(hwnd,nShowCmd);
}

LRESULT CALLBACK WndAdmin(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch(Message) {
		
		case WM_CREATE: {

        	HMENU Menu_bar = CreateMenu();
        	HMENU user = CreateMenu();
        	HMENU product = CreateMenu();

        	AppendMenu(Menu_bar, MF_POPUP, (UINT_PTR)user, "Usuário");
        	AppendMenu(Menu_bar, MF_POPUP, (UINT_PTR)product, "Produto");

        	AppendMenu(user, MF_STRING, 1, "Novo Usuário - Admin");
        	AppendMenu(user, MF_STRING, 2, "Novo Usuário - Loja");

        	AppendMenu(product, MF_STRING, 3, "Novo Produto");
    	    AppendMenu(product, MF_STRING, 4, "Editar Produto");
    	    AppendMenu(product, MF_STRING, 5, "Consultar Produto");
	
	        SetMenu(hwnd, Menu_bar);

			break;
		}
		
		case WM_COMMAND:{
			switch (LOWORD(wParam)){	//Tela novo usuário
				case 1:{
					limparWindowAdmin();
					
					labelAux5 = CreateWindow("STATIC", "Novo Usuário - Admin", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						120, 10, 150, 20, hwnd, NULL, NULL, NULL);
					
					labelAux1 = CreateWindow("STATIC", "Login:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 50, 20, hwnd, NULL, NULL, NULL);
					TextBoxUserLogin = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						70, 40, 300, 20, hwnd, NULL, NULL, NULL);
					labelAux2 = CreateWindow("STATIC", "Senha:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 70, 50, 20, hwnd, NULL, NULL, NULL);
					TextBoxUserSenha = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						70, 70, 300, 20, hwnd, NULL, NULL, NULL);		   			
   			
					ButtonSalvar = CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						385, 90, 50, 20, hwnd, (HMENU) 6, GetModuleHandle(NULL), NULL);
					
					break;
				}
				case 2:{	//Tela novo usuário
					limparWindowAdmin();
					
					labelAux5 = CreateWindow("STATIC", "Novo Usuário - Loja", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						120, 10, 150, 20, hwnd, NULL, NULL, NULL);
					
					labelAux1 = CreateWindow("STATIC", "Login:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 50, 20, hwnd, NULL, NULL, NULL);
					TextBoxUserLogin = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						70, 40, 300, 20, hwnd, NULL, NULL, NULL);
					labelAux2 = CreateWindow("STATIC", "Senha:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 70, 50, 20, hwnd, NULL, NULL, NULL);
					TextBoxUserSenha = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						70, 70, 300, 20, hwnd, NULL, NULL, NULL);		   			
   			
					ButtonSalvar = CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						385, 90, 50, 20, hwnd, (HMENU) 7, GetModuleHandle(NULL), NULL);
					
					break;
				}
				case 3:{	//Tela novo produto.
					
					limparWindowAdmin();
					
					labelAux5 = CreateWindow("STATIC", "Cadastro Novo Produto", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						120, 10, 200, 20, hwnd, NULL, NULL, NULL);
					
					labelAux1 = CreateWindow("STATIC", "Código:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdCodigo = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 40, 300, 20, hwnd, NULL, NULL, NULL);
					labelAux2 = CreateWindow("STATIC", "Nome:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 70, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdDescricao = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 70, 300, 20, hwnd, NULL, NULL, NULL);	
					labelAux3 = CreateWindow("STATIC", "Preço:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 100, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdPreco = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 100, 300, 20, hwnd, NULL, NULL, NULL);
					labelAux4 = CreateWindow("STATIC", "Quantidade:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 130, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdQuantidade = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 130, 300, 20, hwnd, NULL, NULL, NULL);			   			
   			
					ButtonSalvar = CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						500, 160, 50, 20, hwnd, (HMENU) 8, NULL, NULL);
					break;
				}
				case 4:{	//Tela editar produto.
					limparWindowAdmin();
					
					labelAux5 = CreateWindow("STATIC", "Editar Produto", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						120, 10, 150, 20, hwnd, NULL, NULL, NULL);
					
					labelAux1 = CreateWindow("STATIC", "Código:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdCodigo = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 40, 300, 20, hwnd, NULL, NULL, NULL);	
					labelAux2 = CreateWindow("STATIC", "Novo Preço:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 70, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdPreco = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 70, 300, 20, hwnd, NULL, NULL, NULL);
					labelAux3 = CreateWindow("STATIC", "Nova Quantidade:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 100, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdQuantidade = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 100, 300, 20, hwnd, NULL, NULL, NULL);			   			
   			
					ButtonSalvar = CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						500, 130, 50, 20, hwnd, (HMENU) 9, NULL, NULL);
					break;
				}
				case 5:{
					limparWindowAdmin();
					
					labelAux5 = CreateWindow("STATIC", "Consultar produto", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						120, 10, 300, 20, hwnd, NULL, NULL, NULL);
						
					labelAux1 = CreateWindow("STATIC", "Código:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdCodigo = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 40, 300, 20, hwnd, NULL, NULL, NULL);
					ButtonSalvar = CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						500, 70, 50, 20, hwnd, (HMENU) 10, NULL, NULL);
					
					labelAux2 = CreateWindow("STATIC", "Descrição:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 90, 150, 20, hwnd, NULL, NULL, NULL);
					labelAux3 = CreateWindow("STATIC", "Estoque:",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 120, 150, 20, hwnd, NULL, NULL, NULL);
					labelAux4 = CreateWindow("STATIC", "Preço",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 150, 150, 20, hwnd, NULL, NULL, NULL);	
						
					labelAux2 = CreateWindow("STATIC", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 90, 250, 20, hwnd, NULL, NULL, NULL);
					labelAux3 = CreateWindow("STATIC", "",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 120, 250, 20, hwnd, NULL, NULL, NULL);
					labelAux4 = CreateWindow("STATIC", "",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 150, 250, 20, hwnd, NULL, NULL, NULL);
						
					break;
				}
				case 6:{	//Salvar Novo usuário.
				
					int gwtstat = 0;
					
					tipoLogin login_;
					
					gwtstat = GetWindowText(TextBoxUserLogin, login_.login, 50);
					gwtstat = GetWindowText(TextBoxUserSenha, login_.senha, 50);

					login_.classificacao = 1;
					
					inserir(login_);
					
					MessageBox(hwnd, "Usuário inserido com sucesso.", "AVISO", MB_OK);
					
					//Limpar textbox
					SetWindowTextA(TextBoxUserLogin, "");
					SetWindowTextA(TextBoxUserSenha, "");
					break;
					
				}
				case 7:{	//Salvar Novo usuário.
				
					int gwtstat = 0;
					
					tipoLogin login_;
					
					gwtstat = GetWindowText(TextBoxUserLogin, login_.login, 50);
					gwtstat = GetWindowText(TextBoxUserSenha, login_.senha, 50);

					login_.classificacao = 2;
					
					inserir(login_);
					
					MessageBox(hwnd, "Usuário inserido com sucesso.", "AVISO", MB_OK);
					
					//Limpar textbox
					SetWindowTextA(TextBoxUserLogin, "");
					SetWindowTextA(TextBoxUserSenha, "");
					break;
				}
				case 8:{	//Salvar novo produto.
				
					int gwtstat = 0;
					tipoProduto prod_;
					char teste[10];				
					
					gwtstat = GetWindowText(TextBoxProdCodigo, teste, 5);
					prod_.codigo = atof(teste);
					gwtstat = GetWindowText(TextBoxProdDescricao, prod_.descricao, 50);
					gwtstat = GetWindowText(TextBoxProdQuantidade, teste, 5);
					prod_.estoque = atof(teste);
					gwtstat = GetWindowText(TextBoxProdPreco, teste, 5);
					prod_.preco = atof(teste);
					
					MessageBox(hwnd, "Produto inserido com sucesso.", "AVISO", MB_OK);
					
					//Limpar textbox
					SetWindowTextA(TextBoxProdCodigo, "");
					SetWindowTextA(TextBoxProdDescricao, "");
					SetWindowTextA(TextBoxProdQuantidade, "");
					SetWindowTextA(TextBoxProdPreco, "");
					
					break;
				}
				case 9:{	//Editar produto.
					int gwtstat = 0;
					tipoProduto prod_;
					char teste[10];
					
					gwtstat = GetWindowText(TextBoxProdCodigo, teste, 5);
					prod_.codigo = atof(teste);
					gwtstat = GetWindowText(TextBoxProdQuantidade, teste, 5);
					prod_.estoque = atof(teste);
					gwtstat = GetWindowText(TextBoxProdPreco, teste, 5);
					prod_.preco = atof(teste);
					
					//Comando para alterar produto.
					alterarProd(prod_);
					
					MessageBox(hwnd, "Produto alterado com sucesso.", "AVISO", MB_OK);
					
					//Limpar textbox
					SetWindowTextA(TextBoxProdCodigo, "");
					SetWindowTextA(TextBoxProdQuantidade, "");
					SetWindowTextA(TextBoxProdPreco, "");
					
					break;
				}
				case 10:{
					int gwtstat = 0;
					tipoProduto prod_;
					char teste[10];
					
					SetWindowTextA(labelAux2, "");
					SetWindowTextA(labelAux3, "");
					SetWindowTextA(labelAux4, "");
						
					gwtstat = GetWindowText(TextBoxProdCodigo, teste, 5);
					float codigo = (float) atof(teste);
					
					prod_= ConsultarProduto(codigo);
					
					if(prod_.codigo == -1){
						
						MessageBox(hwnd, "Produto não encontrado.", "AVISO", MB_OK);
						
					}else
					{
						char charValTotal[10];                
						char charValPreco[10];					
						sprintf(charValTotal, "%.3f", prod_.estoque);
						sprintf(charValPreco, "%.2f", prod_.preco);
						
						SetWindowTextA(labelAux2, prod_.descricao);
						SetWindowTextA(labelAux3, charValTotal);
						SetWindowTextA(labelAux4, charValPreco);
						
					}
					
					SetWindowTextA(TextBoxProdCodigo, "");						
					
					break;
				}
			}
			break;
		}			
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void limparWindowAdmin(){
	
	DestroyWindow(TextBoxUserLogin);
	DestroyWindow(TextBoxUserSenha);
	DestroyWindow(TextBoxProdCodigo);
	DestroyWindow(TextBoxProdDescricao);
	DestroyWindow(TextBoxProdPreco);
	DestroyWindow(TextBoxProdQuantidade);
	DestroyWindow(ButtonSalvar);
	
	DestroyWindow(labelAux1);
	DestroyWindow(labelAux2);
	DestroyWindow(labelAux3);
	DestroyWindow(labelAux4);
	DestroyWindow(labelAux5);
	DestroyWindow(labelAux6);
	DestroyWindow(labelAux7);
	DestroyWindow(labelAux8);
}

/*Variaveis das telas Loja*/

HWND ButtonAdd;

HWND hgrid;
HWND labelTotal;
HWND labelPreco;


////////////////////////////

void createwindowLoja(WNDCLASSEX &wc,HWND &hwnd,HINSTANCE hInst,int nShowCmd) {
    if (verificarRegistroTelaLoja==false) {
    	
		ZeroMemory(&wc,sizeof(WNDCLASSEX));
    	wc.cbClsExtra=NULL;
    	wc.cbSize=sizeof(WNDCLASSEX);
    	wc.cbWndExtra=NULL;
    	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
    	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    	wc.hIcon=NULL;
    	wc.hIconSm=NULL;
    	wc.hInstance=hInst;
    	wc.lpfnWndProc=(WNDPROC)WndLoja;
    	wc.lpszClassName="Loja";
    	wc.lpszMenuName=NULL;
    	wc.style=CS_HREDRAW|CS_VREDRAW;

    if(!RegisterClassEx(&wc)){
        int nResult=GetLastError();
        MessageBox(hwnd, "Erro ao instaciar window", "AVISO", MB_OK);
    }
    else{
	
        verificarRegistroTelaLoja=true;
    } 
    hwnd=CreateWindowEx(NULL,
            wc.lpszClassName,
            "Loja - Super Mercado IF",
            WS_OVERLAPPEDWINDOW,
            200, 170, 640, 380, NULL, NULL, hInst, NULL);

	}
	
	ShowWindow(hwnd,nShowCmd);
}

float total = 0;
float preco = 0;
	
LRESULT CALLBACK WndLoja(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	switch(Message) {
		
		case WM_CREATE: {

        	HMENU Menu_bar = CreateMenu();
        	HMENU venda = CreateMenu();
        	HMENU produto = CreateMenu();

        	AppendMenu(Menu_bar, MF_POPUP, (UINT_PTR)venda, "Venda");
        	AppendMenu(Menu_bar, MF_POPUP, (UINT_PTR)produto, "Produto");

        	AppendMenu(venda, MF_STRING, 1, "Nova Venda");

        	AppendMenu(produto, MF_STRING, 2, "Consultar Produto");
	
	        SetMenu(hwnd, Menu_bar);

			break;
		}
		case WM_COMMAND:{
			switch (LOWORD(wParam)){
				case 1:{	//Tela Venda				
					
					char charValTotal[10];                
					char charValPreco[10];					
					sprintf(charValTotal, "%.3f", total);
					sprintf(charValPreco, "%.3f", preco);
					
					labelAux1 = CreateWindow("STATIC", "Código:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 10, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdCodigo = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 10, 200, 20, hwnd, NULL, NULL, NULL);
					labelAux2 = CreateWindow("STATIC", "Quantidade:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdQuantidade = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 40, 200, 20, hwnd, NULL, NULL, NULL);			   			
   			
					ButtonAdd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						385, 60, 30, 20, hwnd, (HMENU) 3, NULL, NULL);
						
					labelAux3 = CreateWindow("STATIC", "Total: ", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 90, 150, 20, hwnd, NULL, NULL, NULL);
					labelAux4 = CreateWindow("STATIC", "Qtd Produtos: ", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 120, 150, 20, hwnd, NULL, NULL, NULL);
					
					labelPreco = CreateWindow("STATIC", charValPreco, WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 90, 250, 20, hwnd, NULL, NULL, NULL);
					labelTotal = CreateWindow("STATIC", charValTotal,  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 120, 250, 20, hwnd, NULL, NULL, NULL);
							
					ButtonSalvar = CreateWindow("BUTTON", "FINALIZAR", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						385, 150, 100, 20, hwnd, (HMENU) 4, NULL, NULL);
					break;
				}
				case 2:{	
					limparWindowLoja();
					
					limparWindowAdmin();
					
					labelAux5 = CreateWindow("STATIC", "Consultar produto", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						120, 10, 300, 20, hwnd, NULL, NULL, NULL);
						
					labelAux1 = CreateWindow("STATIC", "Código:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 40, 150, 20, hwnd, NULL, NULL, NULL);
					TextBoxProdCodigo = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 40, 300, 20, hwnd, NULL, NULL, NULL);
					ButtonSalvar = CreateWindow("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 
						500, 70, 50, 20, hwnd, (HMENU) 5, NULL, NULL);
					
					labelAux2 = CreateWindow("STATIC", "Descrição:", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 90, 150, 20, hwnd, NULL, NULL, NULL);
					labelAux3 = CreateWindow("STATIC", "Estoque:",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 120, 150, 20, hwnd, NULL, NULL, NULL);
					labelAux4 = CreateWindow("STATIC", "Preço",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						10, 150, 150, 20, hwnd, NULL, NULL, NULL);	
						
					labelAux2 = CreateWindow("STATIC", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 90, 250, 20, hwnd, NULL, NULL, NULL);
					labelAux3 = CreateWindow("STATIC", "",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 120, 250, 20, hwnd, NULL, NULL, NULL);
					labelAux4 = CreateWindow("STATIC", "",  WS_BORDER | WS_CHILD | WS_VISIBLE, 
						180, 150, 250, 20, hwnd, NULL, NULL, NULL);
						
					break;
				}
				case 3:{
					int gwtstat = 0;
					tipoProduto prod_;
					char teste[10];
					
					gwtstat = GetWindowText(TextBoxProdCodigo, teste, 5);
					float codigo = (float) atof(teste);
					gwtstat = GetWindowText(TextBoxProdQuantidade, teste, 5);
					float quantidade = atof(teste);
					
					prod_= ConsultarProduto(codigo);
					
					if(prod_.codigo == -1){
						MessageBox(hwnd, "Produto não encontrado.", "AVISO", MB_OK);
						
					}else
					{
						if(prod_.estoque < quantidade)
						{
							MessageBox(hwnd, "Produto em falta.", "AVISO", MB_OK);
						}else{
							prod_.estoque = prod_.estoque - quantidade;							
							alterarProd(prod_);
							total = total + quantidade;
							preco = preco + (prod_.preco * quantidade);
						}
					}
					
					SetWindowTextA(TextBoxProdCodigo, "");
					SetWindowTextA(TextBoxProdQuantidade, "");
					
					char charValTotal[10];                
					char charValPreco[10];					
					sprintf(charValTotal, "%.3f", total);
					sprintf(charValPreco, "%.3f", preco);
					
					SetWindowTextA(labelPreco, charValPreco);
					SetWindowTextA(labelTotal, charValTotal);
					
					break;
				}
				case 4:{
					              
					char charValPreco[20];
					char mens[30] = "Valor a ser pago: R$ ";				
					sprintf(charValPreco, "%.3f", preco);
					char * mensagem = strcat(mens, charValPreco);
					MessageBox(hwnd, mensagem, "Compra concluída", MB_OK);
					
					preco = 0;
					total = 0;
					limparWindowLoja();
					break;
				}
				
				case 5:{
					int gwtstat = 0;
					tipoProduto prod_;
					char teste[10];
					
					SetWindowTextA(labelAux2, "");
					SetWindowTextA(labelAux3, "");
					SetWindowTextA(labelAux4, "");
						
					gwtstat = GetWindowText(TextBoxProdCodigo, teste, 5);
					float codigo = (float) atof(teste);
					
					prod_= ConsultarProduto(codigo);
					
					if(prod_.codigo == -1){
						
						MessageBox(hwnd, "Produto não encontrado.", "AVISO", MB_OK);
						
					}else
					{
						char charValTotal[10];                
						char charValPreco[10];					
						sprintf(charValTotal, "%.3f", prod_.estoque);
						sprintf(charValPreco, "%.2f", prod_.preco);
						
						SetWindowTextA(labelAux2, prod_.descricao);
						SetWindowTextA(labelAux3, charValTotal);
						SetWindowTextA(labelAux4, charValPreco);
						
					}
					
					SetWindowTextA(TextBoxProdCodigo, "");	
					
					break;
				}
					
			}
			break;
		}			
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void limparWindowLoja(){
	
	DestroyWindow(TextBoxProdCodigo);
	DestroyWindow(TextBoxProdQuantidade);
	DestroyWindow(ButtonAdd);
	DestroyWindow(ButtonSalvar);
	
	DestroyWindow(labelAux1);
	DestroyWindow(labelAux2);
	DestroyWindow(labelAux3);
	DestroyWindow(labelAux4);
	DestroyWindow(labelAux5);
	DestroyWindow(labelAux6);
	DestroyWindow(labelAux7);
	DestroyWindow(labelAux8);
		
	DestroyWindow(labelPreco);	
	DestroyWindow(labelTotal);
	DestroyWindow(hgrid);
}


