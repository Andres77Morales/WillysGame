#include <iostream>
#include <fstream>
#include <cstring>
#include "MENUS.h"
#include "FUNCIONES.h"
#include <vector>

using namespace std;

struct Administrador {
    char nombre[50];
    char contrasena[20];
};

struct Producto {
    int id;
    char nombre[70];
    char tipo[20];
    float precio;
    int stock;
};

struct Compra {
    char usuario_nombre[20];
    Producto compras[20];
    int numero_compras;
    int mes_compra;
};

struct Usuario {
    int ci;
    char nombre[20];
    char contrasena[20];
    int edad;
};

// Inicio - Opciones de usuario
void historial_compras(char nombre[]){
    LimpiarTerminal();
    Compra compra;
    ifstream archivo;
    int c=0;
    archivo.open(archivo_compras, ios::in | ios::binary);
    while (archivo.read((char*)&compra, sizeof(Compra))) {
        if (strcmp(compra.usuario_nombre,nombre)==0){
            c++;
            Mostrar("------------ Numero de compra: "+to_string(c)+" ------------");
            for (int i=0;i<compra.numero_compras;i++){
                cout<<"Nombre: "<<compra.compras[i].nombre<<endl;
                cout<<"Precio: "<<compra.compras[i].precio<<endl;
                cout<<"Tipo: "<<compra.compras[i].tipo<<endl;
                Mostrar("");
            }cout << "----------------------------------------------" << endl;
        }
    }
    if (c==0){
        Mostrar("\nEl usuario no hizo ninguna compra");
    }
    archivo.close();
    presionar_continuar();
}

void adicionar_compras(char nombre[],vector<Producto> compras,int mes){
    ofstream archivo;
    Compra compra;
    strcpy(compra.usuario_nombre, nombre); 
    compra.numero_compras=compras.size();
    compra.mes_compra=mes;
    for (int i=0;i<compras.size();i++){
        compra.compras[i].id=compras[i].id;
        strcpy(compra.compras[i].nombre,compras[i].nombre);
        strcpy(compra.compras[i].tipo,compras[i].tipo);
        compra.compras[i].precio=compras[i].precio;
        compra.compras[i].stock=compras[i].stock;
    }
    archivo.open(archivo_compras,ios::app | ios::binary);
    archivo.write((char*)&compra, sizeof(Compra));
    archivo.close();
}

void descontar_stock(string tipo,int i){
    ifstream archivoLectura;
    ofstream archivoTemporal;
    Producto producto;
    archivoLectura.open(archivo_productos,ios::in | ios::binary);
    archivoTemporal.open("temporal.bin",ios::app | ios::binary);
    int c=0;
    while (archivoLectura.read((char*)&producto, sizeof(Producto))) {
        if (string(producto.tipo)==tipo){
            c++;
            if (c==i){
                producto.stock=producto.stock-1;
                archivoTemporal.write((char*)&producto, sizeof(Producto));
            }else{
                archivoTemporal.write((char*)&producto, sizeof(Producto));
            }
        }else{
            archivoTemporal.write((char*)&producto, sizeof(Producto));
        }
    }
    archivoTemporal.close();
    archivoLectura.close();
    remove(archivo_productos);
    rename("temporal.bin",archivo_productos);
}

Producto obtener_producto(string tipo, int i){
    ifstream archivo;
    Producto producto;
    archivo.open(archivo_productos, ios::in | ios::binary);
    int c = 0;
    while (archivo.read((char*)&producto, sizeof(Producto))){
        if (string(producto.tipo) == tipo){
            c++;
            if (c == i){
                archivo.close();
                return producto;
            }
        }
    }
    archivo.close();
    return producto;
}


bool compra_disponible(string tipo, int i){
    ifstream archivo;
    Producto producto;
    int c=0;
    archivo.open(archivo_productos,ios::in | ios::binary);
    while (archivo.read((char*)&producto, sizeof(Producto))){
        if (string(producto.tipo)==tipo){
            c++;
            if (c==i){
                if (producto.stock>0){
                    archivo.close();
                    return true;
                }else{
                    archivo.close();
                    return false;
                }
            }
        }
    }
    archivo.close();
    return false;

}



vector<Producto> realizar_compra(string tipo,vector<Producto> carrito){
    vector<Producto> salida=carrito;
    LimpiarTerminal();
    Producto producto;
    ifstream archivo;
    Producto compra;
    while (true) {
        int opcion=0;
        int c=0;
        archivo.open(archivo_productos,ios::in | ios::binary);
        Mostrar("--- "+tipo+"s ---");
        while (archivo.read((char*)&producto, sizeof(Producto))){
            if (string(producto.tipo)==tipo){
                c++;
                Mostrar("("+to_string(c)+") Nombre: "+string(producto.nombre)+" - Precio: "+to_string(producto.precio));
            }
        }
        archivo.close();
        Mostrar("(0) Volver");
        opcion=EntradaEntero("Opcion: ");
        if (opcion==0){
            break;
        }else if (opcion>0 && opcion<=c){
            if (compra_disponible(tipo,opcion)){
                compra=obtener_producto(tipo,opcion);
                salida.push_back(compra);
                descontar_stock(tipo,opcion);
                Mostrar("Compra realizada exitosamente\n");
                
                presionar_continuar();
                break;
            }else{
                LimpiarTerminal();
                Mostrar("-- El producto elejido no esta disponible -- \n");
            }
        }else{
            LimpiarTerminal();
            Mostrar("-- Elija una compra valida -- \n");
        }
    }
    return salida;
}

void factura_compra(vector<Producto> carrito,Usuario usuario,int mes){
    LimpiarTerminal();
    Mostrar("---------- Factura ---------");
    Mostrar("CI: "+to_string(usuario.ci));
    Mostrar("Usuario: "+string(usuario.nombre));
    Mostrar("Mes de compra: "+obtener_mes(mes));
    Mostrar("Producto\tPrecio");
    Mostrar("-----------------------------");
    float total=0.00;
    // for (int i=0;i<carrito.size();i++){
    //     Mostrar(string(carrito.at(i).nombre)+"\t"+to_string(carrito.at(i).precio));
    //     total+=carrito.at(i).precio;
    // }
    for (Producto producto : carrito){
        Mostrar(string(producto.nombre)+"\t"+to_string(producto.precio));
        total+=producto.precio;
    }
    Mostrar("-----------------------------");
    Mostrar("Total\t\t"+to_string(total));
    presionar_continuar();
}

void tipo_compra(char nombre[],Usuario usuario,int mes){
    int opcion=0;
    vector<Producto> carrito;
    while (true){
        LimpiarTerminal();
        opcion=EntradaEntero("Que tipo de producto dessea comprar?\n(1) Mando\n(2) Juego\n(3) Consola\n(0) Terminar la compra y volver.\nOpcion: ");
        if (opcion==0){
            if (carrito.size()==0){
                Mostrar("No se realizao ninguna compra\n");
                presionar_continuar();
            }else{
                factura_compra(carrito,usuario,mes);
                adicionar_compras(nombre,carrito,mes);
            }
            break;
        }
        switch (opcion){
        case 1:
            carrito=realizar_compra("Mando",carrito);
            break;
        case 2:
            carrito=realizar_compra("Juego",carrito);
            break;
        case 3:
            carrito=realizar_compra("Consola",carrito);
            break;
        default:
            break;
        }
    }
    
}

Usuario obtener_usuario(char nombre[]){
    Usuario usuario;
    ifstream archivo;
    archivo.open(archivo_usuarios,ios::in | ios::binary);
    while (archivo.read((char*)&usuario,sizeof(Usuario))) {
        if (strcmp(usuario.nombre,nombre)==0){
            return usuario;
        }
    }
    return usuario;
}

void opciones_usuario(char nombre[],int mes){
    int opcion=0;
    Usuario usuario = obtener_usuario(nombre);
    while (true){
        LimpiarTerminal();
        opcion=EntradaEntero(menu_cliente());
        if (opcion==0){
            break;
        }
        switch (opcion){
            case 1: 
                tipo_compra(nombre,usuario,mes);
                break;
            case 2:
                historial_compras(nombre);
                break;
            default:
                break;
        }
    }
    
}

void cliente_nuevo(int mes){
    Usuario nuevo;
    nuevo.ci=EntradaEntero("CI: ");
    EntradaCadena("Nombre: ",nuevo.nombre,50);
    EntradaCadena("Contrasena: ",nuevo.contrasena,20);
    nuevo.edad=EntradaEntero("Edad: ");
    if (nuevo.edad>=18){
        ofstream archivo;
        archivo.open(archivo_usuarios,ios::app | ios::binary);
        archivo.write((char*)&nuevo, sizeof(Usuario));
        opciones_usuario(nuevo.nombre,mes);
    }else{
        Mostrar("Error: Eres menor, llama a tu tutor");
        presionar_continuar();
    }
}
bool verificar_existencia(char nombre[], char contrasena[]){
    Usuario usuario;
    ifstream archivo;
    archivo.open(archivo_usuarios, ios::in | ios:: binary);
    while(archivo.read((char*)&usuario, sizeof(Usuario))){
        if (strcmp(usuario.nombre, nombre) == 0 && strcmp(usuario.contrasena, contrasena) == 0){
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}
void verificar_usuario(int mes){
    char nombre[20]; 
    char contrasena[20];
    int opcion=0;
    while(true){
        LimpiarTerminal();
        Mostrar("--- Entrada cliente ---");
        EntradaCadena("Nombre de usuario: ",nombre,20);
        EntradaCadena("Contrasena: ",contrasena,20);
        if(verificar_existencia(nombre, contrasena)){
            opciones_usuario(nombre,mes);
            break;
        }else{
            LimpiarTerminal();
            Mostrar("El usuario o contrasena es incorrecto.");
            if (!pregunta_continuar()) {
                break;
            }
        }
    }
}

void pre_opciones_usuario(int mes) {
    int opcion=0;
    while (true){
        LimpiarTerminal();
        opcion=EntradaEntero(menu_pre_cliente());
        if (opcion==0){
            break;
        }
        switch (opcion){
        case 1:
            verificar_usuario(mes);
            break;
        case 2:
            cliente_nuevo(mes);
            break;
        default:
            break;
        }
    }
    
}
// Fin - Opciones de usuario

// Inicio - Menu Administrador
void reporte_productos() {
    LimpiarTerminal();
    Producto producto;
    ifstream archivo;
    cout << "----------------------------------------------" << endl;
    cout << "          INVENTARIO DE PRODUCTOS             " << endl;
    cout << "----------------------------------------------" << endl;
    archivo.open(archivo_productos, ios::in | ios::binary);
    while (archivo.read((char*)&producto, sizeof(Producto))){
        Mostrar("\nProducto:");
        Mostrar("ID: " + to_string(producto.id));
        Mostrar("Nombre: " + string(producto.nombre));
        Mostrar("Tipo: " + string(producto.tipo));
        Mostrar("Precio: " + to_string(producto.precio));
        Mostrar("Stock: " + to_string(producto.stock));
    }
    archivo.close();
    presionar_continuar();
}

void agregar_producto() {
    Producto producto;
    LimpiarTerminal();
    cout << "----------------------------------------------" << endl;
    cout << "        BIENVENIDO AL WILLY GAME'S            " << endl;
    cout << "----------------------------------------------" << endl;
    producto.id = EntradaEntero("ID: ");
    EntradaCadena("Nombre: ", producto.nombre, 70);
    EntradaCadena("Tipo: ", producto.tipo, 20);
    producto.precio = EntradaDecimal("Precio: ");
    producto.stock = EntradaEntero("Stock: ");
    ofstream archivo;
    archivo.open(archivo_productos, ios::app | ios::binary);
    archivo.write((char*)&producto, sizeof(Producto));
    cout << "\n\tProducto agregado exitosamente." << endl;
    archivo.close();
}

void aumentar_stock(int i,int cantidad){
    ifstream archivoLectura;
    ofstream archivoTemporal;
    Producto producto;
    archivoLectura.open(archivo_productos,ios::in | ios::binary);
    archivoTemporal.open("temporal.bin",ios::app | ios::binary);
    int c=0;
    while (archivoLectura.read((char*)&producto, sizeof(Producto))) {
        c++;
        if (c==i){
            producto.stock=producto.stock+cantidad;
            archivoTemporal.write((char*)&producto, sizeof(Producto));
        }else{
            archivoTemporal.write((char*)&producto, sizeof(Producto));
        }
    }
    archivoTemporal.close();
    archivoLectura.close();
    remove(archivo_productos);
    rename("temporal.bin",archivo_productos);
}

void aumentar_producto(){
    Producto producto;
    ifstream archivo;
    int opcion=0;
    int c=0;
    while (true) {
        archivo.open(archivo_productos,ios::in | ios::binary);
        Mostrar("---------- Productos de inventario ----------");
        while (archivo.read((char*)&producto, sizeof(Producto))){
            c++;
            Mostrar("("+to_string(c)+") Nombre: "+string(producto.nombre)+" - Stock: "+to_string(producto.stock));
        }
        
        Mostrar("(0) Volver");
        Mostrar("Elije un producto para aumentar su stock:");
        
        archivo.close();
        opcion=EntradaEntero("Opcion: ");
        if (opcion==0){
            break;
        }else if (opcion>0 && opcion<=c) {
            int cantidad=EntradaEntero("Cuento dessea aumentar?: ");
            aumentar_stock(opcion,cantidad);
            LimpiarTerminal();
            Mostrar("\nSe aumento correctamente el stock.\n");
        }else{
            Mostrar("Elija una opcion valida");
        }
    }
    
}

bool existe_producto(int id,vector<Producto> productos){
    for (int i=0;i<productos.size();i++){
        if (productos[i].id==id){
            return true;
        }
    }
    return false;
}

int obtener_posicion_producto(vector<Producto> productos,int id){
    for (int i=0;i<productos.size();i++){
        if (productos[i].id==id){
            return i;
        }
    }
    return 0;
}

void reporte_mes(int mes){
    vector<Producto> productos;
    vector<int> cantidad;
    Compra compra;
    Producto producto;
    ifstream archivo;
    int posicion=0;
    archivo.open(archivo_compras,ios::in | ios::binary);
    while (archivo.read((char*)&compra, sizeof(Compra))) {
        if (compra.mes_compra==mes){
            for (int i=0;i<compra.numero_compras;i++){
                if (existe_producto(compra.compras[i].id,productos)){
                    posicion=obtener_posicion_producto(productos,compra.compras[i].id);
                    cantidad[posicion]=cantidad[posicion]+1;
                }else{
                    productos.push_back(compra.compras[i]);
                    cantidad.push_back(1);
                }
                
            }
        }
    }
    LimpiarTerminal();
    Mostrar("Numero de ventas en el mes de "+obtener_mes(mes));
    for (int i=0;i<productos.size();i++){
        Mostrar("Producto: "+string(productos[i].nombre)+"\t"+"Cantidad: "+to_string(cantidad[i]));
    }
    presionar_continuar();
}

void opciones_administrador(){
    int opcion = 0;
    int mes=0;
    while (true) {
        LimpiarTerminal();
        opcion = EntradaEntero(menu_administrador());
        if (opcion == 0) {
            break;
        }
        switch (opcion) {
            case 1:
                reporte_productos();
                break;
            case 2:
                agregar_producto();
                break;
            case 3:
                LimpiarTerminal();
                aumentar_producto();
                break;
            case 4:
                LimpiarTerminal();
                mes=0;
                while (true) {
                    LimpiarTerminal();
                    mes=EntradaEntero(meses("En que mes estamos?:"));
                    if (mes>=1 && mes<=12){
                        break;
                    }else{
                        Mostrar("\nElija un mes valido");
                        presionar_continuar();
                    }
                }
                reporte_mes(mes);
                break;
            default:
                break;
        }
    }
}
// Fin - Menu Administrador

// Inicio - Menu de inicio
bool existe_administrador(char nombre[50], char contrasena[20]){
    Administrador usuarios;
    ifstream archivo;
    archivo.open(archivo_administradores, ios::in | ios::binary);
    while (archivo.read((char*)&usuarios, sizeof(Administrador))){
        if (strcmp(usuarios.nombre, nombre) == 0 && strcmp(usuarios.contrasena, contrasena) == 0){
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void verificar_administrador(string mensaje){
    char nombre[50]; 
    char contrasena[20];
    while (true) {
        LimpiarTerminal();
        Mostrar("--- "+mensaje+" ---");
        EntradaCadena("Nombre: ", nombre, 50);
        EntradaCadena("Contrasena: ", contrasena, 20);
        if (existe_administrador(nombre, contrasena)) {
            opciones_administrador();
            break;
        } else {
            LimpiarTerminal();
            Mostrar("El usuario o contrasena es incorrecto.");
            if (!pregunta_continuar()) {
                break;
            }
        }
    }
}

int main(){
    int opcion = 0;
    int mes = 0;
    while (true) {
        LimpiarTerminal();
        mes=EntradaEntero(meses("En que mes estamos?:"));
        if (mes>=1 && mes<=12){
            break;
        }else{
            Mostrar("\nElija un mes valido");
            presionar_continuar();
        }
    }
    while (true) {
        LimpiarTerminal();
        opcion = EntradaEntero(menu_inicio());
        if (opcion == 0)
            break;
        switch (opcion) {
            case 1:
                pre_opciones_usuario(mes);
                break;
            case 2:
                verificar_administrador("Entrada de administrador");
                break;
            default:
                break;
        }
    }
    return 0;
}
// Fin - Menu inicio