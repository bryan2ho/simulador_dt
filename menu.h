#ifndef MENU_H
#define MENU_H
#include "estructuras.h"

    void intercambiar_titular_banca(Club *mi_club);
    void mercado(Club *mi_club, Jugador tienda[], int total_tienda);
    void limpiar_buffer_linea();
    void limpiar_pantalla();
    void enter_continuar();
    void mostrar_plantilla(Club *mi_club);
    void mostrar_menu_inicial();
    void mostrar_menu_principal(const char* nombre_club, int dia_actual, int presupuesto);
    void mostrar_creditos();
    void inicializar_club(Club *mi_club);
    void partida(Club *mi_club);
    void mostrar_tienda(Jugador tienda[], int total_tienda);
    bool puede_vender(Club *mi_club);

#endif
