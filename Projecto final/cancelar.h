#ifndef CANCELAR_H_INCLUDED
#define CANCELAR_H_INCLUDED

#include "consultas.h"
#include "estruturas_dados.h"
#include "ficheiros.h"
#include "funcoes.h"
#include "reservar.h"

void cancelar_reserva(Sala *salas, Lutilizadores util);
void cancelar_pre_reserva(Sala *salas, Lutilizadores util);
Lreservas elimina_no(Lreservas pre_reservas, Data data);


#endif /* CANCELAR_H_INCLUDED*/
