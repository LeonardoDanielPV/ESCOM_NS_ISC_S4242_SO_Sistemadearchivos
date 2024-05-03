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

#include "nodoi.h"

NodoI::NodoI(AtributoArchivo catributo, std::vector<int>& cdireccion_bloque) {
  atributo = catributo;
  direccion_bloque = std::vector<int>(cdireccion_bloque);
};