#include "iButtonAgent.h"

class buttonAgent : public iButtonAgent {

public:

    explicit buttonAgent(iButton &b) : iButtonAgent{b} {
        if (!b.isPullUp()) {
            defaultState = LOW;
            currentState = LOW;
            lastState = LOW;
        }
    }

    bool isSwitched() override {
        currentState = b.readState();
        if (currentState != lastState) {
            unsigned long clockTime = millis();
            if ((clockTime - lastDebounceTime) > debounceDelay) {
                lastState = currentState;
                lastDebounceTime = clockTime;
                return true;
            }
        }
        return false;
    }

    bool isDown() override {
        return currentState != defaultState;
    }

    int onPress() override {
        return isSwitched() && isDown();
    }

    int onRelease() override {
        return isSwitched() && !isDown();
    }

private:
    const unsigned long debounceDelay = 50;
    unsigned long lastDebounceTime = 0;
    int defaultState = HIGH;
    int currentState = HIGH;
    int lastState = HIGH;
};



