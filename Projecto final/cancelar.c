#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "cancelar.h"
#include "consultas.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "funcoes.h"
#include "reservar.h"


void cancelar_reserva(Sala *salas, Lutilizadores util){
	int sala, flag=0;
	Data data;
	char op;
	system("cls");
	puts("\t\tRESERVAS\t\t");
	puts("----------------------------------------------");
	imprime_salas(salas,0);
	puts("----------------------------------------------");
	printf("\nNumero da sala a cancelar(1-30): ");
	do{
		scanf("%d",&sala); fflush(stdin);
		if((sala <1 || sala>30)){
			system("cls");
			printf("numero de sala invalido!\nInsira novamente:");
		}
	}while((sala <1) || (sala>30));

	if(salas[sala-1].res->next==NULL){
		printf("Nao existem reservas para a sala %d\n",sala);
		return;
	}

	printf("Insira a data (DD/MM/AAAA HH-MM): ");
	do{
		scanf("%d/%d/%d %d-%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minutos);
		fflush(stdin);
		switch(verifica_data(&data)){
			case 0: flag=0; break;
			case 1: system("cls"); printf("Ano invalido!\nInsira novamente:"); flag=1; break;
			case 2: system("cls"); printf("Mes invalido!\nInsira novamente:"); flag=1; break;
			case 3: system("cls"); printf("Dia invalido!\nInsira novamente:"); flag=1; break;
			case 4: system("cls"); printf("Hora invalido!\nInsira novamente:"); flag=1; break;
			case 5: system("cls"); printf("Minuto invalido!\nInsira novamente:"); flag=1; break;
			default: break;
		}
	}while(flag!=0);

	if(verifica_reserva_data(salas[sala-1].res,data)==0){
		printf("Nao existem reservas em %d/%d/%d %d-%d\n",data.dia,data.mes,data.ano,data.hora,data.minutos);
		return;
	}
	else{
		Lreservas aux;
		if ((aux=(Lreservas)malloc(sizeof(Reserva)))==NULL){
			printf("erro ao alucar memoria\n");
		}
		aux = procura_no(salas[sala-1].res, data);
		imprime_no(aux,procura_utilizador(util,aux->NIF));
		printf("Deseja confirmar a cancela? (s/n): ");
		do{
			scanf("%c",&op);
			fflush(stdin);
			if(toupper(op)==toupper('n'))
				return ;
			else if(toupper(op)==toupper('s'))
				break;
			else{
				system("cls");
				printf("Opcao invalida, insira novamente (s/n): ");
				continue;
			}
		}while(1);

		if(verifica_reserva_data(salas[sala-1].pre_res,data)==0){
			elimina_no(salas[sala-1].res,data);
		}
		else{
			troca_no(salas[sala-1].res,elimina_no(salas[sala-1].pre_res,data));
		}
		puts("Cancelado com sucesso!");
		free(aux);
	}
}

void cancelar_pre_reserva(Sala *salas, Lutilizadores util){
	int sala, flag=0;
	Data data;
	char op;
	system("cls");
	puts("\t\tPRE-RESERVAS\t\t");
	puts("----------------------------------------------");
	imprime_salas(salas,0);
	puts("----------------------------------------------");
	printf("Numero da sala a cancelar(1-15): ");
	do{
		scanf("%d",&sala); fflush(stdin);
		if((sala <1 || sala>MAXsalas)){
			system("cls");
			printf("numero de sala invalido!\nInsira novamente:");
		}
	}while((sala <1) || (sala>MAXsalas));

	if(salas[sala-1].res->next==NULL){
		printf("Nao existem pre-reservas para a sala %d\n",sala);
		return;
	}

	printf("Insira a data (DD/MM/AAAA HH-MM): ");
	do{
		scanf("%d/%d/%d %d-%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minutos);
		fflush(stdin);
		switch(verifica_data(&data)){
			case 0: flag=0; break;
			case 1: system("cls"); printf("Ano invalido!\nInsira novamente:"); flag=1; break;
			case 2: system("cls"); printf("Mes invalido!\nInsira novamente:"); flag=1; break;
			case 3: system("cls"); printf("Dia invalido!\nInsira novamente:"); flag=1; break;
			case 4: system("cls"); printf("Hora invalido!\nInsira novamente:"); flag=1; break;
			case 5: system("cls"); printf("Minuto invalido!\nInsira novamente:"); flag=1; break;
			default: break;
		}
	}while(flag!=0);

	if(verifica_reserva_data(salas[sala-1].pre_res,data)==0){
		printf("Nao existem pre-reservas em %d/%d/%d %d-%d\n",data.dia,data.mes,data.ano,data.hora,data.minutos);
		return;
	}
	else{
		Lreservas aux;
		if ((aux=(Lreservas)malloc(sizeof(Reserva)))==NULL){
			printf("erro ao alucar memoria\n");
		}
		aux = procura_no(salas[sala-1].pre_res, data);
		imprime_no(aux,procura_utilizador(util,aux->NIF));
		printf("Deseja confirmar a cancela? (s/n): ");
		do{
			scanf("%c",&op);
			fflush(stdin);
			if(toupper(op)==toupper('n'))
				return;
			else if(toupper(op)==toupper('s'))
				break;
			else{
				system("cls");
				printf("Opcao invalida, insira novamente (s/n): ");
				continue;
			}
		}while(1);
		if(elimina_no(salas[sala-1].res,data)!=NULL)
			puts("Eliminado com sucesso!");
		else
			puts("Erro a eliminar...");
	}
}

Lreservas elimina_no(Lreservas pre_reservas, Data data){
	Lreservas aux, ant;
	ant=pre_reservas;
	aux=pre_reservas->next;
	while(aux){
		if((compara_data(aux->data, data)) == 0){
			ant->next=aux->next;
			return aux;
		}
		ant=ant->next;
		aux=aux->next;
	}
	return NULL;
}
