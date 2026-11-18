#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

void borrar_lineas(int n) {
    for (int i = 0; i < n; i++) {
        printf("\033[1A\033[2K");
    }
    printf("\r");
    fflush(stdout);
}

int agregar_jugador(Club *club, const char *nombre, const char *posicion, int media, int valor){

    Jugador *temp = realloc(club->plantilla, (club->total_jugadores + 1)*sizeof(Jugador));

    if(temp == NULL){
        printf("ERROR: No se pudo asignar memoria para el jugador\n");
        return -1;
    }

    //temp por si falla no perder la plantilla

    club->plantilla = temp;
    int indice = club->total_jugadores;

    strncpy(club->plantilla[indice].nombre, nombre, sizeof(club->plantilla[indice].nombre) - 1);
    club->plantilla[indice].nombre[sizeof(club->plantilla[indice].nombre) - 1] = '\0';
    strncpy(club->plantilla[indice].posicion, posicion, sizeof(club->plantilla[indice].posicion) - 1);
    club->plantilla[indice].posicion[sizeof(club->plantilla[indice].posicion) - 1] = '\0';

    club->plantilla[indice].media = media;
    club->plantilla[indice].valor = valor;

    club->total_jugadores++;

    return 1;

}

int eliminar_jugador(Club *club, int indice){
    
    for (int i = indice; i < club->total_jugadores - 1; i++) {
        club->plantilla[i] = club->plantilla[i + 1];
    }

    Jugador *temp = realloc(club->plantilla, (club->total_jugadores - 1) * sizeof(Jugador));

    if (temp == NULL) {
        printf("ERROR: No se pudo redimensionar la memoria.\n");
        return -1;
    }

    club->plantilla = temp;


    club->total_jugadores--;
    return 1;
}



// TODO: Manejo de arreglos dinámicos (agregar tmb en cabecera)