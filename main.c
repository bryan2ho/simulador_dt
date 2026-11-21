#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "estructuras.h"
#include "sistema_guardado.h"
#include "sistema_eventos.h"
#include "misc.h"
#include "menu.h"
#include "sistema_mercado.h"

/*
Recuerden incluir la cabecera estructuras.h en las cabeceras que creen y llamar su cabecera .h correspondiente para cada modulo .c que hagan;
al final todas deben estar incluidas aqui, pueden ver los archivos de sistema_guardado como ejemplola c
*/

//ejecuten el archivo escribiendo gcc main.c sistema_guardado.c -o test_guardado.exe (pero incluyan todos los .c que hayan hasta el momento, o los que ocupen probar)
//gcc main.c sistema_guardado.c sistema_eventos.c misc.c -o test_guardado.exe


int main(){

    Club mi_club;
    mi_club.plantilla = NULL;
    int opcion_inicial;
    srand(time(NULL)); 


do{
    mostrar_menu_inicial();
    scanf("%d", &opcion_inicial);

    switch(opcion_inicial) {
        case 1:
            if (mi_club.plantilla != NULL) {
                free(mi_club.plantilla);
                mi_club.plantilla = NULL;
                mi_club.total_jugadores = 0;
            }
            printf("=========================================\n");
            printf("Ingresa el nombre de tu club: ");
            scanf("%s", mi_club.nombre_equipo);
            printf("=========================================\n");

            inicializar_club(&mi_club);

            partida(&mi_club);
            limpiar_pantalla();
            break;
        case 2:

            if(cargar_partida(&mi_club));
            {
                partida(&mi_club);
            }else{
                prinft("No se pudo cargar la partida. Asegurate de que exista un archivo guardado.\n");
                enter_continuar();
            }
            break;
        case 3:
            mostrar_creditos();
            enter_continuar();
            break;
        case 4:
            printf("Saliendo del juego...\n");
            break;
        default:
            printf("Opcion invalida. Por favor, elige una opción valida.\n");
            enter_continuar();
            break;
    }
}while(opcion_inicial != 4);

if (mi_club.plantilla != NULL) {
    free(mi_club.plantilla);
    mi_club.plantilla = NULL;
    mi_club.total_jugadores = 0;
}
return 0;
}
