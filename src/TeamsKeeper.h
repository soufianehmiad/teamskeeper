#pragma once

#include <windows.h>
#include <memory>

class SystemTray;
class ActivitySimulator;
class PowerManager;

class TeamsKeeper {
public:
    TeamsKeeper();
    ~TeamsKeeper();

    bool Initialize(HWND hwnd);
    void Shutdown();

    // Toggle functions
    void ToggleKeepAwake();
    void ToggleTeamsActivity();
    void Exit();

    // Status getters
    bool IsKeepAwakeEnabled() const { return keepAwakeEnabled_; }
    bool IsTeamsActivityEnabled() const { return teamsActivityEnabled_; }

    // Message handlers
    LRESULT HandleTrayMessage(WPARAM wParam, LPARAM lParam);
    LRESULT HandleCommand(WPARAM wParam);

private:
    void UpdateTrayIcon();
    static void CALLBACK TimerCallback(HWND, UINT, UINT_PTR, DWORD);

private:
    std::unique_ptr<SystemTray> systemTray_;
    std::unique_ptr<ActivitySimulator> activitySimulator_;
    std::unique_ptr<PowerManager> powerManager_;

    bool keepAwakeEnabled_;
    bool teamsActivityEnabled_;
    UINT_PTR timerId_;
    HWND hwnd_;

    static TeamsKeeper* instance_;
};