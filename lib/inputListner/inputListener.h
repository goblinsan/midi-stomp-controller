#ifndef MIDI_STOMP_CONTROLLER_INPUTLISTENER_H
#define MIDI_STOMP_CONTROLLER_INPUTLISTENER_H

#include "iButtonAgent.h"
#include "midiStompTypes.h"


class inputListener {
public:
    inputListener(iButtonAgent* b[], int len) : numberOfButtons{len} {
        for(int i=0; i < numberOfButtons; i++) {
            agents[i] = b[i];
        }
    }
    bool readInputs();

private:
    int numberOfButtons;
    iButtonAgent *agents[];
};


#endif //MIDI_STOMP_CONTROLLER_INPUTLISTENER_H
