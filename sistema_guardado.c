#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sistema_guardado.h"

bool guardar_partida(Club *mi_club) {
    FILE *archivo = fopen("partida.dat", "wb");
    if (archivo == NULL) {
        printf("Error: No se pudo guardar la partida.\n");
        return false;
    }

    fwrite(mi_club->nombre_equipo, sizeof(char), 50, archivo);
    fwrite(&mi_club->presupuesto, sizeof(int), 1, archivo);
    fwrite(&mi_club->dia_actual, sizeof(int), 1, archivo);
    fwrite(&mi_club->total_jugadores, sizeof(int), 1, archivo);
    fwrite(mi_club->plantilla, sizeof(Jugador), (size_t)mi_club->total_jugadores, archivo);

    fclose(archivo);
    printf("La partida se guardo con exito como \"partida.dat\".\n\n");
    return true;
}

bool cargar_partida(Club *mi_club) {
    FILE *archivo = fopen("partida.dat", "rb");
    if (archivo == NULL) {
        printf("No se encontro alguna partida guardada previamente\n\n");
        return false;
    }

    fread(mi_club->nombre_equipo, sizeof(char), 50, archivo);
    fread(&mi_club->presupuesto, sizeof(int), 1, archivo);
    fread(&mi_club->dia_actual, sizeof(int), 1, archivo);
    fread(&mi_club->total_jugadores, sizeof(int), 1, archivo);
    mi_club->nombre_equipo[49] = '\0';

    if (mi_club->plantilla != NULL) {
        free(mi_club->plantilla);
    }

    mi_club->plantilla = malloc((size_t)mi_club->total_jugadores * sizeof(Jugador));
    if (mi_club->plantilla == NULL) {
        printf("Error: no se pudo asignar memoria.\n\n");
        fclose(archivo);
        return false;
    }

    fread(mi_club->plantilla, sizeof(Jugador), (size_t)mi_club->total_jugadores, archivo);
    fclose(archivo);
    return true;
}