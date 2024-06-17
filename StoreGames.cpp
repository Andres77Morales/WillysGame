#include <iostream>
#include "MENUS.h"
#include <fstream>
#include <cstring>

using namespace std;

const char* nombretexto = "USUARIOS.bin";
//jamie secso
// que onda 
struct usuario{
    char nombre[50];
    int edad;
    int ci;
    char contrasena[20];
};

//prototipo
void Menu_cliente();
void Menu_administrador();
void cliente_nuevo();
void cliente_existente();
void verificar_usuario();
bool verificar_existencia();

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
            break;
        
        default:
            Mostrar("opcion invalida");
            break;
        }
    }
    return 0;
}