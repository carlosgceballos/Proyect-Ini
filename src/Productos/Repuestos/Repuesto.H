#ifndef REPUESTO_H
#define REPUESTO_H

#include <string>
using namespace std;

class Repuesto {
private:
    string nombre;
    string modelo;
    string marca;
    string modelo_carro;
    int anio_carro;
    int existencias;
    float precio;

public:
    Repuesto(); // Constructor por defecto

    // Funciones de archivo
    static Repuesto* cargarRepuestos(int& cantidad);
    static void guardarRepuestos(Repuesto* repuestos, int cantidad);

    // Funciones CRUD
    static void agregarRepuesto(Repuesto*& repuestos, int& cantidad, const Repuesto& nuevoRepuesto);
    static void consultarRepuesto(Repuesto* repuestos, int cantidad, const string& nombre, const string& modeloCarro, int anioCarro);
    static void borrarRepuesto(Repuesto*& repuestos, int& cantidad, const string& nombre, const string& modeloCarro, int anioCarro);
    static void modificarRepuesto(Repuesto* repuestos, int cantidad, const string& nombre, const string& modeloCarro, int anioCarro);
    static void leerListaRepuestos(Repuesto* repuestos, int cantidad);
};

#endif