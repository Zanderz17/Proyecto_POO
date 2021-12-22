//
// Created by SANDERS on 22/12/2021.
//

#ifndef PROYECTO_POO_SISTEMA_JUEGO_H
#define PROYECTO_POO_SISTEMA_JUEGO_H

[[noreturn]] void sistemaDelJuego(shared_ptr<CTablero> tablero){
    bool jugador = true;
    while(true){
        tablero->mostrarTablero();
        auto casillerosRiesgo = asistenteBot(tablero);
        for(auto item0: casillerosRiesgo){
            for(auto item1: item0){
                cout<<item1<<" ";
            } cout<<endl;
        }
        if (jugador){
            cout<<"---- TURNO DEL LAS FICHAS BLANCAS ---- "<<endl;
        }
        else{
            cout<<"---- TURNO DEL LAS FICHAS NEGRAS ---- "<<endl;
        }
        cout<<"---- MOVIMIENTO ----"<<endl;
        string posInicial;
        string posFinal;
        cout<<"Origen: "; cin>>posInicial;
        cout<<"Destino: "; cin>>posFinal;
        // tablero->realizarMovimiento(posInicial, posFinal);

        /* Evaluamos si las posiciones seleccionadas pertenecen al tablero*/
        if (!(tablero->valMovimiento1(posInicial, posFinal))){
            cout<<"Movimiento invalido: Se ha seleccionado una posición fuera del tablero"<<endl;
            continue;
        }

        /* Evaluamos si en la posicion seleccionada se encuentra una pieza */
        if (!(tablero->valMovimiento2(posInicial))){
            cout<<"Movimiento invalido: La posición seleccionada no presenta una pieza"<<endl;
            continue;
        }

        /* Evaluamos movimientos especiales */
        /* Desplazamiento del peon de 2 casilleros */
        if ((tablero->valMovimiento5(posInicial))){
            if (!(tablero->valMovimiento3(posFinal))){
                if ((tablero->valMovimiento5_1(posInicial, posFinal))){
                    if ((tablero->valMovimiento6(posInicial, posFinal))){
                        tablero->realizarMovimiento(posInicial, posFinal);
                        jugador = !jugador;
                        continue;
                    }
                    else{
                        cout<<"Movimiento invalido: El movimiento no puede ser realizado por la pieza seleccionada"<<endl;
                        continue;
                    }
                }
            }
        }

        /* Movimiento de ataque del peon */
        if ((tablero->valMovimiento5(posInicial))){
            if ((tablero->valMovimiento3(posFinal))){
                if ((tablero->valMovimiento5_2(posInicial, posFinal))){
                    if ((tablero->valMovimiento6(posInicial, posFinal))){
                        tablero->realizarMovimiento(posInicial, posFinal);
                        jugador = !jugador;
                        continue;
                    }
                    else{
                        cout<<"Movimiento invalido: El movimiento no puede ser realizado por la pieza seleccionada"<<endl;
                        continue;
                    }
                }
            }
        }

        /* Evaluamos si los movimientos individuales a realizar corresponder a las piezas seleccionadas*/
        /* Posicion inicial */
        int xi = posInicial[0] - 65;
        int yi = posInicial[1] - 49;
        /* Posicion final */
        int xf = posFinal[0] - 65;
        int yf = posFinal[1] - 49;

        if (!((((tablero->getCasilleros())[xi][yi])->getPieza())->valMovimiento0(posFinal))){
            cout<<"Movimiento invalido: El movimiento no puede ser realizado por la pieza seleccionada"<<endl;
            continue;
        }

        /* Evaluamos movimientos regulares */
        if((tablero->valMovimiento3(posFinal))){
            if((tablero->valMovimiento4(posInicial, posFinal))){
                cout<<"Movimiento invalido: El movimiento atacará a una pieza aliada"<<endl;
                continue;
            }
            else{
                if ((tablero->valMovimiento6(posInicial, posFinal))){
                    tablero->realizarMovimiento(posInicial, posFinal);
                    jugador = !jugador;
                    continue;
                }
                else{
                    cout<<"Movimiento invalido: Existe una pieza intermedia entre la posicion de origen y destino"<<endl;
                    continue;
                }
            }
        }
        else{
            if ((tablero->valMovimiento6(posInicial, posFinal))){
                tablero->realizarMovimiento(posInicial, posFinal);
                jugador = !jugador;
                continue;
            }
            else{
                cout<<"Movimiento invalido: Existe una pieza intermedia entre la posicion de origen y destino"<<endl;
                continue;
            }
        }
    }
}


#endif //PROYECTO_POO_SISTEMA_JUEGO_H
