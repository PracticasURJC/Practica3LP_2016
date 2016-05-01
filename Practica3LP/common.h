/*
    Header con las cosas en comun para todas las clases
*/

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>

enum CasillasEspeciales
{
    CASILLA_OCA_1       = 5,
    CASILLA_PUENTE_1    = 6,
    CASILLA_OCA_2       = 9,
    CASILLA_PUENTE_2    = 12,
    CASILLA_POSADA      = 19,
    CASILLA_DADO_1      = 26,
    CASILLA_POZO        = 31,
    CASILLA_LABERINTO   = 42,
    CASILLA_CARCEL      = 52,
    CASILLA_DADO_2      = 53,
    CASILLA_CALAVERA    = 58,
    CASILLA_FINAL       = 63,
    MAX_CASILLAS,
};

// Tamaño maximo del buffer de lectura
#define BUFFER_SIZE             256

#define CARAS_DADO                  6
#define MAX_JUGADORES               4
#define DISTANCIA_ENTRE_OCAS        9
#define PENALIZACION_POSADA_POZO    2
#define PENALIZACION_CARCEL         3

// Activa los logs
#define WITH_DEBUG

#ifdef WITH_DEBUG
    #define DEBUG_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(fmt, ...)
#endif

// Optimizacion de tipos
typedef unsigned short uint8;
typedef signed short int8;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned long long uint64;
typedef signed long long int64;

#endif
