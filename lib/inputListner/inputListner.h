#ifndef MIDI_STOMP_CONTROLLER_INPUTLISTNER_H
#define MIDI_STOMP_CONTROLLER_INPUTLISTNER_H

#include "iButtonAgent.h"

class inputListner {
public:
    inputListner(iButtonAgent* b[], int len) : numberOfButtons{len} {
        for(int i=0; i < numberOfButtons; i++) {
            buttonAgents[i] = b[i];
        }
    }
    bool actOnInput();

private:
    int numberOfButtons;
    iButtonAgent* buttonAgents[];
};


#endif //MIDI_STOMP_CONTROLLER_INPUTLISTNER_H
