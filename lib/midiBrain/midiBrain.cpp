#include "midiBrain.h"


void midiBrain::readControlButtons(unsigned long currentTime) {
    buttonState modeState = modeAgent.getButtonState();
    bool updated = false;
    if (modeState == PRESSED) {
        digitalWrite(LED_BUILTIN, HIGH);
        isNotesMode = !isNotesMode;
        theDisplay.clear();
        Serial.println("Mode pressed");
        updated = true;
    } else if (modeState == RELEASED) {
        digitalWrite(LED_BUILTIN, LOW);
    }

    buttonState upState = upAgent.getButtonState();
    if (upState == PRESSED) {
        if (isNotesMode){
            octaveOffset++;
        } else {
            totalSteps++;
        }
        Serial.println("Up pressed");
        updated = true;
    }

    buttonState downState = downAgent.getButtonState();
    if (downState == PRESSED) {
        if (isNotesMode){
            octaveOffset--;
        } else {
            totalSteps--;
        }
        Serial.println("Down pressed");
        updated = true;
    }

    buttonState chordState = chordAgent.getButtonState();
    if (chordState == PRESSED) {
        isChord = !isChord;
        updated = true;
    }

    buttonState arpeggioState = arpeggioAgent.getButtonState();
    if (arpeggioState == PRESSED) {
        isArpeggio = !isArpeggio;
        Serial.println("Arpeggio pressed");
        updated = true;
    }

    if (updated){
        updateDisplay(currentTime);
    }

}

void midiBrain::readNoteTriggers(unsigned long currentTime) {
    bool updated = false;
    for (int i = 0; i < 10; i++) {
        buttonState bas = noteAgents[i].getButtonState();
        if (bas == PRESSED) {
            if (isNotesMode){
                sendMidiNotes(i);
            } else {
                int notes2play[1];
                notes2play[0] = rootStep + (step % totalSteps);
                theNoteRegister.playNotes(i, notes2play, 1);
                updateDisplay(currentTime);
                step = (step + 1) % totalSteps;
            }
            updated = true;
            digitalWrite(LED_BUILTIN, HIGH);
        }
        if (bas == RELEASED ){
            digitalWrite(LED_BUILTIN, LOW);
            theNoteRegister.muteNotes(i);
        }
    }
    if (updated){
        updateDisplay(currentTime);
    }
}

void midiBrain::sendMidiNotes(int i) {
    int baseNote = (octaveOffset * 10) + chordTypeMap[chordType][i];
    if (isChord) {
        int notes2play[3];
        notes2play[0] = baseNote;
        notes2play[1] = baseNote + 4;
        notes2play[2] = baseNote + 7;
        theNoteRegister.playNotes(i, notes2play, 3);
    } else {
        int notes2play[1];
        notes2play[0] = baseNote;
        theNoteRegister.playNotes(i, notes2play, 1);
    }
}

void midiBrain::updateDisplay(unsigned long currentTime) {
    int configState[9] = {isNotesMode, isChord, isArpeggio, octaveOffset, maxOctaves, step, totalSteps, chordType, tempo};
    theDisplay.updateDisplay(configState);
    lastActivity = currentTime;
    sleeping = false;
}

void midiBrain::timeForBed(unsigned long currentTime) {
    if ((currentTime - lastActivity) > sleepDelay){
        if (!sleeping){
            theDisplay.sleep();
            sleeping = true;
        }
    }
}
