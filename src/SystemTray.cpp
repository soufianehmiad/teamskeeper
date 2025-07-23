#include "SystemTray.h"
#include "TeamsKeeper.h"
#include <windows.h>
#include <shellapi.h>

#define IDM_EXIT           1001
#define IDM_TOGGLE_AWAKE   1002
#define IDM_TOGGLE_TEAMS   1003
#define IDM_ABOUT          1004

#define WM_TRAYICON (WM_USER + 1)

SystemTray::SystemTray(TeamsKeeper* keeper)
    : keeper_(keeper)
    , contextMenu_(nullptr)
    , activeIcon_(nullptr)
    , inactiveIcon_(nullptr)
    , initialized_(false) {
    ZeroMemory(&nid_, sizeof(nid_));
}

SystemTray::~SystemTray() {
    Cleanup();
}

bool SystemTray::Initialize(HWND hwnd) {
    // Create simple colored icons programmatically
    CreateIcons();

    // Initialize notification icon data
    nid_.cbSize = sizeof(NOTIFYICONDATA);
    nid_.hWnd = hwnd;
    nid_.uID = 1;
    nid_.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid_.uCallbackMessage = WM_TRAYICON;
    nid_.hIcon = activeIcon_;
    wcscpy_s(nid_.szTip, L"TeamsKeeper - Active");

    // Add to system tray
    if (!Shell_NotifyIcon(NIM_ADD, &nid_)) {
        return false;
    }

    CreateContextMenu();
    initialized_ = true;
    return true;
}

void SystemTray::CreateIcons() {
    // Create simple 16x16 colored icons
    HDC hdc = GetDC(nullptr);
    HDC memDC = CreateCompatibleDC(hdc);
    
    // Active icon (green)
    HBITMAP activeBmp = CreateCompatibleBitmap(hdc, 16, 16);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, activeBmp);
    
    HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
    RECT rect = {0, 0, 16, 16};
    FillRect(memDC, &rect, greenBrush);
    DeleteObject(greenBrush);
    
    SelectObject(memDC, oldBmp);
    
    ICONINFO iconInfo = {};
    iconInfo.fIcon = TRUE;
    iconInfo.hbmColor = activeBmp;
    iconInfo.hbmMask = activeBmp;
    activeIcon_ = CreateIconIndirect(&iconInfo);
    
    DeleteObject(activeBmp);
    
    // Inactive icon (gray)
    HBITMAP inactiveBmp = CreateCompatibleBitmap(hdc, 16, 16);
    SelectObject(memDC, inactiveBmp);
    
    HBRUSH grayBrush = CreateSolidBrush(RGB(128, 128, 128));
    FillRect(memDC, &rect, grayBrush);
    DeleteObject(grayBrush);
    
    SelectObject(memDC, oldBmp);
    
    iconInfo.hbmColor = inactiveBmp;
    iconInfo.hbmMask = inactiveBmp;
    inactiveIcon_ = CreateIconIndirect(&iconInfo);
    
    DeleteObject(inactiveBmp);
    DeleteDC(memDC);
    ReleaseDC(nullptr, hdc);
}

void SystemTray::UpdateIcon(bool isActive) {
    if (!initialized_) return;

    nid_.hIcon = isActive ? activeIcon_ : inactiveIcon_;
    wcscpy_s(nid_.szTip, isActive ? L"TeamsKeeper - Active" : L"TeamsKeeper - Inactive");
    Shell_NotifyIcon(NIM_MODIFY, &nid_);
}

void SystemTray::CreateContextMenu() {
    contextMenu_ = CreatePopupMenu();
    
    // Add menu items
    AppendMenu(contextMenu_, MF_STRING | (keeper_->IsKeepAwakeEnabled() ? MF_CHECKED : MF_UNCHECKED), 
               IDM_TOGGLE_AWAKE, L"Keep System Awake");
    AppendMenu(contextMenu_, MF_STRING | (keeper_->IsTeamsActivityEnabled() ? MF_CHECKED : MF_UNCHECKED),
               IDM_TOGGLE_TEAMS, L"Keep Teams Green");
    AppendMenu(contextMenu_, MF_SEPARATOR, 0, nullptr);
    AppendMenu(contextMenu_, MF_STRING, IDM_ABOUT, L"About");
    AppendMenu(contextMenu_, MF_SEPARATOR, 0, nullptr);
    AppendMenu(contextMenu_, MF_STRING, IDM_EXIT, L"Exit");
}

void SystemTray::ShowContextMenu(int x, int y) {
    if (!contextMenu_) return;

    // Update menu item states
    CheckMenuItem(contextMenu_, IDM_TOGGLE_AWAKE, 
                  keeper_->IsKeepAwakeEnabled() ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(contextMenu_, IDM_TOGGLE_TEAMS,
                  keeper_->IsTeamsActivityEnabled() ? MF_CHECKED : MF_UNCHECKED);

    // Make sure window is foreground so menu appears correctly
    SetForegroundWindow(nid_.hWnd);
    
    // Show context menu
    TrackPopupMenu(contextMenu_, TPM_RIGHTBUTTON, x, y, 0, nid_.hWnd, nullptr);
    
    // Required to make menu disappear properly
    PostMessage(nid_.hWnd, WM_NULL, 0, 0);
}

void SystemTray::Cleanup() {
    if (initialized_) {
        Shell_NotifyIcon(NIM_DELETE, &nid_);
        initialized_ = false;
    }
    
    if (contextMenu_) {
        DestroyMenu(contextMenu_);
        contextMenu_ = nullptr;
    }
    
    if (activeIcon_) {
        DestroyIcon(activeIcon_);
        activeIcon_ = nullptr;
    }
    
    if (inactiveIcon_) {
        DestroyIcon(inactiveIcon_);
        inactiveIcon_ = nullptr;
    }
}