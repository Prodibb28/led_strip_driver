# RGB_driver (P9813)

Librería optimizada para el controlador de tiras LED **P9813** (comúnmente usado en módulos Open-Smart). Esta versión ha sido refactorizada para ofrecer una interfaz limpia, funcional y fácil de integrar en proyectos de firmware.



## Características 🚀
* **Control de Brillo Global:** Nueva función `set_brightness(percent)` que escala automáticamente los canales RGB.
* **Abstracción de Protocolo:** Manejo interno del bit-banging y los anti-codes del chip P9813.
* **Interfaz Simple:** Nombres de funciones intuitivos y consistentes.
* **Eficiente:** Optimizado para arquitecturas de 8 y 32 bits (Arduino, ESP32, STM32).

---

## Instalación 🛠️

1. Descarga este repositorio como un archivo `.zip`.
2. En el IDE de Arduino, ve a **Programa > Incluir Librería > Añadir librería .ZIP...**
3. Selecciona el archivo descargado.

---

## Ejemplo de Uso Rápido 💻

```cpp
#include <RGB_driver.h>

// Definición de pines
const uint8_t CLK_PIN = 4;
const uint8_t DATA_PIN = 5;

// Instancia de la clase
RGBdriver led(CLK_PIN, DATA_PIN);

void setup() {
    led.begin();              // Configura pines como salida
    led.set_brightness(75);   // Establece brillo al 75%
}

void loop() {
    // Establecer color Morado (R, G, B)
    led.set_color(128, 0, 128); 
    delay(2000);
    
    // Apagar el LED
    led.clear();
    delay(1000);
}
```
---


## Referencia de la API

| Función | Parámetros | Descripción |
| :--- | :--- | :--- |
| `begin()` | Ninguno | Inicializa los pines de hardware como salida. |
| `set_brightness()` | `uint8_t percent` (0-100) | Ajusta el límite de intensidad global aplicado a los colores. |
| `set_color()` | `uint8_t r, g, b` (0-255) | Cambia el color actual calculando el brillo y los anti-codes. |
| `clear()` | Ninguno | Apaga el LED enviando un frame de ceros (0, 0, 0). |
| `end()` | Ninguno | Finaliza la comunicación enviando el header de cierre. |
