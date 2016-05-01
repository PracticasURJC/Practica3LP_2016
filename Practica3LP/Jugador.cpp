#include "Jugador.h"

Jugador::Jugador()
{
    m_id                    = 0;
    m_turnosPenalizacion    = 0;
    m_casillaActual         = 0;
    m_nombre                = "";
    m_partida               = nullptr;

    DEBUG_LOG("Jugador vacio creado.");
}

Jugador::Jugador(uint32 id, std::string nombre, Partida* partida)
{
    m_id                    = id;
    m_nombre                = nombre;
    m_casillaActual         = 0;
    m_partida               = partida;
    m_turnosPenalizacion    = 0;

    DEBUG_LOG("Jugador %s creado.\n", ToString().c_str());
}

Jugador::~Jugador()
{
}

// Mueve al jugador tantas casillas como saque. Si se saca puntuacion y se pasa de la casilla final, retrocedera
void Jugador::MoverCasillas(uint32 numCasillas)
{
    if (m_casillaActual + numCasillas > CASILLA_FINAL)
    {
        m_casillaActual = CASILLA_FINAL - (m_casillaActual + numCasillas - CASILLA_FINAL);
    }
    else
        m_casillaActual += numCasillas;
    
    DEBUG_LOG("%s cae en la casilla %u.\n", ToString().c_str(), m_casillaActual);
}

// Mueve al jugador a la siguiente oca
void Jugador::MoverSiguienteOca()
{
    m_casillaActual += DISTANCIA_ENTRE_OCAS;
    DEBUG_LOG("Jugador %s movido a la casilla %u por caer en una Oca.\n", ToString().c_str(), m_casillaActual);
}

// Mueve al jugador a otra casilla del mismo tipo
void Jugador::MoverCasillaLink(bool conTirada /*=false*/)
{
    switch (m_casillaActual)
    {
    case CASILLA_DADO_1:
        m_casillaActual = CASILLA_DADO_2;
        break;
    case CASILLA_DADO_2:
        m_casillaActual = CASILLA_DADO_1;
        break;
    case CASILLA_PUENTE_1:
        m_casillaActual = CASILLA_PUENTE_2;
        break;
    case CASILLA_PUENTE_2:
        m_casillaActual = CASILLA_PUENTE_1;
        break;
    default:
        break;
    }
    
    std::string temp = m_casillaActual == CASILLA_DADO_1 || m_casillaActual == CASILLA_DADO_2 ? "dado" : "puente";
    DEBUG_LOG("Jugador %s movido a la casilla %u por caer en un %s.\n", ToString().c_str(), m_casillaActual, temp.c_str());

    // En caso de caer en los dados, puede volver tirar
    if (conTirada)
    {
        DEBUG_LOG("El jugador puede volver a tirar");

        uint32 tirada = m_partida->GetDado()->LanzarDado();
        DEBUG_LOG("%s tira el dado y saca un %u.\n", ToString().c_str(), tirada);

        MoverCasillas(tirada);

        DEBUG_LOG("%s cae en la casilla %u.\n", ToString().c_str(), m_casillaActual);
    }
}

// Penaliza al jugador varios turnos
void Jugador::Penalizar(uint32 turnos)
{
    m_turnosPenalizacion = turnos;

    std::string temp = m_casillaActual == CASILLA_CARCEL ? "la carcel" : m_casillaActual == CASILLA_POZO ? "el pozo" : "la posada";
    DEBUG_LOG("%s cae en %s. No podra tirar durante los siguientes %u turnos.\n", ToString().c_str(), temp.c_str(), turnos);
}

// Retrocede a la casilla 30 por caer en el laberinto
void Jugador::MoverLaberinto()
{
    m_casillaActual = 30;

    DEBUG_LOG("%s cae en el laberinto. Retrocede a la casilla 30.\n", ToString().c_str());
}

// Retrocede a la casilla de salida por caer en la calavera
void Jugador::VolverInicio()
{
    m_casillaActual = 1;

    DEBUG_LOG("%s cae en la calavera. Retrocede a la casilla de salida.\n", ToString().c_str());
}

// Muestra al jugador como un string "(ID: 'id') 'nombre'" 
std::string Jugador::ToString() const
{
    std::stringstream ss;

    ss << "(ID: " << m_id << ") " << m_nombre;
    return ss.str();
}
