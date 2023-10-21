#ifndef MIDI_STOMP_CONTROLLER_INPUTLISTNER_H
#define MIDI_STOMP_CONTROLLER_INPUTLISTNER_H

#include "iButtonAgent.h"
#include "midiStompTypes.h"

class inputListner {
public:
    inputListner(iButtonAgent* b[], int len) : numberOfButtons{len} {
        for(int i=0; i < numberOfButtons; i++) {
            buttonAgents[i] = b[i];
        }
    }
    bool actOnInput();

protected:
    int totalSteps = 10;
    int currentStep = 0;
    int octaveOffset = 5;
    midiMode mode = NOTES;

private:
    int numberOfButtons;
    iButtonAgent* buttonAgents[];
};


#endif //MIDI_STOMP_CONTROLLER_INPUTLISTNER_H
