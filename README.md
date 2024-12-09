#Proyecto 

Este programa permite la gestión de un negocio de alquiler de vehículos, con funcionalidades para manejar vehículos, repuestos, clientes y usuarios. Implementa un sistema de inicio de sesión con roles y un sistema de copias de seguridad.

La estructura de archivos es la siguiente:
bin/ 
├── datos/ │ 
  ├── clientes.csv │ 
  ├── vehiculos.csv │ 
  ├── repuestos.csv │ 
  └── usuarios.csv 
└── back_ups/ 
├── clientes_<fecha>.csv 
├── vehiculos_<fecha>.csv 
├── repuestos_<fecha>.csv 

src/ 
├── Menus/ │ 
  └── menu.cpp 
├── Productos/ │ 
  ├── Clientes/ │ 
      │ └── Cliente.h │
      │ └── cliente.cpp 
  ├── Repuestos/ │ 
      │  └── Repuesto.h 
      │ └── Repuesto.cpp 
  │ └── Vehiculos/ │ 
      └── Vehiculo.h 
      │ └── Vehiculo.cpp
  └── Usuarios/ 
      └── Usuario.h
      │ └── Usuario.cpp 


##Funcionalidades

1. **Gestión de Vehículos, Repuestos y Clientes**
El programa permite gestionar los vehículos, repuestos y clientes de un negocio de alquiler. Se utilizan clases para representar los diferentes tipos de objetos, y cada uno tiene funciones específicas para manejar las operaciones correspondientes.

- Vehículos: Los vehículos tienen atributos como modelo, marca, placa, color, año, kilometraje, precio de renta, entre otros.
- Repuestos: Los repuestos se gestionan mediante una clase que contiene datos como modelo, marca, existencias y precio.
- Clientes: Los clientes tienen datos como cédula, nombre, apellido, email, dirección, entre otros.

2. Sistema de Roles (Inicio de sesión)
El sistema implementa un sistema de roles con diferentes permisos de acceso:

- Admin: Tiene acceso completo a todas las funciones de gestión de vehículos, repuestos, clientes, y usuarios del programa. Puede agregar, modificar, eliminar y consultar datos, así como gestionar otros usuarios del sistema.
- Manager: Puede gestionar vehículos, repuestos y clientes, pero no puede gestionar los usuarios del sistema.
- Empleado: Tiene acceso solo a la consulta de vehículos, repuestos y clientes, y puede manejar las existencias. 

3. Archivos Temporales
El programa utiliza archivos temporales antes de realizar cualquier cambio permanente en los archivos de datos. Esto asegura que los datos solo se actualicen cuando las operaciones se completan exitosamente.

4. **Copia de Seguridad
El sistema permite crear copias de seguridad de los datos importantes, tales como clientes, vehículos, repuestos y usuarios. Las copias se guardan en un directorio de `back_ups/` con el nombre del archivo seguido de la fecha (ej. `clientes_2023-12-01.csv`). Las copias se crean antes de realizar cualquier cambio permanente en los archivos de datos.

Flujo del Programa
1. El usuario ingresa al sistema con su rol (Admin, Manager o Empleado).
2. Dependiendo del rol, el usuario tiene acceso a diferentes opciones de manejo de vehículos, repuestos, clientes y usuarios.
3. El programa realiza todas las modificaciones primero en archivos temporales y luego las guarda permanentemente si no hay errores.
4. Se pueden generar copias de seguridad de los datos antes de cualquier cambio importante.

