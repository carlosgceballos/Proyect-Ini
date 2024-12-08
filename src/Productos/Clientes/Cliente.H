#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente {
private:
    string nombre;
    string apellido;
    string email;
    string direccion;
    int cantidad_vehiculos_rentados;
    int cedula;
    bool activo;

public:
    Cliente(); // Constructor por defecto

    // Funciones de archivo
    static Cliente* cargarClientes(int& cantidad);
    static void guardarClientes(Cliente* clientes, int cantidad);

    // Funciones CRUD
    static void agregarCliente(Cliente*& clientes, int& cantidad, const Cliente& nuevoCliente);
    static void consultarCliente(Cliente* clientes, int cantidad, int cedula);
    static void borrarCliente(Cliente*& clientes, int& cantidad, int cedula);
    static void modificarCliente(Cliente* clientes, int cantidad, int cedula);
    static void leerListaClientes(Cliente* clientes, int cantidad);
};

#endif
