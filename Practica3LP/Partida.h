#ifndef PARTIDA_H
#define PARTIDA_H

#include "Jugador.h"
#include "Tablero.h"
#include "common.h"

struct Dado
{
    Dado(uint32 caras = CARAS_DADO) { m_caras = caras; }

    uint32 LanzarDado() { return rand() % m_caras + 1; }

private:
    uint32 m_caras;
};

class Tablero;
class Jugador;
class Partida
{
public:
    Partida();
    ~Partida();

    void Reset();

    uint32 GetJugadorActual() const { return m_turnoActual; }
    void SetTurnoActual(uint32 turno) { m_turnoActual = turno; }

    Tablero* GetTablero() const { return m_tablero; }
    std::list<Jugador*> GetJugadores() const { return m_jugadores; }

    Jugador* GetJugadorActual() { return m_jugadorActual; }
    void SetJugadorActual(Jugador* jugador) { m_jugadorActual = jugador; }

    uint32 GetNumJugadores() { return m_jugadores.size(); }

    Dado* GetDado() { return m_dado; }

    Jugador* GetJugador(uint32 id) const;

    void IniciarPartida();
    void BucleJuego();
    void CrearJugadores(uint32 numJugadores);
    void FinPartida();

    void SiguienteTirada();

    bool ManejarRespuesta(std::string buffer);

private:
    uint32 m_turnoActual;
    Tablero* m_tablero;
    Dado* m_dado;
    Jugador* m_jugadorActual;
    Jugador* m_ganador;
    std::list<Jugador*> m_jugadores;

};

#endif
