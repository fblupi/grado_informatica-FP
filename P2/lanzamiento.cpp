/*
 * Archivo: lanzamiento.cpp
 * Descripción: A partir de la velocidad (m/s), el ángulo de elevación (grados),
 *              el angulo de rotación (grados) y la posición del cañón (x/y).
 *              Calcular el tiempo de vuelo, la altura máxima, el alcance y el impacto.
 *              Además, introducir la localización del objetivo y distancias de
 *              impacto para calcular la distancia del impacto al objetivo.
 * Autor: fblupi
 */

#include <iostream> // cin, cout, endl
#include <cmath>    // sin, cos, pow, sqrt

using namespace std;

int main() {
    double vel, ange, angr, xi, yi; // Declaramos la velocidad, los ángulos de elevación y rotación en grados y las coordenadas de la posición inicial
    cout << "Introduzca dos valores con la posición del cañón (x y): ";
    cin >> xi >> yi;
    cout << "Introduzca la velocidad de lanzamienteo (m/s:) ";
    cin >> vel;
    if (vel < 0)
        cout << "Error. Velocidad inicial debe ser positiva." << endl;
    if (vel >= 0) {
         cout << "Introduzca el ángulo de elevación en grados (0-90): ";
         cin >> ange;
         if (ange <= 0 || ange >= 90)
            cout << "Error. Elevación debe estar entre 0 y 90." << endl;
         if (ange > 0 && ange < 90) {
             cout << "Introduzca rotación: ";
             cin >> angr;
             double angra; // Declaramos el angra para el ángulo de rotación que utilizaremos finalmente que estará entre -180 y 180 grados
             if (angr >= -180 && angr <= 180) // Si el ángulo está entre -180 y 180 (incluidos estos), no hará falta sumarle ni restarle nada
                 angra = angr;
             if (angr < -180) // Si el ángulo es menor que -180 sumaremos 360
                 angra = angr + 360;
             if (angr > 180) // Si el ángulo es mayor que 180 restaremos 360
                 angra = angr - 360;
             cout << "---------- Valores de entrada ----------" << endl;
             cout << "Posición del cañón: " << xi << "," << yi << endl;
             cout << "Ángulo de elevación: " << ange << endl;
             cout << "Ángulo de rotación: " << angra << endl;
             cout << "Velocidad inicial: " << vel << endl;
             double t, h, xmax, anre, anrr, xf, yf; // Declaramos el tiempo, la altura, la distancia, los ángulos en radianes y las coordenadas de la posición final
             const double g = 9.80665, pi = 3.141592659; // pi es una aproximación de su valor real, por lo que no convertirá con precisión absoluta un ángulo
             // C++ trabaja con radianes en vez de con grados y aquí convertimos nuestro ángulo a radianes
             anre = ange * pi / 180; // Conversión a radianes del ángulo de elevación
             anrr = angr * pi / 180; // Conversión a radianes del ángulo de rotación
             t = 2 * vel * sin(anre) / g;           // Fórmula tiempo
             h = pow(vel * sin(anre), 2) / (2 * g); // Fórmula altura
             xmax = vel * vel * sin(2 * anre) / g;  // Fórmula alcance
             xf = xi + xmax * sin(anrr);            // Fórmula coordenada x final
             yf = yi + xmax * cos(anrr);            // Fórmula coordenada y final
             cout << "---------- Resultado de disparo ----------" << endl;
             cout << "Tiempo de vuelo: " << t << " segundos." << endl;
             cout << "Altura máxima: " << h << " metros." << endl;
             cout << "Alcance: " << xmax << " metros." << endl;
             cout << "Impacto: " << xf << "," << yf << endl;
             double d, xt, yt, d0, d1, da; // Declaramos las coordenadas de la localizaci�n del objetivo, las distancias de impacto, la distancia del impacto al objetivo y un auxiliar que utilizaremos
             cout << "---------- Comprobación de objetivo ----------" << endl;
             cout << "Introduzca localización del objetivo: ";
             cin >> xt >> yt;
             cout << "Introduzca distancias de impacto: ";
             cin >> d0 >> d1;
             if (d0 > d1) { // Para que están ordenados d1 tendrá que ser mayor que d0, si no es así cambiaremos el valor de las variables con la ayuda de otra variable auxiliar para no perder ningún valor
                 da = d0;
                 d0 = d1;
                 d1 = da;
             }
             d = sqrt(pow((xf - xt), 2) + pow((yf - yt), 2)); // Fórmula de distancia al objetivo
             if (d < d0)
                cout << "Distancia al objetivo: " << d << " -> " << "impacto directo." << endl;
             if (d >= d0 && d <= d1)
                cout << "Distancia al objetivo: " << d << " -> " << "impacto parcial." << endl;
             if (d > d1)
                cout << "Distancia al objetivo: " << d << " -> " << "no hay impacto." << endl;
         }
    }
}
