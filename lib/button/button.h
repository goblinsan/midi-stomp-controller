#ifndef MIDI_STOMP_CONTROLLER_BUTTON_H
#define MIDI_STOMP_CONTROLLER_BUTTON_H

#include <Arduino.h>

class button {
private:
    unsigned long debounceDelay = 50;
    unsigned long lastDebounceTime = 0;
    bool isPullUp = true;
    int16_t defaultState = HIGH;
    int16_t currentState = HIGH;
    int16_t lastState = HIGH;
protected:
    int8_t switch_index = 0;
public:

    explicit button(int8_t switch_index);

    explicit button(int8_t switch_index, bool isPullUp);

    virtual int16_t readState() const;

    bool isSwitched();

    bool isDown() const;

};

#endif //MIDI_STOMP_CONTROLLER_BUTTON_H