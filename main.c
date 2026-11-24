#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "estructuras.h"
#include "sistema_guardado.h"
#include "sistema_eventos.h"
#include "sistema_mercado.h"
#include "misc.h"
#include "menu.h"

//gcc main.c menu.c misc.c sistema_mercado.c sistema_eventos.c sistema_guardado.c -o simulador_dt.exe

static void limpiar_buffer_main(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void liberar_club(Club *club) {
    if (club != NULL && club->plantilla != NULL) {
        free(club->plantilla);
        club->plantilla = NULL;
        club->total_jugadores = 0;
    }
}

static void solicitar_nombre_club(Club *club) {
    printf("=========================================\n");
    printf("Ingresa el nombre de tu club: ");
    if (fgets(club->nombre_equipo, sizeof(club->nombre_equipo), stdin) != NULL) {
        size_t len = strlen(club->nombre_equipo);
        while (len > 0 && (club->nombre_equipo[len - 1] == '\n' || club->nombre_equipo[len - 1] == '\r')) {
            club->nombre_equipo[len - 1] = '\0';
            len--;
        }
    }
    if (club->nombre_equipo[0] == '\0') {
        strcpy(club->nombre_equipo, "FC Nuevo Leon");
    }
    printf("=========================================\n");
}

int main(void) {
    Club mi_club;
    mi_club.plantilla = NULL;
    mi_club.total_jugadores = 0;
    mi_club.presupuesto = 0;
    mi_club.dia_actual = 1;
    mi_club.nombre_equipo[0] = '\0';

    int opcion_inicial = 0;
    srand((unsigned int)time(NULL));

    do {
        mostrar_menu_inicial();

        if (scanf("%d", &opcion_inicial) != 1) {
            limpiar_buffer_main();
            printf("Opcion invalida. Por favor, elige una opcion valida.\n");
            enter_continuar();
            continue;
        }
        limpiar_buffer_main();

        switch (opcion_inicial) {
            case 1:
                liberar_club(&mi_club);
                solicitar_nombre_club(&mi_club);
                inicializar_club(&mi_club);

                if (mi_club.plantilla != NULL) {
                    partida(&mi_club);
                    liberar_club(&mi_club);
                }
                limpiar_pantalla();
                break;

            case 2:
                liberar_club(&mi_club);

                if (cargar_partida(&mi_club)) {
                    partida(&mi_club);
                    liberar_club(&mi_club);
                    limpiar_pantalla();
                } else {
                    printf("No se pudo cargar la partida. Asegurate de que exista un archivo guardado.\n");
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
                printf("Opcion invalida. Por favor, elige una opcion valida.\n");
                enter_continuar();
                break;
        }
    } while (opcion_inicial != 4);

    liberar_club(&mi_club);
    return 0;
}