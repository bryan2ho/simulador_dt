#ifndef MENU_H
#define MENU_H
#include "estructuras.h"


    void limpiar_pantalla();
    void enter_continuar();
    void mostrar_plantilla(Club *mi_club);
    void mostrar_menu_inicial();
    void mostrar_menu_principal(const char* nombre_club, int dia_actual, int presupuesto);
    void mostrar_creditos();
    void inicializar_club(Club *mi_club);
    void partida(Club *mi_club);



#endif
