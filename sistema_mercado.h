#ifndef SISTEMA_MERCADO_H
#define SISTEMA_MERCADO_H
#include "estructuras.h"

int cargar_jugadores(Jugador jugador[]);

void seleccionar_jugadores(Jugador jugador[], int total_jugadores, Jugador tienda[]);

void variar_precios(Jugador jugadores[], int total_jugadores);
#endif