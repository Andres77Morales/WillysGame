#include <iostream>

using namespace std;

int menu_inicial(){
    int opcion=0;
    cout <<"----------------------------------------------"<<endl;
    cout <<"        BIENVENIDO AL WILLY GAME'S            "<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<" tiene cuenta o es nuevo por aca"<<endl;
    cout <<" (1) eres un cliente"<<endl;
    cout <<" (2) eres un administrador"<<endl;
    cout <<" (0) Salir"<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<"Opcion: ";
    cin>>opcion;
    return opcion;
}
int menu_ingreso_usuario()
{   
    int opcion=0;
    cout <<"----------------------------------------------"<<endl;
    cout <<"        BIENVENIDO AL WILLY GAME'S            "<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<" (1)Si es cliente nuevo                       "<<endl;
    cout <<" (2)Si es cliente antiguo                     "<<endl;
    cout <<" (3)Para volver"<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<"Opcion: ";
    cin>>opcion;
    return opcion;
}

int menu_opciones_cliente()
{   
    int opcion=0;
    cout <<"----------------------------------------------"<<endl;
    cout <<"        BIENVENIDO AL WILLY GAME'S            "<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<"(1)Consolas y mandos  "<<endl;
    cout <<"(2)Juegos "<<endl;
    cout <<"(3)Historial de compras"<<endl;
    cout <<"(0)Salir"<<endl;
    cout <<"----------------------------------------------"<<endl;
    cin>>opcion;
    return opcion;
}


void Mostrar(string mensaje){
    cout<<mensaje<<endl;
}