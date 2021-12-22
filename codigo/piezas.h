//
// Created by SANDERS on 22/12/2021.
//

#ifndef PROYECTO_POO_PIEZAS_H
#define PROYECTO_POO_PIEZAS_H

#include "librerias.cpp"

class CPieza{
protected:
    friend class CTablero;
    string id;
    string posicion;
    string color;
    int importancia;
public:
    // Constructors
    CPieza() = default;
    CPieza(string id, string posicion, string color, int importancia):
            id{id}, posicion{posicion}, color{color}, importancia{importancia} {};
    // Getters
    virtual int getImportancia() = 0;
    virtual string getPosicion() = 0;
    virtual string getColor() = 0;
    virtual string getId() = 0;
    // Setters
    virtual void setPosicion(string _posicion) = 0;
    // Validaciones
    virtual bool valMovimiento0(string posFinal) = 0;
    // Destructors
    virtual ~CPieza(){};
};


class CPeon: public CPieza{
    friend class tableroBuilder;
public:
    CPeon() = default;
    CPeon(string id, string posicion, string color, int importancia):
            CPieza(id, posicion, color, importancia) {};

    int getImportancia() override{return importancia;}
    string getPosicion() override{return posicion;}
    string getColor() override{return color;}
    string getId() override{return id;}

    void setPosicion(string _posicion) override{posicion = _posicion;}

    bool valMovimiento0(string posFinal) override{
        /* Posicion inicial */
        int xi = posicion[0];
        int yi = posicion[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Desplazamiento hacia adelante */
        if(((dx == 0) && (dy == 1)) && (color == "blanco")){
            return true;
        }
        else if (((dx == 0) && (dy == -1)) && (color == "negro")){
            return true;
        }
        return false;
    }
    ~CPeon(){};
};

class CTorre: public CPieza{
    friend class tableroBuilder;
public:
    CTorre() = default;
    CTorre(string id, string posicion, string color, int importancia):
            CPieza(id, posicion, color, importancia) {};

    int getImportancia() override{return importancia;}
    string getPosicion() override{return posicion;}
    string getColor() override{return color;}
    string getId() override{return id;}

    void setPosicion(string _posicion) override{posicion = _posicion;}

    bool valMovimiento0(string posFinal) override{
        /* Posicion inicial */
        int xi = posicion[0];
        int yi = posicion[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Desplazamiento vertical */
        if ((dx == 0) && (dy != 0))
            return true;
        /* Desplazamiento horizontal */
        if ((dx != 0) && (dy == 0))
            return true;
        return false;
    }
    ~CTorre(){};
};

class CCaballo: public CPieza{
    friend class tableroBuilder;
public:
    CCaballo() = default;
    CCaballo(string id, string posicion, string color, int importancia):
            CPieza(id, posicion, color, importancia) {};

    int getImportancia() override{return importancia;}
    string getPosicion() override{return posicion;}
    string getColor() override{return color;}
    string getId() override{return id;}

    void setPosicion(string _posicion) override{posicion = _posicion;}

    bool valMovimiento0(string posFinal) override{
        /* Posicion inicial */
        int xi = posicion[0];
        int yi = posicion[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* H vertical */
        if((abs(dx) == 1) && (abs(dy) == 2))
            return true;
        /* H Horiizontal */
        if((abs(dx) == 2) && (abs(dy) == 1))
            return true;

        return false;
    }
    ~CCaballo(){};
};

class CAlfil: public CPieza{
    friend class tableroBuilder;
public:
    CAlfil() = default;
    CAlfil(string id, string posicion, string color, int importancia):
            CPieza(id, posicion, color, importancia) {};

    int getImportancia() override{return importancia;}
    string getPosicion() override{return posicion;}
    string getColor() override{return color;}
    string getId() override{return id;}

    void setPosicion(string _posicion) override{posicion = _posicion;}

    bool valMovimiento0(string posFinal) override{
        /* Posicion inicial */
        int xi = posicion[0];
        int yi = posicion[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Movimiento diagonal */
        if ((abs(dy) != 0) && (abs(dx) != 0))
            return true;

        return false;
    }
    ~CAlfil(){};
};

class CRey: public CPieza{
    friend class tableroBuilder;
public:
    CRey() = default;
    CRey(string id, string posicion, string color, int importancia):
            CPieza(id, posicion, color, importancia) {};

    int getImportancia() override{return importancia;}
    string getPosicion() override{return posicion;}
    string getColor() override{return color;}
    string getId() override{return id;}

    void setPosicion(string _posicion) override{posicion = _posicion;}

    bool valMovimiento0(string posFinal) override{
        /* Posicion inicial */
        int xi = posicion[0];
        int yi = posicion[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Movimiento vertical */
        if ((dx == 0) && (abs(dy) == 1))
            return true;
        /* Movimiento horizontal */
        if ((abs(dx) == 1) && (dy == 0))
            return true;
        /* Movimiento diagonal*/
        if ((abs(dx) == 1) && (abs(dy) == 1))
            return true;

        return false;
    }
    ~CRey(){};
};

class CDama: public CPieza{
    friend class tableroBuilder;
public:
    CDama() = default;
    CDama(string id, string posicion, string color, int importancia):
            CPieza(id, posicion, color, importancia) {};
    int getImportancia() override{return importancia;}
    string getPosicion() override{return posicion;}
    string getColor() override{return color;}
    string getId() override{return id;}

    void setPosicion(string _posicion) override{posicion = _posicion;}

    bool valMovimiento0(string posFinal) override{
        /* Posicion inicial */
        int xi = posicion[0];
        int yi = posicion[1];
        /* Posicion final */
        int xf = posFinal[0];
        int yf = posFinal[1];

        /* Variacion de y */
        int dy = yf - yi;
        /* Variacion de x */
        int dx = xf - xi;

        /* Movimiento vertical */
        if ((dx == 0) && (abs(dy) != 0))
            return true;
        /* Movimiento horizontal */
        if ((abs(dx) != 0) && (dy == 0))
            return true;
        /* Movimiento diagonal*/
        if ((abs(dx) != 0) && (abs(dy) != 0))
            return true;

        return false;
    }
    ~CDama(){};
};

#endif //PROYECTO_POO_PIEZAS_H
