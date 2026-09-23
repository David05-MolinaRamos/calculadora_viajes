#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

float calcular_gasolina(float kms, float rend, float precio){
    float litros = kms /  rend;
    return litros * precio;
}

int main(){
    float cobro_viaje;
    float kilometros;
    float costo_gasolina;
    float ganancia_neta;
    float rendimiento = 13.0;
    float precio_litro = 22.50;
    float comision_app;
    float total_turno = 0;
    char continuar;
cout << fixed << setprecision(2);
do{
    cout << "\n Dame el costo del cobro del viaje: " << endl;
    cin >> cobro_viaje;
    comision_app = cobro_viaje*0.20;
    cout << "=============" << endl;
    cout << "\n Dame los kilometros recorridos: " << endl;
    cin >> kilometros;
    cout << "====" << endl;

    costo_gasolina = calcular_gasolina(kilometros, rendimiento, precio_litro);

    ganancia_neta = cobro_viaje - (costo_gasolina+comision_app);
    total_turno = total_turno + ganancia_neta;
    cout << "\n La plataforma retuvo: $" << comision_app << endl;
    cout << " La ganancia neta de este viaje es: $" << ganancia_neta << endl;
    if(ganancia_neta < 30.00){
        cout << "Alerta: Viaje de muy baja rentabilidad para el vehiculo." << endl;
    } else{
        cout << "Este fue un viaje rentable. " << endl;
    }
    cout << "=========" << endl;
    cout << "\n Registrar otro viaje? (s/n): ";
    cin >> continuar;
} while (continuar == 's');
cout << "==========" << endl;
cout << "Ganancias Total del turno: $" << total_turno << endl;
    
ofstream ticket("corte_turno.txt", ios::app);
ticket << "\n Nuevo turno " << endl;
ticket << " Ganancias totales del Sentra: $" << total_turno << endl;
ticket.close();

    return 0;
}