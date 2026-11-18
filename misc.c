#include <stdio.h>
#include "estructuras.h"

void borrar_lineas(int n) {
    for (int i = 0; i < n; i++) {
        printf("\033[1A\033[2K");
    }
    printf("\r");
    fflush(stdout);
}

// TODO: Manejo de arreglos dinámicos (agregar tmb en cabecera)