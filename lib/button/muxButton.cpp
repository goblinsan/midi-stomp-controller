#include "button.cpp"

class muxButton : public button {
public:

    muxButton(int8_t i, int8_t s, const int *sp, bool pullUp = true) : sig_pin{s}, button{i, pullUp} {
        this->select_pins = new int[4];
        for (int j = 0; j < 4; j++) {
            this->select_pins[j] = sp[j];
        }
    }

    int readState() override{
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
};

