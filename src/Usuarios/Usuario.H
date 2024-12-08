#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
private:
    string usuario;
    string password;
    string rol; // "admin", "manager", "empleado"

public:
    Usuario();
    // Constructor
    Usuario(string usuario, string password, string rol);

    // Métodos getter
    string getUsuario();
    string getPasswd();
    string getRol();
    
    static Usuario** cargarUsuarios(int& cantidad);
    // Método para verificar las credenciales
    bool verificarCredenciales(string usuario, string password);
};

#endif