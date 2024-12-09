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
Vehiculo() : placa(""), modelo(""), marca(""), color(""), motor(""),
                 year(0), kilometraje(0), precio_renta(0.0), rentado(false),
                 fecha_entrega(""), ced_cliente(0) {}

    // Getters
    string getPlaca() const { return placa; }
    string getModelo() const { return modelo; }
    string getMarca() const { return marca; }
    string getColor() const { return color; }
    string getMotor() const { return motor; }
    int getYear() const { return year; }
    int getKilometraje() const { return kilometraje; }
    float getPrecioRenta() const { return precio_renta; }
    bool isRentado() const { return rentado; }
    string getFechaEntrega() const { return fecha_entrega; }
    int getCedCliente() const { return ced_cliente; }

    // Setters
    void setPlaca(const string& p) { placa = p; }
    void setModelo(const string& m) { modelo = m; }
    void setMarca(const string& ma) { marca = ma; }
    void setColor(const string& c) { color = c; }
    void setMotor(const string& mo) { motor = mo; }
    void setYear(int y) { year = y; }
    void setKilometraje(int k) { kilometraje = k; }
    void setPrecioRenta(float precio) { precio_renta = precio; }
    void setRentado(bool r) { rentado = r; }
    void setFechaEntrega(const string& fecha) { fecha_entrega = fecha; }
    void setCedCliente(int cedula) { ced_cliente = cedula; }

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
