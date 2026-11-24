#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sistema_mercado.h"

#define MAX_JUGADORES_TXT 100

static void limpiar_salto_linea(char *texto) {
    if (texto == NULL) return;
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
    printf("Archivo abierto correctamente.\n");
    char linea[128];

    while (total_jugadores < MAX_JUGADORES_TXT && fgets(linea, sizeof(linea), archivo_jugadores) != NULL) {
        limpiar_salto_linea(linea);
        if (linea[0] == '\0') {
            continue;
        }

        char *nombre = strtok(linea, ",");
        char *posicion = strtok(NULL, ",");
        char *media = strtok(NULL, ",");
        char *valor = strtok(NULL, ",");

        if (nombre == NULL || posicion == NULL || media == NULL || valor == NULL) {
            printf("Advertencia: línea con formato inválido omitida.\n");
            continue;
        }

        limpiar_salto_linea(valor);

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
    if (jugador == NULL || total_jugadores <= 0) return;

    for (int i = 0; i < total_jugadores; i++) {
        int cambio = rand() % 2;
        if (cambio == 1) {
            int variacion = (rand() % 21) - 10; // Rango de -10% a +10%
            long long ajuste = ((long long)jugador[i].valor * variacion) / 100LL;
            long long nuevo_valor = (long long)jugador[i].valor + ajuste;
            if (nuevo_valor < 1000LL) {
                nuevo_valor = 1000LL;
            }
            jugador[i].valor = (int)nuevo_valor;
        }
    }
}

void seleccionar_jugadores(Jugador jugador[], int total_jugadores, Jugador tienda[]) {
    if (jugador == NULL || tienda == NULL || total_jugadores <= 0) return;

    int cont_por = 0;
    int cont_def = 0;
    int cont_med = 0;
    int cont_del = 0;

    int disponibles_por = 0;
    int disponibles_def = 0;
    int disponibles_med = 0;
    int disponibles_del = 0;

    for (int i = 0; i < total_jugadores; i++) {
        if (strcmp(jugador[i].posicion, "POR") == 0) disponibles_por++;
        else if (strcmp(jugador[i].posicion, "DEF") == 0) disponibles_def++;
        else if (strcmp(jugador[i].posicion, "MED") == 0) disponibles_med++;
        else if (strcmp(jugador[i].posicion, "DEL") == 0) disponibles_del++;
    }


    int limite_pool = (total_jugadores > MAX_JUGADORES_TXT) ? MAX_JUGADORES_TXT : total_jugadores;
    int seleccionados[MAX_JUGADORES_TXT] = {0};

    while (cont_por < 5 || cont_def < 5 || cont_med < 5 || cont_del < 5) {
        int indice = rand() % limite_pool;
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