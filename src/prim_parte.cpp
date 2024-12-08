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

using namespace std;


int main() {
    int cantidadUsuarios = 0, cantidadVehiculos = 0, cantidadRepuestos = 0, cantidadClientes = 0;
    int op1, op2;
    Vehiculo nuevoVehiculo;
    
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
            string usuarioNuevo, contrasenaNuevo, rolNuevo;
            menuGestUsers();
            cin>>op2;
            switch(op2){
                case 1:
                cout << "Ingrese nombre de usuario: ";
                cin >> usuarioNuevo;
                cout << "Ingrese contraseña: ";
                cin >> contrasenaNuevo;
                cout << "Ingrese rol (admin, manager, empleado): ";
                cin >> rolNuevo;
                agregarUsuario(usuarios, cantidadUsuarios, usuarioNuevo, contrasenaNuevo, rolNuevo);
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
                cout<<"Volviendo al menu principal";
                break;

                default:
                cout<<"Opcion invalida"<<endl;
            }
            }while(op2 != 0);
            break;

            case 2:
            do{
            string placa;
            cout<<endl;
            menuVehiculos();
            cin>>op2;
            switch(op2){
                case 1:{
                }
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

case 0:
cout<<"Volviendo al menu";
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
        do{
            menuManager();
            cin>>op1;
            switch(op1){
                case 1:
                do{
                string placa;
                menuVehiculos();
                cin>>op2;
                cout<<endl;
                switch(op2){
                case 1:{
                }
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

                case 2: 
                do{
                int anioCarro;
                string nombre;
               string modeloCarro;
                menuRepuestos();
                cin>>op2;
                cout<<endl;
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

case 0:
cout<<"Volviendo al menu";
break;

                default:
                cout<<"Opcion invalida"<<endl;

                }
                }while(op2!=0);
                break;

                case 3:
                int cedula;
                cout<<endl;
                do{
                menuClientes();
                cin>>op2;
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
                cout<<"\nSaliendo.\n";
                break;

                default:
                cout<<"\nOpcion invalida.\n";
            }
        }while(op1!=0);
    }else if(rol == "empleado"){
        do{
            string placa;
            string nombre;
            string modeloCarro;
            int anioCarro;
            int cedula;
            menuEmpleado();
            cin>>op1;
            switch(op1){
                case 1:
                cout<<"Ingrese la placa del vehiculo que desea consultar: ";
                cin>>placa;
                Vehiculo::consultarVehiculo(vehiculo, cantidadVehiculos, placa);
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
                cout<<"Ingrese la cedula del cliente que desea consultar: ";
                cin>>cedula;
                cout<<endl;
                Cliente::consultarCliente(clientes, cantidadClientes, cedula);
                cout<<endl;
                break;


                case 4:
                break;

                case 0:
                cout<<"Saliendo.";

                default:
                cout<<"Opcion invalida";
                break;
            }
        }while(op1!=0);
    }else;


    return 0;
}
