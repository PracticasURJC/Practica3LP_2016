#include "Tablero.h"

Tablero::Tablero()
{
    IniciarCasillas();
}

Tablero::~Tablero()
{
    for (uint32 i = 0; i < MAX_CASILLAS; i++)
    {
        delete m_casillas[i];
        m_casillas[i] = nullptr;
    }
}

// Inicia cada casilla del tablero
void Tablero::IniciarCasillas()
{
    for (uint32 i = 0; i < MAX_CASILLAS; i++)
    {
        m_casillas[i] = new Casilla(i);
    }
}

// Maneja al jugador segun su posicion en el tablero
void Tablero::HandleJugador(Jugador* jugador)
{
    Casilla* casilla = GetCasilla(jugador->GetCasillaActual());
    if (!casilla)
        return;

    casilla->JugadorEnCasilla(jugador);
}

// Obtiene un puntero a una casilla determinada segun su id
Casilla* Tablero::GetCasilla(uint32 id)
{
    if (id > CASILLA_FINAL)
        return nullptr;

    return m_casillas[id];
}

// Muestra el log de cada casilla
void Tablero::MostrarLogCasillas()
{
    for (uint32 i = 0; i < MAX_CASILLAS; i++)
    {
        Casilla* casilla = GetCasilla(i);
        if (!casilla)
            return;

        casilla->MostrarLogJugadores();
    }
}

// Reiniciamos el log de cada casilla
void Tablero::Reset()
{
    for (uint32 i = 0; i < MAX_CASILLAS; i++)
    {
        Casilla* casilla = GetCasilla(i);
        if (!casilla)
            return;

        casilla->Reset();
    }
}
