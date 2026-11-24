#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estructuras.h"

void borrar_lineas(int n) {
    for (int i = 0; i < n; i++) {
        printf("\033[1A\033[2K");
    }
    printf("\r");
    fflush(stdout);
}

int agregar_jugador(Club *club, const char *nombre, const char *posicion, int media, int valor) {
    Jugador *temp = realloc(club->plantilla, ((size_t)club->total_jugadores + 1) * sizeof(Jugador));
    if (temp == NULL) {
        printf("ERROR: No se pudo asignar memoria para el jugador\n");
        return -1;
    }

    club->plantilla = temp;
    int indice = club->total_jugadores;

    strncpy(club->plantilla[indice].nombre, nombre, sizeof(club->plantilla[indice].nombre) - 1);
    club->plantilla[indice].nombre[sizeof(club->plantilla[indice].nombre) - 1] = '\0';

    strncpy(club->plantilla[indice].posicion, posicion, sizeof(club->plantilla[indice].posicion) - 1);
    club->plantilla[indice].posicion[sizeof(club->plantilla[indice].posicion) - 1] = '\0';

    club->plantilla[indice].media = media;
    club->plantilla[indice].valor = valor;
    club->plantilla[indice].titular = false;

    club->total_jugadores++;
    return 1;
}

int eliminar_jugador(Club *club, int indice) {
    int nuevo_total = club->total_jugadores - 1;

    for (int i = indice; i < nuevo_total; i++) {
        club->plantilla[i] = club->plantilla[i + 1];
    }

    if (nuevo_total == 0) {
        free(club->plantilla);
        club->plantilla = NULL;
        club->total_jugadores = 0;
        return 1;
    }

    Jugador *temp = realloc(club->plantilla, (size_t)nuevo_total * sizeof(Jugador));
    if (temp == NULL) {
        printf("ERROR: No se pudo redimensionar la memoria.\n");
        return -1;
    }

    club->plantilla = temp;
    club->total_jugadores = nuevo_total;
    return 1;
}