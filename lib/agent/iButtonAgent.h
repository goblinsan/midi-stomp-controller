#ifndef MIDI_STOMP_CONTROLLER_IBUTTONAGENT_H
#define MIDI_STOMP_CONTROLLER_IBUTTONAGENT_H


#include "iButton.h"

class iButtonAgent {
public:
    virtual ~iButtonAgent() = default;

    explicit iButtonAgent(iButton &b) : b(b) {}

    virtual bool isSwitched() = 0;

    virtual bool isDown() = 0;

    virtual int onPress() = 0;

    virtual int onRelease() = 0;

protected:
    iButton &b;

};


#endif //MIDI_STOMP_CONTROLLER_IBUTTONAGENT_H
