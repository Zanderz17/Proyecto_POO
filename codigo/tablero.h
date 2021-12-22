//
// Created by SANDERS on 22/12/2021.
//

#ifndef PROYECTO_POO_TABLERO_H
#define PROYECTO_POO_TABLERO_H

mutex mtx;

class CCasillero{
    shared_ptr<CPieza> pieza;
    friend class CTablero;
    friend class tableroBuilder;
public:
    CCasillero() = default;
    void setPieza(shared_ptr<CPieza> pieza){
        this->pieza = pieza;
    };
    void actualizarPieza(shared_ptr<CPieza> pieza){
        *(this->pieza) = *pieza;
    }
    shared_ptr<CPieza> getPieza(){
        return pieza;
    }
    void removerPieza(){};
    ~CCasillero(){};
};

/* Funciones del metodo CTablero::mostrarTablero() */

void imprimirLineas() {
    int tamanho=8;
    cout<<"   ";
    for(int i=0; i<tamanho; ++i){
        cout<<"+----";
    } cout<<"+"<<endl;
}
void imprimirEtiquetas() {
    int tamanho=8;
    cout<<"  ";
    for(int i=0; i<tamanho; ++i){
        cout<<"   "<<char('A'+i)<<" ";
    } cout<<endl;
}
void imprimirCasilleros(vector<vector<shared_ptr<CCasillero>>> casilleros) {
int tamanho=8;
imprimirLineas();
for(int i=tamanho-1; i>=0; i--){
cout<<" "<<i+1;
for(int j=0; j<tamanho; j++){
cout<<" | ";
shared_ptr<CPieza> pieza = casilleros[j][i]->getPieza();
if(pieza == NULL)
cout<<"  ";
else{
cout<<pieza->getId();
}
}
cout<<" | "<<i+1<<endl;
imprimirLineas();
}
}

class CTablero{
    vector<vector<shared_ptr<CCasillero>>> casilleros;
    friend class tableroBuilder;
    friend void asignacionPBlancas(CTablero& tablero);
    friend void asignacionPNegras(CTablero& tablero);
public:
    CTablero() = default;
    void setCasilleros(){}
    vector<vector<shared_ptr<CCasillero>>> getCasilleros(){
        return casilleros;
    }
    /* Validamos si la posicion de origen y destino pertenecen al tablero */
    bool valMovimiento1(string posInicial, string posFinal){
        /* Posicion inicial */
        int xi = posInicial[0];
        int yi = posInicial[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        if((xi-65 < 0) || (xi-65 > 7))
            return false;
        if((yi-49 < 0) || (yi-49 > 7))
            return false;
        if((xf-65 < 0) || (xf-65 > 7))
            return false;
        if((yf-49 < 0) || (yf-49 > 7))
            return false;
        return true;
    }
    /* Validamos si en la posicion seleccionada existe una pieza */
    bool valMovimiento2(string posInicial){
        /* Posicion inicial */
        int x = posInicial[0];
        int y = posInicial[1];

        if(casilleros[x-65][y-49]->pieza != NULL)
            return true;
        return false;
    }
    /* Validamos si en la posicion de destino existe una pieza */
    bool valMovimiento3(string posFinal){
        /* Posicion inicial */
        int x = posFinal[0];
        int y = posFinal[1];

        if(casilleros[x-65][y-49]->pieza != NULL)
            return true;
        return false;
    }
    /* Validamos si en la posicion de destino existe una pieza aliada */
    bool valMovimiento4(string posInicial, string posFinal){
        /* Posicion inicial */
        int xi = posInicial[0];
        int yi = posInicial[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        string colorPPosInicial = (casilleros[xi-65][yi-49]->pieza)->getColor();
        string colorPPosFinal = (casilleros[xf-65][yf-49]->pieza)->getColor();
        if(colorPPosInicial == colorPPosFinal){
            return true;
        }
        return false;
    };
    /* Validamos movimientos especiales (Movimiento del peon) */
    // Validacion de si la pieza seleccionada es un peon
    bool valMovimiento5(string posInicial){
        int x = posInicial[0];
        int y = posInicial[1];

        string idPieza = (casilleros[x-65][y-49]->pieza)->getId();
        if((idPieza == "PB") || (idPieza == "PN")){
            return true;
        }
        return false;
    }
    // Disponibilidad del movimiento de 2 cuadros
    bool valMovimiento5_1(string posInicial, string posFinal){
        /* Posicion inicial */
        int xi = posInicial[0];
        int yi = posInicial[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        if (((yi-49 == 1) && (dy == 2)) || ((yi-49 == 6) && (dy == -2))){
            return true;
        }
        return false;
    }
    // Movimiento de ataque
    bool valMovimiento5_2(string posInicial, string posFinal){
        /* Posicion inicial */
        int xi = posInicial[0];
        int yi = posInicial[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Color del peon */
        string colorPPosInicial = (casilleros[xi-65][yi-49]->pieza)->getColor();
        if(abs(dx)==1 && dy==1 && colorPPosInicial=="blanco")
            return true;
        if(abs(dx)==1 && dy==-1 && colorPPosInicial=="negro")
            return true;
        return false;
    }

    /* Validamos si en medio del recorrido de una pieza desde su posición de origen hacia su posición de destino, se encuentra una pieza intermendia. Así mismo si entre la pieza de origen y destino no hay desplazamiento */
    bool valMovimiento6(string posInicial, string posFinal){
        /* Posicion inicial */
        int xi = posInicial[0]-65;
        int yi = posInicial[1]-49;
        /* Posicion final */
        int xf = posFinal[0]-65;
        int yf = posFinal[1]-49;

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Caso base*/
        if (dx == 0 && dy == 0){
            return false;
        }
        char pieza = ((casilleros[xi][yi]->pieza)->getId())[0];

        // Peon
        if (pieza == 'P'){
            if (abs(dy) == 2){
                int my = dy/abs(dy);
                auto pieza = (casilleros[xi][yi+(1*my)])->getPieza();
                if(pieza != NULL){
                    return false;
                }
            }
            return true;
        }
        // Torre
        if (pieza == 'T'){
            if (dx == 0){
                for(int i=1; i<abs(dy); ++i){
                    int my = dy/abs(dy);
                    auto pieza = (casilleros[xi][yi+(i*my)])->getPieza();
                    if (pieza != NULL){
                        return false;
                    }
                }
            }
            else if (dy == 0){
                for(int i=1; i<abs(dx); ++i){
                    int mx = dx/abs(dx);
                    auto pieza = (casilleros[xi+(i*mx)][yi])->getPieza();
                    if (pieza != NULL){
                        return false;
                    }
                }
            }
            return true;
        }
        // Caballo
        if (pieza == 'C'){
            return true;
        }
        // Alfil
        if (pieza == 'A'){
            for(int i=1; i<abs(dx); ++i){
                int mx = dx/abs(dx);
                int my = dy/abs(dy);
                auto pieza = (casilleros[xi+(i*mx)][yi+(i*my)])->getPieza();
                if (pieza != NULL){
                    return false;
                }
            }
            return true;
        }
        // Rey
        if (pieza == 'R'){
            return true;
        }
        // Dama
        if (pieza == 'D'){
            if (dx == 0){
                for(int i=1; i<abs(dy); ++i){
                    int m = dy/abs(dy);
                    auto pieza = (casilleros[xi][yi+(i*m)])->getPieza();
                    if (pieza != NULL){
                        return false;
                    }
                }
            }
            else if (dy == 0){
                for(int i=1; i<abs(dx); ++i){
                    int m = dx/abs(dx);
                    auto pieza = (casilleros[xi+(i*m)][yi])->getPieza();
                    if (pieza != NULL){
                        return false;
                    }
                }
            }
            else{
                for(int i=1; i<abs(dx); ++i){
                    int mx = dx/abs(dx);
                    int my = dy/abs(dy);
                    auto pieza = (casilleros[xi+(i*mx)][yi+(i*my)])->getPieza();
                    if (pieza != NULL){
                        return false;
                    }
                }
            }
            return true;
        }
        return true;
    }

    void asignarPieza(shared_ptr<CPieza> pieza){
        string posicion = pieza->posicion;
        int x = posicion[0] - 65;
        int y = posicion[1] - 49;
        casilleros[x][y]->setPieza(pieza);
    }
    void realizarMovimiento(string posInicial, string posFinal){
        /* Posicion inicial */
        int xi = posInicial[0] - 65;
        int yi = posInicial[1] - 49;
        /* Posicion final */
        int xf = posFinal[0] - 65;
        int yf = posFinal[1] - 49;

        /* Movemos los valores de posInicial a posFinal */
        (casilleros[xf][yf])->pieza = move((casilleros[xi][yi])->pieza);
        ((casilleros[xf][yf])->pieza)->setPosicion(posFinal);
    };
    void mostrarTablero(){
        imprimirEtiquetas();
        imprimirCasilleros(casilleros);
        imprimirEtiquetas();
    };
    ~CTablero(){};
};

/* Tablero Builder */
class tableroBuilder{
    shared_ptr<CTablero> tablero;
public:
    void buildTablero(){
        tablero = std::move(make_shared<CTablero>());
        cout<<"buildTablero passed"<<endl;
    }
    void buildCasilleros(){
        int n = 8;
        vector<vector<shared_ptr<CCasillero>>> casilleros(n, vector<shared_ptr<CCasillero>>(n));
        for(auto& filas: casilleros){
            for(auto& item: filas){
                item = move(make_shared<CCasillero>());
            }
        }
        tablero->casilleros = casilleros;
        cout<<"buildCasilleros passed"<<endl;
    }
    shared_ptr<CTablero> getTablero() {
        cout<<"getTablero passed"<<endl;
        return std::move(tablero);
    }
    ~tableroBuilder(){};
};

/* Asignacion de piezas al tablero */
/* Piezas blancas */
void asignacionPBlancas(CTablero& tablero){
    string color = "blanco";
    tablero.asignarPieza(make_shared<CTorre>("TB", "A1", color, 2));
    tablero.asignarPieza(make_shared<CCaballo>("CB", "B1", color, 2));
    tablero.asignarPieza(make_shared<CAlfil>("AB", "C1", color, 2));
    tablero.asignarPieza(make_shared<CDama>("DB", "D1", color, 2));
    tablero.asignarPieza(make_shared<CRey>("RB", "E1", color, 2));
    tablero.asignarPieza(make_shared<CAlfil>("AB", "F1", color, 2));
    tablero.asignarPieza(make_shared<CCaballo>("CB", "G1", color, 2));
    tablero.asignarPieza(make_shared<CTorre>("TB", "H1", color, 2));

    /* Peones blancos */
    vector<string> vPosicionesB2 = {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2"};
    for(auto& posicion: vPosicionesB2)
        tablero.asignarPieza(make_shared<CPeon>("PB", posicion, color, 1));
}

/* Piezas Negras */
void asignacionPNegras(CTablero& tablero){
    string color = "negro";
    tablero.asignarPieza(make_shared<CTorre>("TN", "A8", color, 2));
    tablero.asignarPieza(make_shared<CCaballo>("CN", "B8", color, 2));
    tablero.asignarPieza(make_shared<CAlfil>("AN", "C8", color, 2));
    tablero.asignarPieza(make_shared<CDama>("DN", "D8", color, 2));
    tablero.asignarPieza(make_shared<CRey>("RN", "E8", color, 2));
    tablero.asignarPieza(make_shared<CAlfil>("AN", "F8", color, 2));
    tablero.asignarPieza(make_shared<CCaballo>("CN", "G8", color, 2));
    tablero.asignarPieza(make_shared<CTorre>("TN", "H8", color, 2));
    /* Peones negros */
    vector<string> vPosicionesN7 = {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7"};
    for(auto& posicion: vPosicionesN7)
        tablero.asignarPieza(make_shared<CPeon>("PN", posicion, color, 1));
}

bool validacionBot(shared_ptr<CTablero> tablero, string posInicial, string posFinal){
    /* Evaluamos si las posiciones seleccionadas pertenecen al tablero*/
    if (!(tablero->valMovimiento1(posInicial, posFinal))){
        return false;
    }

    /* Evaluamos si en la posicion seleccionada se encuentra una pieza */
    if (!(tablero->valMovimiento2(posInicial))){
        return false;
    }

    /* Evaluamos movimientos especiales */
    /* Desplazamiento del peon de 2 casilleros */
    if ((tablero->valMovimiento5(posInicial))){
        if (!(tablero->valMovimiento3(posFinal))){
            if ((tablero->valMovimiento5_1(posInicial, posFinal))){
                if ((tablero->valMovimiento6(posInicial, posFinal))){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }

    /* Movimiento de ataque del peon */
    if ((tablero->valMovimiento5(posInicial))){
        if ((tablero->valMovimiento3(posFinal))){
            if ((tablero->valMovimiento5_2(posInicial, posFinal))){
                if ((tablero->valMovimiento6(posInicial, posFinal))){
                    return  true;
                }
                else{
                    return false;
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
        return false;
    }

    /* Evaluamos movimientos regulares */
    if((tablero->valMovimiento3(posFinal))){
        if((tablero->valMovimiento4(posInicial, posFinal))){
            return false;
        }
        else{
            if ((tablero->valMovimiento6(posInicial, posFinal))){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        if ((tablero->valMovimiento6(posInicial, posFinal))){
            return true;
        }
        else{
            return false;
        }
    }
}

vector<vector<int>> asistenteBot(shared_ptr<CTablero> tablero){
    vector<vector<int>> riesgoCasilleros(8, vector<int>(8));
    for(auto& filas: riesgoCasilleros){
        for(auto& item: filas){
            item = 0;
        }
    }
    vector<thread> vectorHilos(16);
    auto casilleros = tablero->getCasilleros();
    int n = 0;
    for(auto& filas: casilleros){
        if (n == 15)
            break;
        for(auto& item: filas){
            if (n == 15)
                break;
            auto pieza = item->getPieza();
            if (pieza == nullptr)
                continue;
            if(pieza->getColor() == "blanco"){
                vectorHilos[n] = thread([&pieza, &tablero, &riesgoCasilleros](){
                    auto posInicial = pieza->getPosicion();
                    for(int i=65; i<=72; ++i){
                        for(int j=49; j<=56; ++j){
                            lock_guard<mutex> lg(mtx);
                            string posFinal = {(char)i, (char)j};
                            if(validacionBot(tablero, posInicial, posFinal)){
                                ++(riesgoCasilleros[i-65][j-49]);
                            };
                        }
                    }
                });
                if(pieza->getColor() == "blanco")
                    vectorHilos[n].join();
                ++n;
            }
        }
    }
    return riesgoCasilleros;
}



#endif //PROYECTO_POO_TABLERO_H
