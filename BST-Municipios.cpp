#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <locale.h>
#include <conio.h>
using namespace std;

struct Municipio {
	char nome_municipio[50];
	int area;
	int pop;
	float densi;
};

struct no
{
    Municipio m;
    struct no *d, *e;
};

no *raiz;

char menu();
//void titulo(char *);
void pausa();
void inserir();
void listar();
void contarMunicipio();
void mostraBigMunicipio();
void mostraDensidade();
void mostraSoma();
//void maiorPop();

int main (void)
{
	//int x;
	setlocale(LC_ALL, "Portuguese");
	
    char op;

	raiz = NULL;

    do
    {
        op = menu();
    } while (op != '0');
        
	
    // inserir();
    // inserir();
    // inserir();
    // listar();
    // contarMunicipio();
    // mostraBigMunicipio();
    // mostraDensidade();
    // mostraSoma();
    // //maiorPop();
    
}



//MENU

char menu()
{
	system("cls");
    char op;
    printf("\n======= MENU =======\n");
    printf("\nEscolha uma opção: \n");
    printf("0 - Encerrar\n");
    printf("1 - Inserir\n");
    printf("2 - Exibir número de municípios\n");
    printf("3 - Exibir municípios com mais de cem mil habitantes\n");
    printf("4 - Exibir densidade demográfica dos municípios\n");
    printf("5 - Exibir somatório das áreas em relação ao território nacional\n");
    printf("6 - Listar municípios em ordem\n");
    //printf("7 - Exibir município com maior população\n");
    op = _getche();

    switch (op)
    {
        case '0': break;
        case '1': inserir(); break;
        case '2': contarMunicipio(); break;
        case '3': mostraBigMunicipio(); break;
        case '4': mostraDensidade(); break;
        case '5': mostraSoma(); break;
        case '6': listar(); break;

        default: printf("\nOpção inválida!"); pausa(); break;
    }

    return op;
}

void pausa()
{
    printf("\nTecle algo...");
    _getch();
}




//FUNÇÃO PARA RECEBER OS MUNICIPIOS INFORMADOS PELO USUÁRIO:

Municipio recebeMunicipio()
{	    
    Municipio aux;
    printf("\n\nInforme o Nome do Municipio: ");
    scanf("%s", &aux.nome_municipio);
    printf("\nInforme a area do municipio em Km2: ");
    scanf("%d", &aux.area);
    printf("\nInforme qual a populacao do municipio: ");
    scanf("%d", &aux.pop);
    aux.densi = (aux.pop / aux.area);
    return aux;
}

//===========================================================


//FUNÇÃO PARA MOSTRAR DADOS INFORMADOS PELO USUÁRIO:

void mostraMunicipio(Municipio aux)
{
    printf("\nMunicipio de nome: %s ; de area: %d e populacao: %d\n", aux.nome_municipio, aux.area, aux.pop);
}

//===========================================================


//ESTRUTURAS DE INSERÇÃO DOS NÓS

struct no inserir_no_recursivo(no *aux, no *novo)
{
    if(aux != NULL)
    {
        //maior vai pra direita
        if(strcmp(novo->m.nome_municipio, aux->m.nome_municipio)>0)
        {
            if(aux->d == NULL)
            {
                aux->d = novo;
            }
            else
            {
                inserir_no_recursivo(aux->d, novo);
            }
        }
        //menor vai pra esquerda
        else
        {
            if(aux->e == NULL)
            {
                aux->e = novo;
            }
            else
            {
                inserir_no_recursivo(aux->e, novo);
            }

        }

    }
}

struct no* inserir_no()
{
    struct no *novo, *aux;
    novo = (struct no*) malloc(sizeof(struct no));
    if (novo != NULL)
    {
        novo->m = recebeMunicipio();
        novo->d = novo->e = NULL;

        if (raiz == NULL)
        {
            raiz = novo;
        }
        else
        {
            inserir_no_recursivo(raiz, novo);
        }
        return novo;
    }

}


//FUNÇÃO PARA INSERIR DADOS INFORMADOS PELO USUÁRIO NA ÁRVORE

void inserir(){
	system("cls");
    printf("\n======= INSERIR =======\n");
	no *aux;
    aux = inserir_no();    
    if(aux != NULL)
    {
        printf("\nInserido com sucesso no endereco: %x", aux);
        printf("\nNome: %s", aux->m.nome_municipio);
        printf("\nArea de: %d Km2", aux->m.area);
        printf("\nPopulacao de: %d", aux->m.pop);        
    }
    else
    {
        printf("\nErro na insercao!");
    }

	printf("\n\nTecle algo.");
    _getch();
}

//===========================================================


//FUNÇÃO PARA LISTAR MUNICIPIOS EM ORDEM E COM TODOS OS DADOS

void listar_no_emordem (no *aux)
{
    if (aux != NULL)
    {
        listar_no_emordem(aux->e);
        mostraMunicipio(aux->m);
        listar_no_emordem(aux->d);
    }
}

void listar(){
	system("cls");
	printf("\n======= LISTAR MUNICIPIOS EM ORDEM =======\n");    
	listar_no_emordem(raiz);
	printf("\n\nTecle algo.");
    _getch();
}

//===========================================================


//FUNÇÃO PARA CONTAR OS MUNICÍPIOS

int conta_nos (no *aux) {
    if (aux == NULL) return 0;
    else {
        int conte = conta_nos (aux->e);
        int contd = conta_nos (aux->d);
        return conte + contd + 1;
    }
}

void contarMunicipio()
{
	system("cls");
	printf("\n======= NÚMERO DE MUNICIPIOS =======\n");     
    conta_nos(raiz);
    printf("\n\nA quantidade de municípios é: %d\n", conta_nos(raiz));
    printf("\n\nTecle algo.");
    _getch();
}

//===========================================================


//FUNÇÃO QUE MOSTRA CIDADES COM MAIS DE 100.000 HABITANTES

int x = 0;

void bigMunicipio(no *aux)
{
	x = 100000;
    if (aux != NULL)
    {   
		bigMunicipio(aux->e);    
    	if (aux->m.pop >= x) 
        {
            
            mostraMunicipio(aux->m);
            bigMunicipio (aux->d);
        }
	}
}

void mostraBigMunicipio()
{
	system("cls");
	printf("\n======= MUNICIPIOS COM MAIS DE CEM MIL HABITANTES =======\n");    
    printf("\n\nMunicipios com mais de 100.000 habitantes: \n" );
    bigMunicipio(raiz);
    printf("\n\nTecle algo.");
    _getch();
}

//===========================================================


//FUNÇÃO QUE MOSTRA A DENSIDADE DEMOGRÁFICA

void densidade (Municipio aux)
{	
	printf("\nA densidade demografica de %s e: %.2f hab/Km2", aux.nome_municipio, aux.densi);	
}

void calcDensidade(no *aux)
{	
	
	if (aux != NULL)
	{
		calcDensidade(aux->e);
		densidade(aux->m);
		calcDensidade(aux->d);		
	}
}

void mostraDensidade()
{
	system("cls");
	printf("\n======= DENSIDADE DEMOGRAFICA DOS MUNICIPIOS =======\n");    
	calcDensidade(raiz);
	printf("\n\nTecle algo.");
    _getch();
}

//===========================================================


//FUNÇÃO MOSTRA SOMATÓRIO DA ÁREA DAS CIDADES EM RELAÇÃO AO TERRITÓRIO NACIONAL(PORCENTAGEM)

int somaArea(no *aux)
{
	int soma = 0;
		
	if (aux == NULL) return 0;	
	else 
	{		
		soma += somaArea(aux->e);
		soma += (aux->m.area);
		soma += somaArea(aux->d);
	
		return soma;
	}
}

void mostraSoma()
{	
	system("cls");
	printf("\n======= SOMA DAS AREAS =======\n");    
	float areaNacio = 8511000;
	float calcNacio;
	somaArea(raiz);
 	printf("\n\nA soma das areas e: %d", somaArea(raiz));
 	calcNacio = (somaArea(raiz) / areaNacio) * 100;
 	printf("\n\nA soma das areas informadas equivale a %f %% do territorio nacional.", calcNacio);
 	printf("\n\nTecle algo.");
    _getch();
}


//-----------------------------------------------------------------------------------------------

