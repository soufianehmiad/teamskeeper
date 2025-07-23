#pragma once

#include <windows.h>

class ActivitySimulator {
public:
    ActivitySimulator();
    ~ActivitySimulator();

    void SimulateActivity();
    void ResetLastActivity();

private:
    void SimulateMouseMove();
    void SimulateKeyPress();

private:
    DWORD lastActivityTime_;
    bool useMouseMove_;
};