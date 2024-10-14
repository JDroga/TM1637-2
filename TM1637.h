#ifndef TM1637_H
#define TM1637_H

#include "mbed.h"

class TM1637 {
public:
    // Constructor
    TM1637(PinName sclk, PinName dio);

    // Encender o apagar el display
    void power_on();
    void power_off();

    // Enviar los datos para mostrar números
    void send_data(int number);

private:
    DigitalOut sclk;   // Pin de reloj
    DigitalInOut dio;  // Pin de datos

    const char digitToSegment[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

    // Funciones internas para el control del display
    void condicion_start(void);
    void condicion_stop(void);
    void send_byte(char data);
};

#endif
