#ifndef CONSULTAS_H_INCLUDED
#define CONSULTAS_H_INCLUDED

#include "cancelar.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "funcoes.h"
#include "reservar.h"

void imprime_sala(Sala *salas, Lutilizadores cliente);
void imprime_utilizador(Sala *salas, Lutilizadores cliente);
Lreservas procura_no(Lreservas res, Data data);
void imprime_salas(Sala *salas,int f);
void imprime_informacao(Lreservas reservas, Lutilizadores util);
void imprime_no(Lreservas lista_res, Lutilizadores lista_util);
Lutilizadores procura_utilizador(Lutilizadores lista,int nif);


#endif /*CONSULTAS_H_INCLUDED*/
