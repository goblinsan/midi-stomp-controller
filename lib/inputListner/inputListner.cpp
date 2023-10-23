#include "inputListener.h"

bool inputListener::readInputs(){
    bool anyButtonIsSwitched = false;

    for(int i=0; i < numberOfButtons; i++) {
        anyButtonIsSwitched = agents[i]->getButtonState() || anyButtonIsSwitched;
    }

    return anyButtonIsSwitched;
}

void doStuff(){
    controlButton mode;
    controlButton controlUp;
    controlButton controlDown;
    controlButton chord;
    controlButton arpeggio;
    controlButton chordType;
    controlButton tempoTap;

    noteButton n0;
    noteButton n1;
    noteButton n2;
    noteButton n3;
    noteButton n4;
    noteButton n5;
    noteButton n6;
    noteButton n7;
    noteButton n8;
    noteButton n9;
}