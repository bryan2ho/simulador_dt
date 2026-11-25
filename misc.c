#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estructuras.h"

void borrar_lineas(int n){
    for (int i = 0; i < n; i++) {
        printf("\033[1A\033[2K");
    }
    printf("\r");
    fflush(stdout);
}

int agregar_jugador(Club *club, char *nombre, char *posicion, int media, int valor){
    Jugador *temp = realloc(club->plantilla, ((size_t)club->total_jugadores + 1) * sizeof(Jugador));
    if (temp == NULL) {
        printf("ERROR: No se pudo asignar memoria para el jugador\n");
        return -1;
    }

    club->plantilla = temp;
    Jugador *j = &club->plantilla[club->total_jugadores];

    strncpy(j->nombre, nombre, sizeof(j->nombre) - 1);
    j->nombre[sizeof(j->nombre) - 1] = '\0';

    strncpy(j->posicion, posicion, sizeof(j->posicion) - 1);
    j->posicion[sizeof(j->posicion) - 1] = '\0';

    j->media = media;
    j->valor = valor;
    j->titular = false;

    club->total_jugadores++;
    return 1;
}

int eliminar_jugador(Club *club, int indice){
    int nuevo_total = club->total_jugadores - 1;
    Jugador *temp = realloc(club->plantilla, (size_t)nuevo_total * sizeof(Jugador));
    if (temp == NULL) {
        printf("ERROR: No se pudo redimensionar la memoria.\n");
        return -1;
    }

    for (int i = indice; i < nuevo_total; i++){
        temp[i] = temp[i + 1];
    }

    club->plantilla = temp;
    club->total_jugadores = nuevo_total;
    return 1;
}