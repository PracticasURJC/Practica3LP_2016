#include "Partida.h"
#include "common.h"

int main(int argc, char** argv) {

    // Inicializa la seed
    srand((unsigned int)(time(nullptr)));

    // Creamos una nueva partida y la iniciamos
    Partida* partida = new Partida();
    partida->IniciarPartida();

    system("PAUSE");
    return EXIT_SUCCESS;
}
