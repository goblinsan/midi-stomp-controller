#include "buttonAgent.h"

#include <utility>

buttonAgent::buttonAgent(iButton& b) : b{b} {
}

int buttonAgent::onPress() {
    if(b.isSwitched() && b.isDown()){
        return 0;
    }
    return 1;
}

int buttonAgent::onRelease() {
    if(b.isSwitched() && b.isDown()){
        return 1;
    }
    return 0;
}
