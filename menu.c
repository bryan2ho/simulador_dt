#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "sistema_guardado.h"
#include "sistema_eventos.h"
#include <time.h>
#include "menu.h"

void limpiar_pantalla(){
#ifdef _WIN32
    system("cls");   // para limpiar pantalla en windows
#else
    system("clear"); // para limpiar pantalla en linux porque alejandro es linuxero
#endif
}

void enter_continuar() {
    int a;
    while ((a=getchar()) != '\n' && a != EOF) {} // Limpiar el buffer de entrada
    printf("\nPresiona Enter para continuar...");
    getchar();
}

void mostrar_plantilla(Club *mi_club) {
    limpiar_pantalla();
    printf("\n");
    printf("========================================\n");
    printf("         PLANTILLA DE JUGADORES         \n");
    printf("========================================\n");
    printf("%-40s %-5s %-4s $%-10s\n", "Nombre", "Posicion", "Media", "Valor");
    printf("----------------------------------------\n");

    for(int i = 0; i < mi_club->total_jugadores; i++) {
        Jugador jugador = mi_club->plantilla[i];
        printf("%-40s %-5s %-4d $%-10d\n", jugador.nombre, jugador.posicion, jugador.media, jugador.valor);
    }
    printf("----------------------------------------\n");

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
    mi_club->presupuesto = 10000000;
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
    }
    
}

void mercado(Club *mi_club) {
    int opcion_mercado;
    char jugador_vender[50];

    do{
    limpiar_pantalla();
    printf("========================================\n");
    printf("         MERCADO DE FICHAJES            \n");
    printf("========================================\n");
    printf("[1] Comprar jugador\n");
    printf("[2] Vender jugador\n");
    printf("[3] Regresar al menu principal\n");
    printf("----------------------------------------\n");
    printf("Elige una opcion: ");
    int opcion_mercado;
    scanf("%d", &opcion_mercado);

    switch(opcion_mercado) {
        case 1:
            limpiar_pantalla();
            printf(".\n");
            break;
        case 2:
            limpiar_pantalla();
            mostrar_plantilla(mi_club);
            printf("Ingrese el nombre del jugador que desea vender: ");
            scanf(" %[^\n]", jugador_vender);
            //vender()
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
    
    }while(opcion_mercado != 3);
}
void partida(Club *mi_club) {

    int opcion_principal;
    do{
        mostrar_menu_principal(mi_club->nombre_equipo, mi_club->dia_actual, mi_club->presupuesto);
        scanf("%d", &opcion_principal);

        switch(opcion_principal) {
            case 1:
                limpiar_pantalla();
                mostrar_plantilla(mi_club);
                enter_continuar();
                break;
            case 2:
                mercado(mi_club);
                enter_continuar();
                break;
            case 3:
                limpiar_pantalla();
               
                printf("Avanzando al siguiente dia...\n");
                enter_continuar();
                if(mi_club->dia_actual < 7){
                    eventos_ejecutar(mi_club);
                    
                }else{
                    eventos_final(mi_club);
                }
                enter_continuar();
                mi_club->dia_actual++;
                mi_club->presupuesto += 700000; // Incrementar el presupuesto en $700,000 cada día
                //seleccionar_jugadores(mi_club->plantilla, mi_club->total_jugadores, );
                //variar_precios()
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

    } while(mi_club->dia_actual <= 7 && opcion_principal != 5);
}

