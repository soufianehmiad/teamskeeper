#include "PowerManager.h"
#include <windows.h>

PowerManager::PowerManager() 
    : preventingSleep_(false)
    , previousState_(0) {
}

PowerManager::~PowerManager() {
    AllowSleep();
}

void PowerManager::PreventSleep() {
    if (preventingSleep_) {
        return; // Already preventing sleep
    }

    // Prevent system sleep, display sleep, and away mode
    EXECUTION_STATE newState = ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED | ES_AWAYMODE_REQUIRED;
    
    previousState_ = SetThreadExecutionState(newState);
    
    if (previousState_ != 0) {
        preventingSleep_ = true;
    }
}

void PowerManager::AllowSleep() {
    if (!preventingSleep_) {
        return; // Not preventing sleep
    }

    // Restore previous execution state
    SetThreadExecutionState(ES_CONTINUOUS);
    preventingSleep_ = false;
    previousState_ = 0;
}