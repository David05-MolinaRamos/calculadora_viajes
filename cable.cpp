#include <iostream>
using namespace std;


int main(){
int revoluciones = 1000;

cout << " Direccion en la RAM: " << &revoluciones << endl;

int* conector = &revoluciones;
*conector = 3000;

cout << "Revoluciones actuales: " << revoluciones << endl;


    return 0;
}