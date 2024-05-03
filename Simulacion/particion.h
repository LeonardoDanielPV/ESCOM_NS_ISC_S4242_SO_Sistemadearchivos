/**
 * particion.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * 
 * 30/04/2024
 * 
 * Verción 4
*/

#ifndef PARTICION_H
#define PARTICION_H

#include <deque>
#include <vector>

#include "superbloque.h"
#include "nodoi.h"

class Particion {
  // Atributos
  public:
    SuperBloque sp;
    std::deque<int> bloques_libres;
    std::vector<NodoI> noodos_indices;
};

#endif  // PARTICION_H