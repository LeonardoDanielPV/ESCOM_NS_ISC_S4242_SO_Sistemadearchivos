#include <string>
#include <vector>
#include <map>

using namespace std;

#include <stdio.h>
#include <time.h>

#define FAT 11

struct Directorio {
  string direccion_absoluta;
  int numero_nodo;
};

struct AtributosArchivo {
  int creador;
  int solo_lectura;
  int oculto;
  int sistema;
  int archivo;
  int ASCIIbin;
  int temporal;
  int bloqueo;
  int hora_creacion;
  int tam_actual;
  int tam_maximo;
};

struct NodoI {
  AtributosArchivo atributos_archivo;
  vector<int> direcciones;
};

struct SuperBloque {
  int numero_magico;
  int numero_bloques;
};

struct Disco {
  SuperBloque super_bloque;
  vector<int> espacio_libre;
  vector<NodoI> nodos_i;
  vector<Directorio> directorio;
  vector<char> bytes;

  map<string, int> hash;
};

Disco CrearDisco(int numero_bloques, int bytes_por_bloque);
SuperBloque CrearSuperBloque(int numero_magico, int numero_bloques);
int BytesPorBloque(Disco& d);
int DivCeil(int a, int b);
AtributosArchivo CrearAtributos(int tam_actual, int tam_maximo);
bool CrearArchivo(Disco& d, string contenido, string direccion_absoluta);
int LlenarBloqueNuevo(Disco& d, string contenido);
void EstablecerHash(Disco& d, Directorio directorio);
string ObtenerContenidoArchivo(Disco& d, string direccion_absoluta);
void EliminarArchivo(Disco& d, string direccion_absoluta);
string ObtenerBytesArchivos(Disco& d);
void Imprimirbytes(string s);
void GuardarInstantanea(Disco& d);
string IntAString4Bytes(int a);
void ImprimirInt(FILE* archivo, int a);
void ImprimirAtributos(FILE* archivo, AtributosArchivo atributos_archivo);

int main(int argc, char* argv[]) {
  Disco d = CrearDisco(100, 2);
  string contenido_actual;
  string direccion_actual;


  contenido_actual = "12345678910111213";
  direccion_actual = "C:\\Raiz.txt";
  CrearArchivo(d, contenido_actual, direccion_actual);
  contenido_actual = ObtenerContenidoArchivo(d, direccion_actual);
  printf("%s\n", contenido_actual.c_str());

  contenido_actual = "235711";
  direccion_actual = "C::\\Primos.txt";
  CrearArchivo(d, contenido_actual, direccion_actual);
  contenido_actual = ObtenerContenidoArchivo(d, direccion_actual);
  printf("%s\n", contenido_actual.c_str());

  EliminarArchivo(d, "C:\\Raiz2.txt");

  contenido_actual = "101010101010101010101010101101";
  direccion_actual = "C:\\Raiz2.txt";
  CrearArchivo(d, contenido_actual, direccion_actual);
  contenido_actual = ObtenerContenidoArchivo(d, direccion_actual);
  printf("%s\n", contenido_actual.c_str());

  Imprimirbytes(ObtenerBytesArchivos(d));

  GuardarInstantanea(d);

  return 0;
}

Disco CrearDisco(int numero_bloques, int bytes_por_bloque) {
  SuperBloque sb = CrearSuperBloque(FAT, numero_bloques);
  vector<int> espacio_libre = vector<int>(numero_bloques, 0);
  vector<NodoI> nodos_i = vector<NodoI>();
  vector<Directorio> directorio = vector<Directorio>();
  vector<char> bytes = vector<char>(numero_bloques * bytes_por_bloque);

  map<string, int> hash = map<string, int>();

  Disco d = {sb, espacio_libre, nodos_i, directorio, bytes, hash};
  return d;
}

SuperBloque CrearSuperBloque(int numero_magico, int numero_bloques) {
  SuperBloque sb = {numero_magico, numero_bloques};
  return sb;
}

int BytesPorBloque(Disco& d) {
  int bpb = d.bytes.size() / d.super_bloque.numero_bloques;
  return bpb;
}

int DivCeil(int a, int b) {
  int div_ceil = a / b;
  if (a % b) {
    ++div_ceil;
  }
  
  return div_ceil;
}

AtributosArchivo CrearAtributos(int tam_actual, int tam_maximo) {
  AtributosArchivo actual;

  actual.creador = 23;
  actual.solo_lectura = 0;
  actual.oculto = 0;
  actual.sistema = 0;
  actual.archivo = 1;
  actual.ASCIIbin = 0;
  actual.temporal = 0;
  actual.bloqueo = 0;
  actual.hora_creacion = time(NULL);
  actual.tam_actual = tam_actual;
  actual.tam_maximo = tam_maximo;

  return actual;
}

bool CrearArchivo(Disco& d, string contenido, string direccion_absoluta) {
  int numero_bloques_a_ocupar = DivCeil(contenido.size(), BytesPorBloque(d));

  vector<int> direcciones;
  int indice_espacio_llenado;
  for (int i = 0; i < numero_bloques_a_ocupar; ++i) {
    indice_espacio_llenado = LlenarBloqueNuevo(
        d, contenido.substr(i * BytesPorBloque(d), BytesPorBloque(d)));
    if (indice_espacio_llenado == -1) {
      return false;
    } else {
      direcciones.push_back(indice_espacio_llenado);
    }
  }

  AtributosArchivo atributos_archivo = CrearAtributos(contenido.size(), 1024);

  NodoI actual = {atributos_archivo, direcciones};
  Directorio directorio = {direccion_absoluta, (int)(d.nodos_i.size())};

  d.nodos_i.push_back(actual);
  d.directorio.push_back(directorio);
  EstablecerHash(d, directorio);

  return true;
}

int LlenarBloqueNuevo(Disco& d, string contenido) {
  int indice_espacio_libre = 0;
  bool encontrado = false;
  while (indice_espacio_libre < d.espacio_libre.size() && !encontrado) {
    if (d.espacio_libre[indice_espacio_libre] == 0) {
      encontrado = true;
    } else {
      ++indice_espacio_libre;
    }
  }
  if (!encontrado) {
    return -1;
  }

  d.espacio_libre[indice_espacio_libre] = 1;
  int i = 0;
  for (char c : contenido) {
    d.bytes[indice_espacio_libre * BytesPorBloque(d) + i] = c;
    ++i;
  }

  return indice_espacio_libre;
}

void EstablecerHash(Disco& d, Directorio directorio) {
  d.hash[directorio.direccion_absoluta] = directorio.numero_nodo;
}

string ObtenerContenidoArchivo(Disco& d, string direccion_absoluta) {
  int indice_nodo_i = d.hash[direccion_absoluta];

  NodoI actual = d.nodos_i[indice_nodo_i];

  string contenido;

  for (int dir : actual.direcciones) {
    for (int i = 0; i < BytesPorBloque(d); ++i) {
      contenido.push_back(d.bytes[dir * BytesPorBloque(d) + i]);
    }
  }

  return contenido;
}

void EliminarArchivo(Disco& d, string direccion_absoluta) {
  int indice_nodo_i = d.hash[direccion_absoluta];

  NodoI actual = d.nodos_i[indice_nodo_i];

  for (int dir : actual.direcciones) {
    d.espacio_libre[dir] = 0;
  }

  d.nodos_i[indice_nodo_i].direcciones.clear();
}

string ObtenerBytesArchivos(Disco& d) {
  string b;

  for (int i = 0; i < d.bytes.size(); ++i) {
    b.push_back(d.bytes[i]);
  }

  return b;
}

void Imprimirbytes(string s) {
  for (char c : s) {
    printf("%02X ", c);
  }
  putchar('\n');
}

void GuardarInstantanea(Disco& d) {
  FILE* instantanea = fopen("instantanea.dat", "wb");

  // Super bloque
  ImprimirInt(instantanea, d.super_bloque.numero_magico);
  ImprimirInt(instantanea, d.super_bloque.numero_bloques);

  // Nodos-I
  int nodos_i_cantidad = 0;
  for (NodoI nodo_i : d.nodos_i) {
    if (nodo_i.direcciones.size()) {
      ++nodos_i_cantidad;
    }
  }
  ImprimirInt(instantanea, nodos_i_cantidad);
  for (NodoI nodo_i : d.nodos_i) {
    if (nodo_i.direcciones.size()) {
      ImprimirAtributos(instantanea, nodo_i.atributos_archivo);
      ImprimirInt(instantanea, nodo_i.direcciones.size());
      for (int dir : nodo_i.direcciones) {
        ImprimirInt(instantanea, dir);
      }
    }
  }

  // Directorios
  ImprimirInt(instantanea, d.directorio.size());
  for (Directorio d : d.directorio) {
    ImprimirInt(instantanea, d.direccion_absoluta.size());
    fprintf(instantanea, "%s", d.direccion_absoluta.c_str());
    ImprimirInt(instantanea, d.numero_nodo);
  }

  ImprimirInt(instantanea, d.bytes.size());
  for (char c : d.bytes) {
    fputc(c, instantanea);
  }

  fclose(instantanea);
}

string IntAString4Bytes(int a) {
  string actual;

  char b0 = a >> 3 * 8;
  char b1 = ((a << 1 * 8) >> 1 * 8) >> 2 * 8;
  char b2 = ((a << 2 * 8) >> 2 * 8) >> 1 * 8;
  char b3 = ((a << 3 * 8) >> 3 * 8);

  actual.push_back(b0);
  actual.push_back(b1);
  actual.push_back(b2);
  actual.push_back(b3);

  return actual;
}

void ImprimirInt(FILE* archivo, int a) {
  string b = IntAString4Bytes(a);

  fputc(b[0], archivo);
  fputc(b[1], archivo);
  fputc(b[2], archivo);
  fputc(b[3], archivo);
}

void ImprimirAtributos(FILE* archivo, AtributosArchivo atributos_archivo) {
  ImprimirInt(archivo, atributos_archivo.creador);

  int mascara_bits = 0;
  mascara_bits += atributos_archivo.solo_lectura;
  mascara_bits = mascara_bits << 1;
  mascara_bits += atributos_archivo.oculto;
  mascara_bits = mascara_bits << 1;
  mascara_bits += atributos_archivo.sistema;
  mascara_bits = mascara_bits << 1;
  mascara_bits += atributos_archivo.archivo;
  mascara_bits = mascara_bits << 1;
  mascara_bits += atributos_archivo.ASCIIbin;
  mascara_bits = mascara_bits << 1;
  mascara_bits += atributos_archivo.temporal;
  mascara_bits = mascara_bits << 1;
  mascara_bits += atributos_archivo.bloqueo;
  mascara_bits = mascara_bits << 1;

  fputc(mascara_bits, archivo);

  ImprimirInt(archivo, atributos_archivo.hora_creacion);
  ImprimirInt(archivo, atributos_archivo.tam_actual);
  ImprimirInt(archivo, atributos_archivo.tam_maximo);
}