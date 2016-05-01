#ifndef JUGADOR_H
#define JUGADOR_H

#include "Casilla.h"
#include "Partida.h"
#include "common.h"

class Partida;
class Jugador
{
public:
    Jugador();
    Jugador(uint32 id, std::string nombre, Partida* partida);
    ~Jugador();

    uint32 GetId() const { return m_id; }
    void SetId(uint32 id) { m_id = id; }

    uint32 GetCasillaActual() const { return m_casillaActual; }
    void SetCasillaActual(uint32 casilla) { m_casillaActual = casilla; }

    uint32 GetTurnosPenalizacion() const { return m_turnosPenalizacion; }
    void SetTurnosPenalizacion(uint32 turnos) { m_turnosPenalizacion = turnos; }

    bool TienePenalizacion() { return m_turnosPenalizacion > 0; }
    void DisminuirTurnosPenalizacion() { m_turnosPenalizacion = std::max<int32>(0, m_turnosPenalizacion - 1); }

    Partida* GetPartida() const { return m_partida; }

    void MoverCasillas(uint32 numCasillas);
    void MoverSiguienteOca();
    void MoverCasillaLink(bool conTirada = false);
    void Penalizar(uint32 turnos);
    void MoverLaberinto();
    void VolverInicio();

    std::string ToString() const;

private:
    uint32 m_id;
    std::string m_nombre;
    uint32 m_casillaActual;
    uint32 m_turnosPenalizacion;
    Partida* m_partida;

};

#endif
