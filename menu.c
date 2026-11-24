#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "sistema_guardado.h"
#include "sistema_eventos.h"
#include <time.h>
#include "menu.h"

void limpiar_buffer_linea(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void limpiar_pantalla(){
#ifdef _WIN32
    system("cls");   // para limpiar pantalla en windows
#else
    system("clear"); // para limpiar pantalla en linux porque alejandro es linuxero
#endif
}

void enter_continuar() {
    printf("\nPresiona Enter para continuar...");
    getchar();
}

void mostrar_plantilla(Club *mi_club) {
    limpiar_pantalla();
    printf("\n");
    printf("========================================\n");
    printf("                TITULARES               \n");
    printf("========================================\n");
    printf("%-3s %-32s %-5s %-5s $%-10s\n", "#", "Nombre", "Pos", "Med", "Valor");
    printf("----------------------------------------\n");

    for(int i = 0; i<mi_club->total_jugadores; i++){
        Jugador j = mi_club->plantilla[i];

        if(j.titular){
            printf("%-3d %-32s %-5s %-5d $%-10d\n", i + 1, j.nombre, j.posicion, j.media, j.valor);
        }
    }

    int cuenta_banca = 0;

    printf("\n============================================================\n");
        printf("                           BANCA                            \n");
        printf("============================================================\n");
        printf("%-3s %-32s %-5s %-5s $%-10s\n", "#", "Nombre", "Pos", "Med", "Valor");
        printf("------------------------------------------------------------\n");

        for(int i = 0; i<mi_club->total_jugadores; i++){
            Jugador j = mi_club->plantilla[i];

            if(!j.titular){
                printf("%-3d %-32s %-5s %-5d $%-10d\n", i + 1, j.nombre, j.posicion, j.media, j.valor);
                cuenta_banca++;
            }
        }

        if(cuenta_banca == 0){
            printf("No hay jugadores en la banca\n");
        }

    printf("------------------------------------------------------------\n");
    printf("Total plantilla: %d (11 titulares | %d banca)\n", mi_club->total_jugadores, cuenta_banca);

}

void mostrar_menu_inicial(){
    limpiar_pantalla();
    printf("\n");
    printf("========================================\n");
    printf("           SIMULADOR DE DT              \n");
    printf("========================================\n");
    printf(" [1] Iniciar Nueva Partida\n");
    printf(" [2] Cargar Partida Guardada\n");
    printf(" [3] Creditos\n");
    printf(" [4] Salir\n");
    printf("----------------------------------------\n");
    printf("Elige una opcion: ");

}

void mostrar_menu_principal(const char* nombre_club, int dia_actual, int presupuesto){
    limpiar_pantalla();
    printf("\n");
    printf("========================================\n");
    printf("  %s\n", nombre_club);
    printf("  Día %d / 7  |  Presupuesto: $%d\n", dia_actual, presupuesto);
    printf("========================================\n");
    printf(" [1] Ver plantilla de jugadores\n");
    printf(" [2] Mercado de fichajes (Comprar/Vender)\n"); // <--- Aquí
    printf(" [3] Avanzar al siguiente dia\n");
    printf(" [4] Guardar partida\n");
    printf(" [5] Salir al menu principal\n");
    printf("----------------------------------------\n");
    printf("Elige una opcion: ");
}

void mostrar_creditos(){
        limpiar_pantalla();
        printf("=========================================\n");
        printf("                Créditos                 \n");
        printf("=========================================\n");
        printf("Equipo \n");
        printf("Alejandro Guardiola Rodríguez________\n");
        printf("Bryan Armando Cano Guzmán____________\n");
        printf("Ian Emmanuel Valle Reza______________\n");
        printf("Miranda Mariel Vidales Gutiérrez_____\n");

}

void inicializar_club(Club *mi_club) {
    mi_club->dia_actual = 1;
    mi_club->presupuesto = 5000000;
    mi_club->total_jugadores = 11;
    mi_club->plantilla = (Jugador *) malloc(mi_club->total_jugadores * sizeof(Jugador));
    if(mi_club->plantilla == NULL){
        printf("Error al asignar memoria \n");
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

    for(int i = 0; i < mi_club->total_jugadores; i++) {
        mi_club->plantilla[i] = jugadores_iniciales[i];
        mi_club->plantilla[i].titular = true;
    }
    
}

void mercado(Club *mi_club) {
    int opcion_mercado = 0;
    char jugador_vender[50];

    do {
        limpiar_pantalla();
        printf("========================================\n");
        printf("         MERCADO DE FICHAJES            \n");
        printf("========================================\n");
        printf("[1] Comprar jugador\n");
        printf("[2] Vender jugador\n");
        printf("[3] Regresar al menu principal\n");
        printf("----------------------------------------\n");
        printf("Elige una opcion: ");

        if (scanf("%d", &opcion_mercado) != 1) {
            limpiar_buffer_linea();
            opcion_mercado = 0;
        } else {
            limpiar_buffer_linea();
        }

        switch (opcion_mercado) {
            case 1:
                limpiar_pantalla();
                printf(".\n");
                enter_continuar();
                break;
            case 2:
                limpiar_pantalla();
                mostrar_plantilla(mi_club);
                printf("Ingrese el nombre del jugador que desea vender: ");
                if (scanf(" %49[^\n]", jugador_vender) == 1) {
                    limpiar_buffer_linea();
                    // vender(mi_club, jugador_vender);
                } else {
                    limpiar_buffer_linea();
                }
                enter_continuar();
                break;
            case 3:
                limpiar_pantalla();
                printf("Regresando al menu principal...\n");
                enter_continuar();
                break;
            default:
                limpiar_pantalla();
                printf("Opcion invalida. Por favor, elige una opcion valida.\n");
                enter_continuar();
                break;
        }
    } while (opcion_mercado != 3);
}

void partida(Club *mi_club){
    int opcion_principal = 0;

    do {
        mostrar_menu_principal(mi_club->nombre_equipo, mi_club->dia_actual, mi_club->presupuesto);
        
        if(scanf("%d", &opcion_principal) != 1){ //scanf retorna la cantidad de elementos que leyo correctamente, si no leyo solo uno entonces es opcion invalida.
            limpiar_buffer_linea();
            opcion_principal = 0; 
        } 

        else{
            limpiar_buffer_linea(); 
        }

        switch (opcion_principal) {
            case 1: {

                mostrar_plantilla(mi_club);
                printf("\n¿Deseas intercambiar titular por banca? (1 = Si, 0 = No): ");
                int resp = 0;

            if (scanf("%d", &resp) != 1) {
                limpiar_buffer_linea();
                resp = 0;
            } else {
                limpiar_buffer_linea();
            }

            if (resp == 1) {
                intercambiar_titular_banca(mi_club);
            } else {
                enter_continuar();
            }
                break;

            case 2:
                mercado(mi_club);
                break;
            case 3:
                limpiar_pantalla();
                printf("Avanzando al siguiente dia...\n");
                enter_continuar();
                if (mi_club->dia_actual < 7) {
                    eventos_ejecutar(mi_club);
                } else {
                    eventos_final(mi_club);
                }
                enter_continuar();
                mi_club->dia_actual++;
                mi_club->presupuesto += 700000;
                // seleccionar_jugadores(...);
                // variar_precios(...);
                break;
            case 4:
                guardar_partida(mi_club);
                enter_continuar();
                limpiar_pantalla();
                break;
            case 5:
                printf("Regresando al menu principal...\n");
                enter_continuar();
                break;
            default:
                printf("Opcion invalida. Por favor, elige una opcion valida.\n");
                enter_continuar();
                break;
            }
        }

    } while (mi_club->dia_actual <= 7 && opcion_principal != 5);
}

bool puede_vender(Club *mi_club){

    if (mi_club == NULL || mi_club->plantilla == NULL) {
        return false;
    }
    if (mi_club->total_jugadores <= 11) {
        printf("\nNo puedes vender mas jugadores: la plantilla debe tener al menos 11 jugadores.\n");
        return false;
    }
    return true;
}

void intercambiar_titular_banca(Club *mi_club) {

    mostrar_plantilla(mi_club);

    if (mi_club->total_jugadores <= 11) {
        printf("\nNo tienes jugadores en la banca para intercambiar (plantilla minima de 11).\n");
        enter_continuar();
        return;
    }

    int num_titular = 0;
    int num_banca = 0;

    printf("\nIngresa el # del TITULAR que pasa a banca: ");
    if (scanf("%d", &num_titular) != 1) {
        limpiar_buffer_linea();
        printf("Entrada invalida.\n");
        enter_continuar();
        return;
    }
    limpiar_buffer_linea();

    printf("Ingresa el # de la BANCA que pasa a titular: ");
    if (scanf("%d", &num_banca) != 1) {
        limpiar_buffer_linea();
        printf("Entrada invalida.\n");
        enter_continuar();
        return;
    }
    limpiar_buffer_linea();

    int idx_titular = num_titular - 1;
    int idx_banca = num_banca - 1;

    if (idx_titular < 0 || idx_titular >= mi_club->total_jugadores ||
        idx_banca < 0 || idx_banca >= mi_club->total_jugadores) {
        printf("Numero de jugador fuera de rango.\n");
        enter_continuar();
        return;
    }

    if (!mi_club->plantilla[idx_titular].titular) {
        printf("El jugador #%d no esta como titular.\n", num_titular);
        enter_continuar();
        return;
    }

    if (mi_club->plantilla[idx_banca].titular) {
        printf("El jugador #%d ya esta como titular (no esta en banca).\n", num_banca);
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
