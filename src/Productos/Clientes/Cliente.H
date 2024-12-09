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
Cliente() : cedula(0), nombre(""), apellido(""), email(""), direccion(""),
            cantidad_vehiculos_rentados(0), activo(false) {}


    // Getters
    int getCedula() const { return cedula; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getEmail() const { return email; }
    string getDireccion() const { return direccion; }
    int getCantidadVehiculosRentados() const { return cantidad_vehiculos_rentados; }
    bool isActivo() const { return activo; }

    // Setters
    void setCedula(int c) { cedula = c; }
    void setNombre(const string& n) { nombre = n; }
    void setApellido(const string& a) { apellido = a; }
    void setEmail(const string& e) { email = e; }
    void setDireccion(const string& d) { direccion = d; }
    void setCantidadVehiculosRentados(int cantidad) { cantidad_vehiculos_rentados = cantidad; }
    void setActivo(bool estado) { activo = estado; }

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
