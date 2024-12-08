#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Usuario::Usuario(string usuario, string password, string rol) {
    this->usuario = usuario;
    this->password = password;
    this->rol = rol;
}

string Usuario::getUsuario() {
    return usuario;
}

string Usuario::getPasswd() {
    return password;
}

string Usuario::getRol() {
    return rol;
}

// Verificar el rol
bool Usuario::verificarCredenciales(string usuario, string password) {
    return this->usuario == usuario && this->password == password;
}
// Función para guardar los usuarios en un archivo CSV
void guardarUsuarios(Usuario** usuarios, int cantidad) {
    ofstream archivo("bin/datos/usuarios.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << usuarios[i]->getUsuario() << ","
                << usuarios[i]->getPasswd() << ","
                << usuarios[i]->getRol() << "\n";
    }

    archivo.close();
}

// Función para cargar los usuarios 
Usuario** Usuario::cargarUsuarios(int& cantidad) {
    ifstream archivo("bin/datos/usuarios.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return nullptr;
    }

    cantidad = 0;
    Usuario** usuarios = new Usuario*[0];
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string usuario, password, rol;

        getline(ss, usuario, ',');
        getline(ss, password, ',');
        getline(ss, rol, ',');

        Usuario* nuevoUsuario = new Usuario(usuario, password, rol);
        Usuario** temp = new Usuario*[cantidad + 1];

        for (int i = 0; i < cantidad; i++) {
            temp[i] = usuarios[i];
        }

        temp[cantidad] = nuevoUsuario;

        delete[] usuarios;
        usuarios = temp;
        cantidad++;
    }

    archivo.close();
    return usuarios;
}
