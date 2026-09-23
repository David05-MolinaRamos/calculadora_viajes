#include <iostream>
#include <string>
using namespace std;

class Auto{
    public: 
    string marca;
    int anio;
    float kilometraje_total;

void registrar_viaje(float kms){
kilometraje_total = kilometraje_total + kms;
cout << "Kilometraje del tablero: " << kilometraje_total << endl;
    }
};

int main(){
Auto mi_sentra;
mi_sentra.marca = "Nissan";
mi_sentra.anio = 2017;
mi_sentra.kilometraje_total = 180254;
mi_sentra.registrar_viaje(12.5);
mi_sentra.registrar_viaje(8.0);


    return 0;
}