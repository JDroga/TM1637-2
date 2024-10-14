// TM1637.cpp

#include "TM1637.h"

// Constructor: Definir los pines SCLK y DIO
TM1637::TM1637(PinName sclk, PinName dio) : sclk(sclk), dio(dio) {}

// Encender el display
void TM1637::power_on() {
    send_byte(0x8F);  // Enviar el comando de encendido
}

// Apagar el display
void TM1637::power_off() {
    send_byte(0x80);  // Enviar el comando de apagado
}

// Enviar datos al display (número de 0 a 9999)
void TM1637::send_data(int number) {
    condicion_start();
    send_byte(0x40);  // Modo de escritura
    condicion_stop();
    condicion_start();
    send_byte(0xC0);  // Dirección del display

    // Descomponer el número en dígitos y enviarlos de izquierda a derecha
    for (int i = 3; i >= 0; i--) {
        int digit = number % 10;
        send_byte(digitToSegment[digit]);  // Enviar dígito al display
        number /= 10;
    }
    condicion_stop();
    condicion_start();
    send_byte(0x88 + 1);  // Ajustar el brillo
    condicion_stop();
}

// Enviar un byte al TM1637
void TM1637::send_byte(char data) {
    dio.output();
    for (int i = 0; i < 8; i++) {
        sclk = 0;
        dio = (data & 0x01) ? 1 : 0;
        data >>= 1;
        sclk = 1;
    }
    dio.input();
    sclk = 0;
    wait_us(1);
    if (dio == 0) {
        sclk = 1;
        sclk = 0;
    }
}

// Función de inicio del protocolo
void TM1637::condicion_start(void) {
    sclk = 1;
    dio.output();
    dio = 1;
    wait_us(1);
    dio = 0;
    sclk = 0;
}

// Función de parada del protocolo
void TM1637::condicion_stop(void) {
    sclk = 0;
    dio.output();
    dio = 0;
    wait_us(1);
    sclk = 1;
    dio = 1;
}
