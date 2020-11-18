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

#define op_reservar 	'1'
#define op_cancelar		'2'
#define op_listar		'3'
#define op_guardar		'4'
#define op_sair			'0'

#define op_list_dataSala	'1'
#define op_list_dataUtilizador	'2'
#define op_voltar		'0'

#define op_reserva	'1'
#define op_pre_reserva	'2'

char *MainMenu[]={
   "1. FAZER UMA RESERVA",
   "2. CANCELAR ",
   "3. LISTAGENS",
   "4. gravar dados",
   "0. Sair",
   NULL   /* Acabaram as Opçoes */
  };

char *MenuPesquisas[]={
	"1- Listagem por Sala:",
	"2- Listagem por Utilizador:",
	"0- Voltar",
	NULL
};
char *MenuCancelar[]={
	"1- Reserva:",
	"2- Pre-Reserva:",
	"0- Voltar",
	NULL
};

char Menu(char *Opcoes[]){
    int i;
    char ch;
    system("cls");
    while (1){
        printf("\n");
        for (i=0; Opcoes[i]!=NULL; i++){
            printf("\t%s\n",Opcoes[i]);
        }
        printf("\n\tOpcao: ");
        ch = getchar();
        fflush(stdin);
        for (i=0; Opcoes[i]!=NULL; i++){
            if (Opcoes[i][0]==ch)
                return ch;
        }
        return ch;
    }
}

int main()
{
    char opcao;
    Sala lista_salas[MAXsalas];
    Lutilizadores util=cria_lista_util();
    carregar_dados(lista_salas,util);

    system("cls");
    while((opcao=Menu(MainMenu))!=op_sair){
        system("cls");
        switch(opcao){
            case op_reservar: {
                fazer_reserva(lista_salas,util);
                system("pause");
                break;
            }
            case op_cancelar:{
				while((opcao=Menu(MenuCancelar))!=op_voltar){
					switch(opcao){
						case op_reserva: cancelar_reserva(lista_salas,util); system("pause"); break;
						case op_pre_reserva: cancelar_pre_reserva(lista_salas,util); system("pause"); break;
						default: break;
					}
				}
			} break;
			case op_listar:{
				while((opcao=Menu(MenuPesquisas))!=op_voltar){
					switch(opcao){
						case op_list_dataSala: imprime_sala(lista_salas,util); system("pause"); break;
						case op_list_dataUtilizador: imprime_utilizador(lista_salas,util); system("pause"); break;
						default: break;
					}
				}
			} break;
			case op_guardar: guardar_dados(lista_salas,util); puts("Guardado com sucesso!\n"); system("pause"); break;
			default: break;
		}
	}
	guardar_dados(lista_salas, util);
	destruir_tudo(lista_salas, util);
	return 0;
}
