#include "RGB_driver.h"


RGBdriver::RGBdriver(uint8_t clk_pin, uint8_t data_pin) {
    _clkPin = clk_pin;
    _dataPin = data_pin;
    _brightness = 1.0f;
}

void RGBdriver::begin() {
    pinMode(_clkPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    send_header();
}

void RGBdriver::set_brightness(uint8_t percent) {
    if (percent > 100) percent = 100;
    _brightness = percent / 100.0f;
}

void RGBdriver::set_color(uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t packet = 0;

    uint8_t adj_r = (uint8_t)(red   * _brightness);
    uint8_t adj_g = (uint8_t)(green * _brightness);
    uint8_t adj_b = (uint8_t)(blue  * _brightness);

    packet |= (uint32_t)0x03 << 30; // Start bits
    packet |= (uint32_t)calculate_anticode(adj_b) << 28;
    packet |= (uint32_t)calculate_anticode(adj_g) << 26;
    packet |= (uint32_t)calculate_anticode(adj_r) << 24;
    
    packet |= (uint32_t)adj_b << 16;
    packet |= (uint32_t)adj_g << 8;
    packet |= adj_r;

    send_32_bits(packet);
}

void RGBdriver::clear() {
    set_color(0, 0, 0);
}

void RGBdriver::end() {
    send_header();
}

// --- Métodos Privados (Abstracción del Protocolo) ---

void RGBdriver::generate_clock_pulse() {
    digitalWrite(_clkPin, LOW);
    delayMicroseconds(20); 
    digitalWrite(_clkPin, HIGH);
    delayMicroseconds(20);   
}

void RGBdriver::send_header() {
    send_32_bits(0x00000000);
}

uint8_t RGBdriver::calculate_anticode(uint8_t color_byte) {
    uint8_t checksum = 0;

    if ((color_byte & 0x80) == 0) checksum |= 0x02; 
    if ((color_byte & 0x40) == 0) checksum |= 0x01; 
    return checksum;
}

void RGBdriver::send_32_bits(uint32_t data) {
    for (uint8_t i = 0; i < 32; i++) {
        if ((data & 0x80000000) != 0) {
            digitalWrite(_dataPin, HIGH);
        } else {
            digitalWrite(_dataPin, LOW);
        }
        
        data <<= 1;
        generate_clock_pulse();
    }
}