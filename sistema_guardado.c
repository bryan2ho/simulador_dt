#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_guardado.h"

//ultima modificacion hecha por bryan lunes 11am

void guardar_partida(Club *mi_club){

    FILE *archivo = fopen("partida.dat", "wb");

    if(archivo == NULL){
        printf("Error: No se pudo guardar la partida. \n");
        return;
    }

    fwrite(mi_club->nombre_equipo, sizeof(char), 50, archivo);
    fwrite(&(mi_club->presupuesto), sizeof(int), 1, archivo);
    fwrite(&(mi_club->dia_actual), sizeof(int), 1, archivo);
    fwrite(&(mi_club->total_jugadores), sizeof(int), 1, archivo);
    fwrite(mi_club->plantilla, sizeof(Jugador), mi_club->total_jugadores, archivo);


    fclose(archivo);
    printf("La partida se guardo con exito como \"partida.dat\". \n\n");

}

void cargar_partida(Club *mi_club){

    FILE *archivo = fopen("partida.dat", "rb");

    if(archivo == NULL){
        printf("No se encontro alguna partida guardada previamente \n\n");
        return;
    }

    fread(mi_club->nombre_equipo, sizeof(char), 50, archivo);
    fread(&(mi_club->presupuesto), sizeof(int), 1, archivo);
    fread(&(mi_club->dia_actual), sizeof(int), 1, archivo);
    fread(&(mi_club->total_jugadores), sizeof(int), 1, archivo);

    if(mi_club->plantilla != NULL){
        free(mi_club->plantilla);
    }

    mi_club->plantilla = (Jugador *) malloc(mi_club->total_jugadores*sizeof(Jugador));

    fread(mi_club->plantilla, sizeof(Jugador), mi_club->total_jugadores, archivo);

    fclose(archivo);
}