#ifndef MIDI_STOMP_CONTROLLER_IBUTTON_H
#define MIDI_STOMP_CONTROLLER_IBUTTON_H
#include <Arduino.h>

class iButton {
public:
    virtual ~iButton() = default;
    virtual bool isPullUp() = 0;
    virtual int readState() = 0;
};

#endif //MIDI_STOMP_CONTROLLER_IBUTTON_H
