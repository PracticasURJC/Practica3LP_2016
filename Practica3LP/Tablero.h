#ifndef TABLERO_H
#define TABLERO_H

#include "Casilla.h"
#include "Jugador.h"
#include "common.h"

class Casilla;
class Jugador;
class Tablero
{
public:
    Tablero();
    ~Tablero();

    void IniciarCasillas();

    void HandleJugador(Jugador* jugador);

    Casilla* GetCasilla(uint32 id);

    void MostrarLogCasillas();

    void Reset();

private:
    Casilla* m_casillas[MAX_CASILLAS];

};

#endif

