#ifndef MIDI_STOMP_CONTROLLER_IBUTTON_H
#define MIDI_STOMP_CONTROLLER_IBUTTON_H
#include <Arduino.h>

class iButton {
public:
    virtual ~iButton() = default;
    virtual int readState() = 0;
    virtual bool isSwitched() = 0;
    virtual bool isDown() = 0;
};

#endif //MIDI_STOMP_CONTROLLER_IBUTTON_H
