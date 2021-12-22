#include <iostream>
#include "piezas.h"

#include "tablero.h"
#include "Sistema_juego.h"


int main() {
    /* Construimos el tablero */
    tableroBuilder tabBuilder;
    tabBuilder.buildTablero();
    tabBuilder.buildCasilleros();
    shared_ptr<CTablero> tablero;
    tablero = tabBuilder.getTablero();

    /* Asignamos las piezas al tablero */
    asignacionPBlancas(*tablero);
    asignacionPNegras(*tablero);

    //cout<<((((tablero->getCasilleros())[0][1])->getPieza())->valMovimiento0("A5"))<<endl;

    /* Mostramos el tablero */
    //tablero->mostrarTablero();

    /* Casilleros */
    //auto casilleros = tablero->getCasilleros();
    //cout<< (casilleros[0][0]->getPieza())->getId()<<" "; // A1
    //cout<< (casilleros[1][0]->getPieza())->getId()<<" "; // B1
    //cout<< (casilleros[2][0]->getPieza())->getId()<<endl; // C1

    //tablero->realizarMovimiento("A1", "B1");
    //tablero->mostrarTablero();
    /* Ejecución del juego */
    sistemaDelJuego(tablero);
}
