#include "TeamsKeeper.h"
#include "SystemTray.h"
#include "ActivitySimulator.h"
#include "PowerManager.h"
#include "resource.h"
#include <memory>

#define WM_TRAYICON (WM_USER + 1)
#define TIMER_ID 1
#define ACTIVITY_INTERVAL (4 * 60 * 1000) // 4 minutes in milliseconds

TeamsKeeper* TeamsKeeper::instance_ = nullptr;

TeamsKeeper::TeamsKeeper() 
    : keepAwakeEnabled_(true)
    , teamsActivityEnabled_(true)
    , timerId_(0)
    , hwnd_(nullptr) {
    instance_ = this;
}

TeamsKeeper::~TeamsKeeper() {
    Shutdown();
    instance_ = nullptr;
}

bool TeamsKeeper::Initialize(HWND hwnd) {
    hwnd_ = hwnd;

    // Initialize components
    systemTray_ = std::make_unique<SystemTray>(this);
    activitySimulator_ = std::make_unique<ActivitySimulator>();
    powerManager_ = std::make_unique<PowerManager>();

    if (!systemTray_->Initialize(hwnd)) {
        return false;
    }

    // Start with both features enabled
    if (keepAwakeEnabled_) {
        powerManager_->PreventSleep();
    }

    // Set up timer for Teams activity
    timerId_ = SetTimer(hwnd, TIMER_ID, ACTIVITY_INTERVAL, TimerCallback);
    
    UpdateTrayIcon();
    return true;
}

void TeamsKeeper::Shutdown() {
    if (timerId_) {
        KillTimer(hwnd_, timerId_);
        timerId_ = 0;
    }

    if (powerManager_) {
        powerManager_->AllowSleep();
    }

    if (systemTray_) {
        systemTray_->Cleanup();
    }
}

void TeamsKeeper::ToggleKeepAwake() {
    keepAwakeEnabled_ = !keepAwakeEnabled_;
    
    if (keepAwakeEnabled_) {
        powerManager_->PreventSleep();
    } else {
        powerManager_->AllowSleep();
    }
    
    UpdateTrayIcon();
}

void TeamsKeeper::ToggleTeamsActivity() {
    teamsActivityEnabled_ = !teamsActivityEnabled_;
    UpdateTrayIcon();
}

void TeamsKeeper::Exit() {
    PostMessage(hwnd_, WM_CLOSE, 0, 0);
}

void TeamsKeeper::UpdateTrayIcon() {
    bool isActive = keepAwakeEnabled_ || teamsActivityEnabled_;
    systemTray_->UpdateIcon(isActive);
}

LRESULT TeamsKeeper::HandleTrayMessage(WPARAM wParam, LPARAM lParam) {
    if (wParam == 1) { // Our tray icon ID
        switch (lParam) {
            case WM_RBUTTONUP: {
                POINT pt;
                GetCursorPos(&pt);
                systemTray_->ShowContextMenu(pt.x, pt.y);
                return 0;
            }
        }
    }
    return 0;
}

LRESULT TeamsKeeper::HandleCommand(WPARAM wParam) {
    switch (LOWORD(wParam)) {
        case IDM_TOGGLE_AWAKE:
            ToggleKeepAwake();
            return 0;
            
        case IDM_TOGGLE_TEAMS:
            ToggleTeamsActivity();
            return 0;
            
        case IDM_EXIT:
            Exit();
            return 0;
            
        case IDM_ABOUT:
            MessageBox(hwnd_, 
                L"TeamsKeeper v1.0\n\nKeeps your system awake and Microsoft Teams status green.\n\nRight-click the tray icon to toggle features.",
                L"About TeamsKeeper", MB_OK | MB_ICONINFORMATION);
            return 0;
    }
    return 0;
}

void CALLBACK TeamsKeeper::TimerCallback(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (instance_ && instance_->teamsActivityEnabled_ && idEvent == TIMER_ID) {
        instance_->activitySimulator_->SimulateActivity();
    }
}