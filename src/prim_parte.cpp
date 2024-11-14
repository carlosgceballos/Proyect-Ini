#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Vehiculo{
  string modelo, marca, placa, color, motor, ced_cliente, fecha_entrega;
  int year, kilometraje;
  bool rentado;
  float precio_renta;
};

struct Cliente {
    string cedula, nombre, apellido, email, direccion;
    int cantidad_vehiculos_rentados;
    bool activo;
};

struct Repuesto {
    string modelo, marca, nombre, modelo_carro;
    int anio_carro, existencias;
    float precio;
};


//funcion para leer clientes
void leerClientes() {
    ifstream archivo("bin/datos/clientes.csv");
    string cliente;
    cout << "Datos de Clientes:";
    cout<< endl;
    while (getline(archivo, cliente)) {
        cout << cliente << endl;
    }
    archivo.close();
}

//funcion para agregar clientes
void agregarCliente() {
    Cliente cl;
    cout << "Ingrese los datos del cliente:\n";
    cout << "Cedula: "; 
    cin >> cl.cedula;
    cout << "Nombre: "; 
    cin >> cl.nombre;
    cout << "Apellido: "; 
    cin >> cl.apellido;
    cout << "Email: "; 
    cin >> cl.email;
    cout << "Cantidad de vehiculos rentados: "; 
    cin >> cl.cantidad_vehiculos_rentados;
    cout << "Direccion: "; 
    cin.ignore(); 
    getline(cin, cl.direccion);
    cout << "Activo (1 para si, 0 para no): "; 
    cin >> cl.activo;

    ofstream archivo("bin/datos/clientes.csv", ios::app);
    archivo << cl.cedula << "," << cl.nombre << "," << cl.apellido << "," << cl.email << "," << cl.cantidad_vehiculos_rentados 
    << "," << cl.direccion << "," << cl.activo << endl;
    archivo.close();
    cout << "Cliente agregado.";
    cout << endl;
}


int main(){
    
    return 0;
}