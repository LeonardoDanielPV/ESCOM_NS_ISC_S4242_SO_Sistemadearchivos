/**
 * atributoarchivo.cpp
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * 
 * 30/04/2024
 * 
 * Verción 4
*/

#include "atributoarchivo.h"

// COnstructor
AtributoArchivo::AtributoArchivo(int cproteccion, int cclave,
                                 int ccreador, int cpropietario,
                                 bool csolo_lectura, bool coculto,
                                 bool csistema, bool carchivo,
                                 bool cascii_binario, bool cacceso_aleatorio,
                                 bool ctemporal,    bool cbloqueo,
                                 int clongitud_registro, int cposicion_llave,
                                 int clongitud_llave, int chora_creacion,
                                 int chora_ultima_modificacion, int clongitud,
                                 int clongitud_maxima) {
  proteccion = cproteccion;
  clave = cclave;
  creador = ccreador;
  propietario =cpropietario;
  solo_lectura = csolo_lectura;
  oculto = coculto;
  sistema = csistema;
  archivo = carchivo;
  ascii_binario = cascii_binario;
  temporal = ctemporal;
  bloqueo = cbloqueo;
  longitud_registro = clongitud_registro;
  posicion_llave = cposicion_llave;
  longitud_llave = clongitud_llave;
  hora_creacion = chora_creacion;
  hora_ultima_modificacion = chora_ultima_modificacion;
  longitud = clongitud;
  longitud_maxima = clongitud_maxima;
};

AtributoArchivo::AtributoArchivo() {

};