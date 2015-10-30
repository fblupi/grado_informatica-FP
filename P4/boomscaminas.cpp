/*
 * Archivo: boomscaminas.cpp
 * Descripción: Juego que consiste en despejar todas las casillas sin minas de un tablero
 * Autor: fblupi
 */

#include <iostream> // cin, cout
#include <string>   // string
#include <vector>   // vector
#include <cstdlib>  // rand, srand
#include <ctime>    // time
#include <locale>   // locale, toupper

using namespace std;

// Variables globales
#define MIN_FILAS 5
#define MAX_FILAS 20
#define MIN_COLUMNAS 5
#define MAX_COLUMNAS 20
#define MIN_MINAS 5
#define TAPADA_SIN_MINA 0
#define TAPADA_CON_MINA 9
#define ABIERTA_SIN_MINA 10
#define ABIERTA_CON_MINA 19
#define MARCADA_SIN_MINA 20
#define MARCADA_CON_MINA 29

string toUpper(string s) { // Convertir un string a mayúsculas (no funciona con tildes)
    locale loc;
    string str = s;
    for (int i = 0; i < str.length(); i++)
        str[i] = toupper(str[i], loc);
    return str;
}

void mensajeBienvenida() {
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "   BOOMSCAMINAS v1.0                                           by fblupi   " << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "¡Bienvenido al boomscaminas!" << endl;
    cout << "¿Estás preparado para pasar un buen rato? ¡Allá vamos!" << endl;
}

void mensajeDespedida() {
    cout << endl;
    cout << "Gracias por haber jugado al Boomscaminas. Espero que te hayas divertido." << endl;
    cout << "¡Hasta luego! :)" << endl;
}

void seleccionDificultad(int &f, int &c, int &m) {
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "   SELECCIÓN DE DIFICULTAD" <<endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Introduce número de filas: ";
    cin >> f;
    while (f < MIN_FILAS || f > MAX_FILAS) { // Mensaje de error para filas
        if (f < MIN_FILAS) // Pocas filas
            cout << "¿Es que eres un duende? ¡Ese tablero es muy pequeño!" << endl;
        if (f > MAX_FILAS) // Muchas filas
            cout << "Jugar un poco está bien, pero tampoco te pases. ¡Ese tablero es muy grande!" << endl;
        cout << " > Introduce como mínimo " << MIN_FILAS << " filas y como máximo " << MAX_FILAS << "." << endl;
        cout << endl;
        cout << "Introduce número de filas: ";
        cin >> f;
    }
    cout << endl;
    cout << "Introduce número de columnas: ";
    cin >> c;
    while (c < MIN_COLUMNAS || c > MAX_COLUMNAS) { // Mensaje de error para columnas
        if (c < MIN_COLUMNAS) // Pocas columnas
            cout << "¿Es que eres un duende? ¡Ese tablero es muy pequeño!" << endl;
        if (c > MAX_COLUMNAS) // Muchas columnas
            cout << "Jugar un poco está bien, pero tampoco te pases. ¡Ese tablero es muy grande!" << endl;
        cout << " > Introduce como mínimo " << MIN_COLUMNAS << " columnas y como máximo " << MAX_COLUMNAS << "." << endl;
        cout << endl;
        cout << "Introduce número de columnas: ";
        cin >> c;
    }
    cout << endl;
    cout << "Introduce número de minas: ";
    cin >> m;
    while (m < MIN_MINAS || m > (f * c / 2)) { // Mensaje de error para número de minas inapropiado
        if (m < MIN_MINAS) // Pocas minas
            cout << "¡Así hasta mi perro con los ojos vendados puede ganar!" << endl;
        if (m > f * c / 2) // Muchas minas
            cout << "Si tan bueno eres, deja este juego y apúntate a un campeonato." << endl;
        cout << "Ese número de minas no es el apropiado:" << endl;
        cout << " > No puedes poner menos de " << MIN_MINAS << " minas." << endl;
        cout << " > No puedes poner más de la mitad de las casillas infectadas." << endl;
        cout << endl;
        cout << "Introduce número de minas: ";
        cin >> m;
    }
    cout << "---------------------------------------------------------------------------" << endl;
    if (f * c / m >= 20) // Criterio de dificultad: fácil
        cout << "   DIFICULTAD: Fácil" << endl;
    if (f * c / m < 20 && f * c / m >= 5) // Criterio de dificultad: media
        cout << "   DIFICULTAD: Media" << endl;
    if (f * c / m < 5) // Criterio de dificultad: difícil
        cout << "   DIFICULTAD: Difícil" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Tamaño: " << f << "x" << c << endl; // Imprime filas x columnas
    cout << "Minas: " << m << endl; // Imprime minas
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "   ¡QUE EMPIECE EL JUEGO!" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
}

void generacionMatriz(const int m, vector<vector<int> > &matriz) {
    // GENERACIÓN DE MINAS
    srand (time(0));  // Inicializamos la semilla
    for (int i = 0; i < m; i++) { // Repetimos procedimiento hasta llegar al número de minas
        int posfil = rand() % matriz.size();    // Crea número aleatoria para las filas
        int poscol = rand() % matriz[0].size(); // Crea número aleatoria para las columnas
        while (matriz[posfil][poscol] == TAPADA_CON_MINA) {   // Repetimos creación si hay bomba
            posfil = rand() % matriz.size();
            poscol = rand() % matriz[0].size();
        }
        matriz[posfil][poscol] = TAPADA_CON_MINA; // Creamos mina
    }
    // GENERACIÓN DE NÚMEROS ALREDEDOR DE MINAS
    for (int a = 0; a < matriz.size(); a++) { // Recorre las filas
        for (int b = 0; b < matriz[0].size(); b++) { // Recorre las columnas
            int cont = 0; // Iniciamos contador que contará las minas de alrededor
            for (int x = a - 1; x < a + 2; x++) { // Nos desplazaremos de arriba a abajo en la matriz
                for (int y = b - 1; y < b + 2; y++) { // Nos movemos de izquierda a derecha en la matriz
                    if (x >= 0 && x < matriz.size() && y >= 0 && y < matriz[0].size()) // Comprobamos que estamos dentro de la matriz
                        if (matriz[x][y] == TAPADA_CON_MINA) // Casilla con boma, aumenta contador
                            cont++;
                }
            }
            if (matriz[a][b] != TAPADA_CON_MINA) // Aplicamos esto solo a las casillas sin mina
                matriz[a][b] = cont;
        }
    }
}

void imprimirTablero(const vector<vector<int> > &matriz) {
    cout << "    ";
    for (int i = 0; i < matriz[0].size(); i++) // Recorre las columnas
        if (i < 10)  // Un número de dos cifras ocupa solo un espacio. Para no descuadrar el tablero lo escribiremos
            cout << " " << i << " "; // Imprime coordenada
        else
            cout << i << " "; // Imprime coordenada
    cout << endl;
    cout << "   ";
    for (int i = 0; i < matriz[0].size(); i++) // Recorre las columnas
        cout << "---";
    cout << "-" << endl;
    for (int i = 0; i < matriz.size(); i++) { // Recorre las filas
        if (i < 10)  // Un número de dos cifras ocupa solo un espacio. Para no descuadrar el tablero lo escribiremos
            cout << " " << i << " |"; // Imprime coordenada
        else
            cout << i << " |"; // Imprime coordenada
        for (int iter = 0; iter < matriz[0].size(); iter++) { // Recorre las columnas
            cout << " ";
            if (matriz[i][iter] >= TAPADA_SIN_MINA && matriz[i][iter] <= TAPADA_CON_MINA) // Casilla oculta
                cout << "*";
            if (matriz[i][iter] >= MARCADA_SIN_MINA && matriz[i][iter] <= MARCADA_CON_MINA) // Casilla marcada
                cout << "?";
            if (matriz[i][iter] == ABIERTA_SIN_MINA) // Casilla sin mina
                cout << " ";
            if (matriz[i][iter] > ABIERTA_SIN_MINA && matriz[i][iter] < ABIERTA_CON_MINA) // Casilla con minas alrededor
                cout << matriz[i][iter] - 10;
            if (matriz[i][iter] == ABIERTA_CON_MINA) // Casilla con mina
                cout << "X";
            cout << "|";
        }
        cout << endl;
    }
    cout << "   ";
    for (int i = 0; i < matriz[0].size(); i++) // Recorre las columnas
        cout << "---";
    cout << "-" << endl;
}

void imprimirTableroResuelto(const vector<vector<int> > &matriz) { // Se imprimirá al fin de la partida si se requiere
    cout << "    ";
    for( int i = 0; i < matriz[0].size(); i++) // Recorre las columnas
        if (i < 10)  // Un número de dos cifras ocupa solo un espacio. Para no descuadrar el tablero lo escribiremos
            cout << " " << i << " "; // Imprime coordenada
        else
            cout << i << " "; // Imprime coordenada
    cout << endl;
    cout << "   ";
    for (int i = 0; i < matriz[0].size(); i++) // Recorre las columnas
        cout << "---";
    cout << "-" << endl;
    for (int i = 0; i < matriz.size(); i++) // Recorre las filas
    {
        if (i < 10)  // Un número de dos cifras ocupa solo un espacio. Para no descuadrar el tablero lo escribiremos
            cout << " " << i << " |"; // Imprime coordenada
        else
            cout << i << " |"; // Imprime coordenada
        for (int iter = 0; iter < matriz[0].size(); iter++) // Recorre las columnas
        {
            cout << " ";
            if ((matriz[i][iter] >= TAPADA_SIN_MINA && matriz[i][iter] < TAPADA_CON_MINA)       // La casilla puede estar tapada
                || (matriz[i][iter] >= ABIERTA_SIN_MINA && matriz[i][iter] < ABIERTA_CON_MINA)  // La casilla puede estar destapada
                || (matriz[i][iter] >= MARCADA_SIN_MINA && matriz[i][iter] < MARCADA_CON_MINA)) // La casilla puede estar marcada
                cout << " "; // Casilla sin mina
            if (matriz[i][iter] == TAPADA_CON_MINA || matriz[i][iter] == ABIERTA_CON_MINA || matriz[i][iter] == MARCADA_CON_MINA) cout << "X"; // Casilla con mina
            cout << "|";
        }
        cout << endl;
    }
    cout << "   ";
    for (int i = 0; i < matriz[0].size(); i++) // Recorre las columnas
        cout << "---";
    cout << "-" << endl;
}

void imprimirSolucion(const vector<vector<int> > matriz) { // Preguna imprimir tablero resuelto
    string respuesta; // Declaramos cadena para respuesta
    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << endl;
    bool confirm = false; // Confirmación de código bien introducido
    while (confirm == false) {
        cout << "¿Quieres ver la solución del tablero? ";
        cin >> respuesta;
        if (toUpper(respuesta) == "SI" || toUpper(respuesta) == "SÍ" || toUpper(respuesta) == "Sí" || toUpper(respuesta) == "S"
            || toUpper(respuesta) == "YES" || toUpper(respuesta) == "Y") { // LECTURA AFIRMATIVA
            confirm = true; // No vuelve a preguntar si quiere ver la solución del tablero
            cout << endl;
            cout << "La solución es:" << endl;
            cout << endl;
            imprimirTableroResuelto(matriz); // Imprime solución
        }
        if (toUpper(respuesta) == "NO" || toUpper(respuesta) == "N") { // LECTURA NEGATIVA
            confirm = true; // No vuelve a preguntar si quiere ver la solución del tablero
        }
    }
}

void expandir(const int f, const int c, vector<vector<int> > &matriz) {
    for (int a = f - 1; a < f + 2; a++) { // Recorre alrededor de la casilla, de arriba a abajo
        for (int b = c - 1; b < c + 2; b++) { // Recorre alrededor de la casilla, de derecha a izquierda
            if (a >= 0 && a < matriz.size() && b >= 0 && b < matriz[0].size()) { // Comprobamos que estamos dentro de la matriz
                if (matriz[a][b] == 0) { // Si la casilla no tiene minas alrededor
                    matriz[a][b] += 10; // Abre la casilla
                    if (matriz[a][b] == 10)
                        expandir(a, b, matriz); // Repetimos expansión
                }
                if (matriz[a][b] > 0 && matriz[a][b] <= 9) // Si la casilla tiene minas alrededor o es mina
                    matriz[a][b] += 10; // Abre la casilla
            }
        }
    }
}

void abrir(const int f, const int c, vector<vector<int> > &matriz) {
    if (matriz[f][c] >= TAPADA_SIN_MINA && matriz[f][c] <= TAPADA_CON_MINA) { // Si la casilla está cerrada la abrimos
        matriz[f][c] += 10; // Abre casilla
        if (matriz[f][c] == ABIERTA_SIN_MINA)
            expandir(f, c, matriz); // Expandimos si la casilla no tiene minas alrededor
    }
}

void marcar(const int f, const int c, vector<vector<int> > &matriz, int &marcada) {
    matriz[f][c] += 20; // Marcamos casilla
    marcada = 1; // Marcar para que no se ejecute la función desmarcar y deshaga el cambio
}

void desmarcar(const int f, const int c, vector<vector<int> > &matriz) {
    matriz[f][c] -= 20; // Desmarcamos casilla
}

void comprobarEstado(const vector<vector<int> > &matriz, bool &victoria, bool &derrota)
{
    int tapadas = 0; // Definimos variable de casillas SIN mina tapadas
    int marcadas = 0; // Definimos variable de casillas SIN mina marcadas
    for (int a = 0; !derrota && a < matriz.size(); a++) { // Recorre las filas
        for (int b = 0; !derrota && b < matriz[0].size(); b++) { // Recorre las columnas
            if (matriz[a][b] == ABIERTA_CON_MINA)
                derrota = true; // DERROTA. Si encuentra mina destapada
            if (matriz[a][b] >= TAPADA_SIN_MINA && matriz[a][b] < TAPADA_CON_MINA)
                tapadas++; // Aumenta la variable de casillas sin mina tapadas
            if (matriz[a][b] >= MARCADA_SIN_MINA && matriz[a][b] < MARCADA_CON_MINA)
                marcadas++; // Aumenta la variable de casillas sin mina marcadas
        }
    }
    if (tapadas == 0 && marcadas == 0)
        victoria = true;  // VICTORIA. Si no hay casillas sin mina tapadas ni marcadas
}

int main() {
    mensajeBienvenida(); // Imprime mensaje de bienvenida
    int filas, columnas, minas; // Declaramos variables
    seleccionDificultad(filas, columnas, minas); // Damos valor a las variables
    vector<vector<int> >matriz(filas, vector<int> (columnas)); // Creamos nuestra matriz que es un vector de vectores enteros
    generacionMatriz(minas, matriz); // Damos valores a las "casillas"
    imprimirTablero(matriz); // Imprime tablero
    bool victoria = false; // Declaramos booleano de victoria con valor incicial falso
    bool derrota = false; // Declaramos booleano de derrota con valor incicial falso
    while (victoria == false && derrota == false) { // Repetiremos el proceso mientras no hayamos perdido ni ganado
        string jugada; // Declaramos la cadena que indica jugada
        int x, y; // Declaramos coordenadas
        int marcada = 0; // Cuando no marcada aún el valor será 0, cuando se ha maracado la función la cambiará a 1
        cout << endl;
        cout << "Dime acción y posición (fil y col): ";
        cin >> jugada >> x >> y; // Lee jugada y coordenadas
        while (x < 0 || x>=matriz.size() || y < 0 || y >= matriz[0].size()) { // Repetimos con coordenadas incorrectas
            cout << "Dime acción y posición (fil y col): ";
            cin >> jugada >> x >> y; // Lee jugada y coordenadas
        }
        if (toUpper(jugada) == "ABRIR" || toUpper(jugada) == "A") // Lectura de la función abrir
            abrir(x,y,matriz);
        if (toUpper(jugada) == "MARCAR" || toUpper(jugada) == "M") { // Lectura de la función marcar
            if (matriz[x][y] >= TAPADA_SIN_MINA && matriz[x][y] <= TAPADA_CON_MINA)
                marcar(x, y, matriz, marcada); // Para casilla tapada. marcar
            if (matriz[x][y] >= MARCADA_SIN_MINA && matriz[x][y] <= MARCADA_CON_MINA && marcada == 0)
                desmarcar(x, y, matriz); // Para casilla marcada. desmarcar
        }
        cout << endl;
        comprobarEstado(matriz, victoria, derrota); // Comprueba estado para ver si itera al bucle
        if (victoria == false && derrota == false)
            imprimirTablero(matriz);  // Si se sigue en juego imprime tablero
    }
    cout << endl;
    if (derrota == true) // Condición partida perdida
        cout << "Lo siento. Has perdido." << endl;
    if (victoria == true) // Condición partida ganada
        cout << "¡Enhorabuena! Has ganado" << endl;
    cout << "El tablero ha quedado así:" << endl;
    cout << endl;
    imprimirTablero(matriz); // Imprime tablero final
    imprimirSolucion(matriz); // Pregunta imprimir o no la solución del tablero
    mensajeDespedida(); // Imprime mensaje de despedida
}
