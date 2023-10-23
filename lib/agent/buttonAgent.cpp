#include "iButtonAgent.h"
#include "midiStompTypes.h"

class buttonAgent : public iButtonAgent {

public:

    explicit buttonAgent(iButton &b) : iButtonAgent{b} {
        if (!b.isPullUp()) {
            this->defaultState = LOW;
            this->currentState = LOW;
            this->lastState = LOW;
        }
    }

    buttonState getButtonState() override {
        currentClockTime = millis();
        currentState = b.readState();

        bool s_change = stateChange();
        bool rdx = readDelayExpired();
        bool switched = isSwitched(s_change, rdx);
        bool down = isDown();

        if (switched && down) return PRESSED;
        if (switched && !down) return RELEASED;
        if (!switched && down) return HELD;
        if (!switched && !down) return UP;
        return UP;
    }

    bool isSwitched(bool st_change, bool rdx) {
        if (st_change && rdx) {
            lastState = currentState;
            return true;
        }
        return false;
    }

    unsigned long getLastReadingTime() const {
        return currentClockTime - lastDebounceTime;
    }

    bool readDelayExpired() {
        unsigned long lastReading = getLastReadingTime();
        if (lastReading > debounceDelay) {
            lastDebounceTime = currentClockTime;
            return true;
        }
        return false;
    }

    bool stateChange() const {
        return currentState != lastState;
    }

    bool isDown() {
        return currentState != defaultState;
    }


private:
    unsigned long currentClockTime = 0;
    const unsigned long debounceDelay = 50;
    unsigned long lastDebounceTime = 0;
    int defaultState = HIGH;
    int currentState = HIGH;
    int lastState = HIGH;
};



