#include <iostream>
#include "Rn.h"

using namespace std;

void RnVectorSpace() {
    // Aquí puedes implementar la lógica para el espacio vectorial Rn
    cout << "Implementando el espacio vectorial Rn..." << endl;
    RnVector v1(0, -6.21, 2.71); // Vector en R^3
    RnVector v2(1.41, 0, -3.14,5,-6); // Otro vector en R^5
    v1.printVector();
    v2.printVector();
    // Ejemplo de operaciones con vectores en Rn
    // Puedes agregar más funcionalidades según sea necesario
}