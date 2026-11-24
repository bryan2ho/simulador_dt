#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <stdbool.h>

typedef struct {
    char nombre[50];
    char posicion[4];
    int media;
    int valor;
    bool titular;
} Jugador;

typedef struct {
    char nombre_equipo[50];
    int presupuesto;
    int dia_actual;
    int total_jugadores;
    Jugador *plantilla;
} Club;

#endif
