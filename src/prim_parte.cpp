#include <iostream>
#include <fstream>
#include <string>
#include "../src/Usuarios/Usuario.h"
#include "../src/Usuarios/usuario.cpp"
#include "../src/Productos/Clientes/Cliente.h"
#include "../src/Productos/Clientes/Cliente.cpp"
#include "../src/Productos/Repuestos/Repuesto.h"
#include "../src/Productos/Repuestos/Repuesto.cpp"
#include "../src/Productos/Vehiculos/Vehiculo.h"
#include "../src/Productos/Vehiculos/Vehiculo.cpp"
#include "../src/Menus/menu.cpp"

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
        cout << "¿Desea confirmar la eliminación del usuario? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            // Eliminar el archivo original y renombrar el archivo temporal
            remove("bin/datos/usuarios.csv");
            rename("bin/datos/usuarios_temp.csv", "bin/datos/usuarios.csv");
            cout << "Usuario eliminado exitosamente.\n";
            cantidad--;  // Decrementar la cantidad de usuarios
        } else {
            remove("bin/datos/usuarios_temp.csv");
            cout << "Operación cancelada. No se eliminó el usuario.\n";
        }
    } else {
        remove("bin/datos/usuarios_temp.csv");
        cout << "No se encontró el usuario con el nombre proporcionado.\n";
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
    cout << "¿Desea confirmar la creación del nuevo usuario? (1 para confirmar, 0 para cancelar): ";
    cin >> confirmar;

    if (confirmar == 1) {
        // Eliminar el archivo original y renombrar el archivo temporal
        remove("bin/datos/usuarios.csv");
        rename("bin/datos/usuarios_temp.csv", "bin/datos/usuarios.csv");
        cout << "Nuevo usuario creado exitosamente.\n";
        cantidad++;  // Incrementar la cantidad de usuarios
    } else {
        remove("bin/datos/usuarios_temp.csv");
        cout << "Operación cancelada. No se creó el usuario.\n";
    }
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
            cout << "Ingrese el nuevo nombre de usuario: ";
            cin >> nuevoUsuario;
            cout << "Ingrese la nueva contraseña: ";
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
        cout << "¿Desea confirmar los cambios realizados? (1 para confirmar, 0 para cancelar): ";
        cin >> confirmar;

        if (confirmar == 1) {
            // Eliminar el archivo original y renombrar el archivo temporal
            remove("bin/datos/usuarios.csv");
            rename("bin/datos/usuarios_temp.csv", "bin/datos/usuarios.csv");
            cout << "Usuario modificado exitosamente.\n";
        } else {
            remove("bin/datos/usuarios_temp.csv");
            cout << "Operación cancelada. No se modificó el usuario.\n";
        }
    } else {
        remove("bin/datos/usuarios_temp.csv");
        cout << "No se encontró un usuario con el nombre proporcionado.\n";
    }
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

int main() {
    int cantidadUsuarios = 0, cantidadVehiculos = 0, cantidadRepuestos = 0, cantidadClientes = 0;
    int op1, op2;
    
// Cargar datos desde archivos
Usuario** usuarios = Usuario::cargarUsuarios(cantidadUsuarios);
Cliente* clientes = Cliente::cargarClientes(cantidadClientes);
Vehiculo* vehiculo = Vehiculo::cargarVehiculos(cantidadVehiculos);
Repuesto* repuestos = Repuesto::cargarRepuestos(cantidadRepuestos);

Usuario* usuarioAutenticado = nullptr;
    do {
        usuarioAutenticado = autenticarUsuario(usuarios, cantidadUsuarios);
    } while (usuarioAutenticado == nullptr);

    string rol = usuarioAutenticado->getRol();
    cout << "Rol del usuario autenticado: " << rol << endl;
    cout <<endl;

    if(rol=="admin"){
        do{
        menuAdmin();
        cin>>op1;
        switch(op1){
            case 1:
            do{
            string usuarioEditar;
            menuGestUsers();
            cin>>op2;
            switch(op2){
                case 1:
                break;

                case 2:
                cout<<"Ingrese el usuario que desea editar: ";
                cin>>usuarioEditar;
                modificarUsuario(usuarios, cantidadUsuarios, usuarioEditar);
                break;

                case 3:
                cout<<"Ingrese el usuario que desea eliminar: ";
                cin>>usuarioEditar;
                eliminarUsuario(usuarios, cantidadUsuarios, usuarioEditar);
                break;

                case 0:
                break;

                default:
                cout<<"Opcion invalida"<<endl;
            }
            }while(op2 != 0);
            //gestion users
            break;

            case 2:
            do{
            string placa;
            cout<<endl;
            menuVehiculos();
            cin>>op2;
            switch(op2){
                case 1:
                //Agregar
                break;

                case 2:
                cout<<"Ingrese la placa del vehiculo que desea consultar: ";
                cin>>placa;
                Vehiculo::consultarVehiculo(vehiculo, cantidadVehiculos, placa);
                break;

                case 3:
                cout<<"Ingrese la placa del vehiculo que desea borrar: ";
                cin>>placa;
                Vehiculo::borrarVehiculo(vehiculo, cantidadVehiculos, placa);
                break;

                case 4:
                cout<<"Ingrese la placa del vehiculo que desea modificar: ";
                cin>>placa;
                Vehiculo::modificarVehiculo(vehiculo, cantidadVehiculos, placa);
                break;

                case 5:
                Vehiculo::leerListaVehiculos(vehiculo, cantidadVehiculos);
                break;

                case 0:
                cout<<"Volviendo al menu principal";
                break;

                default:
                cout<<"Opcion invalida"<<endl;
            }
            }while(op2!=0);
            break;

            case 3:
            cout<<endl;
            do{
            int anioCarro;
            string nombre;
            string modeloCarro;
            menuRepuestos();
            cin>>op2;
            switch(op2){
                case 1:
                //agregar
                break;

                case 2:
                cout<<"Ingrese el nombre del repuesto a consultar: ";
                cin>>nombre;
                cout<<"Ingrese el modelo del carro del repuesto: ";
                cin>>modeloCarro;
                cout<<"Ingrese el year del carro del repuesto: ";
                cin>>anioCarro;
                Repuesto::consultarRepuesto(repuestos, cantidadRepuestos, nombre, modeloCarro, anioCarro);
                break;

                case 3:
                cout<<"Ingrese el nombre del repuesto a borrar: ";
                cin>>nombre;
                cout<<"Ingrese el modelo del carro del repuesto: ";
                cin>>modeloCarro;
                cout<<"Ingrese el year del carro del repuesto: ";
                cin>>anioCarro;
                Repuesto::borrarRepuesto(repuestos, cantidadRepuestos, nombre, modeloCarro, anioCarro);
                break;

                case 4:
                cout<<"Ingrese el nombre del repuesto a modificar: ";
                cin>>nombre;
                cout<<"Ingrese el modelo del carro del repuesto: ";
                cin>>modeloCarro;
                cout<<"Ingrese el year del carro del repuesto: ";
                cin>>anioCarro;
                Repuesto::modificarRepuesto(repuestos, cantidadRepuestos, nombre, modeloCarro, anioCarro);
                break;

                case 5:
                Repuesto::leerListaRepuestos(repuestos, cantidadRepuestos);
                break;

                default:
                cout<<"Opcion invalida"<<endl;
            }
            }while(op2!=0);
            break;

            case 4:
            //clientes
            int cedula;
            cout<<endl;
            do{
            menuClientes();
            cin>>op2;
            cout<<endl;
            switch(op2){
                case 1:{
                break;
                }
                case 2:
                cout<<"Ingrese la cedula del cliente que desea consultar: ";
                cin>>cedula;
                cout<<endl;
                Cliente::consultarCliente(clientes, cantidadClientes, cedula);
                cout<<endl;
                break;

                case 3:
                cout<<"Ingrese la cedula del cliente que quiere borrar: ";
                cin>>cedula;
                Cliente::borrarCliente(clientes, cantidadClientes, cedula);
                break;

                case 4:
                cout<<"Ingrese la cedula del cliente a buscar: ";
                cin>>cedula;
                Cliente::modificarCliente(clientes, cantidadClientes, cedula);
                break;

                case 5:
                Cliente::leerListaClientes(clientes, cantidadClientes);
                cout<<endl;
                break;

                case 0:
                cout<<"Volviendo al menu principal"<<endl;
                cout<<endl;
                break; 

                default:
                cout<<"Opcion invalida"<<endl;
            }
            }while(op2!=0);
            break;

            case 0:
            cout<<"Saliendo del programa";
            break;

            default:
            cout<<"Opcion invalida:"<<endl;
        }
        }while(op1!=0);

    }else if(rol=="manager"){
        menuManager();


    }else if(rol=="empleado"){
        menuEmpleado();

    }else{
        cout<<"Error.";
    }

    return 0;
}
