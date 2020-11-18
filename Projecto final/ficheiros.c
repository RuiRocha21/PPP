#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "cancelar.h"
#include "consultas.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "funcoes.h"
#include "reservar.h"

void carregar_dados(Sala *salas, Lutilizadores util){
    int i;
	ler_nomes(util);
	for(i=0; i<MAXsalas; i++){
		salas[i].res=cria_lista_res();
		salas[i].pre_res=cria_lista_res();
	}
	ler_reservas(salas, freservas);
	ler_reservas(salas, fpre_reservas);
}

void ler_nomes(Lutilizadores util){
    Lutilizadores aux;
    Lutilizadores ant;
	aux=util;
	ant=util;
	if (ficheiro_vazio(futil) == 1){
		return;
	}

	if ((fp=fopen(futil,"r"))==NULL){
		printf("erro ao abrir ficheiro\n");
	}
	if ((aux=(Lutilizadores)malloc(sizeof(Pessoa)))==NULL){
		printf("erro ao alucar memoria\n");
	}
	while((fscanf(fp,"%d %s %d", &aux->NIF, aux->nome, &aux->n_telemovel))!=EOF){
		Lutilizadores aux2;
		if ((aux2=(Lutilizadores)malloc(sizeof(Pessoa)))==NULL){
			printf("erro ao alucar memoria\n");
		}
		tirar_(aux->nome);
		*aux2 = *aux;
		while(ant->next){
			ant = ant->next;
		}
		ant->next = aux2;
		aux2->next = NULL;
	}
	fclose(fp);
}

void ler_reservas(Sala *salas, char *ficheiro){
	Lreservas aux;
	if (ficheiro_vazio(ficheiro) == 1)
		return;
	if((fp=fopen(ficheiro,"r"))==NULL)
		printf("erro ao abrir o ficheiro\n");
	if((aux=(Lreservas)malloc(sizeof(Reserva)))==NULL)
		printf("erro ao alucar memoria\n");
	if(strcmp(ficheiro,freservas)==0){
		while((fscanf(fp,"%d %d %d/%d/%d %d-%d", &aux->NIF, &aux->sala, &aux->data.dia, &aux->data.mes, &aux->data.ano, &aux->data.hora, &aux->data.minutos))!=EOF){
			Lreservas aux2;
			if((aux2=(Lreservas)malloc(sizeof(Reserva)))==NULL)
				printf("erro ao alucar memoria");
			*aux2 = *aux;
			insere_no(salas[aux->sala-1].res,aux2);
		}
	}
	else if(strcmp(ficheiro,fpre_reservas)==0){
		while((fscanf(fp,"%d %d %d/%d/%d %d-%d", &aux->NIF, &aux->sala, &aux->data.dia, &aux->data.mes, &aux->data.ano, &aux->data.hora, &aux->data.minutos))!=EOF){
			Lreservas aux2;
			if((aux2=(Lreservas)malloc(sizeof(Reserva)))==NULL)
				printf("erro ao alucar memoria");
			*aux2 = *aux;
			insere_no(salas[aux->sala-1].pre_res,aux2);
		}
	}
	fclose(fp);
}

void guardar_dados(Sala *salas, Lutilizadores util){
	int i;
	Lutilizadores aux;
    Lreservas aux2;
	if((fp=fopen(futil,"w"))==NULL)
		printf("erro ao abrir o ficheiro\n");
	aux=util->next;
	while(aux){
		por_(aux->nome);
		if((fprintf(fp,"%d %s %d\n", aux->NIF, aux->nome, aux->n_telemovel))<=0)
			printf("erro ao escrever no ficheiro\n");
		aux=aux->next;
	}
	fclose(fp);

	if((fp=fopen(freservas,"w"))==NULL)
		printf("erro ao abrir o ficheiro\n");
	for (i=0; i<MAXsalas; i++){
		aux2=salas[i].res->next;
		while(aux2){
			if((fprintf(fp,"%d %d %d/%d/%d %d-%d\n", aux2->NIF, aux2->sala, aux2->data.dia, aux2->data.mes, aux2->data.ano, aux2->data.hora, aux2->data.minutos))<=0)
				printf("erro ao escrever no ficheiro");
			aux2=aux2->next;
		}
	}
	fclose(fp);

	if((fp=fopen(fpre_reservas,"w"))==NULL)
		printf("erro ao abrir o ficheiro");
	for (i=0; i<MAXsalas; i++){
		aux2=salas[i].pre_res->next;
		while(aux2){
			if((fprintf(fp,"%d %d %d/%d/%d %d-%d\n", aux2->NIF, aux2->sala, aux2->data.dia, aux2->data.mes, aux2->data.ano, aux2->data.hora, aux2->data.minutos))<=0)
				printf("erro ao escrever no ficheiro");
			aux2=aux2->next;
		}
	}
	fclose(fp);
}

int ficheiro_vazio(char *fich){
	if((fp=fopen(fich,"r"))==NULL)
		return 1;
	return 0;
}
