#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Vehiculo{
  string modelo, marca, placa, color, motor, fecha_entrega;
  int year, kilometraje, ced_cliente;
  bool rentado;
  float precio_renta;
};

struct Cliente {
    string nombre, apellido, email, direccion;
    int cantidad_vehiculos_rentados, cedula;
    bool activo;
};

struct Repuesto {
    string modelo, marca, nombre, modelo_carro;
    int anio_carro, existencias;
    float precio;
};


//funcion para leer lista completa de clientes
void leerListaClientes(){
    ifstream archivo("bin/datos/clientes.csv");
    string cliente;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de clientes.\n";
        return;
    }
    
    cout << "Datos de Clientes:";
    cout<< endl;
    while (getline(archivo, cliente)) {
        cout << cliente << endl;
    }
    archivo.close();
}

//funcion para agregar clientes
void agregarCliente(){
    Cliente cl;
    cout << "Ingrese los datos del cliente:\n";
    cout << "Cedula: "; 
    cin >> cl.cedula;
    cout << "Nombre: "; 
    cin >> cl.nombre;
    cout << "Apellido: "; 
    cin >> cl.apellido;
    cout << "Email: "; 
    cin >> cl.email;
    cout << "Cantidad de vehiculos rentados: "; 
    cin >> cl.cantidad_vehiculos_rentados;
    cout << "Direccion: "; 
    cin.ignore(); 
    getline(cin, cl.direccion);
    cout << "Activo (1 para si, 0 para no): "; 
    cin >> cl.activo;

    ofstream archivo("bin/datos/clientes.csv", ios::app);
    archivo <<"C.I: "<< cl.cedula << "\t" << "Nombre: "<< cl.nombre <<"\t" <<"Apellido: "<< cl.apellido << "\t" << "Email: "<< cl.email << "\t" << "Cantidad Autos Rentados: "<< cl.cantidad_vehiculos_rentados 
    << "\t" <<"Direccion: "<< cl.direccion << "\t" << "Activo (1=Si, 0=No): "<< cl.activo << endl;
    archivo.close();
    cout << "Cliente agregado.";
    cout << endl;
}

//funcion consulta de clientes
void ConsCl(){
    ifstream archivo("bin/datos/clientes.csv");
    string cliente, cedulaBuscar;

    if (!archivo.is_open()){
        cout<< "No se pudo acceder al archivo."<<endl;
        return;
    }
    cout<<"Ingrese la cedula del cliente: ";
    cin>> cedulaBuscar;

    bool encontrado = false;
    while(getline(archivo, cliente)){
        size_t posi = cliente.find(cedulaBuscar);
        if(posi != string::npos && posi == 5){// posi == 0 porque la cedula esta al principio de la linea
            cout << cliente<<endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado){
        cout<<"No se encontro un cliente con la cedula proporcionada."<<endl;
    }
    archivo.close();
}

// funcion para leer vehiculos
void leerVehiculos(){
    ifstream archivo("bin/datos/vehiculos.csv");
    string Vehiculo;
    cout << "Datos de Vehiculos:\n";
    while (getline(archivo,Vehiculo)){
        cout << "vehiculo" << endl;
    }
    archivo.close();
}

// Funcion para agregar Vehiculos
void agregarVehiculo(){
    Vehiculo vehi;
    cout << "Ingrese los datos del vehiculo:\n";
    cout << "Modelo:";
    cin >> vehi.modelo;
    cout << "Marca:";
    cin >> vehi.marca;
    cout << "Placa:";
    cin >> vehi.placa;
    cout << "Color:";
    cin >> vehi.color;
    cout << "Year:";
    cin >> vehi.year;
    cout << "Kilometraje:";
    cin >> vehi.kilometraje;
    cout << "Rentado (1 para si,0 para no):";
    cin >> vehi.rentado;
    cout << "Motor:";
    cin >> vehi.motor;
    cout << "Precio de renta:";
    cin >> vehi.precio_renta;
    cout << "Cedula del cliente:";
    cin >> vehi.ced_cliente;
    cout << "Fecha de entrega:";
    cin >> vehi.fecha_entrega;
    
    ofstream archivo("bin/datos/vehiculos.csv", ios:: app);
    archivo << vehi.modelo << "\t" << vehi.marca << "\t" << vehi.placa << "\t"<< vehi.color << "\t" << vehi.year << "\t" << vehi.kilometraje << "\t" << vehi.rentado << "\t" << vehi.motor << "\t" << vehi.precio_renta << "\t" << vehi.ced_cliente << "\t" << vehi.fecha_entrega << endl;
    archivo.close();
    cout << "Vehiculo agregado.\n";

}

void agregarRepuesto(){
    Repuesto re;
    cout<<"Ingrese los datos del repuesto:\n";
    cout<<"Nombre:\n";
    cin>> re.nombre;
    cout<<"Marca:\n";
    cin>>re.marca;
    cout<<"Modelo:\n";
    cin>>re.modelo;
    cout<<"Modelo de carro:\n";
    cin>>re.modelo_carro;
    cout<<"Year del carro\n";
    cin>>re.anio_carro;
    cout<<"Precio:\n";
    cin>>re.precio;
    cout<<"Existencias:\n";
    cin>>re.existencias;

    ofstream archivo("bin/datos/repuestos.cvs", ios::app);
    archivo<< re.nombre<<"\t"<<re.marca<<"\t"<<re.modelo<<"\t"<<re.modelo_carro<<"\t"<<re.anio_carro<<"\t"
    <<re.precio<<"\t"<<re.existencias<<endl;
    archivo.close();

    cout<<"Repuesto agregado";

}

void actualizarDatos(){

}

void borrarDatos(){



}
//Funcion para leer la lista de repuestos

void leerRepuestos(){
    ifstream archivo("bin/datos/lista repuestos.csv");
    string Repuesto;
    
    cout << "Datos de repuesto:\n";

    if (!archivo.is_open()){
        
        cout << "Error al abrir el archivo de repuestos.\n";
    }
    while(getline(archivo, Repuesto)){
        cout << "repuesto" << endl;
    }
    archivo.close();

}

int main(){

    int opcion;
    do{
        cout <<"1. Agregar Cliente:\n";
        cout <<"2. Agregar Vehiculo:\n";
        cout <<"3. Agregar Repuesto:\n";
        cout <<"4. Actualizar Dato:\n";
        cout <<"5. Borrar Dato:\n";
        cout << "0. Salir:\n";
        cin >> opcion;

        switch(opcion){
            case 1:
            agregarCliente();
            break;

            case 2:
            agregarVehiculo();
            break;

            case 3:
            agregarRepuesto();
            break;

            case 4:
            actualizarDatos();
            break;

            case 5:
            borrarDatos();
            break;

            case 0:
            cout << "Saliendo del programa...\n";
            break;

            default:
            cout << "Opcion no valida, intente de nuevo. \n ";
        }
    }while(opcion !=0);



    return 0;
}