
#include <iostream>
#include <limits>
#include <cstdlib>
#include <string.h>
using namespace std;

const char* archivo_administradores = "ADMINISTRADORES.bin";
const char* archivo_productos = "PRODUCTOS.bin";
const char* archivo_usuarios = "USUARIOS.bin";
const char* archivo_compras = "COMPRAS.bin";

void menu_(){
    int opcion;
    cout <<"----------------------------------------------";
    cout <<"        BIENVENIDO AL WILLY GAME'S            ";
    cout <<"----------------------------------------------";
    cout <<" tiene cuenta o es nuevo por aca";
    cout <<" (1) para abrir una nueva cuenta";
    cout <<" (2) si tiene cuenta existente";
    
}
string menu_cliente(){   
    string salida = "";
    salida+="\n----------------------------------------------\n";
    salida+="        BIENVENIDO AL WILLY GAME'S            \n";
    salida+="----------------------------------------------\n";
    salida+="(1) Realizar una compra\n";
    salida+="(2) Historial de compras\n";
    salida+="(0) Volver\n";
    salida+="----------------------------------------------\n";
    salida+="Opcion: ";
    return salida;
}
string menu_pre_cliente()
{
    string salida = "";
    salida+="\n----------------------------------------------\n";
    salida+="        BIENVENIDO AL WILLY GAME'S            \n";
    salida+="----------------------------------------------\n";
    salida+=" (1) Si es cliente antiguo\n";
    salida+=" (2) Si es cliente nuevo\n";
    salida+=" (0) Volver\n";
    salida+="----------------------------------------------\n";
    salida+="Opcion: ";
    return salida;
}
void cuenta_existente()
{
    cout<<"ingrese su nombre :";
    cout<<"ingrese su contraseña:";
}

string menu_administrador() { ///
    string salida = "";
    salida+="\n----------------------------------------------\n";
    salida+="        BIENVENIDO AL WILLY GAME'S            \n";
    salida+="----------------------------------------------\n";
    // cout<<"1 reporte de ventas mes";
    // cout<<"2 reporte de ventas año";
    // cout<<"3 reporte de cuentas ";
    // cout<<"4 facturacion de personas ";
    salida+=" (1) Reporte de inventario\n";
    salida+=" (2) Adicionar producto a inventario\n";
    salida+=" (3) Aumentar producto\n";
    salida+=" (4) Reporte de ventas del mes\n";
    salida+=" (0) Volver\n";
    salida+="----------------------------------------------\n";
    salida+="Opcion: ";
    return salida;
}

string menu_inicio(){ ///
    string salida = "";
    salida+="\n----------------------------------------------\n";
    salida+="        BIENVENIDO AL WILLY GAME'S            \n";
    salida+="----------------------------------------------\n";
    salida+=" tiene cuenta o es nuevo por aca\n";
    salida+=" (1) eres un cliente\n";
    salida+=" (2) eres un administrador\n";
    salida+=" (0) Salir\n";
    salida+="----------------------------------------------\n";
    salida+="Opcion: ";
    return salida;
}

int menu_ingreso_usuario()
{   
    int opcion=0;
    cout <<"----------------------------------------------"<<endl;
    cout <<"        BIENVENIDO AL WILLY GAME'S            "<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<" (1)Si es cliente nuevo                       "<<endl;
    cout <<" (2)Si es cliente antiguo                     "<<endl;
    cout <<" (0)Para volver"<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout <<"Opcion: ";
    cin>>opcion;
    return opcion;
}



int cuenta_administrador(){
    int opcion=0;
    // cout<<"1 reporte de ventas mes";
    // cout<<"2 reporte de ventas año";
    // cout<<"3 reporte de cuentas ";
    // cout<<"4 facturacion de personas ";
    cout<<"5 Reporte de inventario"<<endl;
    cout<<"6 Adicionar producto"<<endl;
    cout <<"----------------------------------------------"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    return opcion;
}

string meses(string mensaje){
    string salida="";
    salida+=mensaje;
    salida+="\n1) Enero\n";
    salida+="2) Febrero\n";
    salida+="3) Marzo\n";
    salida+="4) Abril\n";
    salida+="5) Mayo\n";
    salida+="6) Junio\n";
    salida+="7) Julio\n";
    salida+="8) Agosto\n";
    salida+="9) Septiembre\n";
    salida+="10) Octubre\n";
    salida+="11) Noviembre\n";
    salida+="12) Diciembre\n";
    salida+="Mes: ";
    return salida;
}

string obtener_mes(int n) {
    switch (n) {
        case 1: return "Enero";
        case 2: return "Febrero";
        case 3: return "Marzo";
        case 4: return "Abril";
        case 5: return "Mayo";
        case 6: return "Junio";
        case 7: return "Julio";
        case 8: return "Agosto";
        case 9: return "Septiembre";
        case 10: return "Octubre";
        case 11: return "Noviembre";
        case 12: return "Diciembre";
        default: return "Número inválido";
    }
}
