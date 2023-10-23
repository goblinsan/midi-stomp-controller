#ifndef MIDI_STOMP_CONTROLLER_IBUTTONAGENT_H
#define MIDI_STOMP_CONTROLLER_IBUTTONAGENT_H

#include "iButton.h"
#include "midiStompTypes.h"

class iButtonAgent {
public:
    virtual ~iButtonAgent() = default;

    explicit iButtonAgent(iButton &b) : b(b) {}

    virtual buttonState getButtonState() = 0;

protected:
    iButton &b;
};


#endif //MIDI_STOMP_CONTROLLER_IBUTTONAGENT_H
