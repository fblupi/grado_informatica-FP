/*
 * Archivo: contacto.cpp
 * Descripción: Desencriptador de un número cabalístico
 * Autor: fblupi
 */

#include <iostream>

using namespace std;

int main() {
    int valor, secCeros = 0, secUnos = 0, num = 1, sec = 0, contador = 0;
    bool error=false;
    cout << "Escriba a continuación una secuencia de 0 y 1, acabada en cinco 0." << endl;
    cout << "Secuencia: ";
    do {
        cin >> valor;
        if(valor == 1) {
            secCeros = 0;
            secUnos++;
            sec = secUnos;
        }
        if (valor == 0) {
            secCeros++;
            if (secCeros == 1) { // Solo se realizarán cuentas si la secuencia de 0 es 1. Si no, se machaca una variable y fallará el programa.
                if (secUnos != 0){
                    bool esPrimo = true;
                    for (int i = 2; i < secUnos && esPrimo; ++i) {
                        if (secUnos%i == 0) esPrimo=false;
                    }
                    if (esPrimo == true){
                        num = num * secUnos;
                    }
                    secUnos = 0;
                }
            }
        }
        if (valor != 0 && valor != 1) {
            error = true; // Si se falla en la introducción de valores en la secuencia, aparecerán las siguientes instrucciones.
            cout << "La secuencia introducida no es correcta." << endl;
            cout << "Solo se pueden introducir 1 y 0 separados por espacios." << endl;
            cout << "La secuencia finalizará con cinco 0 seguidos." << endl;
        }
        contador++;
    } while (secCeros < 5);

    if (contador == 5)
        num = 0; // Se añade este condicional porque se le ha dado valor 1 al número inicial para que pudiese hacer la primera multiplicación. Así, si la secuencia es 0 0 0 0 0 el número codificado será 0.
    if (error == true) 
        cout << "Error en secuencia introducida." << endl; //Si ha habido un error en la secuencia, no devuelve ningún número.
    else cout << "El número codificado es: " << num << endl;
}
