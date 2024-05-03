/**
 * atributoarchivo.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * 
 * 30/04/2024
 * 
 * Verción 4
*/

#ifndef ATRIBUTOARCHIVO_H
#define ATRIBUTOARCHIVO_H

class AtributoArchivo {
  public:
    // En que forma se puede acceder al archivo
    int proteccion;
    // Constraseña necesario para acceder al archivo
    int clave;
    // ID del propietario actual
    int propietario;
    // 0 para lectura/escritura; 1 para sólo lectura
    bool solo_lectura;
    // 0 para normal; 1 para que no aparezca en los listados
    bool oculto;
    // 0 para archivos normales; 1 para archivo del sistema
    bool sistema;
    // 0 si ha sido respaldado; 1 si necesita respaldarse
    bool archivo;
    // 0 para archivo ASCII; 1 para archivo binario
    bool ascii_binario;
    // 0 para sólo acceso secuencia; 1 para acceso aleatorio
    bool acceso_aleatorio;
    // 0 para normal; 1 para eliminar archivo al salir del proceso
    bool temporal;
    // 0 para desbloqueado; distinto de cero para bloqueado
    bool bloqueo;
    // Número de bytes en un registro
    int longitud_registro;
    // Desplazamiento de la llave dentro de cada registro
    int posicion_llave;
    // Número de bytes en el campo llave
    int longitud_llave;
    // Fecha y hora en que se creó el archivo
    int hora_creacion;
    // Fecha y hora en que se modificó por última vez el archivo
    int hora_ultima_modificacion;
    // Número de bytes en el archivo
    int longitud;
    // Número de bytes hasta donde puede crecer el archivo
    int longitud_maxima;
  private:
    // ID de la persona que creó el archivo
    int creador;
  public:
    AtributoArchivo();
    AtributoArchivo(int cproteccion, int cclave,
                    int ccreador, int cpropietario,
                    bool csolo_lectura, bool coculto,
                    bool csistema, bool carchivo,
                    bool cascii_binario, bool cacceso_aleatorio,
                    bool ctemporal,    bool cbloqueo,
                    int clongitud_registro, int cposicion_llave,
                    int clongitud_llave, int chora_creacion,
                    int chora_ultima_modificacion, int clongitud,
                    int clongitud_maxima);
};

#endif  // ATRIBUTOARCHIVO_H