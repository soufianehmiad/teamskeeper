#include "ActivitySimulator.h"
#include <windows.h>
#include <random>

ActivitySimulator::ActivitySimulator() 
    : lastActivityTime_(0)
    , useMouseMove_(true) {
    lastActivityTime_ = GetTickCount();
}

ActivitySimulator::~ActivitySimulator() {
}

void ActivitySimulator::SimulateActivity() {
    DWORD currentTime = GetTickCount();
    
    // Alternate between mouse movement and key press to be less detectable
    if (useMouseMove_) {
        SimulateMouseMove();
    } else {
        SimulateKeyPress();
    }
    
    useMouseMove_ = !useMouseMove_;
    lastActivityTime_ = currentTime;
}

void ActivitySimulator::SimulateMouseMove() {
    // Get current cursor position
    POINT currentPos;
    GetCursorPos(&currentPos);
    
    // Create very subtle mouse movement (1-2 pixels)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-2, 2);
    
    int deltaX = dis(gen);
    int deltaY = dis(gen);
    
    // Ensure we actually move at least 1 pixel
    if (deltaX == 0 && deltaY == 0) {
        deltaX = 1;
    }
    
    // Move cursor slightly
    SetCursorPos(currentPos.x + deltaX, currentPos.y + deltaY);
    
    // Move it back after a short delay to minimize visual impact
    Sleep(50);
    SetCursorPos(currentPos.x, currentPos.y);
}

void ActivitySimulator::SimulateKeyPress() {
    // Simulate a very subtle key combination that shouldn't interfere with work
    // F15 key is rarely used and won't affect most applications
    BYTE VK_F15 = 0x7E;
    
    // Simulate F15 key press and release
    keybd_event(VK_F15, 0, 0, 0);               // Key down
    Sleep(10);
    keybd_event(VK_F15, 0, KEYEVENTF_KEYUP, 0); // Key up
}

void ActivitySimulator::ResetLastActivity() {
    lastActivityTime_ = GetTickCount();
}