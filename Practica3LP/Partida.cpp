#include "Partida.h"

Partida::Partida()
{
    m_turnoActual   = 0;
    m_jugadorActual = nullptr;
    m_ganador       = nullptr;
    m_tablero       = new Tablero();
    m_dado          = new Dado();
    m_jugadores.clear();
}

Partida::~Partida()
{
    delete m_dado;
    m_dado = nullptr;

    delete m_tablero;
    m_tablero = nullptr;
}

// Reiniciamos las variables para una nueva partida
void Partida::Reset()
{
    m_turnoActual   = 0;
    m_jugadorActual = nullptr;
    m_ganador       = nullptr;
    m_jugadores.clear();

    m_tablero->Reset();
}

// Devuelve un puntero a un jugador dado un id
Jugador* Partida::GetJugador(uint32 id) const
{
    for (Jugador* jugador : m_jugadores)
    {
        if (jugador->GetId() == id)
            return jugador;
    }
    return nullptr;
}

// Inicia una nueva partida
void Partida::IniciarPartida()
{
    DEBUG_LOG("Comenzando partida.\n");
    DEBUG_LOG("Introduzca numero de jugadores (introduzca 0 para usar unos jugadores creados por defecto).\n");

    char input[BUFFER_SIZE];

    int32 numJugadores = 0;
    do
    {
        fgets(input, BUFFER_SIZE, stdin);

        numJugadores = std::atoi(input);
    }
    while (numJugadores > MAX_JUGADORES || numJugadores < 0);

    CrearJugadores(std::max<int32>(0, numJugadores));

    // Iniciamos al primer jugador como jugador actual
    m_jugadorActual = GetJugador(0);

    // Entramos en el bucle inicial del juego
    BucleJuego();
}

// Bucle del juego
void Partida::BucleJuego()
{
    while (!m_ganador)
    {
        SiguienteTirada();
    }

    FinPartida();
}

// Crea los jugadores, en caso de no introducir un numero, se utilizara una plantilla predefinida
void Partida::CrearJugadores(uint32 numJugadores)
{
    if (!numJugadores)
    {
        Jugador* jugador1 = new Jugador(0, "Jugador 1", this);
        m_jugadores.push_back(jugador1);

        Jugador* jugador2 = new Jugador(1, "Jugador 2", this);
        m_jugadores.push_back(jugador2);
    }
    else
    {
        char buffer[BUFFER_SIZE];
        for (uint32 i = 0; i < numJugadores; i++)
        {
            DEBUG_LOG("Elige un nombre para el jugador %u.\n", i + 1);
            fgets(buffer, BUFFER_SIZE, stdin);

            // Eliminamos el caracter "\n" del buffer.
            std::string nombre = buffer;
            nombre.pop_back();

            // Creamos un nuevo jugador y lo añadimos a la lista
            Jugador* jugador = new Jugador(i, nombre, this);
            m_jugadores.push_back(jugador);
        }
    }
}

void Partida::FinPartida()
{
    if (!m_ganador || !m_tablero)
        return;

    DEBUG_LOG("%s ha ganado!\n", m_ganador->ToString().c_str());

    // Muestra el log de cada casilla al acabar el juego
    m_tablero->MostrarLogCasillas();
    
    DEBUG_LOG("Quieres jugar otra partida? (Y/N)");

    char buffer[BUFFER_SIZE];

    // Admite "Y","y", "N" y "n"
    do
    {
        fgets(buffer, BUFFER_SIZE, stdin);
    }
    while (!ManejarRespuesta(std::string(buffer)));

    // En caso afirmativo, reiniciamos la partida e iniciamos una nueva
    Reset();
    IniciarPartida();
}

bool Partida::ManejarRespuesta(std::string buffer)
{
    // Borra el caracter "\n" del string y convierte todo el string a mayusculas
    buffer.pop_back();
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);

    // En caso afirmativo crea otra partida, sino finaliza la ejecucion
    if (buffer == "Y")
        return true;
    else if (buffer == "N")
        exit(EXIT_SUCCESS);

    return false;
}

// Siguiente tirada de la partida
void Partida::SiguienteTirada()
{
    // Si el jugador esta penalizado, reducimos la penalizacion y pasamos al siguiente jugador
    if (m_jugadorActual->TienePenalizacion())
    {
        m_jugadorActual->DisminuirTurnosPenalizacion();
        DEBUG_LOG("%s esta penalizado. Turnos restantes %u.\n", m_jugadorActual->ToString().c_str(), m_jugadorActual->GetTurnosPenalizacion());
    }
    // En el caso normal, tiramos el dado
    else
    {
        uint32 tirada = m_dado->LanzarDado();
    
        DEBUG_LOG("%s tira el dado y saca un %u.\n", m_jugadorActual->ToString().c_str(), tirada);
        // Movemos al jugador tantas casillas como haya sacado con el dado
        m_jugadorActual->MoverCasillas(tirada);

        // Manejamos la casilla en la que ha caido el jugador desde el tablero
        m_tablero->HandleJugador(m_jugadorActual);

        // Si el jugador esta en la casilla final, lo marcamos como ganador
        if (m_jugadorActual->GetCasillaActual() == CASILLA_FINAL)
        {
            m_ganador = m_jugadorActual;
            return;
        }
    }

    // Actualizamos el siguiente jugador en tirar y aumentamos el turno
    m_turnoActual = (m_turnoActual + 1) >= GetNumJugadores() ? 0 : m_turnoActual + 1;
    m_jugadorActual = GetJugador(m_turnoActual);

    // Obligamos a pulsar una tecla, evita la ejecucion del programa hasta el final
    system("PAUSE");
}
