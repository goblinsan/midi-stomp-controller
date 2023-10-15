#include "button.h"

button::button(int8_t i) : switch_index{i} {
}

button::button(int8_t i, bool p) : switch_index{i}, isPullUp{p} {
    if (!isPullUp) {
        defaultState = LOW;
        currentState = LOW;
        lastState = LOW;
    }
}

int16_t button::readState() const{
    return digitalRead(switch_index);
}

bool button::isSwitched() {
    if (currentState != lastState) {
        if ((millis() - lastDebounceTime) > debounceDelay) {
            lastState = currentState;
            lastDebounceTime = millis();
            return true;
        }
    }
    return false;
}

bool button::isDown() const {
    return currentState != defaultState;
}

