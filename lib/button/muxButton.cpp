#ifndef MIDI_STOMP_CONTROLLER_MUXBUTTON
#define MIDI_STOMP_CONTROLLER_MUXBUTTON

#include "button.cpp"

class muxButton : public button {
public:

    muxButton(int8_t i, int8_t s, const int *sp, bool p = true) : sig_pin{s}, button(i, p) {
        this->select_pins = new int[4];
        for (int j = 0; j < 4; j++) {
            this->select_pins[j] = sp[j];
        }
    }

    int readState() override{
        if (!initialized){
            setPins();
            initialized = true;
        }
        for (int k = 0; k < 4; k++) {
            int mask = 1 << k;
            int masked_n = switch_index & mask;
            int bit = masked_n >> k;
            digitalWrite(select_pins[k], bit);
        }
        return digitalRead(sig_pin);
    }

private:
    int8_t sig_pin;
    int *select_pins;
    bool initialized = false;
    void setPins() const {
        if (pullUp) {
            pinMode(sig_pin, INPUT_PULLUP);
        } else {
            pinMode(sig_pin, INPUT);
        }
        for (int i = 0; i < 4; i++) {
            pinMode(select_pins[i], OUTPUT);
            digitalWrite(select_pins[i], LOW);
        }
    }
};

#endif