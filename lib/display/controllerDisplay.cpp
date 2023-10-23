#include "controllerDisplay.h"
#include "clib/u8x8.h"
#include <Arduino.h>


void controllerDisplay::updateDisplay(const int configState[9]) {
    bool isNotesMode = configState[0];
    bool isChord = configState[1];
    bool isArpeggio = configState[2];
    int octaveOffset = configState[3];
    int maxOctaves = configState[4];
    int step = configState[5];
    int totalSteps = configState[6];
    int chordType = configState[7];
    int tempo = configState[8];

    //    length of display 15 letters "==============="
    if (isNotesMode) {
        printText(false, 0, 0, String("O#   Chrd: "));
        printCheckMark(isChord);
        printText(true, 0, 1, String(octaveOffset % maxOctaves));
        printText(false, 5, 1, String("Arpg: "));
        printCheckMark(isArpeggio);
        printText(false, 5, 2, String("Type: ") + String(chordType));
        printText(false, 5, 3, String("Mode: ") + String(isNotesMode));
    } else {
        printText(false, 0, 0, String("S#   Step: ") + String(step));
        printText(true, 0, 1, String(totalSteps));
    }

}

void controllerDisplay::printCheckMark(bool value) {
    display->setFont(u8x8_font_open_iconic_check_1x1);
    if (value) {
        display->print(String(char(64)));
    } else {
        display->print(String(char(68)));
    }
}

void controllerDisplay::printText(bool isBig, int x, int y, const String &text) {
    if (isBig) {
        display->setFont(u8x8_font_courB18_2x3_r);
    } else {
        display->setFont(u8x8_font_pressstart2p_f);
    }
    display->setCursor(x, y);
    display->print(text);
}

void controllerDisplay::sleep() {
    display->clearDisplay();
    printText(true, 2, 1, String("zzz..."));
    delay(3 * 1000);
    display->clearDisplay();
}

void controllerDisplay::clear() {
    display->clearDisplay();
}
