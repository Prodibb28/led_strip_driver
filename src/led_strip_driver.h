#ifndef RGB_DRIVER_H
#define RGB_DRIVER_H
#include <inttypes.h>
#include <Arduino.h>

class RGBdriver
{
  public:
    
  
    RGBdriver(uint8_t _clkPin, uint8_t _dataPin);
    void begin();
    void set_brightness(uint8_t percent);
    void set_color(uint8_t red, uint8_t green, uint8_t blue);
    void clear(); // Una función útil para apagar todo rápido
    void end();

  private:
    private:
    uint8_t _clkPin;
    uint8_t _dataPin;
    float _brightness;

    void send_32_bits(uint32_t data);
    void send_header(); // Antes era Send32Zero
    void generate_clock_pulse(); // Antes era ClkRise
    uint8_t calculate_anticode(uint8_t color_byte); // Antes era TakeAntiCode
};

#endif
