#include <iostream>
using namespace std;


void menuClientes(){
    cout << "1. Agregar Cliente" << endl;
    cout << "2. Consultar Cliente" << endl;
    cout << "3. Borrar Cliente" << endl;
    cout << "4. Actualizar Cliente" << endl;
    cout << "5. Leer todos los Clientes" << endl;
    cout << "0. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

void menuVehiculos() {
    cout << "1. Agregar Vehiculo" << endl;
    cout << "2. Consultar Vehiculo" << endl;
    cout << "3. Borrar Vehiculo" << endl;
    cout << "4. Actualizar Vehiculo" << endl;
    cout << "5. Leer todos los Vehiculos" << endl;
    cout << "0. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

void menuRepuestos() {
    cout << "1. Agregar Repuesto" << endl;
    cout << "2. Consultar Repuesto" << endl;
    cout << "3. Borrar Repuesto" << endl;
    cout << "4. Actualizar Repuesto" << endl;
    cout << "5. Leer todos los Repuestos" << endl;
    cout << "0. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
}

void menuAdmin(){
  cout<<"Status: Admin."<<endl;
  cout<<" 1. Gestion de usuarios: "<<endl;
  cout<<" 2. Menu de vehiculos: "<<endl;
  cout<<" 3. Menu de repuestos: "<<endl;
  cout<<" 4. Menu de clientes: "<<endl;
  cout<<" 0. Salir: "<<endl;

}

void menuManager(){
  cout<<"Status: Manager."<<endl;
  cout<<" 1. Menu de vehiculos: "<<endl;
  cout<<" 2. Menu de repuestos: "<<endl;
  cout<<" 3. Menu de clientes: "<<endl;
  cout<<" 0. Salir: "<<endl;
}

void menuEmpleado(){
  cout<<"Status: Regular."<<endl;
  cout<<" 1. Consultar vehiculos."<<endl;
  cout<<" 2. Consultar repuestos."<<endl;
  cout<<" 3. Consultar clientes."<<endl;
  cout<<" 0. Salir"<<endl;
}