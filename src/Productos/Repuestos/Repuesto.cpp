#include "Repuesto.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

Repuesto::Repuesto() {}

// Función para cargar repuestos desde el archivo
Repuesto* Repuesto::cargarRepuestos(int& cantidad) {
    ifstream archivo("bin/datos/repuestos.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de repuestos.\n";
        return NULL;
    }

    cantidad = 0;
    Repuesto* repuestos = new Repuesto[100]; // Tamaño inicial
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, repuestos[cantidad].nombre, ',');
        getline(ss, repuestos[cantidad].marca, ',');
        getline(ss, repuestos[cantidad].modelo, ',');
        getline(ss, repuestos[cantidad].modelo_carro, ',');
        ss >> repuestos[cantidad].anio_carro;
        ss.ignore();
        ss >> repuestos[cantidad].precio;
        ss.ignore();
        ss >> repuestos[cantidad].existencias;

        cantidad++;
    }

    archivo.close();
    return repuestos;
}

// Función para guardar repuestos en el archivo
void Repuesto::guardarRepuestos(Repuesto* repuestos, int cantidad) {
    ofstream archivo("bin/datos/repuestos.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de repuestos.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << repuestos[i].nombre << "," << repuestos[i].marca << "," << repuestos[i].modelo << ","
                << repuestos[i].modelo_carro << "," << repuestos[i].anio_carro << ","
                << repuestos[i].precio << "," << repuestos[i].existencias << "\n";
    }

    archivo.close();
}

// Función para agregar un repuesto
void Repuesto::agregarRepuesto(Repuesto*& repuestos, int& cantidad, const Repuesto& nuevoRepuesto) {
    Repuesto* temp = new Repuesto[cantidad + 1];
    for (int i = 0; i < cantidad; i++) {
        temp[i] = repuestos[i];
    }

    temp[cantidad] = nuevoRepuesto;

    // Crear archivo temporal para agregar el nuevo repuesto
    ofstream tempArchivo("bin/datos/repuestos_temp.csv");
    if (!tempArchivo.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        delete[] temp;
        return;
    }

    // Escribir el nuevo repuesto 
    for (int i = 0; i < cantidad; i++) {
        tempArchivo << repuestos[i].nombre << "," << repuestos[i].marca << "," << repuestos[i].modelo << ","
                << repuestos[i].modelo_carro << "," << repuestos[i].anio_carro << ","
                << repuestos[i].precio << "," << repuestos[i].existencias << "\n";
    }

    // Confirmación del usuario
    int confirmar;
    cout << "¿Desea confirmar el agregado de un nuevo repuesto? (1 para confirmar, 0 para cancelar): ";
    cin >> confirmar;

    if (confirmar == 1) {
        delete[] repuestos;
        repuestos = temp;
        cantidad++;

        // Guardar cambios permanentemente
        remove("bin/datos/repuestos.csv");
        rename("bin/datos/repuestos_temp.csv", "bin/datos/repuestos.csv");

        cout << "Repuesto agregado exitosamente.\n";
    } else {
        delete[] temp;
        remove("bin/datos/repuestos_temp.csv");
        cout << "Operación cancelada. No se agregó el repuesto.\n";
    }
}

// Función para consultar un repuesto por nombre
void Repuesto::consultarRepuesto(Repuesto* repuestos, int cantidad, const string& nombre, const string& modeloCarro, int anioCarro) {
    bool encontrado = false;

    // Crear archivo temporal para almacenar repuestos consultados
    ofstream tempArchivo("bin/datos/repuestos_temp.csv");
    if (!tempArchivo.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }
    // Consultar repuestos
    for (int i = 0; i < cantidad; i++) {
        if (repuestos[i].nombre == nombre) {
            tempArchivo << "Repuesto encontrado:\n";
            cout<<"Nombre: " << repuestos[i].nombre << ", Marca: " << repuestos[i].marca << "\n"<<", Modelo: "<<repuestos[i].modelo
        <<", Modelo de carro: "<<repuestos[i].modelo_carro<<", Year del carro: "<<repuestos[i].anio_carro<<endl;
            encontrado = true;
            break;
        }
    }

    tempArchivo.close();

    if (!encontrado) {
        cout << "No se encontró un repuesto con el nombre proporcionado.\n";
    }
}

// Función para borrar un repuesto por nombre
void Repuesto::borrarRepuesto(Repuesto*& repuestos, int& cantidad, const string& nombre, const string& modeloCarro, int anioCarro) {
    bool encontrado = false;
    Repuesto* temp = new Repuesto[cantidad - 1];
    int j = 0;

    for (int i = 0; i < cantidad; i++) {
        if (repuestos[i].nombre == nombre && repuestos[i].modelo_carro == modeloCarro && repuestos[i].anio_carro== anioCarro) {
            encontrado = true;
        } else {
            temp[j++] = repuestos[i];
        }
    }

    // Crear archivo temporal para borrar el repuesto
    ofstream tempArchivo("bin/datos/repuestos_temp.csv");
    if (!tempArchivo.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        delete[] temp;
        return;
    }

    // Escribir los repuestos restantes en el archivo temporal
    if (encontrado) {
        for (int i = 0; i < cantidad - 1; i++) {
            tempArchivo << repuestos[i].nombre << "," << repuestos[i].marca << "," << repuestos[i].modelo << ","
                << repuestos[i].modelo_carro << "," << repuestos[i].anio_carro << ","
                << repuestos[i].precio << "," << repuestos[i].existencias << "\n";
        }

        int confirmar;
        cout << "¿Desea confirmar la eliminación del repuesto? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            delete[] repuestos;
            repuestos = temp;
            cantidad--;
            remove("bin/datos/repuestos.csv");
            rename("bin/datos/repuestos_temp.csv", "bin/datos/repuestos.csv");
            cout << "Repuesto borrado exitosamente.\n";
        } else {
            delete[] temp;
            remove("bin/datos/repuestos_temp.csv");
            cout << "Operación cancelada. No se eliminó el repuesto.\n";
        }
    } else {
        delete[] temp;
        remove("bin/datos/repuestos_temp.csv");
        cout << "No se encontró un repuesto con el nombre proporcionado.\n";
    }
}

// Función para modificar un repuesto por nombre
void Repuesto::modificarRepuesto(Repuesto* repuestos, int cantidad, const string& nombre, const string& modeloCarro, int anioCarro) {
    bool encontrado = false;

    // Crear archivo temporal para guardar los repuestos modificados
    ofstream tempArchivo("bin/datos/repuestos_temp.csv");
    if (!tempArchivo.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        // Verificar si el repuesto coincide con el nombre, modelo de carro y año del carro
        if (repuestos[i].nombre == nombre && repuestos[i].modelo_carro == modeloCarro && repuestos[i].anio_carro==anioCarro) {
            cout << "Modificando repuesto...\n";

            // Pedir los nuevos datos
            cout << "Ingrese el nuevo nombre: ";
            cin >> repuestos[i].nombre;
            cout << "Ingrese la nueva marca: ";
            cin >> repuestos[i].marca;
            cout << "Ingrese el nuevo modelo: ";
            cin >> repuestos[i].modelo;
            cout << "Ingrese el nuevo modelo del carro: ";
            cin >> repuestos[i].modelo_carro;
            cout << "Ingrese el nuevo año del carro: ";
            cin >> repuestos[i].anio_carro;
            cout << "Ingrese el nuevo precio: ";
            cin >> repuestos[i].precio;
            cout << "Ingrese la cantidad en existencia: ";
            cin >> repuestos[i].existencias;
            encontrado = true;
        }

        // Escribir todos los repuestos al archivo temporal
        tempArchivo << repuestos[i].nombre << "," << repuestos[i].marca << "," << repuestos[i].modelo << ","
                    << repuestos[i].modelo_carro << "," << repuestos[i].anio_carro << ","
                    << repuestos[i].precio << "," << repuestos[i].existencias << "\n";
    }

    tempArchivo.close();

    // Confirmación del usuario para guardar los cambios
    if (encontrado) {
        int confirmar;
        cout << "¿Desea confirmar los cambios realizados? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            remove("bin/datos/repuestos.csv");
            rename("bin/datos/repuestos_temp.csv", "bin/datos/repuestos.csv");
            cout << "Repuesto modificado exitosamente.\n";
        } else {
            remove("bin/datos/repuestos_temp.csv");
            cout << "Operación cancelada. No se modificó el repuesto.\n";
        }
    } else {
        remove("bin/datos/repuestos_temp.csv");
        cout << "No se encontró un repuesto con los criterios proporcionados.\n";
    }
}

// Función para leer todos los repuestos
void Repuesto::leerListaRepuestos(Repuesto* repuestos, int cantidad) {
    cout << "Lista de repuestos:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". Nombre: " << repuestos[i].nombre << " Marca: " << repuestos[i].marca << "\n"<<" Modelo: "<<repuestos[i].modelo
        <<" Modelo de carro: "<<repuestos[i].modelo_carro<<" Year del carro: "<<repuestos[i].anio_carro<<endl;
    }
}