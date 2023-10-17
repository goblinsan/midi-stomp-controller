#ifndef MIDI_STOMP_CONTROLLER_BUTTONDEF_H
#define MIDI_STOMP_CONTROLLER_BUTTONDEF_H

#include "iButton.h"

class button : public iButton {
public:
    explicit button(int8_t i, bool p) : switch_index{i}, pullUp{p} {
    }

    explicit button(int8_t i) : button(i, true) {}

    bool isPullUp() override{
        return pullUp;
    }

    int readState() override {
        if (!initialized){
            setPins();
            initialized = true;
        }
        return digitalRead(switch_index);
    }

protected:
    int8_t switch_index = 0;
    bool pullUp = true;

private:
    bool initialized = false;
    void setPins() const {
        if (pullUp) {
            pinMode(switch_index, INPUT_PULLUP);
        } else {
            pinMode(switch_index, INPUT);
        }
    }
};

#endif
