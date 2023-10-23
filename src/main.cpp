#include <Arduino.h>
#include <U8g2lib.h>
#include "midiBrain.h"
#include "midiStompTypes.h"
#include "arduino/midi/Adafruit_USBD_MIDI.h"

//Adafruit_USBD_MIDI usb_midi;
midiUsbType usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

//U8X8_SSD1306_128X32_UNIVISION_HW_I2C display(U8X8_PIN_NONE);
displayType display(U8X8_PIN_NONE);

midiBrain brain = midiBrain(MIDI, &display);


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    MIDI.begin(1);
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
    brain.updateDisplay(0);
    Serial.println("Begin Loop");
}

void loop() {
    unsigned long curTime = millis();
    brain.readControlButtons(curTime);
    brain.readNoteTriggers(curTime);
    brain.timeForBed(curTime);
}


