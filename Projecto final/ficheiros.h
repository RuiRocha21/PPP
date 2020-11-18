#ifndef FICHEIROS_H_INCLUDED
#define FICHEIROS_H_INCLUDED

#include "cancelar.h"
#include "consultas.h"
#include "estruturas_dados.h"
#include "funcoes.h"
#include "reservar.h"

void carregar_dados(Sala *salas, Lutilizadores util);
void ler_nomes(Lutilizadores util);
void ler_reservas(Sala *salas, char *ficheiro);
void guardar_dados(Sala *salas, Lutilizadores util);
int ficheiro_vazio(char *fich);

#endif /* FICHEIROS_H_INCLUDED */
