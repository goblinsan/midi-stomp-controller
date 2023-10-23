#ifndef MIDI_STOMP_CONTROLLER_CONTROLLERDISPLAY_H
#define MIDI_STOMP_CONTROLLER_CONTROLLERDISPLAY_H

#include <Arduino.h>

#include <utility>
#include "midiStompTypes.h"
#include "Vector.h"

class controllerDisplay {
private:
    displayType *display;
public:
    explicit controllerDisplay(displayType *display) : display{display} {}
    void printText(bool isBig, int x, int y, const String &text);
    void printCheckMark(bool value);
    void updateDisplay(const int configState[8]);
    void sleep();
    void clear();
};

#endif //MIDI_STOMP_CONTROLLER_CONTROLLERDISPLAY_H
