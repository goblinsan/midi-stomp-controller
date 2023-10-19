#include "inputListner.h"

bool inputListner::actOnInput(){
    bool anyButtonIsSwitched = false;

    for(int i=0; i < numberOfButtons; i++) {
        anyButtonIsSwitched = buttonAgents[i]->isSwitched() || anyButtonIsSwitched;
    }

    return anyButtonIsSwitched;
}