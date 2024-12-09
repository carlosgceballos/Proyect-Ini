#include "Cliente.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Cliente* Cliente::cargarClientes(int& cantidad){
    ifstream archivo("bin/datos/clientes.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de clientes.\n";
        return NULL;
    }

    cantidad = 0;
    Cliente* clientes = new Cliente[100];
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        ss >> clientes[cantidad].cedula;
        ss.ignore();
        getline(ss, clientes[cantidad].nombre, ',');
        getline(ss, clientes[cantidad].apellido, ',');
        getline(ss, clientes[cantidad].email, ',');
        ss >> clientes[cantidad].cantidad_vehiculos_rentados;
        ss.ignore();
        getline(ss, clientes[cantidad].direccion, ',');
        ss >> clientes[cantidad].activo;

        cantidad++;
    }

    archivo.close();
    return clientes;
}


void Cliente::guardarClientes(Cliente* clientes, int cantidad) {
    ofstream archivo("bin/datos/clientes.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de clientes.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << clientes[i].cedula << "," << clientes[i].nombre << "," << clientes[i].apellido << ","
                << clientes[i].email << "," << clientes[i].cantidad_vehiculos_rentados << ","
                << clientes[i].direccion << "," << clientes[i].activo << "\n";
    }

    archivo.close();
}


void Cliente::agregarCliente(Cliente*& clientes, int& cantidad, const Cliente& nuevoCliente) {
    // Creamos un archivo temporal
    ofstream archivoTemp("bin/datos/clientes_temp.csv", ios::app);
    if (!archivoTemp.is_open()) {
        cout << "Error al abrir el archivo temporal.\n";
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        archivoTemp << clientes[i].cedula << "," << clientes[i].nombre << "," << clientes[i].apellido << ","
                << clientes[i].email << "," << clientes[i].cantidad_vehiculos_rentados << ","
                << clientes[i].direccion << "," << clientes[i].activo << "\n";
    }
    archivoTemp << nuevoCliente.cedula << "," << nuevoCliente.nombre << "," << nuevoCliente.apellido << ","
                << nuevoCliente.email << "," << nuevoCliente.cantidad_vehiculos_rentados << ","
                << nuevoCliente.direccion << "," << nuevoCliente.activo << "\n";

    archivoTemp.close();

    int confirmar;
    cout << "¿Desea confirmar los cambios? (1 para confirmar, 0 para cancelar): ";
    cin >> confirmar;

    if (confirmar == 1) {
        // Eliminar el archivo original y renombrar el archivo temporal
        remove("bin/datos/clientes.csv");
        rename("bin/datos/clientes_temp.csv", "bin/datos/clientes.csv");
        cout << "Cliente agregado exitosamente.\n";
        cantidad++; 
    } else {
        // Si no se confirma, eliminamos el archivo temporal
        remove("bin/datos/clientes_temp.csv");
        cout << "Operación cancelada. No se realizaron cambios.\n";
    }
}

// Función para consultar un cliente por cédula
void Cliente::consultarCliente(Cliente* clientes, int cantidad, int cedula) {
    bool encontrado = false;

    for (int i = 0; i < cantidad; i++) {
        if (clientes[i].cedula == cedula) {
            cout << "Cliente encontrado:\n"
                 << "Nombre: " << clientes[i].nombre << "\nApellido: " << clientes[i].apellido << "\nCedula: "<<clientes[i].cedula<<"\nEmail: "<<clientes[i].email<<
                 "\nDireccion: "<<clientes[i].direccion<<"\nActivo (1 si, 0 no): "<<clientes[i].activo<<"\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un cliente con la cedula proporcionada.\n";
    }
}

// Función para borrar un cliente por cédula
void Cliente::borrarCliente(Cliente*& clientes, int& cantidad, int cedula) {
    // Creamos un archivo temporal
    ofstream archivoTemp("bin/datos/clientes_temp.csv");
    if (!archivoTemp.is_open()) {
        cout << "Error al abrir el archivo temporal.\n";
        return;
    }


bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        if (clientes[i].cedula == cedula) {
            encontrado = true;
            continue; // No copiamos este cliente al archivo temporal
        }
        archivoTemp << clientes[i].cedula << "," << clientes[i].nombre << "," << clientes[i].apellido << ","
                << clientes[i].email << "," << clientes[i].cantidad_vehiculos_rentados << ","
                << clientes[i].direccion << "," << clientes[i].activo << "\n";
    }

    archivoTemp.close();

    if (encontrado) {
        // Confirmar cambios
        int confirmar;
        cout << "¿Desea confirmar los cambios? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            // Eliminar el archivo original y renombrar el archivo temporal
            remove("bin/datos/clientes.csv");
            rename("bin/datos/clientes_temp.csv", "bin/datos/clientes.csv");
            cantidad--; // Decrementamos la cantidad de clientes
            cout << "Cliente borrado exitosamente.\n";
        } else {
            // Si no se confirma, eliminamos el archivo temporal
            remove("bin/datos/clientes_temp.csv");
            cout << "Operación cancelada. No se realizaron cambios.\n";
        }
    } else {
        // Si no se encuentra, eliminamos el archivo temporal
        remove("bin/datos/clientes_temp.csv");
        cout << "No se encontró un cliente con la cédula proporcionada.\n";
    }
}

// Función para modificar un cliente por cédula
void Cliente::modificarCliente(Cliente* clientes, int cantidad, int cedula) {
    bool encontrado = false;

    // Creamos un archivo temporal
    ofstream archivoTemp("bin/datos/clientes_temp.csv");
    if (!archivoTemp.is_open()) {
        cout << "Error al abrir el archivo temporal.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (clientes[i].cedula == cedula) {
            cout << "Modificando cliente...\n";

            cout << "Ingrese el nombre: ";
            cin >> clientes[i].nombre;
            cout << "Ingrese el apellido: ";
            cin >> clientes[i].apellido;
            cout << "Ingrese el email: ";
            cin >> clientes[i].email;
            cout << "Ingrese la direccion: ";
            cin.ignore();
            getline(cin, clientes[i].direccion);
            cout << "Ingrese la cantidad de vehiculos rentados: ";
            cin >> clientes[i].cantidad_vehiculos_rentados;
            cout << "Activo (1 para si, 0 para no): ";
            cin >> clientes[i].activo;

            encontrado = true;
        }

        archivoTemp << clientes[i].cedula << "," << clientes[i].nombre << "," << clientes[i].apellido << ","
                << clientes[i].email << "," << clientes[i].cantidad_vehiculos_rentados << ","
                << clientes[i].direccion << "," << clientes[i].activo << "\n";
    }

    archivoTemp.close();

    if (encontrado) {
        // Confirmar cambios
        int confirmar;
        cout << "¿Desea confirmar los cambios? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            // Eliminar el archivo original y renombrar el archivo temporal
            remove("bin/datos/clientes.csv");
            rename("bin/datos/clientes_temp.csv", "bin/datos/clientes.csv");
            cout << "Cliente modificado exitosamente.\n";
        } else {
            // Si no se confirma, eliminamos el archivo temporal
            remove("bin/datos/clientes_temp.csv");
            cout << "Operacion cancelada. No se realizaron cambios.\n";
        }
    } else {
        // Si no se encuentra, eliminamos el archivo temporal
        remove("bin/datos/clientes_temp.csv");
        cout << "No se encontro un cliente con la cedula proporcionada.\n";
    }
}


// Función para leer todos los clientes
void Cliente::leerListaClientes(Cliente* clientes, int cantidad) {
    cout << "Lista de clientes:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". Cedula: " << clientes[i].cedula << ", Nombre: " << clientes[i].nombre <<", Apellido: "<<clientes[i].apellido 
        <<", Cantidad de autos Rentados: "<<clientes[i].cantidad_vehiculos_rentados<<", Direccion: "<<clientes[i].direccion<<", Activo: "<<clientes[i].activo<<endl;
    }
}
