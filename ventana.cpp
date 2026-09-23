#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>
#include <fstream>
#include <QDoubleValidator>
#include <QIntValidator>

using namespace std;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QWidget mi_ventana;
    mi_ventana.resize(600, 500);
    mi_ventana.setWindowTitle("calculadora de Sentra para Uber");

    int viajes_totales = 0;
    int viaje_actual = 1;
    double ganancias_turno = 0.0;
    QString nombre_turno = "";


    QVBoxLayout *layout = new QVBoxLayout(&mi_ventana);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15); 
    QLabel etiqueta_turno("Nombre del Turno (ej. Lunes):", &mi_ventana);
    etiqueta_turno.setAlignment(Qt::AlignCenter);
    
    QLineEdit caja_turno(&mi_ventana);
    caja_turno.setAlignment(Qt::AlignCenter);
    caja_turno.setFixedSize(300, 40);

    QLabel etiqueta_viajes("¿Cuántos viajes registrarás?:", &mi_ventana);
    etiqueta_viajes.setAlignment(Qt::AlignCenter);
    
    QLineEdit caja_viajes(&mi_ventana);
    caja_viajes.setAlignment(Qt::AlignCenter);
    caja_viajes.setFixedSize(300, 40);
    caja_viajes.setValidator(new QIntValidator(1, 50, &mi_ventana)); 

    QPushButton boton_iniciar("Iniciar Turno", &mi_ventana);
    boton_iniciar.setFixedSize(300, 50);

    QLabel etiqueta("Costo del Viaje:", &mi_ventana);
    etiqueta.setAlignment(Qt::AlignCenter);
    
    QLineEdit caja_costo(&mi_ventana);
    caja_costo.setAlignment(Qt::AlignCenter);
    caja_costo.setFixedSize(300, 40);

    QLabel etiqueta_km("Kilometros recorridos:", &mi_ventana);
    etiqueta_km.setAlignment(Qt::AlignCenter);
    
    QLineEdit caja_km(&mi_ventana);
    caja_km.setAlignment(Qt::AlignCenter);
    caja_km.setFixedSize(300, 40);

    caja_costo.setValidator(new QDoubleValidator(0.0, 999.0, 2, &mi_ventana));
    caja_km.setValidator(new QDoubleValidator(0.0, 999.0, 2, &mi_ventana));

    QPushButton boton("Registrar Viaje", &mi_ventana);
    boton.setFixedSize(300, 50);

    QLabel etiqueta_resultado("Ganancia libre: $0.00", &mi_ventana);
    etiqueta_resultado.setAlignment(Qt::AlignCenter);

    layout->addWidget(&etiqueta_turno);
    layout->addWidget(&caja_turno);
    layout->addWidget(&etiqueta_viajes);
    layout->addWidget(&caja_viajes);
    layout->addWidget(&boton_iniciar);

    layout->addWidget(&etiqueta);
    layout->addWidget(&caja_costo);
    layout->addWidget(&etiqueta_km);
    layout->addWidget(&caja_km);
    layout->addWidget(&boton);
    layout->addWidget(&etiqueta_resultado);

    QObject::connect(&boton_iniciar, &QPushButton::clicked, [&]() {
        nombre_turno = caja_turno.text();
        viajes_totales = caja_viajes.text().toInt();
        etiqueta_turno.hide();
        caja_turno.hide();
        etiqueta_viajes.hide();
        caja_viajes.hide();
        boton_iniciar.hide();
        etiqueta.setText("Costo del Viaje (1 de " + QString::number(viajes_totales) + "):");
        
        etiqueta.show();
        caja_costo.show();
        etiqueta_km.show();
        caja_km.show();
        boton.show();
        etiqueta_resultado.show();
    });
    QObject::connect(&boton, &QPushButton::clicked, [&]() {
        QString valor = caja_costo.text();
        double costo_real = valor.toDouble();
        
        QString valor_km = caja_km.text();
        double kilometros = valor_km.toDouble();
        
        double gasto_gasolina = kilometros * 2.0;
        double ganancia_final = (costo_real * 0.80) - gasto_gasolina;
        
        ganancias_turno += ganancia_final;
        ofstream archivo("corte_turno.txt", ios::app);
        if(archivo.is_open()) {
            archivo << "Turno " << nombre_turno.toStdString() << " | Viaje " << viaje_actual << " - cobro: $" << costo_real << " | Libre: $" << ganancia_final << endl;
            archivo.close();
            caja_costo.clear();
            caja_km.clear();
        }

        viaje_actual++;
        if (viaje_actual <= viajes_totales) {
            etiqueta.setText("Costo del Viaje (" + QString::number(viaje_actual) + " de " + QString::number(viajes_totales) + "):");
            etiqueta_resultado.setText("Ganancia del último viaje: $" + QString::number(ganancia_final));
        } else {
            caja_costo.hide();
            caja_km.hide();
            etiqueta.hide();
            etiqueta_km.hide();
            boton.hide();
            
        
            etiqueta_resultado.setText("Turno terminado  Ganancia total: $" + QString::number(ganancias_turno));
        
            ofstream archivo_final("corte_turno.txt", ios::app);
            if(archivo_final.is_open()) {
                archivo_final << ">>> Total en el turno" << nombre_turno.toStdString() << ": $" << ganancias_turno << " <<<\n" << endl;
                archivo_final.close();
            }
        }
    });
    etiqueta.hide();
    caja_costo.hide();
    etiqueta_km.hide();
    caja_km.hide();
    boton.hide();
    etiqueta_resultado.hide();

    
    mi_ventana.setStyleSheet(
        "QWidget { background-color: #040404; color: #ffffff; font-family: Arial; font-size: 18px; }"
        "QPushButton { background-color: #f55c88; color: white; border-radius: 8px; font-weight: bold; font-size: 20px; }"
        "QLineEdit { background-color: #333333; border: 2px solid #555; border-radius: 6px; padding: 5px; font-size: 22px; color: #e1e7ec; }"
        "QLabel { font-weight: bold; }"
    );

    mi_ventana.show();

    return app.exec();
}