#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sistema_mercado.h"
#include "misc.h"

#define MAX_JUGADORES_TXT 100

static void limpiar_salto_linea(char *texto) {
    size_t len = strlen(texto);
    while (len > 0 && (texto[len - 1] == '\n' || texto[len - 1] == '\r')) {
        texto[len - 1] = '\0';
        len--;
    }
}

int cargar_jugadores(Jugador jugador[]) {
    FILE *archivo_jugadores = fopen("jugadores.txt", "r");
    if (archivo_jugadores == NULL) {
        printf("Error: el archivo no se pudo abrir\n");
        return 0;
    }

    int total_jugadores = 0;
    char linea[128];

    while (total_jugadores < MAX_JUGADORES_TXT && fgets(linea, sizeof(linea), archivo_jugadores) != NULL) {
        limpiar_salto_linea(linea);

        char *nombre = strtok(linea, ",");
        char *posicion = strtok(NULL, ",");
        char *media = strtok(NULL, ",");
        char *valor = strtok(NULL, ",");

        strncpy(jugador[total_jugadores].nombre, nombre, sizeof(jugador[total_jugadores].nombre) - 1);
        jugador[total_jugadores].nombre[sizeof(jugador[total_jugadores].nombre) - 1] = '\0';

        strncpy(jugador[total_jugadores].posicion, posicion, sizeof(jugador[total_jugadores].posicion) - 1);
        jugador[total_jugadores].posicion[sizeof(jugador[total_jugadores].posicion) - 1] = '\0';

        jugador[total_jugadores].media = atoi(media);
        jugador[total_jugadores].valor = atoi(valor);
        jugador[total_jugadores].titular = false;

        total_jugadores++;
    }

    fclose(archivo_jugadores);
    printf("Se cargaron %d jugadores.\n", total_jugadores);
    return total_jugadores;
}

void variar_precios(Jugador jugador[], int total_jugadores) {
    for (int i = 0; i < total_jugadores; i++) {
        if (rand() % 2 == 1) {
            int variacion = (rand() % 21) - 10; // -10% a +10%
            long nuevo_valor = (long)jugador[i].valor + ((long)jugador[i].valor * variacion) / 100L;
            if (nuevo_valor < 1000L) {
                nuevo_valor = 1000L;
            }
            jugador[i].valor = (int)nuevo_valor;
        }
    }
}

void seleccionar_jugadores(Jugador jugador[], int total_jugadores, Jugador tienda[]) {
    int cont_por = 0;
    int cont_def = 0;
    int cont_med = 0;
    int cont_del = 0;
    int seleccionados[MAX_JUGADORES_TXT] = {0};

    while (cont_por < 5 || cont_def < 5 || cont_med < 5 || cont_del < 5) {
        int indice = rand() % total_jugadores;
        if (seleccionados[indice] == 0) {
            if (strcmp(jugador[indice].posicion, "POR") == 0 && cont_por < 5) {
                seleccionados[indice] = 1;
                tienda[cont_por] = jugador[indice];
                tienda[cont_por].titular = false;
                cont_por++;
            } else if (strcmp(jugador[indice].posicion, "DEF") == 0 && cont_def < 5) {
                seleccionados[indice] = 1;
                tienda[5 + cont_def] = jugador[indice];
                tienda[5 + cont_def].titular = false;
                cont_def++;
            } else if (strcmp(jugador[indice].posicion, "MED") == 0 && cont_med < 5) {
                seleccionados[indice] = 1;
                tienda[10 + cont_med] = jugador[indice];
                tienda[10 + cont_med].titular = false;
                cont_med++;
            } else if (strcmp(jugador[indice].posicion, "DEL") == 0 && cont_del < 5) {
                seleccionados[indice] = 1;
                tienda[15 + cont_del] = jugador[indice];
                tienda[15 + cont_del].titular = false;
                cont_del++;
            }
        }
    }
}

bool comprar_jugador(Club *club, Jugador tienda[], int total_tienda, int idx_tienda) {
    if (idx_tienda < 0 || idx_tienda >= total_tienda) {
        printf("Numero de jugador fuera de rango.\n");
        return false;
    }

    Jugador fichaje = tienda[idx_tienda];
    if (fichaje.valor <= 0) {
        printf("Ese jugador ya no esta disponible en la tienda.\n");
        return false;
    }

    if (club->presupuesto < fichaje.valor) {
        printf("Presupuesto insuficiente (%d < %d).\n", club->presupuesto, fichaje.valor);
        return false;
    }

    if (agregar_jugador(club, fichaje.nombre, fichaje.posicion, fichaje.media, fichaje.valor) != 1) {
        return false;
    }

    club->presupuesto -= fichaje.valor;
    tienda[idx_tienda].valor = 0;

    printf("Fichaste a %s por %d.\n", fichaje.nombre, fichaje.valor);
    return true;
}

bool vender_jugador(Club *club, int idx_plantilla) {
    if (idx_plantilla < 0 || idx_plantilla >= club->total_jugadores) {
        printf("Indice de jugador no valido.\n");
        return false;
    }

    Jugador vendido = club->plantilla[idx_plantilla];
    bool era_titular = vendido.titular;
    int monto = vendido.valor;

    if (eliminar_jugador(club, idx_plantilla) != 1) {
        return false;
    }

    club->presupuesto += monto;

    if (era_titular && club->total_jugadores >= 11) {
        for (int i = 0; i < club->total_jugadores; i++) {
            if (!club->plantilla[i].titular) {
                club->plantilla[i].titular = true;
                printf("%s pasa de la banca a titular tras la venta.\n", club->plantilla[i].nombre);
                break;
            }
        }
    }

    printf("Vendiste a %s por %d.\n", vendido.nombre, monto);
    return true;
}