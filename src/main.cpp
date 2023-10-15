#include <Arduino.h>
// for nano need adafruit midi
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
#include <U8g2lib.h>
#include "components.h"


U8X8_SSD1306_128X32_UNIVISION_HW_I2C display(U8X8_PIN_NONE);

const int numberOfNotes = 10;
int totalSteps = 10;
int step = 60;
int octaveOffset = 5;
int chordType = 0; // 0=major, 1=minor, 2=Diminished, 3=Maj 7, 4=Min 7
bool wasNotesMode = true;

midiButton noteC = midiButton(15, 0);
midiButton noteD = midiButton(14, 2);
midiButton noteE = midiButton(13, 4);
midiButton noteF = midiButton(12, 5);
midiButton noteG = midiButton(11, 7);
midiButton noteA = midiButton(10, 9);
midiButton noteB = midiButton(9, 11);
midiButton noteC2 = midiButton(8, 12);
midiButton noteD2 = midiButton(7, 14);
midiButton noteE2 = midiButton(6, 16);
midiButton allNotes[numberOfNotes];
button buttonNumberSeven = button(7);
button noteModeButton = button(8);
//button tempoButton = button(10);
muxButton octaveUpButton = muxButton(0);
muxButton octaveDownButton = muxButton(1);
muxButton chordButton = muxButton(2);
muxButton arpeggioButton = muxButton(3);
muxButton chordTypeButton = muxButton(4);

void setup() {
    noteModeButton.isOn = true;
    allNotes[0] = noteC;
    allNotes[1] = noteD;
    allNotes[2] = noteE;
    allNotes[3] = noteF;
    allNotes[4] = noteG;
    allNotes[5] = noteA;
    allNotes[6] = noteB;
    allNotes[7] = noteC2;
    allNotes[8] = noteD2;
    allNotes[9] = noteE2;
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);

    pinMode(SIG_PIN, INPUT_PULLUP);
    for (int i: SELECT_PINS) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }

    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    turnOnLED(14, false);
    turnOnLED(15, false);
    MIDI.begin(5);
    Serial.begin(115200);
    display.begin();
    display.setFont(u8x8_font_chroma48medium8_r);
    display.setCursor(0, 0); // char row, col - not pixel

    display.println("===============");
    display.println("Hi Mason");
    display.println("and Ellie!");
    display.println("===============");
    delay(3 * 1000);
    display.clearDisplay();
    Serial.println("Begin Loop");
}

void loop() {
    buttonNumberSeven.readButton();
    if (buttonNumberSeven.isSwitched()) {
        if (buttonNumberSeven.currentState == LOW) {
            turnOnLED(14, true);
            MIDI.sendNoteOn(60, 127, 3);
        } else {
            turnOnLED(14, false);
            MIDI.sendNoteOff(60, 127, 3);
        }

    }
    handleOctaveButtons(octaveOffset, totalSteps, octaveUpButton, octaveDownButton, noteModeButton.isOn);
    handleChordButton(chordButton);
    handleArpeggioButton(arpeggioButton);
    handleChordTypeButton(chordType, chordTypeButton);
    handleModeButton(noteModeButton);
    handleNotes(allNotes, noteModeButton.isOn, chordButton.isOn, octaveOffset, step, totalSteps);
    handleDisplay();
}

void printText(bool isBig, int x, int y, const String &text) {
    if (isBig) {
        display.setFont(u8x8_font_courB18_2x3_r);
    } else {
        display.setFont(u8x8_font_pressstart2p_f);
    }
    display.setCursor(x, y);
    display.print(text);
}

void printCheckMark(bool value) {
    display.setFont(u8x8_font_open_iconic_check_1x1);
    if (value) {
        display.print(String(char(64)));
    } else {
        display.print(String(char(68)));
    }
}

void handleDisplay() {
    if ((millis() - lastActivity) < sleepDelay) {
        //    length of display 15 letters "==============="
        if (noteModeButton.isOn) {
            if (!wasNotesMode) {
                display.clearDisplay();
                wasNotesMode = !wasNotesMode;
            }
            printText(false, 0, 0, String("O#   Chrd: "));
            printCheckMark(chordButton.isOn);
            printText(true, 0, 1, String(octaveOffset % maxOctaves));
            printText(false, 5, 1, String("Arpg: "));
            printCheckMark(arpeggioButton.isOn);
            printText(false, 5, 2, String("Type: ") + String(chordType));
            printText(false, 5, 3, String("Mode: ") + String(noteModeButton.isOn));
        } else {
            if (wasNotesMode) {
                display.clearDisplay();
                wasNotesMode = !wasNotesMode;
            }
            printText(false, 0, 0, String("S#   Step: ") + String(step));
            printText(true, 0, 1, String(totalSteps));
        }

    } else if (!sleeping) {
        display.clearDisplay();
        printText(true, 2, 1, String("zzz..."));
        delay(3 * 1000);
        display.clearDisplay();
        sleeping = true;
    }
}
