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

    //var multiusos
    bool act;
    int cedula, ced_cli;
    float precio;
    string marca;

    //var para vehiculos
    string model, color, motor, fechaentrega;
    int year, kmj;

    //var para clientes
    string name, apellido, email, direccion;
    int cantidadVehiculosRent;

    //var para repuesto
    string nombre, modelo, modeloCarro;
    int inputInt;
    int anioCarro, existencias;

    Vehiculo nuevoVehiculo;
    Repuesto nuevoRepuesto;
    Cliente nuevoCliente;
    
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
                case 1:
                    cout<<"Ingrese el modelo del vehiculo: ";
                    cin.ignore();
                    getline(cin, model);
                    cout<<"Ingrese la marca del vehiculo: ";
                    cin>>marca;
                    cout<<"Ingrese el year del vehiculo: ";
                    cin>>year;
                    cout<<"Ingrese la placa: ";
                    cin>>placa;
                    cout<<"Ingrese el color: ";
                    cin>>color;
                    cout<<"Ingrese el tipo de motor: ";
                    cin>>motor;
                    cout<<"Ingrese el kilomeraje: ";
                    cin>>kmj;
                    cout<<"Ingrese el precio de renta: ";
                    cin>>precio;
                    cout<<"El vehiculo esta rentado (1-si, 0-no): ";
                    cin>>act;
                    if(act==1){
                        cout<<"Cedula del cliente que renta: ";
                        cin>>ced_cli;
                        cout<<"Fecha de entrega: ";
                        cin>>fechaentrega;
                    }else{
                        ced_cli = 0;
                        fechaentrega = "N/A";
                    }
                    nuevoVehiculo.setCedCliente(ced_cli);
                    nuevoVehiculo.setColor(color);
                    nuevoVehiculo.setFechaEntrega(fechaentrega);
                    nuevoVehiculo.setKilometraje(kmj);
                    nuevoVehiculo.setMarca(marca);
                    nuevoVehiculo.setModelo(model);
                    nuevoVehiculo.setMotor(motor);
                    nuevoVehiculo.setPlaca(placa);
                    nuevoVehiculo.setPrecioRenta(precio);
                    nuevoVehiculo.setRentado(act);
                    nuevoVehiculo.setYear(year);
                    Vehiculo::agregarVehiculo(vehiculo,cantidadVehiculos,nuevoVehiculo);
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
                cout << "Ingrese el nombre del repuesto: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese la marca del repuesto: ";
    getline(cin, marca);
    cout << "Ingrese el modelo del repuesto: ";
    getline(cin, modelo);
    cout << "Ingrese el modelo del carro para el que es el repuesto: ";
    getline(cin, modeloCarro);
    cout << "Ingrese el año del carro: ";
    cin >> anioCarro;
    cout << "Ingrese el precio del repuesto: ";
    cin >> precio;
    cout << "Ingrese las existencias: ";
    cin >> existencias;

    // Configurar el nuevo objeto Repuesto con los datos ingresados
    nuevoRepuesto.setNombre(nombre);
    nuevoRepuesto.setMarca(marca);
    nuevoRepuesto.setModelo(modelo);
    nuevoRepuesto.setModeloCarro(modeloCarro);
    nuevoRepuesto.setAnioCarro(anioCarro);
    nuevoRepuesto.setPrecio(precio);
    nuevoRepuesto.setExistencias(existencias);

    // Agregar el nuevo repuesto
    Repuesto::agregarRepuesto(repuestos, cantidadRepuestos, nuevoRepuesto);
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
            cout<<endl;
            do{
            menuClientes();
            cin>>op2;
            cout<<endl;
            switch(op2){
                case 1:{
                    cout<<"Ingrese la cedula del cliente: ";
                    cin>>cedula;
                    cout<<"Ingrese el nombre del cliente: ";
                    cin>>name;
                    cout<<"Ingrese el apellido del cliente: ";
                    cin>>apellido;
                    cout<<"Ingrese el email del cliente: ";
                    cin>>email;
                    cout<<"Ingrese la cantidad de vehiculos rentados por el cliente: ";
                    cin>>cantidadVehiculosRent;
                    cout<<"Ingrese la direccion del cliente: ";
                    cin.ignore();
                    getline(cin,direccion);
                    cout<<"Ingrese si el cliente esta activo (1, si - 0, no): ";
                    cin>>act;

                    nuevoCliente.setNombre(name);
                    nuevoCliente.setApellido(apellido);
                    nuevoCliente.setCedula(cedula);
                    nuevoCliente.setEmail(email);
                    nuevoCliente.setDireccion(direccion);
                    nuevoCliente.setCantidadVehiculosRentados(cantidadVehiculosRent);
                    nuevoCliente.setActivo(act);

                    Cliente::agregarCliente(clientes, cantidadClientes, nuevoCliente);
                    

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
                case 1:
                cout<<"Ingrese el modelo del vehiculo: ";
                    cin.ignore();
                    getline(cin, model);
                    cout<<"Ingrese la marca del vehiculo: ";
                    cin>>marca;
                    cout<<"Ingrese el year del vehiculo: ";
                    cin>>year;
                    cout<<"Ingrese la placa: ";
                    cin>>placa;
                    cout<<"Ingrese el color: ";
                    cin>>color;
                    cout<<"Ingrese el tipo de motor: ";
                    cin>>motor;
                    cout<<"Ingrese el kilomeraje: ";
                    cin>>kmj;
                    cout<<"Ingrese el precio de renta: ";
                    cin>>precio;
                    cout<<"El vehiculo esta rentado (1-si, 0-no): ";
                    cin>>act;
                    if(act==1){
                        cout<<"Cedula del cliente que renta: ";
                        cin>>ced_cli;
                        cout<<"Fecha de entrega: ";
                        cin>>fechaentrega;
                    }else{
                        ced_cli = 0;
                        fechaentrega = "N/A";
                    }
                    nuevoVehiculo.setCedCliente(ced_cli);
                    nuevoVehiculo.setColor(color);
                    nuevoVehiculo.setFechaEntrega(fechaentrega);
                    nuevoVehiculo.setKilometraje(kmj);
                    nuevoVehiculo.setMarca(marca);
                    nuevoVehiculo.setModelo(model);
                    nuevoVehiculo.setMotor(motor);
                    nuevoVehiculo.setPlaca(placa);
                    nuevoVehiculo.setPrecioRenta(precio);
                    nuevoVehiculo.setRentado(act);
                    nuevoVehiculo.setYear(year);
                    Vehiculo::agregarVehiculo(vehiculo,cantidadVehiculos,nuevoVehiculo);
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
                                    cout << "Ingrese el nombre del repuesto: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese la marca del repuesto: ";
    getline(cin, marca);
    cout << "Ingrese el modelo del repuesto: ";
    getline(cin, modelo);
    cout << "Ingrese el modelo del carro para el que es el repuesto: ";
    getline(cin, modeloCarro);
    cout << "Ingrese el año del carro: ";
    cin >> anioCarro;
    cout << "Ingrese el precio del repuesto: ";
    cin >> precio;
    cout << "Ingrese las existencias: ";
    cin >> existencias;

    // Configurar el nuevo objeto Repuesto con los datos ingresados
    nuevoRepuesto.setNombre(nombre);
    nuevoRepuesto.setMarca(marca);
    nuevoRepuesto.setModelo(modelo);
    nuevoRepuesto.setModeloCarro(modeloCarro);
    nuevoRepuesto.setAnioCarro(anioCarro);
    nuevoRepuesto.setPrecio(precio);
    nuevoRepuesto.setExistencias(existencias);

    // Agregar el nuevo repuesto
    Repuesto::agregarRepuesto(repuestos, cantidadRepuestos, nuevoRepuesto);
                
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
                case 1:
                     cout<<"Ingrese la cedula del cliente: ";
                    cin>>cedula;
                    cout<<"Ingrese el nombre del cliente: ";
                    cin>>name;
                    cout<<"Ingrese el apellido del cliente: ";
                    cin>>apellido;
                    cout<<"Ingrese el email del cliente: ";
                    cin>>email;
                    cout<<"Ingrese la cantidad de vehiculos rentados por el cliente: ";
                    cin>>cantidadVehiculosRent;
                    cout<<"Ingrese la direccion del cliente: ";
                    cin.ignore();
                    getline(cin,direccion);
                    cout<<"Ingrese si el cliente esta activo (1, si - 0, no): ";
                    cin>>act;

                    nuevoCliente.setNombre(name);
                    nuevoCliente.setApellido(apellido);
                    nuevoCliente.setCedula(cedula);
                    nuevoCliente.setEmail(email);
                    nuevoCliente.setDireccion(direccion);
                    nuevoCliente.setCantidadVehiculosRentados(cantidadVehiculosRent);
                    nuevoCliente.setActivo(act);

                    Cliente::agregarCliente(clientes, cantidadClientes, nuevoCliente);
                    
               
                break;
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
