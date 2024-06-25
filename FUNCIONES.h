

#include <iostream>

#include <cstdlib>

using namespace std;

void LimpiarTerminal();
void Mostrar(string mensaje);
void EntradaCadena();
void LimpiarBuffer();

int EntradaEntero(string mensaje) {
    int salida = 0;
    while (true) {
        cout << mensaje;
        cin >> salida;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            LimpiarTerminal();
            Mostrar("\nError: Ingrese unicamente valores enteros.");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return salida;
        }
    }
}

float EntradaDecimal(string mensaje) {
    float salida = 0.0;
    while (true) {
        cout << mensaje;
        cin >> salida;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Mostrar("\nError: Ingrese unicamente valores decimales.");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return salida;
        }
    }
}

void EntradaCadena(string mensaje,char salida[], int longitud) {
    while (true) {
        cout << mensaje;
        cin.getline(salida, longitud);
        if (cin.fail()) {
            cout << "\nError al ingresar la cadena. Intente de nuevo.\n" << endl;
        } else {
            break;
        }
    }
}

bool pregunta_continuar(){
    int opcion=0;
    while (true) {
        opcion=EntradaEntero("\nDesea continuar?\n1) si\n2) no\nOpcion: ");
        if (opcion==1){
            return true;
        }else if (opcion==2) {
            return false;
        }else{
            LimpiarTerminal();
            Mostrar("\nIngrese una opcion valida");
        }
    }
}

void presionar_continuar(){
    cout << "\nPresione enter para continuar:";
    cin.ignore();
}

void Mostrar(string mensaje) {
    cout << mensaje << endl;
}

void LimpiarTerminal() {
    system("clear");
}
