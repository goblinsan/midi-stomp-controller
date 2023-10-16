#ifndef MIDI_STOMP_CONTROLLER_BUTTONAGENT_H
#define MIDI_STOMP_CONTROLLER_BUTTONAGENT_H


#include "iButton.h"

class buttonAgent {
public:
    iButton& b;
    explicit buttonAgent(iButton& b);

    int onPress();

    int onRelease();

};


#endif //MIDI_STOMP_CONTROLLER_BUTTONAGENT_H
