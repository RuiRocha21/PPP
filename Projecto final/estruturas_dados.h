#ifndef ESTRUTURAS_DADOS_H_INCLUDED
#define ESTRUTURAS_DADOS_H_INCLUDED

#define MAXsalas 30
#define tamanho 50

#define freservas "reservas.txt"
#define fpre_reservas "pre-reservas.txt"
#define futil "clientes.txt"

typedef struct Reserva *Lreservas;
typedef struct Pessoa *Lutilizadores;

typedef struct Data{
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
}Data;

typedef struct Pessoa{
    int NIF;
    int n_telemovel;
    char nome[tamanho];
    Lutilizadores next;
}Pessoa;

typedef struct Reserva{
    int NIF;
    int sala;
    Data data;
    Lreservas next;
}Reserva;

typedef struct Sala{
    Lreservas res;
    Lreservas pre_res;
}Sala;

FILE *fp;	/*ponteiro para o ficheiro*/

#endif /*ESTRUTURAS_DADOS_H_INCLUDED*/
