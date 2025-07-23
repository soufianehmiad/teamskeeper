#pragma once

#include <windows.h>

class PowerManager {
public:
    PowerManager();
    ~PowerManager();

    void PreventSleep();
    void AllowSleep();
    bool IsPreventingSleep() const { return preventingSleep_; }

private:
    bool preventingSleep_;
    EXECUTION_STATE previousState_;
};