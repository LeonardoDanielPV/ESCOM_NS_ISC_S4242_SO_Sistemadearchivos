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

#ifndef SUPERBLOQUE_H
#define SUPERBLOQUE_H

// Contiene todos los parámetros clave acerca del sistema de archivos
class SuperBloque {
  // Atributos
  public:
    int numero_magico;
    int nro_bloques;
  public:
    SuperBloque(int cnumero_magico, int cnro_bloques);
};

#endif  // SUPERBLOQUE_H