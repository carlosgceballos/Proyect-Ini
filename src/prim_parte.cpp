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

//funcion para borrar registros de vehiculos y clientes
void borrarRegistro(const string& archivoOriginal, const string& identificador) {
    ifstream archivo(archivoOriginal);
    ofstream archivoTemp("bin/datos/temp.csv");
    string aborrar;
    bool encontrado = false;

    if (!archivo.is_open() || !archivoTemp.is_open()) {
        cout << "No se pudo abrir el archivo para borrado.\n";
        return;
    }

    // Copiar todas las líneas, excepto la que contiene el identificador al archivo temporal
    while (getline(archivo, aborrar)) {
        if (aborrar.find(identificador) == string::npos) {
            archivoTemp << aborrar << endl;  // Copia la línea al archivo temporal si no coincide
        } else {
            encontrado = true;  // Marca que el registro fue encontrado y omitido
        }
    }

    archivo.close();
    archivoTemp.close();

    //verificar que se quiere confirmar el cambio
    int confirmar;
    if (encontrado) {
        cout<<"Confirme que desea realizar un cambio en el documento: (1 para confirmar, 0 para cancelar)";
        cin>> confirmar;
        if(confirmar ==  1){
        remove(archivoOriginal.c_str());           // Elimina el archivo original
        rename("bin/datos/temp.csv", archivoOriginal.c_str());  // Renombra el temporal al nombre original
        cout << "Registro borrado exitosamente.\n";
        }else{
            cout << "Operación cancelada. No se realizó ningún cambio.\n";
            remove("bin/datos/temp.csv");
        }
        }else{
        cout << "No se encontró un registro con el identificador especificado.\n";
        remove("bin/datos/temp.csv");  // Elimina el archivo temporal si no se encontró el registro
        }   
}

//funcion para borrar registro de repuestos
void borrarRepuesto(){
    string nombreRepuesto, modeloCarro;
    int anioCarro;
    cout << "Ingrese el nombre del repuesto que desea borrar: ";
    cin >> nombreRepuesto;
    cout << "Ingrese el modelo del carro al que pertenece el repuesto: ";
    cin >> modeloCarro;
    cout << "Ingrese el año del carro al que pertenece el repuesto: ";
    cin >> anioCarro;

    ifstream archivo("bin/datos/repuestos.csv");
    ofstream archivoTemp("bin/datos/temp.csv");
    string linea;
    bool encontrado = false;

    if (!archivo.is_open() || !archivoTemp.is_open()) {
        cout << "No se pudo abrir el archivo para borrado.\n";
        return;
    }

    // Copiar todas las líneas, excepto la que coincide al archivo temporal
    while (getline(archivo, linea)) {
        if (linea.find(nombreRepuesto) != string::npos && linea.find(modeloCarro) != string::npos && linea.find(to_string(anioCarro)) != string::npos) {
            // Si todos los criterios coinciden, se omite la línea 
            encontrado = true;
        } else {
            archivoTemp << linea << endl;
        }
    }

    archivo.close();
    archivoTemp.close();

    // Reemplazar el archivo original con el archivo temporal si se encontró el registro
    int confirmar;
    if (encontrado) {
        cout<<"Confirme que desea borrar el registro: (1 para confirmar, 0 para cancelar)";
        cin>>confirmar;
        if(confirmar==1){
        remove("bin/datos/repuestos.csv");           
        rename("bin/datos/temp.csv", "bin/datos/repuestos.csv");  
        cout << "Repuesto borrado exitosamente.\n";
        }else{
            cout << "Operación cancelada. No se realizó ningún cambio.\n";
            remove("bin/datos/temp.csv");
        }
     }else {
        cout << "No se encontró un repuesto con los criterios especificados.\n";
        remove("bin/datos/temp.csv");  // Elimina el archivo temporal si no se encontró el registro
    }
}

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

   confirmarAgregado(cl, "bin/datos/clientes.csv", "bin/datos/clientes_temp.csv");
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
        if(posi != string::npos && posi == 5){// posi == 0 porque la cedula debe estar en 0 en la primera linea
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
    
    confirmarAgregado(vehi, "bin/datos/vehiculos.csv", "bin/datos/vehiculos_temp.csv");

}

//funcion para agregar repuestos
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

    confirmarAgregado(re, "bin/datos/repuestos.csv", "bin/datos/repuestos_temp.csv");
}

void actualizarDatos(){

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
//Funcion consulta de vehiculo
void consultaVehiculo(){
    ifstream archivo("bin/datos/vehiculos.cvs");
    string vehiculos, Placa;
    bool encontrado = false;
    if(!archivo.is_open()){
        cout << "No se puede acceder al archivo" << endl;
        return;
    }
    cout << "Ingrese la placa que desee buscar:";
    cin >> Placa;

    while(getline(archivo, vehiculos)){
        size_t posi = vehiculos.find(Placa);
        if(posi !=string::npos && posi == 0){
            cout << vehiculos << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado){
        cout << "No se encontro el vehiculo con la placa especificada." << endl;
    }
    archivo.close();

}

//Funcion para consultar un repuesto especifico por nombre, modelo de carro, y año
void consultaRepuesto(){

    ifstream archivo("bin/datos/vehiculos.cvs");
    string Repuesto, nombreBuscar,modeloCarroBuscar;
    int anioCarroBuscar;
    bool encontrado = false;
    if(!archivo.is_open()){
        cout << "No se pudo abrir el archivo de repuestos.\n";
        return;

    }
    //Solicitar los datos de busqueda
    cout << "Ingrese el nombre del repuesto que desea buscar:";
    cin >> nombreBuscar;
    cout << "Ingrese el modelo del carro asociado al repuesto:";
    cin >> modeloCarroBuscar;
    cout << "Ingrese el año del carro asociado al repuesto:";
    cin >> anioCarroBuscar;

    //Recorrer el archivo linea por linea 
    while(getline(archivo, Repuesto)){
        //verificar si todos los criterios estan en la linea actual
        size_t posNombre =
        Repuesto.find("Nombre:" + nombreBuscar);
        size_t posModeloCarro =
        Repuesto.find("Modelo de carro:" + modeloCarroBuscar);
        size_t posAnioCarro = Repuesto.find("Year del carro:" + to_string(anioCarroBuscar));

        //Comprobar que todos los criterios coincidan
        if(posNombre != string::npos&& posModeloCarro != string::npos&& posAnioCarro != string::npos){
            cout << "Repuesto encontrado:\n"; 
            cout << Repuesto << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado){
        cout << "No se encontro un repuesto con los datos especificados.\n";
    }
    archivo.close();

}

//Funcion para no alterar archivos hasta confirmarlos 
template <typename T>//nos permite trabajar con cualquier tipo de dato
void confirmarAgregado(const T& nuevoRegistro,const string& archivoOriginal,const string& archivoTemporal){
    //const T& nuevoRegistro es el registro que se desea agregar(de tipocliente,vehiculo o repuesto).
    //const string& archivoOriginal el nombre del archivo donde se almacenan lo datos confirmados.
    //const string& archivoTemporal el nombre del archivo donde se almacenan los dayos hasta que el usuario confirme.

    ofstream tempArchivo(archivoTemporal,ios::app);
    if constexpr (is_same<T,Cliente>::value){
        tempArchivo<<
        nuevoRegistro.cedula << "," <<
        nuevoRegistro.nombre << "," << 
        nuevoRegistro.apellido << "," << nuevoRegistro.email << "," << nuevoRegistro.cantidad_vehiculos_rentados <<"," << nuevoRegistro.direccion << "," << nuevoRegistro.activo << endl;

    }else if constexpr(is_same<T, vehiculo>::value){
        tempArchivo << nuevoRegistro.placa << "," << nuevoRegistro.modelo << "," << 
        nuevoRegistro.marca << "," << nuevoRegistro.color << "," nuevoRegistro.year << "," << nuevoRegistro.kilometraje << ","<< nuevoRegistro.rentado << "," << nuevoRegistro.motor << "," << nuevoRegistro.precio_renta << "," << nuevoRegistro.ced_cliente << "," << nuevoRegistro.fecha_entrega << endl;

    }else if constexpr(is_same<T, Repuesto>::value){
        tempArchivo << nuevoRegistro.nombre << "," << nuevoRegistro.anio_carro << "," << nuevoRegistro.precio << "," << nuevoRegistro.existencias << endl;

    }
    tempArchivo.close();

    int confirmar;
    cout << "Desea confirmar el agregado del registro? (1 para confirmar,0 para cancelar):";
    cin >> confirmar;

    if (confirmar==1){
        remove(archivoOriginal.c_str()); //Elimina el archivo original y renombra el temporal al nombre original
        rename(archivoTemporal.c_str(), archivoOriginal.c_str());
        cout << "Registro agregado exitosamente.\n";
    }else{
        remove(archivoTemporal.c_str()); //Elimina el archivo temporal si se cancela la operacion
        cout << "Operacion cancelada. No se realizo ningun cambio.\n";
    }
    
     
}

//Funcion actualizar
template <typename T> 
void modificarRegistro(const string& archivoOriginal, const string& archivoTemporal, const string& identificador){
    ifstream archivo(archivoOriginal);
    ofstream tempArchivo(archivoTemporal);

    if(!archivo.is_open()||! tempArchivo.is_open()){
        cout << "No se pudo abrir uno de los archivos.\n";
        return;
    }
    string linea;
    bool encontrado = false;

    //Leemos cada linea y buscamos el identificador 
    while(getline(archivo, linea)){
        size_tpos = linea.find(identificador);

        if(pos != string::npos && pos== 0) {
            //Identificador encontrado al inicio de la linea

            encontrado= true;
            T registroModificado;

            //Pedir datos dependiendo del tipo de registro 
            if constexpr(is_same<T,Cliente>::value){
                cout << "Ingrese los nuevos datos del cliente:\n";
                cout << "Cedula:";
                cin >> registroModificado.cedula;
                cout << "Nombre:";
                cin >> registroModificado.nombre;
                cout << "Apellido:";
                cin >> registroModificado.apellido;
                cout << "Email:";
                cin >> registroModificado.email;
                cout << "Cantidad de vehiculos rentados:";
                cin >> registroModificado.cantidad_vehiculos_rentados;
                cout << "Direccion:";
                cin.ignore();
                getline(cin, registroModificado.direccion);
                cout << "Archivo(1 para si,0 para no):";
                cin >> registroModificado.activo;

                //Escribimos los datos nuevos en el archivo temporal
                tempArchivo << registroModificado.cedula << "," << registroModificado.nombre << "," << registroModificado.apellido << "," << registroModificado.email << "," << registroModificado.cantidad_vehiculo_rentados << "," << registroModificado.direccion << "," << registroModificado.activo << endl;

            }else if constexpr(is_same <T, vehiculo>::value){
                cout << "Ingrese los nuevos datos del vehiculo:\n";
                cout << "Placa:";
                cin >> registroModificado.placa;
                cout << "Modelo:";
                cin >> registroModificado.modelo;
                cout << "Marca";
                cin >> registroModificado.marca;
                cout << "Color";
                cin >> registroModificado.color;
                cout << "Kilometraje";
                cin >> registroModificado.kilometraje;
                cout << "Rentado (1 para si, 0 para no):";
                cin >> registroModificado.rentado;
                cout << "Motor:";
                cin >> registroModificado.motor;
                cout << "Precio de renta:";
                cin >> registroModificado.precio_renta;
                cout << "Fecha de entrega:";
                cin >> registroModificado.fecha_entrega;
                
                tempArchivo << registroModificado.placa << "," << registroModificado.modelo << "," << registroModificado.marca << "," << registroModificado.color << "," << registroModificado.year << "," << registroModificado.kilometraje << "," << registroModificado.rentado << "," << registroModificado.motor << "," << registroModificado.precio_renta << "," << registroModificado.ced_cliente << "," << registroModificado.fecha_entrega << "," << endl;


            }else if constexpr (is_same<T,Repuesto>::value){
                cout << "Ingrese los nuevos datos del repuesto:\n";
                cout << "Nombre:";
                cin >> registroModificado.nombre;
                cout << "Marca:";
                cin >> registroModificado.marca;
                cout << "Modelo:";
                cin >> registroModificado.modelo;
                cout << "Modelo de carro:";
                cin >> registroModificado.modelo_carro;
                cout << "Año del carro:";
                cin >> registroModificado.anio_carro;
                cout << "Precio:";
                cin >> registroModificado.precio;
                cout << "Existencias:";
                cin >> registroModificado.existencias;

                tempArchivo << registroModificado.nombre << "," << registroModificado.marca << "," << registroModificado.modelo << "," << registroModificado.modelo_carro << "," << registroModificado.anio_carro << "," << registroModificado.precio << "," << registroModificado.existencias << endl;

            }
        }else{
            //Si no es el registro que queremos modificar,lo copiamos directamente
            tempArchivo << linea << endl;
        }
    }
    archivo.close();
    tempArchivo.close();

    if(encontrado){
        int confirmar;
        cout << "Desea confirmar la modificacion? (1 para confirmar, 0 para cancelar):";
        cin >> confirmar;

        if(confirmar ==1){
            remove(archivoOriginal.c_str());
            rename(archivoTemporal.c_str(), archivoOrginal.c_str());
            cout << "Registro modificado exitosamente.\n";

        }else{
            remove(archivoTemporal.c_str());
            cout << "Operacion cancelada. No se realizo ningun cambio.\n";
        }
    }else{
        remove(archivoTemporal.c_str());
        cout << "No se encontro ningun registro con el identificador especificado.\n";
        remove(archivoTemporal.c_str());
    }
}


int main(){

    int opcion;
    do{
        cout <<"1. Agregar registro:\n";
        cout <<"2. Consultar dato en un registro\n";
        cout <<"3. Borrar registro:\n";
        cout <<"4. Actualizar Dato:\n";
        cout <<"";
        cout << "0. Salir:\n";
        cin >> opcion;

        switch(opcion){
            case 1: {
            int op;
            do{
                cout<<"1. Agregar cliente."<<endl;
                cout<<"2. Agregar vehiculo."<<endl;
                cout<<"3. Agregar repuesto."<<endl;
                cout<<"0. Cancelar." <<endl;
                cin>>op;
                switch(op){
                    case 1:
                agregarCliente();
                break;
                case 2:
                agregarVehiculo();
                break;
                case 3:
                agregarRepuesto();
                case 0:
                cout<<"Regresando al menu principal."<<endl;
                break;
                default:
                cout<<"Opcion invalida.";
            }
            }while(op!=0);
            break;
            }
            case 2: {
                int op;
                do{
                    cout<<"1. Consultar cliente."<<endl;
                    cout<<"2. Consultar vehiculo."<<endl;
                    cout<<"3. Consultar repuesto."<<endl;
                    cout<<"0. Regresar al menu principal"<<endl;
                    cin>>op;
                    switch(op){
                        case 1:
                        ConsCl();
                        break;
                        case 2:
                        consultaVehiculo();
                        break;
                        case 3:
                        consultaRepuesto();
                        break;
                        case 0:
                        cout<<"Regresando al menu principal."<<endl;
                        break;
                        default:
                        cout<<"Opcion invalida";
                    }

                }while(op!=0);
            break;
            }
            case 3:{
                int op;
                do{
                    cout<<"1. Borrar registro de cliente."<<endl;
                    cout<<"2. Borrar registro de vehiculo."<<endl;
                    cout<<"3. Borrar registro de Repuesto."<<endl;
                    cout<<"0. Regresar al menu principal."<<endl;
                    cin>>op;
                    switch(op){
                        case 1:{
                        string cedula;
                        cout<<"Ingrese la cedula del cliente: ";
                        cin>>cedula;
                        borrarRegistro("bin/datos/clientes.csv", cedula);
                        break;
                        }
                        case 2:{
                        string placa;
                        cout<<"Ingrese la placa del vehiculo";
                        cin>>placa;
                        borrarRegistro("bin/datos/vehiculos.csv", placa);
                        break;
                        }
                        case 3:{
                            borrarRepuesto();
                        break;
                        }
                        case 0:
                        cout<<"Regresando al menu principal."<<endl;
                        break;
                        default:
                        cout<<"Opcion invalida";
                    }
                }while(op !=0);
                break;
            }
    
            break;

            case 4:
            actualizarDatos();
            break;

            case 5:
        
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

