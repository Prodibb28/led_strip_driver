/**
 * @file basic_usage_example.ino
 * @author Jaider Hoyos
 * @brief Ejemplo de uso de la librería RGBdriver para el chip P9813.
 * Muestra el control de colores y el ajuste de brillo global.
 */

#include "RGB_driver.h"

// Definición de pines (Ajusta según tu conexión)
#define CLK_PIN 4
#define DATA_PIN 5

// Instancia de la librería
RGBdriver led(CLK_PIN, DATA_PIN);

void setup() {

    led.begin();
    led.set_brightness(50);
}

void loop() {
    led.set_color(255, 0, 0);   // Rojo
    delay(1000);
    
    led.set_color(0, 255, 0);   // Verde
    delay(1000);
    
    led.set_color(0, 0, 255);   // Azul
    delay(1000);

    // 2. Efecto de "Respiración" (Fading)
    // Esto demuestra por qué abstraer el brillo fue una gran idea
    for (int b = 0; b <= 100; b++) {
        led.set_brightness(b);
        led.set_color(255, 255, 255); // Color blanco
        delay(20); // Ajusta la velocidad del efecto
    }
    
    for (int b = 100; b >= 0; b--) {
        led.set_brightness(b);
        led.set_color(255, 255, 255);
        delay(20);
    }

    delay(500);
}