/*
 * Archivo: parabola.cpp
 * Descripción: A partir de la velocidad (m/s) y el ángulo de tiro (grados),
 *              calcular el tiempo de vuelo, y la altura y distancia máxima.
 * Autor: fblupi
 */

#include <iostream> // cin, cout, endl
#include <cmath>    // sin, pow

using namespace std;

int main() {
    double vel, ang; // Declaramos la velocidad y el ángulo en grados
    cout << "Introduzca la velocidad inicial del lanzamienteo en m/s: ";
    cin >> vel;
    cout << "Introduzca el ángulo de lanzamiento en grados: ";
    cin >> ang;
    double t, h, xmax, anr; // Declaramos el tiempo, la altura, la distancia y el ángulo en radianes
    const double g = 9.80665, pi = 3.141592659; // pi es una aproximación de su valor real, por lo que no convertirá con precisión absoluta un ángulo
    anr = ang * pi / 180; // c++ trabaja con radianes en vez de con grados y aquí convertimos nuestro ángulo a radianes
    t = 2 * vel* sin(anr) / g;
    h = pow(vel * sin(anr), 2) / (2 * g);
    xmax = vel * vel * sin(2 * anr) / g;
    cout << "El tiempo de vuelo del proyectil será: " << t << " segundos." << endl;
    cout << "El proyectil alcanzará una altura de: " << h << " metros." << endl;
    cout << "El proyectil recorrerá una distancia de: " << xmax << " metros." << endl;
}
