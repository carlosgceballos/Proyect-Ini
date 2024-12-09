#include "Vehiculo.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Función para cargar vehículos desde el archivo
Vehiculo* Vehiculo::cargarVehiculos(int& cantidad) {
    ifstream archivo("bin/datos/vehiculos.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de vehículos.\n";
        return nullptr;
    }

    cantidad = 0;
    Vehiculo* vehiculos = new Vehiculo[100]; // Tamaño inicial
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, vehiculos[cantidad].placa, ',');
        getline(ss, vehiculos[cantidad].modelo, ',');
        getline(ss, vehiculos[cantidad].marca, ',');
        getline(ss, vehiculos[cantidad].color, ',');
        getline(ss, vehiculos[cantidad].motor, ',');
        ss >> vehiculos[cantidad].year;
        ss.ignore();
        ss >> vehiculos[cantidad].kilometraje;
        ss.ignore();
        ss >> vehiculos[cantidad].precio_renta;
        ss.ignore();
        ss >> vehiculos[cantidad].rentado;
        ss.ignore();
        ss >> vehiculos[cantidad].ced_cliente;
        ss.ignore();
        getline(ss, vehiculos[cantidad].fecha_entrega);

        cantidad++;
    }

    archivo.close();
    return vehiculos;
}

// Función para guardar vehículos en el archivo
void Vehiculo::guardarVehiculos(Vehiculo* vehiculos, int cantidad) {
    ofstream archivo("bin/datos/vehiculos.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de vehículos.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << vehiculos[i].placa << "," << vehiculos[i].modelo << "," << vehiculos[i].marca << ","
                << vehiculos[i].color << "," << vehiculos[i].year << "," << vehiculos[i].kilometraje << ","
                << vehiculos[i].rentado << "," << vehiculos[i].motor << "," << vehiculos[i].precio_renta
                << "," << vehiculos[i].ced_cliente << "," << vehiculos[i].fecha_entrega << "\n";
    }

    archivo.close();
}

// Función para agregar un vehículo
void Vehiculo::agregarVehiculo(Vehiculo*& vehiculos, int& cantidad, const Vehiculo& nuevoVehiculo) {
    Vehiculo* temp = new Vehiculo[cantidad + 1];
    for (int i = 0; i < cantidad; i++) {
        temp[i] = vehiculos[i];
    }

    temp[cantidad] = nuevoVehiculo;
    delete[] vehiculos;
    vehiculos = temp;
    cantidad++;
}

// Función para consultar un vehículo por placa
void Vehiculo::consultarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
    bool encontrado = false;

    for (int i = 0; i < cantidad; i++) {
        if (vehiculos[i].placa == placa) {
            cout << "Vehículo encontrado:\n"
                 << "Placa: " << vehiculos[i].placa << "\nModelo: " << vehiculos[i].modelo
                 << "\nMarca: " << vehiculos[i].marca << "\nColor: " << vehiculos[i].color << "\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un vehículo con la placa proporcionada.\n";
    }
}

// Función para borrar un vehículo por placa
void Vehiculo::borrarVehiculo(Vehiculo*& vehiculos, int& cantidad, const string& placa) {
    bool encontrado = false;
    Vehiculo* temp = new Vehiculo[cantidad - 1];
    int j = 0;

    for (int i = 0; i < cantidad; i++) {
        if (vehiculos[i].placa == placa) {
            encontrado = true;
        } else {
            temp[j++] = vehiculos[i];
        }
    }

    // Crear archivo temporal para guardar los cambios
    ofstream tempArchivo("bin/datos/vehiculos_temp.csv");
    if (!tempArchivo.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }

    if (encontrado) {
        delete[] vehiculos;
        vehiculos = temp;
        cantidad--;
        // Escribir los datos modificados en el archivo temporal
        for (int i = 0; i < cantidad; i++) {
            tempArchivo << vehiculos[i].placa << "," << vehiculos[i].modelo << "," << vehiculos[i].marca << ","
                << vehiculos[i].color << "," << vehiculos[i].year << "," << vehiculos[i].kilometraje << ","
                << vehiculos[i].rentado << "," << vehiculos[i].motor << "," << vehiculos[i].precio_renta
                << "," << vehiculos[i].ced_cliente << "," << vehiculos[i].fecha_entrega << "\n";
        }

        tempArchivo.close();

        // Confirmación del usuario para aplicar los cambios
        int confirmar;
        cout << "¿Desea confirmar la eliminación del vehículo? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            remove("bin/datos/vehiculos.csv");
            rename("bin/datos/vehiculos_temp.csv", "bin/datos/vehiculos.csv");
            cout << "Vehículo borrado exitosamente.\n";
        } else {
            remove("bin/datos/vehiculos_temp.csv");
            cout << "Operación cancelada. El vehículo no fue borrado.\n";
        }
    } else {
        delete[] temp;
        cout << "No se encontró un vehículo con la placa proporcionada.\n";
    }
}

// Función para modificar un vehículo por placa
void Vehiculo::modificarVehiculo(Vehiculo* vehiculos, int cantidad, const string& placa) {
    bool encontrado = false;

    // Crear archivo temporal para guardar los cambios
    ofstream tempArchivo("bin/datos/vehiculos_temp.csv");
    if (!tempArchivo.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (vehiculos[i].placa == placa) {
            cout << "Modificando vehículo...\n";

            cout << "Ingrese el nuevo modelo: ";
            cin >> vehiculos[i].modelo;
            cout << "Ingrese la nueva marca: ";
            cin >> vehiculos[i].marca;
            cout << "Ingrese el nuevo color: ";
            cin >> vehiculos[i].color;
            cout << "Ingrese el nuevo motor: ";
            cin >> vehiculos[i].motor;
            cout << "Ingrese el nuevo año: ";
            cin >> vehiculos[i].year;
            cout << "Ingrese el nuevo kilometraje: ";
            cin >> vehiculos[i].kilometraje;
            cout << "Ingrese el precio de renta: ";
            cin >> vehiculos[i].precio_renta;
            cout << "¿Está rentado (1 para sí, 0 para no)?: ";
            cin >> vehiculos[i].rentado;

            if (vehiculos[i].rentado) {
                cout << "Ingrese la cédula del cliente: ";
                cin >> vehiculos[i].ced_cliente;
                cout << "Ingrese la fecha de entrega: ";
                cin.ignore();
                getline(cin, vehiculos[i].fecha_entrega);
            } else {
                vehiculos[i].ced_cliente = 0;
                vehiculos[i].fecha_entrega = "N/A";
            }

            encontrado = true;
        }

        // Escribir los datos en el archivo temporal
        tempArchivo << vehiculos[i].placa << "," << vehiculos[i].modelo << "," << vehiculos[i].marca << ","
                << vehiculos[i].color << "," << vehiculos[i].year << "," << vehiculos[i].kilometraje << ","
                << vehiculos[i].rentado << "," << vehiculos[i].motor << "," << vehiculos[i].precio_renta
                << "," << vehiculos[i].ced_cliente << "," << vehiculos[i].fecha_entrega << "\n";
    }

    tempArchivo.close();

    if (encontrado) {
        // Confirmación del usuario para aplicar los cambios
        int confirmar;
        cout << "¿Desea confirmar la modificación del vehículo? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            remove("bin/datos/vehiculos.csv");
            rename("bin/datos/vehiculos_temp.csv", "bin/datos/vehiculos.csv");
            cout << "Vehículo modificado exitosamente.\n";
        } else {
            remove("bin/datos/vehiculos_temp.csv");
            cout << "Operación cancelada. El vehículo no fue modificado.\n";
        }
    } else {
        cout << "No se encontró un vehículo con la placa proporcionada.\n";
    }
}

// Función para leer todos los vehículos
void Vehiculo::leerListaVehiculos(Vehiculo* vehiculos, int cantidad) {
    cout << "Lista de vehículos:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". Placa: " << vehiculos[i].placa << " Modelo: " << vehiculos[i].modelo << "\n";
    }
}
