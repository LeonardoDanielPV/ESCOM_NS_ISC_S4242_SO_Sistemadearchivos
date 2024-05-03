/**
 * superbloque.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * 
 * 30/04/2024
 * 
 * Verción 4
*/

#ifndef NODOI_H
#define NODOI_H

#include <vector>

#include "atributoarchivo.h"

class NodoI {
  public:
    AtributoArchivo atributo;
    std::vector<int> direccion_bloque; //Arreglo de la particion

  public:
    NodoI();
    NodoI(AtributoArchivo catributo, std::vector<int>& cdireccion_bloque);
};

#endif  // NODOI_H