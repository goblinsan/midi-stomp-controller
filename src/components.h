//
// Created by Momito on 10/12/2023.
//

#ifndef MIDI_STOMP_CONTROLLER_COMPONENTS_H
#define MIDI_STOMP_CONTROLLER_COMPONENTS_H

#include <U8g2lib.h>
#include <MIDI.h>
#include <Adafruit_TinyUSB.h>
#include <Arduino.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

const int maxOctaves = 10;
const int rootStep = 60;

const int8_t SIG_PIN = 2;
const int8_t SELECT_0 = 3;
const int8_t SELECT_1 = 4;
const int8_t SELECT_2 = 5;
const int8_t SELECT_3 = 6;
const int SELECT_PINS[4] = {SELECT_0, SELECT_1, SELECT_2, SELECT_3};
unsigned long sleepDelay = 30000;
unsigned long lastActivity = 0;
bool sleeping = false;

void turnOnLED(int8_t pin, bool turnOn) {
    if (turnOn) {
        digitalWrite(pin, LOW);
    } else {
        digitalWrite(pin, HIGH);
    }
}

class momentarySwitch {
private:
    unsigned long debounceDelay = 50;

public:
    int8_t switch_index{};
    bool isPullUp{};
    bool isMux{};
    int16_t defaultState = HIGH;
    int16_t currentState = HIGH;
    int16_t lastState = HIGH;
    bool isOn = false;
    unsigned long lastDebounceTime = 0;

    explicit momentarySwitch(int8_t i = 0, bool p = true, bool m = false) : switch_index{i}, isPullUp{p}, isMux{m} {
        if (!isPullUp) {
            defaultState = LOW;
            currentState = LOW;
            lastState = LOW;
        }
    }

    bool isSwitched() {
        if (currentState != lastState) {
            if ((millis() - lastDebounceTime) > debounceDelay) {
                lastState = currentState;
                lastDebounceTime = millis();
                lastActivity = millis();
                sleeping = false;
                return true;
            }
        }
        return false;
    }

    void readButton() {
        if (isMux) {
            for (int k = 0; k < 4; k++) {
                int mask = 1 << k;
                int masked_n = switch_index & mask;
                int bit = masked_n >> k;
                digitalWrite(SELECT_PINS[k], bit);
            }
            currentState = digitalRead(SIG_PIN);
        } else {
            currentState = digitalRead(switch_index);
        }
    }

    bool isPressed() {
        readButton();
        if (isSwitched()) {
            if (currentState != defaultState) {
                return true;
            }
        }
        return false;
    }

    void toggleOnIfPressed() {
        if (isPressed()) {
            isOn = !isOn;
        }
    }

    int addIfPressed(int value, int amount) {
        if (isPressed()) {
            return value + amount;
        }
        return value;
    }

};

class button : public momentarySwitch {
public:
    explicit button(int8_t i = 0, bool pullUp = true) : momentarySwitch(i, pullUp) {
        if (pullUp) {
            pinMode(switch_index, INPUT_PULLUP);
        } else {
            pinMode(switch_index, INPUT);
        }
    }
};

class muxButton : public momentarySwitch {
public:
    explicit muxButton(int8_t i, bool pullUp = true) : momentarySwitch(i, pullUp, true) {
    }
};

class midiButton : public muxButton {
private:
    bool openChord = false;
    int lastNotePlayed = 0;
public:
    int noteIndex{};

    explicit midiButton(int8_t i = 0, int n = 0) : muxButton{i}, noteIndex{n} {
    }

    void playNote(bool isNotes, bool isChord, int octaveOffset, int &step, int &totalSteps) {
        turnOnLED(15, true);
        int midiNote;
        if (isNotes) {
            midiNote = ((octaveOffset % maxOctaves) * 12) + noteIndex;
        } else {
            midiNote = rootStep + (step % totalSteps);
            step++;
        }
        MIDI.sendNoteOn(midiNote, 127, 1);
        if (isChord && isNotes) {
            MIDI.sendNoteOn(midiNote + 4, 127, 1);
            MIDI.sendNoteOn(midiNote + 7, 127, 1);
            openChord = true;
        }
        lastNotePlayed = midiNote;
    }

    void releaseNote() {
        turnOnLED(15, false);
        MIDI.sendNoteOff(lastNotePlayed, 0, 1);
        if (openChord) {
            MIDI.sendNoteOff(lastNotePlayed + 4, 0, 1);
            MIDI.sendNoteOff(lastNotePlayed + 7, 0, 1);
            openChord = false;
        }
    }

};

void handleDisplay();

void handleNotes(midiButton (&allNotes)[10], bool isNotes, bool isChord, int octaveOffset, int &step, int &totalSteps) {
    for (auto &note: allNotes) {
        note.readButton();
        if (note.isSwitched()) {
            if (note.currentState == LOW) {
                note.playNote(isNotes, isChord, octaveOffset, step, totalSteps );
            } else {
                note.releaseNote();
            }
        }
    }
}

void handleOctaveButtons(int &octaveOffset, int &totalSteps, muxButton octaveUpButton, muxButton octaveDownButton,
                        bool isNotes) {
    if (isNotes) {
        octaveOffset = octaveUpButton.addIfPressed(octaveOffset, 1);
        octaveOffset = octaveDownButton.addIfPressed(octaveOffset, -1);
    } else {
        totalSteps = octaveUpButton.addIfPressed(totalSteps, 1);
        totalSteps = octaveDownButton.addIfPressed(totalSteps, -1);
    }
}

void handleChordButton(muxButton chordButton) {
    chordButton.toggleOnIfPressed();
}

void handleArpeggioButton(muxButton arpeggioButton) {
    arpeggioButton.toggleOnIfPressed();
}

void handleChordTypeButton(int &chordType, muxButton chordTypeButton) {
    chordType = chordTypeButton.addIfPressed(chordType, 1) % 6;
}

void handleModeButton(button noteModeButton) {
    noteModeButton.toggleOnIfPressed();
}


#endif //MIDI_STOMP_CONTROLLER_COMPONENTS_H
