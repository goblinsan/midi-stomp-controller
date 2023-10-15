#include "muxButton.h"

muxButton::muxButton(int8_t i, int8_t s, const int *sp, bool pullUp) : sig_pin{s}, button(i, pullUp) {
    this->select_pins = new int[4];
    for (int j = 0; j < 4; j++) {
        this->select_pins[j] = sp[j];
    }
}

int16_t muxButton::readState() const {
    for (int k = 0; k < 4; k++) {
        int mask = 1 << k;
        int masked_n = switch_index & mask;
        int bit = masked_n >> k;
        digitalWrite(select_pins[k], bit);
    }
    return digitalRead(sig_pin);
}
