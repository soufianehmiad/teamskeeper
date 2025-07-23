#pragma once

#include <windows.h>
#include <shellapi.h>

class TeamsKeeper;

class SystemTray {
public:
    SystemTray(TeamsKeeper* keeper);
    ~SystemTray();

    bool Initialize(HWND hwnd);
    void UpdateIcon(bool isActive);
    void ShowContextMenu(int x, int y);
    void Cleanup();

    // Message handling
    LRESULT HandleTrayMessage(WPARAM wParam, LPARAM lParam);

private:
    void CreateContextMenu();
    void CreateIcons();

private:
    TeamsKeeper* keeper_;
    NOTIFYICONDATA nid_;
    HMENU contextMenu_;
    HICON activeIcon_;
    HICON inactiveIcon_;
    bool initialized_;
};