#include <iostream>
#include "MENUS.h"
#include <fstream>
#include <cstring>

using namespace std;

const char* nombretexto = "USUARIOS.bin";
const char* JUEGOS = "JUEGOS.bin";
const char* MAN_CONS = "MAN_CONS.bin";
//jamie secso
// que onda jysvejkfghsef
struct usuario{
    char nombre[50];
    int edad;
    int ci;
    char contrasena[20];
};

struct Juegos{
    char nombre[100];
    float precio;
    char tipo[20];
    int stock;
};

struct MandosConsola{
    char nombre[100];
    float precio;
    char tipo[20];
    int stock;
};

//prototipo
void Menu_cliente();
void Menu_administrador();
void cliente_nuevo();
void cliente_existente();
void verificar_usuario();
bool verificar_existencia();

void Reporte_producto(){
    ifstream archivo1;
    Juegos juego;
    archivo1.open(JUEGOS,ios::in | ios::binary);
    while (archivo1.read((char*)&juego,sizeof(Juegos)))
    {
        cout<<"Nombre: "<<juego.nombre<<"\tPrecio: "<<juego.precio<<"\tTipo: "<<juego.tipo<<"\tStock: "<<juego.stock<<endl;
    }
    archivo1.close();
    ifstream archivo2;
    MandosConsola producto;
    archivo2.open(MAN_CONS,ios::in | ios::binary);
    while (archivo2.read((char*)&producto,sizeof(MandosConsola)))
    {
        cout<<"Nombre: "<<producto.nombre<<"\tPrecio: "<<producto.precio<<"\tTipo: "<<producto.tipo<<"\tStock: "<<producto.stock<<endl;
    }
    archivo2.close();
}

void Adicionar_producto(){
    ofstream archivo;
    int opcion =0;
    cout<<"Que tipo de producto dessea adicionar: \n1) Mandos\2 Consola\n3) Juego\nOpcion: ";
    cin>>opcion;
    const char* archivoSelecionado;
    if (opcion == 3){
        cin.ignore();
        archivoSelecionado=JUEGOS;
        Juegos juego;
        cout<<"Nombre: ";
        cin.getline(juego.nombre,100);
        cout<<"TIpo: ";
        cin.getline(juego.tipo,20);
        cout<<"Precio: ";
        cin>>juego.precio;
        cout<<"Stock: ";
        cin>>juego.stock;
        archivo.open(archivoSelecionado,ios::app | ios::binary);
        archivo.write((char*)&juego, sizeof(Juegos));
        archivo.close();
    }else{
        archivoSelecionado=MAN_CONS;
        cin.ignore();
        archivoSelecionado=JUEGOS;
        MandosConsola juego;
        cout<<"Nombre: ";
        cin.getline(juego.nombre,100);
        cout<<"TIpo: ";
        cin.getline(juego.tipo,20);
        cout<<"Precio: ";
        cin>>juego.precio;
        cout<<"Stock: ";
        cin>>juego.stock;
        archivo.open(archivoSelecionado,ios::app | ios::binary);
        archivo.write((char*)&juego, sizeof(MandosConsola));
        archivo.close();
    }
}

void Menu_Administrador(){
    int opcion=0;
    while (true){
        opcion=cuenta_del_administrador();
        if (opcion==0){
            break;
        }
        switch (opcion){
            case 5:
                Reporte_producto();
                break;
            case 6:
                Adicionar_producto();
                break;
        
            default:
                Mostrar("opcion invalida");
                break;
        }
    }
}

void Menu_Usuario(char nombre[50]){
    int opcion=0;
    while (true)
    {
        opcion=menu_opciones_cliente();
        if (opcion==0){
            break;
        }
        switch (opcion)
        {
        case 1:
    
            break;
        case 2:
            
            break;
        
        default:
            Mostrar("opcion invalida");
            break;
        }
    }
}

void cliente_nuevo(){
    usuario nuevo;
    cin.ignore();
    cout<<"Nombre: ";
    cin.getline(nuevo.nombre,50);
    cout<<"Contrasena: ";
    cin.getline(nuevo.contrasena,20);
    cout<<"Edad: ";
    cin>> nuevo.edad;
    cout<<"CI: ";
    cin>> nuevo.ci;
    
    ofstream archivo;
    archivo.open(nombretexto,ios::app | ios::binary);
    archivo.write((char*)&nuevo, sizeof(usuario));
    Menu_Usuario(nuevo.nombre);
}

bool verificar_existencia(char nombre[50], char contrasena[20]){
    
    usuario usuarios;
    ifstream archivo;
    archivo.open(nombretexto, ios::in | ios:: binary);
    while(archivo.read((char*)&usuarios, sizeof(usuario))){
        if (strcmp(usuarios.nombre, nombre) == 0 && strcmp(usuarios.contrasena, contrasena) == 0){
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}


void verificar_usuario(){
    char nombre[50]; 
    char contrasena[20];
    int opcion=0;
    while(true)
    {
        cin.ignore();
        cout<<"NOmbre de usuario: ";
        cin.getline(nombre,50);
        cout<<"Contrasena: ";
        cin.getline(contrasena,20);
        if(verificar_existencia(nombre, contrasena))
        {
            Menu_Usuario(nombre);
        }
        else
        {
            Mostrar("El usuario o contrasena es incorrecto.");
            cout<<"Desea continuar?\n1) si\n2) no\nOpcion: ";
            cin>>opcion;
            if (opcion==2)
            {
                break;
            }
        }
    }
}


void Menu_cliente(){
    int opciones=0;
    while(true){
        opciones=menu_ingreso_usuario();
        if (opciones==0){
            break;
        }
        switch (opciones){
            case 1:
                cliente_nuevo();
                break;
            case 2:
                verificar_usuario();
                break;
            default:
                cout<<"Opcion invalida"<<endl;
                break;
        }
    } 
}

int main(){
    int opcion=0;
    while (true)
    {
        opcion=menu_inicial();
        if (opcion==0){
            break;
        }
        switch (opcion)
        {
        case 1:
            Menu_cliente();
            break;
        case 2:
            Menu_Administrador();
            break;
        
        default:
            Mostrar("opcion invalida");
            break;
        }
    }
    return 0;
}