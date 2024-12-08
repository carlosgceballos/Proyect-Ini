#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
using namespace std;

class Vehiculo {
private:
    string modelo;
    string marca;
    string placa;
    string color;
    string motor;
    string fecha_entrega;
    int year;
    int kilometraje;
    int ced_cliente;
    bool rentado;
    float precio_renta;

public:
    Vehiculo(); // Constructor por defecto

    // Funciones de archivo
    static Vehiculo* cargarVehiculos(int& cantidad);
    static void guardarVehiculos(Vehiculo* vehiculos, int cantidad);

    // Funciones CRUD
    static void agregarVehiculo(Vehiculo*& vehiculos, int& cantidad, const Vehiculo& nuevoVehiculo);
    static void consultarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa);
    static void borrarVehiculo(Vehiculo*& vehiculos, int& cantidad, const string& placa);
    static void modificarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa);
    static void leerListaVehiculos(Vehiculo* vehiculos, int cantidad);
};

#endif