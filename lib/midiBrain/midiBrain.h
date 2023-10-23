#ifndef MIDI_STOMP_CONTROLLER_MIDIBRAIN_H
#define MIDI_STOMP_CONTROLLER_MIDIBRAIN_H

#include <utility>

#include "midiStompTypes.h"
#include "button.cpp"
#include "muxButton.cpp"
#include "buttonAgent.cpp"
#include "noteRegister.h"
#include "../display/controllerDisplay.h"

class midiBrain {
public:
// general operation settings
    const int maxOctaves = 10;
    const int rootStep = 60;
    bool isChord = false;
    bool isArpeggio = false;
    int totalSteps = 10;
    int step = 60;
    int octaveOffset = 5;
    int chordType = 0; // 0=major, 1=minor, 2=Diminished, 3=Maj 7, 4=Min 7
    bool isNotesMode = true;
    int tempo = 100;
    unsigned long lastActivity = 0;
// display settings
    unsigned long sleepDelay = 30000;
    bool sleeping = false;


    explicit midiBrain(MidiInterface MIDI, displayType *display) : theNoteRegister(MIDI, 1), theDisplay(display){
    }

    void readControlButtons(unsigned long currentTime);

    void readNoteTriggers(unsigned long currentTime);

    void updateDisplay(unsigned long currentTime);

    void timeForBed(unsigned long currentTime);

private:
    controllerDisplay theDisplay;
    noteRegister theNoteRegister;

    int chordTypeMap[1][10] = {{0,2,4,5,7,9,11,12,14,16}};

    // mux pins
    const int8_t sigPin = 2;
    const int sp[4] = {3, 4, 5, 6};

    // Control Buttons
    button controlMode = button(10);
    button controlTempoTap = button(9);
    muxButton controlUp = muxButton(0, sigPin, sp);
    muxButton controlDown = muxButton(1, sigPin, sp);
    muxButton controlChord = muxButton(2, sigPin, sp);
    muxButton controlArpeggio = muxButton(3, sigPin, sp);
    muxButton controlChordType = muxButton(4, sigPin, sp);
    buttonAgent modeAgent = buttonAgent(controlMode);
    buttonAgent tempoTapAgent = buttonAgent(controlTempoTap);
    buttonAgent upAgent = buttonAgent(controlUp);
    buttonAgent downAgent = buttonAgent(controlDown);
    buttonAgent chordAgent = buttonAgent(controlChord);
    buttonAgent arpeggioAgent = buttonAgent(controlArpeggio);
    buttonAgent chordTypeAgent = buttonAgent(controlChordType);

// Note Buttons
    muxButton note0 = muxButton(15, sigPin, sp);
    muxButton note1 = muxButton(14, sigPin, sp);
    muxButton note2 = muxButton(13, sigPin, sp);
    muxButton note3 = muxButton(12, sigPin, sp);
    muxButton note4 = muxButton(11, sigPin, sp);
    muxButton note5 = muxButton(10, sigPin, sp);
    muxButton note6 = muxButton(9, sigPin, sp);
    muxButton note7 = muxButton(8, sigPin, sp);
    muxButton note8 = muxButton(7, sigPin, sp);
    muxButton note9 = muxButton(6, sigPin, sp);
    buttonAgent note0Agent = buttonAgent(note0);
    buttonAgent note1Agent = buttonAgent(note1);
    buttonAgent note2Agent = buttonAgent(note2);
    buttonAgent note3Agent = buttonAgent(note3);
    buttonAgent note4Agent = buttonAgent(note4);
    buttonAgent note5Agent = buttonAgent(note5);
    buttonAgent note6Agent = buttonAgent(note6);
    buttonAgent note7Agent = buttonAgent(note7);
    buttonAgent note8Agent = buttonAgent(note8);
    buttonAgent note9Agent = buttonAgent(note9);
    buttonAgent noteAgents[10] = {
            note0Agent,
            note1Agent,
            note2Agent,
            note3Agent,
            note4Agent,
            note5Agent,
            note6Agent,
            note7Agent,
            note8Agent,
            note9Agent
    };

    void sendMidiNotes(int i);
};


#endif //MIDI_STOMP_CONTROLLER_MIDIBRAIN_H
