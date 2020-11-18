#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include "cancelar.h"
#include "consultas.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "reservar.h"

Lreservas cria_lista_res(void);
Lutilizadores cria_lista_util(void);
Lreservas destroi_lista_reservas(Lreservas lista);
Lutilizadores destroi_lista_util(Lutilizadores lista);
int compara_data(Data data1, Data data2);
int verifica_data(Data *dat);
int bissexto(int ano);
int conta(Lreservas lista_res);
void tirar_(char *s);
void por_(char *s);
void destruir_tudo(Sala *salas, Lutilizadores util);
int controla_digitos(int num);
int verifica_nif(int nif, Lutilizadores lista, Lutilizadores util);
void ordena(Lreservas reserva, int ord);

#endif /*FUNCOES_H_INCLUDED*/
