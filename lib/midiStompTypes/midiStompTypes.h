#ifndef MIDI_STOMP_CONTROLLER_MIDISTOMPTYPES_H
#define MIDI_STOMP_CONTROLLER_MIDISTOMPTYPES_H

#include <MIDI.h>
#include <Adafruit_TinyUSB.h>
#include <U8g2lib.h>

#ifdef ADAFRUIT_TINYUSB_H_
#include <Adafruit_TinyUSB.h>
    using midiUsbType = Adafruit_USBD_MIDI;
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<Adafruit_USBD_MIDI>;
//    using MidiTransport = Adafruit_USBD_MIDI;
#else
    union fakeSerial{
        void write(byte value){};
    };
    using midiUsbType = fakeSerial;
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<fakeSerial>;
#endif

#ifdef U8X8LIB_HH
#include <U8g2lib.h>
    using displayType = U8X8_SSD1306_128X32_UNIVISION_HW_I2C;
#else
union fakeDisplay{
        void setFont(const uint8_t *font_8x8){};
        void setCursor(uint8_t x, uint8_t y){};
        void clearDisplay(void) {};
        void print(String) {};
};
union fakePin {};
using displayType = fakeDisplay;
using U8X8LIB_HH = 255;
#endif

using MidiInterface = MIDI_NAMESPACE::MidiInterface<MidiTransport>;
enum midiMode {NOTES, STEPS};
enum buttonState {UP, PRESSED, HELD, RELEASED};

#endif //MIDI_STOMP_CONTROLLER_MIDISTOMPTYPES_H
