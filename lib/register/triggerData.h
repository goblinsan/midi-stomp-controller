#ifndef MIDI_STOMP_CONTROLLER_TRIGGERDATA_H
#define MIDI_STOMP_CONTROLLER_TRIGGERDATA_H


#include "Vector.h"

struct triggerData {
    bool isPlaying = false;
    Vector<int> playedNotes;
};


#endif //MIDI_STOMP_CONTROLLER_TRIGGERDATA_H
