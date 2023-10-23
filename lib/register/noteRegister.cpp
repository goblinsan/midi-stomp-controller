#include "noteRegister.h"


void noteRegister::playNotes(int triggerIndex, int *notes, int numNotes) {
    for (int i = 0; i < numNotes; ++i) {
        MIDI.sendNoteOn(notes[i], 127, channel);
        triggers[triggerIndex].playedNotes.push_back(notes[i]);
        triggers[triggerIndex].isPlaying = true;
    }
}

void noteRegister::muteNotes(int triggerIndex) {
    if (triggers[triggerIndex].isPlaying) {
        for (auto & note : triggers[triggerIndex].playedNotes){
            MIDI.sendNoteOff(note, 0, channel);
        }
    }
    triggers[triggerIndex].playedNotes.empty();
    triggers[triggerIndex].isPlaying = false;
}
