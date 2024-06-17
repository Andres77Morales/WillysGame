#include <iostream>
using namespace std;


void menu_();
int main()
{

}

void menu_(){
    int opcion;
    cout <<"----------------------------------------------";
    cout <<"        BIENVENIDO AL WILLY GAME'S            ";
    cout <<"----------------------------------------------";
    cout <<" tiene cuenta o es nuevo por aca";
    cout <<" (1) para abrir una nueva cuenta";
    cout <<" (2) si tiene cuenta existente";
    
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
    cout <<"----------------------------------------------"<<endl;
    cin>>opcion;
    return opcion;
}
void menu_cliente()
{
    cout <<"----------------------------------------------"<<endl;
    cout <<"        BIENVENIDO AL WILLY GAME'S            "<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<" (1)Si es cliente nuevo                       "<<endl;
    cout <<" (2)Si es cliente antiguo                     "<<endl;
    cout <<" (3)Para volver"                              ;
    cout <<"----------------------------------------------";
}
void cuenta_existente()
{
    cout<<"ingrese su nombre :";
    cout<<"ingrese su contraseña:";
}



void cuenta_del_administrador()
{
    int opcion=0;
    // cout<<"1 reporte de ventas mes";
    // cout<<"2 reporte de ventas año";
    // cout<<"3 reporte de cuentas ";
    // cout<<"4 facturacion de personas ";
    cout<<"5 inventario de juegos";
    cout<<"6 inventarios de consolas y mandos";
    cout <<"----------------------------------------------";
    cout<<"Opcion: ";
    cin>>opcion;
}
void menu_de_consolas()
{
    cout<<"consolas y mandos :";
    cout<<"catalogo de juegos :";
    /****************************/
    cout<<"consolas--";
    cout<<"1) nintendo ";
    //-------
    cout<<"1)consolas nintendo switch";
    cout<<"2)mando simple que se puede divir";
    cout<<"3)mando complex ";
    //------
    cout <<"2)xbox";
    cout<<"3)xbox 6 genereacion";
    /*   */
    cout<<"play station";

}
void juegos()
{
    cout<<" terror"; 
    /********/
    cout<<"accion";
    /*******/
    cout<<"peleas";
    /*******/
    cout<<"musica";
    /*******/
}