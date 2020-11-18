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

Lreservas cria_lista_res(void){
    Lreservas aux;
    aux = (Lreservas)malloc(sizeof(Reserva));
    if(aux==NULL){
        printf("erro ao alucar memoria\n");
        exit(-1);
    }
    aux->next=NULL;
    return aux;
}

Lutilizadores cria_lista_util(void){
    Lutilizadores aux;
    aux = (Lutilizadores)malloc(sizeof(Pessoa));
    if(aux==NULL){
        printf("erro ao alucar memoria\n");
        exit(-1);
    }
    aux->next=NULL;
    return aux;
}

Lreservas destroi_lista_reservas(Lreservas lista){
    Lreservas temp_ptr;
    while(lista!=NULL){
        temp_ptr = lista;
        lista = lista->next;
        free(temp_ptr);
    }
    free(lista);
    return NULL;
}

Lutilizadores destroi_lista_util(Lutilizadores lista){
    Lutilizadores temp_ptr;
    while(lista!=NULL){
        temp_ptr = lista;
        lista = lista->next;
        free(temp_ptr);
    }
    free(lista);
    return NULL;
}

int compara_data(Data data1, Data data2){
    if(data1.ano > data2.ano){
        return 1;
    }
    else if(data1.ano < data2.ano){
        return -1;
    }
    else{
        if(data1.mes > data2.mes){
            return 1;
        }
        else if(data1.mes < data2.mes){
            return -1;
        }
        else{
            if(data1.dia > data2.dia){
                return 1;
            }
            else if(data1.dia < data2.dia){
                return -1;
            }
            else{
                if(data1.hora > data2.hora){
                    return 1;
                }
                else if(data1.hora < data2.hora){
                    return -1;
                }
                else{
                    if(data1.minutos > data2.minutos){
                        return 1;
                    }
                    else if(data1.minutos < data2.minutos){
                        return -1;
                    }
                    else{
                        return 0;
                    }
                }
            }
        }
    }
}

int verifica_data(Data *data){
	int ano,mes,dia,hora,minutos;
	ano=data->ano;
	mes=data->mes;
	dia=data->dia;
	hora=data->hora;
	minutos=data->minutos;

	if(ano<2013)	/*nao podes reservar atras da data atual*/
		return 1;
	else{
		if( ((mes<5 && ano==2013) || mes>12)  ||  (mes<0||mes>12) )	/*se ano 2013 n pode rsvr mes<5 */
			return 2;
		else{
			if(((dia>28 && mes==2 && bissexto(ano)!=0) || (dia>29 && mes==2)) || ((mes==4 || mes==6 || mes==9 || mes==11) && dia>30) || ((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && dia>31) || dia<0)
				return 3;	/*testar os dias dos meses*/
			else{
				if(hora<10 || hora>24)
					return 4;
				else{
					if(minutos!=0 && minutos!=30)
						return 5;	/*so pode reservar em intervalos de 30min*/
					else
						return 0;
				}
			}
		}
	}
}

int bissexto(int ano){
	if(ano%4==0)
		return 0;
	return 1;
}

int conta(Lreservas lista_res){
	int tam;
	Lreservas aux;
	aux=lista_res->next;
    tam=0;
	while(aux!=NULL){
		tam++;
		aux = aux->next;
	}
	return tam;
}

void por_(char *s){
	int i;
	for(i=0; s[i]!='\0';i++){
		if(s[i]==' ')
			s[i]='_';
	}
}

void tirar_(char *s){
	int i;
	for(i=0; s[i]!='\0';i++){
		if(s[i]=='_')
			s[i]=' ';
	}
}

void destruir_tudo(Sala *salas, Lutilizadores util)
{
    int i;
	destroi_lista_util(util);
	for (i=0; i<MAXsalas; i++){
		destroi_lista_reservas(salas[i].res);
		destroi_lista_reservas(salas[i].pre_res);
	}
}

int controla_digitos(int num){
	int conta=0;
	while(num>0)
	{
		num = num/10;
		conta++;
	}
	return conta;
}

int verifica_nif(int nif, Lutilizadores lista, Lutilizadores util){
	Lutilizadores aux = lista->next;
	while(aux){
		if(nif==aux->NIF){
			*util=*aux;
			return 1;
		}
		aux=aux->next;
	}
	return 0;
}

void ordena(Lreservas res, int ord){	/* se 1-> crescente, -1->decrescente*/
	int i,j;
	Lreservas ant,atual,pro,aux;
	for (i = 0; i <(conta(res)); ++i)
	{
		j = 1;
		ant = res;
		atual = res->next;
		while(j<(conta(res)))
		{
			pro = atual->next;
			aux = pro->next;
			if(compara_data((atual->data),(pro->data)) == ord)
			{
				ant->next = pro;
				pro->next = atual;
				atual->next = aux;
			}
			ant = ant->next;
			atual = ant->next;
			j++;
		}
	}
}
