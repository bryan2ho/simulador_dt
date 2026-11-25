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
#include <locale.h> //para poder incluir acentos y la ñ
#ifdef _WIN32
    #include <windows.h>
#endif

// gcc main.c menu.c misc.c sistema_mercado.c sistema_eventos.c sistema_guardado.c -o simulador_dt.exe

static void liberar_club(Club *club) {
    if (club->plantilla != NULL) {
        free(club->plantilla);
        club->plantilla = NULL;
        club->total_jugadores = 0;
    }
}

static void solicitar_nombre_club(Club *club) {
    printf("=========================================\n");
    printf("Ingresa el nombre de tu club: ");
    if (fgets(club->nombre_equipo, sizeof(club->nombre_equipo), stdin) != NULL) {
        club->nombre_equipo[strcspn(club->nombre_equipo, "\r\n")] = '\0';
    }
    if (club->nombre_equipo[0] == '\0') {
        strcpy(club->nombre_equipo, "FC FM");
    }
    printf("=========================================\n");
}

int main(void) {

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    setlocale(LC_ALL, ".UTF-8");

    Club mi_club = {0};
    mi_club.dia_actual = 1;
    int opcion_inicial = 0;
    srand((unsigned int)time(NULL));

    do {
        mostrar_menu_inicial();

        if (scanf("%d", &opcion_inicial) != 1) {
            opcion_inicial = -1;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        switch (opcion_inicial) {
            case 1:
                liberar_club(&mi_club);
                solicitar_nombre_club(&mi_club);
                inicializar_club(&mi_club);
                partida(&mi_club);
                liberar_club(&mi_club);
                break;

            case 2:
                liberar_club(&mi_club);
                if (cargar_partida(&mi_club)) {
                    partida(&mi_club);
                    liberar_club(&mi_club);
                } else {
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
                printf("Opcion invalida.\n");
                enter_continuar();
                break;
        }
    } while (opcion_inicial != 4);

    liberar_club(&mi_club);
    return 0;
}