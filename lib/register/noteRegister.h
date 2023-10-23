#ifndef MIDI_STOMP_CONTROLLER_NOTEREGISTER_H
#define MIDI_STOMP_CONTROLLER_NOTEREGISTER_H

#include "midiStompTypes.h"
#include "triggerData.h"

class noteRegister {
private:
    MidiInterface MIDI;
    int channel = 0;
    triggerData triggers[10];

public:
    noteRegister(const MidiInterface& MIDI, int midiChannel) : MIDI{MIDI}, channel{midiChannel} {}

    void playNotes(int triggerIndex, int notes[], int numNotes);

    void muteNotes(int triggerIndex);

};


#endif //MIDI_STOMP_CONTROLLER_NOTEREGISTER_H
