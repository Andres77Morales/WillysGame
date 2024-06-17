#include <iostream>
#include "MENUS.h"
#include <fstream>

using namespace std;

string nombretexto = "USUARIOS.bin";

struct usuario
{
    char nombre[45];
    int edad;
    int ci;
    char contrasena[30];
};



//prototipo
void Menu_cliente();
void cliente_nuevo();
void cliente_existente();
void verificar_usuario();
bool verificar_existencia();

void Menu_Usuario(char nombre[]){
    int opcion=0;
    while (true)
    {
        cin>>opcion;
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
    cout<<"Nombre: ";
    cin.getline(nuevo.nombre,45);
    cout<<"Edad: ";
    cin>> nuevo.edad;
    cout<<"CI: ";
    cin>> nuevo.ci;
    cout<<"Contrasena: ";
    cin.getline(nuevo.contrasena,30);
    ofstream archivo;
    archivo.open(nombretexto,ios::app | ios::binary);
    archivo.write((char*)&nuevo, sizeof(usuario));
    Menu_Usuario(nuevo.nombre);
}

bool verificar_existencia(char nombre[], char contrasena[]){
    
    usuario usuarios;
    ifstream archivo;
    archivo.open(nombretexto, ios::in | ios:: binary);
    while(archivo.read((char*)&usuarios, sizeof(usuario))){
        if (usuarios.nombre == nombre && usuarios.contrasena == contrasena)
        {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}


void verificar_usuario(){
    char nombre[45]; 
    char contrasena[30];
    int opcion=0;
    while(true){
        cin.getline(nombre, 45);
        cin.getline(contrasena, 30);
        if(verificar_existencia(nombre, contrasena)){
            Menu_Usuario(nombre);
        }else{
            Mostrar("El usuario o contrasena es incorrecto.");
            Mostrar("Desea continuar?\n1) si\n2) no\nOpcion: ");
            cin>>
        }
    }
}


void Menu_cliente(){
    int opciones;
    while(true)
    {
        cin>>opciones;
        switch (opciones)
        {
            if (opciones==0){
                break;
            }
            
            case 1:
                cliente_nuevo();
                break;
            
            case 2:
                verificar_usuario();
                break;
            

            default:
                cout<<"Salida"<<endl;
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