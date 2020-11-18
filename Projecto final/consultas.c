#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "cancelar.h"
#include "consultas.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "funcoes.h"
#include "reservar.h"

void imprime_sala(Sala *salas, Lutilizadores clientes)
{
    int sala;
    printf("Numero da sala a listar(1-%d): ",MAXsalas);
    do
    {
        scanf("%d",&sala);
        fflush(stdin);
        if((sala <1 || sala>MAXsalas))
        {
            system("cls");
            printf("numero de sala invalido!\nInsira novamente:");
        }
    }
    while((sala <1) || (sala>MAXsalas));
    system("cls");
    if(salas[sala-1].res->next==NULL)
    {
        printf("Nao tem reservas para a sala %d\n", sala);
    }
    else
    {
        puts("---------------------------------------");
        puts("RESERVAS");
        puts("---------------------------------------");
        ordena(salas[sala-1].res,1);
        imprime_informacao(salas[sala-1].res,clientes);
    }
    if(salas[sala-1].pre_res->next==NULL)
    {
        printf("Nao tem pre-reservas para a sala %d\n", sala);
    }
    else
    {
        puts("PRE-RESERVAS");
        puts("---------------------------------------");
        ordena(salas[sala-1].pre_res,1);
        imprime_informacao(salas[sala-1].pre_res,clientes);
    }
}

void imprime_utilizador(Sala *salas, Lutilizadores clientes)
{
    int nif;
    Lutilizadores x,aux;
    Lreservas res, pre_res;
    char op;
    aux=clientes->next;
    res=cria_lista_res();
    pre_res=cria_lista_res();
    system("cls");
    puts("\tUTILIZADORES");
    puts("-----------------------------------");
    while(aux)
    {
        printf("NIF: %d \tNome: %s\n",aux->NIF, aux->nome);
        aux=aux->next;
    }
    puts("-----------------------------------");
    if((x=(Lutilizadores) malloc(sizeof(Pessoa)))==NULL)
        printf("erro ao alucar memoria\n");
    do
    {
        printf("\nInsira o numero de identificacao:");
        do
        {
            scanf("%d",&nif);
            fflush(stdin);
            if ((controla_digitos(nif))!=9)
            {
                system("cls");
                printf("Numero tem de ter 9 digitos!!\nIntroduza novamente : ");
            }
        }
        while((controla_digitos(nif))!=9);
        system("cls");
        if(verifica_nif(nif,clientes,x)!=1)
        {
            printf("Numero de identificacao inexistente!\nInserir de novo(s/n):\n");
            do
            {
                scanf("%c",&op);
                fflush(stdin);
                if(toupper(op)==toupper('n'))
                    return ;
                else if(toupper(op)==toupper('s'))
                    break;
                else
                {
                    system("cls");
                    printf("Opcao invalida, insira novamente (s/n): ");
                    continue;
                }
            }
            while(1);
        }
    }
    while(verifica_nif(nif,clientes,x)!=1);
    system("cls");
    preencher(salas,clientes,res,nif,0);
    if(res->next==NULL)
        printf("Nao tem reservas para o numero de identificacao %d\n",nif);
    else
    {
        puts("---------------------------------------");
        puts("RESERVAS");
        puts("---------------------------------------");
        ordena(res,-1);
        imprime_informacao(res,clientes);
    }
    preencher(salas,clientes,pre_res,nif,1);
    if(pre_res->next==NULL)
        printf("Nao tem pre-reservas para o numero de identificacao %d\n",nif);
    else
    {
        puts("PRE-RESERVAS");
        puts("---------------------------------------");
        ordena(pre_res,-1);
        imprime_informacao(pre_res,clientes);
    }
    free(x);
}

Lreservas procura_no(Lreservas res, Data data){
	Lreservas aux = res->next;
	while(aux){
		if((compara_data(aux->data, data) == 0))
			return aux;
		aux=aux->next;
	}
	return NULL;
}

void imprime_salas(Sala *salas,int f){
	int i;
	Lreservas aux;
	for (i=0; i<MAXsalas; i++){
		if(f==0){
			aux=salas[i].res->next;
			while(aux){
				printf("Sala: %d\tData: %d/%d/%d %d-%d\tN.I: %d\n",i+1, aux->data.dia, aux->data.mes, aux->data.ano, aux->data.hora, aux->data.minutos, aux->NIF);
				aux=aux->next;
			}
		}
		else if(f==1){
			aux=salas[i].pre_res->next;
			while(aux){
				printf("Sala: %d\tData: %d/%d/%d %d-%d\tN.I: %d\n",i+1, aux->data.dia, aux->data.mes, aux->data.ano, aux->data.hora, aux->data.minutos, aux->NIF);
				aux=aux->next;
			}
		}
	}
}

void imprime_informacao(Lreservas reservas, Lutilizadores util){
	Lreservas aux=reservas->next;
	while(aux){
		imprime_no(aux,procura_utilizador(util,aux->NIF));
		aux=aux->next;
	}
}

void imprime_no(Lreservas lista_res, Lutilizadores lista_util){
	printf("Numero de contribuinte:   %d\n",lista_res->NIF);
	printf("Nome:                %s\n",lista_util->nome);
	printf("telemovel:           %d\n",lista_util->n_telemovel);
	printf("Sala:                %d\n",lista_res->sala);
	printf("Data:                %d/%d/%d %d-%d\n", lista_res->data.dia, lista_res->data.mes, lista_res->data.ano, lista_res->data.hora, lista_res->data.minutos);
	puts("-----------------------------------------------------------------");
}

Lutilizadores procura_utilizador(Lutilizadores lista,int nif){
    Lutilizadores aux=lista->next;
	while(aux){
		if(aux->NIF==nif)
			return aux;
		aux=aux->next;
	}
	return NULL;
}
