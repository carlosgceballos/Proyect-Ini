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
Repuesto() : nombre(""), modelo(""), marca(""), modelo_carro(""), anio_carro(0), existencias(0), precio(0.0) {}

    // Getters
    string getNombre() const { return nombre; }
    string getModelo() const { return modelo; }
    string getMarca() const { return marca; }
    string getModeloCarro() const { return modelo_carro; }
    int getAnioCarro() const { return anio_carro; }
    int getExistencias() const { return existencias; }
    float getPrecio() const { return precio; }

    // Setters
    void setNombre(const string& n) { nombre = n; }
    void setModelo(const string& m) { modelo = m; }
    void setMarca(const string& ma) { marca = ma; }
    void setModeloCarro(const string& mc) { modelo_carro = mc; }
    void setAnioCarro(int ac) { anio_carro = ac; }
    void setExistencias(int e) { existencias = e; }
    void setPrecio(float p) { precio = p; }

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