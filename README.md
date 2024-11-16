#Proyecto Inicial - Primera parte

Este proyecto es un sistema de gestión de registros para un negocio de vehículos. Permite administrar registros de clientes, vehículos, y repuestos almacenados en archivos CSV.

Estructura del proyecto:
proyecto-final/
│
├── src/
│   > main.cpp             # Código fuente principal
│
├── bin/
│   > datos/               # Carpeta con los archivos CSV
│      >clientes.csv
│      >vehiculos.csv
│      >repuestos.csv
│    >proyecto_final.exe   # Ejecutable del proyecto
│
|>README.md             

Funciones:
El programa cuenta con las siguientes opciones:

- Agregar Registro:
  Agregar cliente
  Agregar vehículo
  Agregar repuesto
  Consultar Registro:

-Consultar: 
  cliente por cédula
  Consultar vehículo por placa
  Consultar repuesto por nombre, modelo de carro y año
  
-Borrar Registro:
  Borrar cliente por cédula
  Borrar vehículo por placa
  Borrar repuesto por nombre, modelo de carro y año
  
-Actualizar Registro:
  Modificar información de un cliente
  Modificar información de un vehículo
  Modificar información de un repuesto
  
-Leer Todos los Registros:
  Mostrar todos los clientes
  Mostrar todos los vehículos
  Mostrar todos los repuestos
