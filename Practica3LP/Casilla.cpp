#include "Casilla.h"

Casilla::Casilla()
{
    m_id = 0;
    m_mapJugadores.clear();
}

Casilla::Casilla(uint32 id)
{
    m_id = id;
    m_mapJugadores.clear();
}

Casilla::~Casilla()
{
}

void Casilla::JugadorEnCasilla(Jugador* jugador)
{
    // Maneja los posibles efectos especiales de la casilla
    ManejarCasilla(jugador);

    // Si el jugador ya ha caido anteriormente en la casilla
    // aumentamos en 1 el numero de veces que ha estado
    // sino, la iniciamos a 1
    if (m_mapJugadores.find(jugador) != m_mapJugadores.end())
        m_mapJugadores[jugador] += 1;
    else
        m_mapJugadores[jugador] = 1;
}

void Casilla::ManejarCasilla(Jugador* jugador)
{
    switch (m_id)
    {
    // Mueve al jugador hacia la siguiente oca
    case CASILLA_OCA_1:
    case CASILLA_OCA_2:
        jugador->MoverSiguienteOca();
        break;
    // Mueve al jugador hacia el otro extremo del puente, hacia adelante o hacia atras
    case CASILLA_PUENTE_1:
    case CASILLA_PUENTE_2:
        jugador->MoverCasillaLink();
        break;
    // Mueve al jugador hacia la otra casilla de dados, permitiendole tirar otra vez al llegar
    case CASILLA_DADO_1:
    case CASILLA_DADO_2:
        jugador->MoverCasillaLink(true);
        break;
    // Penaliza al jugador 2 turnos sin tirar
    case CASILLA_POSADA:
    case CASILLA_POZO:
        jugador->Penalizar(PENALIZACION_POSADA_POZO);
        break;
    // Mueve al jugador hacia la casilla 30
    case CASILLA_LABERINTO:
        jugador->MoverLaberinto();
        break;
    // Penaliza al jugador 3 turnos sin tirar
    case CASILLA_CARCEL:
        jugador->Penalizar(PENALIZACION_CARCEL);
        break;
    // Mueve al jugador a la casilla de inicio
    case CASILLA_CALAVERA:
        jugador->VolverInicio();
        break;
    // Caso standard
    case CASILLA_FINAL:
    default:
        break;
    }
}

// Muestra el log de la casilla
void Casilla::MostrarLogJugadores()
{
    if (m_mapJugadores.empty())
        return;

    DEBUG_LOG("Mostrando historial de la casilla %u.\n", m_id);
    for (MapJugadores::const_iterator itr = m_mapJugadores.begin(); itr != m_mapJugadores.end(); itr++)
    {
        Jugador const* jugador = (itr)->first;
        if (!jugador)
            continue;

        uint32 veces = (itr)->second;

        DEBUG_LOG("%s ha caido %u %s.\n", jugador->ToString().c_str(), veces, veces == 1 ? "vez" : "veces");
    }
}
