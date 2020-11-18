#ifndef RESERVAR_H_INCLUDED
#define RESERVAR_H_INCLUDED

#include "cancelar.h"
#include "consultas.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "funcoes.h"

void fazer_reserva(Sala *salas, Lutilizadores util);
int pedir_dados(Sala *salas, Lutilizadores util, Lreservas *aux);
int ver_disponibilidade(Sala *salas, int sala, Data data);
int tem_pre_reservas(Lreservas pre_reservas, int nif, Data data);
int verifica_reserva_data(Lreservas pre_reservas, Data data);
void troca_no(Lreservas res, Lreservas no_pre);
void preencher(Sala *salas, Lutilizadores cliente, Lreservas res, int nif, int flag);
void insere_no(Lreservas lista, Lreservas no);
void insere_nome(Lutilizadores lista, Lutilizadores no);

#endif /*RESERVAR_H_INCLUDED*/
