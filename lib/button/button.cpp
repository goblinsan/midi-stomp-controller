#ifndef MIDI_STOMP_CONTROLLER_BUTTONDEF_H
#define MIDI_STOMP_CONTROLLER_BUTTONDEF_H

#include "iButton.h"

class button : public iButton {
public:
    explicit button(int8_t i) : switch_index{i} {}

    button(int8_t i, bool p) : switch_index{i}, isPullUp{p} {
        if (!isPullUp) {
            defaultState = LOW;
            currentState = LOW;
            lastState = LOW;
        }
    }

    int readState() override {
        currentState = digitalRead(switch_index);
        return currentState;
    }

    bool isSwitched() override {
        if (currentState != lastState) {
            unsigned long clockTime = millis();
            if ((clockTime - lastDebounceTime) > debounceDelay) {
                lastState = currentState;
                lastDebounceTime = clockTime;
                return true;
            }
        }
        return false;
    }

    bool isDown() override {
        return currentState != defaultState;
    }
private:
    const unsigned long debounceDelay = 50;
    unsigned long lastDebounceTime = 0;
    bool isPullUp = true;
    int defaultState = HIGH;
    int currentState = HIGH;
    int lastState = HIGH;
protected:
    int8_t switch_index = 0;
};

#endif
