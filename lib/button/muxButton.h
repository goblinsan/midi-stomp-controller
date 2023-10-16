#ifndef MIDI_STOMP_CONTROLLER_MUXBUTTON_H
#define MIDI_STOMP_CONTROLLER_MUXBUTTON_H

#include "iButton.h"

class muxButton : public iButton {
private:
    int8_t sig_pin;
    int *select_pins;
public:

    explicit muxButton(int8_t i = 0, int8_t s = 2, const int *sp = nullptr, bool pullUp = true);

    int readState() override;

};

#endif //MIDI_STOMP_CONTROLLER_MUXBUTTON_H
