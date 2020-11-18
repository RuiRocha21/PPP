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

void fazer_reserva(Sala *salas, Lutilizadores util){
	Lreservas aux, aux2;
	int x;
	if((aux=(Lreservas) malloc(sizeof(Reserva)))==NULL)
		printf("erroao alucar memoria\n");
	if((aux2=(Lreservas) malloc(sizeof(Reserva)))==NULL)
		printf("erroao alucar memoria\n");
	x=pedir_dados(salas, util, &aux);
	*aux2=*aux;
	if(x==0){
		insere_no(salas[aux2->sala-1].res,aux2);
		puts("Inserido com sucesso!");
	}
	else if(x==1){
		insere_no(salas[aux2->sala-1].pre_res,aux2);
		puts("Inserido com sucesso!");
	}
	else
		puts("Operacao cancelada!");
	free(aux);
}

int pedir_dados(Sala *salas, Lutilizadores util, Lreservas *aux){
	char op;
	int flag=0, tipo;
	Lutilizadores x;
	system("cls");
	printf("Numero da sala pretendida(1-30): ");
	do{
		scanf("%d",&(*aux)->sala); fflush(stdin);
		if(((*aux)->sala <1 || (*aux)->sala>30)){
			system("cls");
			printf("numero de sala invalido!\nInsira novamente:");
		}
	}while(((*aux)->sala <1 || (*aux)->sala>30));
	printf("Insira a data (DD/MM/AAAA HH-MM): ");
	do{
		scanf("%d/%d/%d %d-%d", &(*aux)->data.dia, &(*aux)->data.mes, &(*aux)->data.ano, &(*aux)->data.hora, &(*aux)->data.minutos);
		fflush(stdin);
		switch(verifica_data(&(*aux)->data)){
			case 0: flag=0; break;
			case 1: system("cls"); printf("Ano invalido!\nInsira novamente:"); flag=1; break;
			case 2: system("cls"); printf("Mes invalido!\nInsira novamente:"); flag=1; break;
			case 3: system("cls"); printf("Dia invalido!\nInsira novamente:"); flag=1; break;
			case 4: system("cls"); printf("Hora invalido!\nInsira novamente:"); flag=1; break;
			case 5: system("cls"); printf("Minuto invalido!\nInsira novamente:"); flag=1; break;
			default: break;
		}
	}while(flag!=0);

	tipo=ver_disponibilidade(salas,(*aux)->sala,(*aux)->data);
	if (tipo==1){
		system("cls");
		printf("Data indisponivel, deseja Pre-reservar? (s/n): ");
		do{
			scanf("%c",&op);
			fflush(stdin);
			if(toupper(op)==toupper('n'))
				return -1;
			else if(toupper(op)==toupper('s'))
				break;
			else{
				system("cls");
				printf("Opcao invalida, insira novamente (s/n): ");
				continue;
			}
		}while(1);
	}
	do{
		printf("Numero de contribuinte: ");
		do{
			scanf("%d",&(*aux)->NIF); fflush(stdin);
			if ((controla_digitos((*aux)->NIF))!=9){
				system("cls");
				printf("Numero tem de ter 9 digitos!!\nIntroduza novamente : ");
			}
		}while((controla_digitos((*aux)->NIF))!=9);
		if((x=(Lutilizadores) malloc(sizeof(Pessoa)))==NULL)
			printf("erro ao alucar memoria");

		if((verifica_nif((*aux)->NIF,util,x)==1)){
			system("cls");
			puts("Registo ja existente!!");
			printf("Numero de contribuinte: %d\n",x->NIF);
			printf("Nome: %s\n",x->nome);
			printf("Contacto: %d\n",x->n_telemovel);
			printf("\nConfima esta informacao? (s/n): ");
			do{
				scanf("%c",&op); fflush(stdin);
				if(toupper(op)==toupper('n')){
					system("cls");
					flag=1;
					break;
				}
				else if(toupper(op)==toupper('s')){
					if ((tem_pre_reservas(salas[(*aux)->sala].pre_res,(*aux)->NIF,(*aux)->data)!=0) && (tipo == 1)){
						system("cls");
						printf("Impossivel pre-reservar \"%s\" ja tem pre-reserva para a sala \"%d\" na data \"%d/%d/%d %d:%d\"\n",x->nome, (*aux)->sala, (*aux)->data.dia, (*aux)->data.mes, (*aux)->data.ano, (*aux)->data.hora, (*aux)->data.minutos);
						return -1;
					}
					flag=0;
					break;
				}
				else{
					system("cls");
					printf("Opcao invalida, insira novamente (s/n): ");
					continue;
					}
			}while(1);
		}
		else{
			x->NIF=(*aux)->NIF;
			printf("Nome:"); gets(x->nome); fflush(stdin);
			printf("Contacto:");
			do{
				scanf("%d",&x->n_telemovel); fflush(stdin);
				if ((controla_digitos(x->n_telemovel))!=9){
					system("cls");
					printf("Numero tem de ter 9 digitos!!\nIntroduza novamente : ");
				}
			}while((controla_digitos(x->n_telemovel))!=9);
			insere_nome(util,x);
		}
	}while(flag!=0);
	(*aux)->next=NULL;
	return tipo;
}

int ver_disponibilidade(Sala *salas, int sala, Data data){
	Lreservas aux;
	int i;
	for (i=0; i<MAXsalas; i++){
		aux=salas[i].res->next;
		while(aux){
			if((aux->sala == sala) && (compara_data(aux->data, data) == 0))
				return 1;
			aux=aux->next;
		}
	}
	return 0;
}

int tem_pre_reservas (Lreservas pre_reservas, int nif, Data data){
	Lreservas aux = pre_reservas->next;
	while(aux){
		if((nif==aux->NIF) && (compara_data(aux->data, data) == 0))
			return 1;
		aux=aux->next;
	}
	return 0;
}

int verifica_reserva_data(Lreservas pre_reservas, Data data){
	Lreservas aux = pre_reservas->next;
	while(aux){
		if((compara_data(aux->data, data) == 0))
			return 1;
		aux=aux->next;
	}
	return 0;
}

void troca_no(Lreservas res, Lreservas no_pre){
	Lreservas ant=res;
	Lreservas aux=res->next;
	while(aux){
		if(compara_data(aux->data, no_pre->data)==0){
			ant->next=no_pre;
			no_pre->next=aux->next;
			free(aux);
			return;
		}
		aux=aux->next;
		ant=ant->next;
	}
}

void preencher(Sala *salas, Lutilizadores cliente, Lreservas res, int nif, int f)
{
    int i;
    Lreservas aux;
    for (i=0; i<MAXsalas; i++)
    {
        if(f==0)
        {
            aux=salas[i].res->next;
            while(aux)
            {
                Lreservas aux2;
                if((aux2=(Lreservas) malloc(sizeof(Reserva)))==NULL)
                    printf("erro ao alucar memoria\n");
                if(aux->NIF==nif)
                {
                    *aux2=*aux;
                    insere_no(res,aux2);
                }
                aux=aux->next;
            }
        }
        else if(f==1)
        {
            aux=salas[i].pre_res->next;
            while(aux)
            {
                Lreservas aux2;
                if((aux2=(Lreservas) malloc(sizeof(Reserva)))==NULL)
                    printf("erro ao alucar memoria\n");
                if(aux->NIF==nif)
                {
                    *aux2=*aux;
                    insere_no(res,aux2);
                }
                aux=aux->next;
            }
        }
    }
    free(aux);
}

void insere_no(Lreservas lista, Lreservas no){
	Lreservas aux;
	aux=lista;
	while(aux->next)
		aux=aux->next;
	aux->next=no;
	no->next=NULL;
}

void insere_nome(Lutilizadores lista, Lutilizadores no){
	Lutilizadores aux;
	aux=lista;
	while(aux->next)
		aux=aux->next;
	aux->next=no;
	no->next=NULL;
}
