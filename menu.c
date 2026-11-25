#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estructuras.h"
#include "sistema_guardado.h"
#include "sistema_eventos.h"
#include "sistema_mercado.h"
#include "menu.h"

#define MAX_POOL_MENU 100 //cantidad de jugadores que hay en jugadores.txt
#define TAM_TIENDA_MENU 20 //cantidad de jugadores a mostrar en la tienda

static int leer_entero(char *mensaje){
    int valor = 0;
    printf("%s", mensaje);
    if (scanf("%d", &valor) != 1) {
        valor = -1;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return valor;
}

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void enter_continuar() {
    printf("\nPresiona Enter para continuar...");
    getchar();
}

void mostrar_plantilla(Club *mi_club) {
    limpiar_pantalla();
    printf("\n================ TITULARES ================\n");
    printf("%-3s %-32s %-5s %-5s $%-10s\n", "#", "Nombre", "Pos", "Med", "Valor");
    printf("-------------------------------------------\n");

    for (int i = 0; i < mi_club->total_jugadores; i++) {
        Jugador j = mi_club->plantilla[i];
        if (j.titular) {
            printf("%-3d %-32s %-5s %-5d $%-10d\n", i + 1, j.nombre, j.posicion, j.media, j.valor);
        }
    }

    int cuenta_banca = 0;
    printf("\n================= BANCA ===================\n");
    printf("%-3s %-32s %-5s %-5s $%-10s\n", "#", "Nombre", "Pos", "Med", "Valor");
    printf("-------------------------------------------\n");

    for (int i = 0; i < mi_club->total_jugadores; i++) {
        Jugador j = mi_club->plantilla[i];
        if (!j.titular) {
            printf("%-3d %-32s %-5s %-5d $%-10d\n", i + 1, j.nombre, j.posicion, j.media, j.valor);
            cuenta_banca++;
        }
    }

    if (cuenta_banca == 0) {
        printf("No hay jugadores en la banca\n");
    }

    printf("-------------------------------------------\n");
    printf("Total plantilla: %d (11 titulares | %d banca)\n", mi_club->total_jugadores, cuenta_banca);
}

void mostrar_menu_inicial() {
    limpiar_pantalla();
    printf("\n========================================\n");
    printf("           SIMULADOR DE DT              \n");
    printf("========================================\n");
    printf(" [1] Iniciar Nueva Partida\n");
    printf(" [2] Cargar Partida Guardada\n");
    printf(" [3] Creditos\n");
    printf(" [4] Salir\n");
    printf("----------------------------------------\n");
    printf("Elige una opcion: ");
}

void mostrar_menu_principal(const char *nombre_club, int dia_actual, int presupuesto) {
    limpiar_pantalla();
    printf("\n========================================\n");
    printf("  %s\n", nombre_club);
    printf("  Día %d / 7  |  Presupuesto: $%d\n", dia_actual, presupuesto);
    printf("========================================\n");
    printf(" [1] Ver plantilla de jugadores\n");
    printf(" [2] Mercado de fichajes (Comprar/Vender)\n");
    printf(" [3] Avanzar al siguiente dia\n");
    printf(" [4] Guardar partida\n");
    printf(" [5] Salir al menu principal\n");
    printf("----------------------------------------\n");
    printf("Elige una opcion: ");
}

void mostrar_creditos() {
    limpiar_pantalla();
    printf("=========================================\n");
    printf("                Créditos                 \n");
    printf("=========================================\n");
    printf("Equipo\n");
    printf("Alejandro Guardiola Rodríguez\n");
    printf("Bryan Armando Cano Guzmán\n");
    printf("Ian Emmanuel Valle Reza\n");
    printf("Miranda Mariel Vidales Gutiérrez\n");
}

void inicializar_club(Club *mi_club) {
    mi_club->dia_actual = 1;
    mi_club->presupuesto = 5000000;
    mi_club->total_jugadores = 11;
    mi_club->plantilla = malloc(mi_club->total_jugadores * sizeof(Jugador));
    if (mi_club->plantilla == NULL) {
        printf("Error al asignar memoria\n");
        return;
    }

    Jugador jugadores_iniciales[11] = {
        {"Amadeo Gonzalez", "DEL", 70, 220000},
        {"Donatello Versus", "DEF", 69, 340000},
        {"Ceasar Zeppeli", "MED", 71, 260000},
        {"Chiruno", "DEL", 72, 280000},
        {"Saul Goodman", "DEF", 75, 340000},
        {"Alesin", "MED", 71, 480000},
        {"Dewey Wilkerson", "MED", 70, 200000},
        {"Finnick Odair", "MED", 68, 230000},
        {"Dio Brando", "DEF", 70, 700000},
        {"Oliver Atom", "DEF", 67, 520000},
        {"Gagamaru", "POR", 70, 370000}
    };

    for (int i = 0; i < mi_club->total_jugadores; i++) {
        mi_club->plantilla[i] = jugadores_iniciales[i];
        mi_club->plantilla[i].titular = true;
    }
}

void mercado(Club *mi_club, Jugador tienda[], int total_tienda) {
    int opcion = 0;

    do {
        limpiar_pantalla();
        printf("========================================\n");
        printf("         MERCADO DE FICHAJES            \n");
        printf("  Presupuesto: $%d | Plantilla: %d\n", mi_club->presupuesto, mi_club->total_jugadores);
        printf("========================================\n");
        printf("[1] Comprar jugador\n");
        printf("[2] Vender jugador\n");
        printf("[3] Regresar al menu principal\n");
        printf("----------------------------------------\n");

        opcion = leer_entero("Elige una opcion: ");

        switch (opcion) {
            case 1: {
                limpiar_pantalla();
                mostrar_tienda(tienda, total_tienda);
                int num_elegido = leer_entero("\nIngresa el # del jugador a comprar (0 para cancelar): ");
                if (num_elegido > 0) {
                    comprar_jugador(mi_club, tienda, total_tienda, num_elegido - 1);
                } else if (num_elegido < 0) {
                    printf("Entrada invalida.\n");
                }
                enter_continuar();
                break;
            }

            case 2: {
                limpiar_pantalla();
                if (!puede_vender(mi_club)) {
                    enter_continuar();
                    break;
                }
                mostrar_plantilla(mi_club);
                int num_vender = leer_entero("\nIngresa el # del jugador de tu plantilla a vender (0 para cancelar): ");
                if (num_vender > 0) {
                    vender_jugador(mi_club, num_vender - 1);
                } else if (num_vender < 0) {
                    printf("Entrada invalida.\n");
                }
                enter_continuar();
                break;
            }

            case 3:
                break;

            default:
                printf("Opcion invalida.\n");
                enter_continuar();
                break;
        }
    } while (opcion != 3);
}

void partida(Club *mi_club){
    Jugador pool[MAX_POOL_MENU];
    int total_pool = cargar_jugadores(pool);
    Jugador tienda[TAM_TIENDA_MENU] = {0};

    seleccionar_jugadores(pool, total_pool, tienda);

    int opcion = 0;

    do {
        mostrar_menu_principal(mi_club->nombre_equipo, mi_club->dia_actual, mi_club->presupuesto);
        opcion = leer_entero("");

        switch (opcion) {
            case 1: {
                mostrar_plantilla(mi_club);
                int resp = leer_entero("\n¿Deseas intercambiar titular por banca? (1 = Si, 0 = No): ");
                if (resp == 1) {
                    intercambiar_titular_banca(mi_club);
                } else {
                    enter_continuar();
                }
                break;
            }

            case 2:
                mercado(mi_club, tienda, TAM_TIENDA_MENU);
                break;

            case 3:
                limpiar_pantalla();
                printf("Avanzando al siguiente dia...\n");
                if (mi_club->dia_actual < 7) {
                    eventos_ejecutar(mi_club);
                    mi_club->dia_actual++;
                    mi_club->presupuesto += 700000;
                    variar_precios(pool, total_pool);
                    seleccionar_jugadores(pool, total_pool, tienda);
                } else {
                    eventos_final(mi_club);
                    mi_club->dia_actual++;
                }
                enter_continuar();
                break;

            case 4:
                guardar_partida(mi_club);
                enter_continuar();
                break;

            case 5:
                break;

            default:
                printf("Opcion invalida.\n");
                enter_continuar();
                break;
        }
    } while (mi_club->dia_actual <= 7 && opcion != 5);
}

bool puede_vender(Club *mi_club) {
    if (mi_club->total_jugadores <= 11) {
        printf("\nNo puedes vender mas jugadores: la plantilla debe tener al menos 11 jugadores.\n");
        return false;
    }
    return true;
}

void intercambiar_titular_banca(Club *mi_club) {
    mostrar_plantilla(mi_club);

    if (mi_club->total_jugadores <= 11) {
        printf("\nNo tienes jugadores en la banca para intercambiar.\n");
        enter_continuar();
        return;
    }

    int num_titular = leer_entero("\nIngresa el # del TITULAR que pasa a banca: ");
    int num_banca = leer_entero("Ingresa el # de la BANCA que pasa a titular: ");

    int idx_titular = num_titular - 1;
    int idx_banca = num_banca - 1;

    if (idx_titular < 0 || idx_titular >= mi_club->total_jugadores ||
        idx_banca < 0 || idx_banca >= mi_club->total_jugadores) {
        printf("Numero de jugador fuera de rango.\n");
        enter_continuar();
        return;
    }

    if (!mi_club->plantilla[idx_titular].titular || mi_club->plantilla[idx_banca].titular) {
        printf("Seleccion invalida: verifica quien es titular y quien esta en banca.\n");
        enter_continuar();
        return;
    }

    mi_club->plantilla[idx_titular].titular = false;
    mi_club->plantilla[idx_banca].titular = true;

    printf("\nIntercambio listo: %s (banca) <-> %s (titular).\n",
           mi_club->plantilla[idx_titular].nombre,
           mi_club->plantilla[idx_banca].nombre);
    enter_continuar();
}

void mostrar_tienda(Jugador tienda[], int total_tienda) {
    printf("\n================ JUGADORES EN TIENDA ================\n");
    printf("%-4s %-28s %-5s %-5s %-12s\n", "#", "Nombre", "Pos", "Med", "Valor");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < total_tienda; i++) {
        if (tienda[i].valor <= 0) {
            printf("%-4d %-28s %-5s %-5s %-12s\n", i + 1, "FICHADO / NO DISPONIBLE", "-", "-", "-");
        } else {
            printf("%-4d %-28s %-5s %-5d $%-11d\n",
                   i + 1, tienda[i].nombre, tienda[i].posicion, tienda[i].media, tienda[i].valor);
        }
    }
    printf("-----------------------------------------------------\n");
}