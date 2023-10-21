#include <MIDI.h>
#ifdef ADAFRUIT_TINYUSB_H_
    #include <Adafruit_TinyUSB.h>
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<Adafruit_USBD_MIDI>;
#else
    union fakeSerial{
        void write(byte value){};
    };
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<fakeSerial>;
#endif
#include "buttonAgent.cpp"

class noteButtonAgent : public buttonAgent {
private:
    using MidiInterface = MIDI_NAMESPACE::MidiInterface<MidiTransport>;
    int lastNoteSize = 0;
    int *lastNotes = nullptr;
public:

    void playNote(MidiInterface MIDI, int midiChannel, int notes[], int numNotes) {
        lastNoteSize = numNotes;
        lastNotes = notes;
        for (int i = 0; i < numNotes; ++i) {
            MIDI.sendNoteOn(notes[i], 127, midiChannel);
        }
    }

    void muteNote(MidiInterface MIDI, int midiChannel) {
        for (int i = 0; i < lastNoteSize; ++i) {
            MIDI.sendNoteOff(lastNotes[i], 0, midiChannel);
        }
    }

};
