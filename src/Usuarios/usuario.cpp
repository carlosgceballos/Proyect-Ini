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

Usuario* autenticarUsuario(Usuario** usuarios, int cantidad) {
    string usuario, password;
    cout << "Ingrese el nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese la password: ";
    cin >> password;

    for (int i = 0; i < cantidad; i++) {
        if (usuarios[i]->verificarCredenciales(usuario, password)) {
            cout << "Autenticacion exitosa.\n";
            return usuarios[i];  // Devuelve el puntero al usuario autenticado
        }
    }

    cout << "Credenciales incorrectas.\n";
    return nullptr;
}

void modificarUsuario(Usuario**& usuarios, int& cantidad, const string& usuarioEditar) {
    bool encontrado = false;
    // Crear archivo temporal para almacenar los usuarios modificados
    ofstream archivoTemp("bin/datos/usuarios_temp.csv");
    if (!archivoTemp.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (usuarios[i]->getUsuario() == usuarioEditar) {
            encontrado = true;
            cout << "Modificando usuario...\n";

            // Pedir los nuevos datos
            string nuevoUsuario, nuevaPassword, nuevoRol;
            cout << "Ingrese el nombre de usuario: ";
            cin >> nuevoUsuario;
            cout << "Ingrese la contraseña: ";
            cin >> nuevaPassword;
            cout << "Ingrese el nuevo rol (admin, manager, empleado): ";
            cin >> nuevoRol;

            // Actualizar el usuario con los nuevos datos
            usuarios[i] = new Usuario(nuevoUsuario, nuevaPassword, nuevoRol);
        }

        // Escribir al archivo temporal (los usuarios, ya sean modificados o no)
        archivoTemp << usuarios[i]->getUsuario() << ","
                    << usuarios[i]->getPasswd() << ","
                    << usuarios[i]->getRol() << "\n";
    }

    archivoTemp.close();

    if (encontrado) {
        // Confirmación de la modificación
        int confirmar;
        cout << "Desea confirmar los cambios realizados? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            // Eliminar el archivo original y renombrar el archivo temporal
            remove("bin/datos/usuarios.csv");
            rename("bin/datos/usuarios_temp.csv", "bin/datos/usuarios.csv");
            cout << "Usuario modificado exitosamente.\n";
        } else {
            remove("bin/datos/usuarios_temp.csv");
            cout << "Operacion cancelada. No se modifico el usuario.\n";
        }
    } else {
        remove("bin/datos/usuarios_temp.csv");
        cout << "No se encontro un usuario con el nombre proporcionado.\n";
    }
}

void agregarUsuario(Usuario**& usuarios, int& cantidad, const string& usuario, const string& password, const string& rol) {
    // Crear un nuevo usuario
    Usuario* nuevoUsuario = new Usuario(usuario, password, rol);

    // Crear un archivo temporal para agregar el nuevo usuario
    ofstream archivoTemp("bin/datos/usuarios_temp.csv", ios::app);
    if (!archivoTemp.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }

    // Escribir los usuarios existentes al archivo temporal
    for (int i = 0; i < cantidad; i++) {
        archivoTemp << usuarios[i]->getUsuario() << ","
                    << usuarios[i]->getPasswd() << ","
                    << usuarios[i]->getRol() << "\n";
    }

    // Agregar el nuevo usuario
    archivoTemp << nuevoUsuario->getUsuario() << ","
                << nuevoUsuario->getPasswd() << ","
                << nuevoUsuario->getRol() << "\n";

    archivoTemp.close();

    // Confirmación de la creación del nuevo usuario
    int confirmar;
    cout << "Desea confirmar la creacion del nuevo usuario? (1 para confirmar, 0 para cancelar): ";
    cin >> confirmar;

    if (confirmar == 1) {
        // Eliminar el archivo original y renombrar el archivo temporal
        remove("bin/datos/usuarios.csv");
        rename("bin/datos/usuarios_temp.csv", "bin/datos/usuarios.csv");
        cout << "Nuevo usuario creado exitosamente.\n";
        cantidad++;  // Incrementar la cantidad de usuarios
    } else {
        remove("bin/datos/usuarios_temp.csv");
        cout << "Operacion cancelada. No se creo el usuario.\n";
    }
}

void eliminarUsuario(Usuario**& usuarios, int& cantidad, const string& usuarioEliminar) {
    bool encontrado = false;
    // Crear un archivo temporal para almacenar los usuarios restantes
    ofstream archivoTemp("bin/datos/usuarios_temp.csv");
    if (!archivoTemp.is_open()) {
        cout << "Error al crear el archivo temporal.\n";
        return;
    }

    // Escribir todos los usuarios excepto el que se desea eliminar
    for (int i = 0; i < cantidad; i++) {
        if (usuarios[i]->getUsuario() == usuarioEliminar) {
            encontrado = true;  // No escribimos al usuario que queremos eliminar
        } else {
            archivoTemp << usuarios[i]->getUsuario() << ","
                        << usuarios[i]->getPasswd() << ","
                        << usuarios[i]->getRol() << "\n";
        }
    }

    archivoTemp.close();

    if (encontrado) {
        // Confirmación de eliminación
        int confirmar;
        cout << "Desea confirmar la eliminacion del usuario? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            // Eliminar el archivo original y renombrar el archivo temporal
            remove("bin/datos/usuarios.csv");
            rename("bin/datos/usuarios_temp.csv", "bin/datos/usuarios.csv");
            cout << "Usuario eliminado exitosamente.\n";
            cantidad--;  // Decrementar la cantidad de usuarios
        } else {
            remove("bin/datos/usuarios_temp.csv");
            cout << "Operacion cancelada. No se eliminó el usuario.\n";
        }
    } else {
        remove("bin/datos/usuarios_temp.csv");
        cout << "No se encontro el usuario con el nombre proporcionado.\n";
    }
}