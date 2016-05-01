#ifndef CASILLA_H
#define CASILLA_H

#include "Jugador.h"
#include "common.h"

class Jugador;

typedef std::unordered_map<Jugador const*, uint32> MapJugadores;

class Casilla
{
public:
    Casilla();
    Casilla(uint32 id);
    ~Casilla();

    uint32 GetId() const { return m_id; }

    MapJugadores GetMapJugadores() const { return m_mapJugadores; }

    void JugadorEnCasilla(Jugador* jugador);

    void ManejarCasilla(Jugador* jugador);

    void MostrarLogJugadores();

    void Reset() { m_mapJugadores.clear(); }

private:
    uint32 m_id;
    MapJugadores m_mapJugadores; 

};

#endif
