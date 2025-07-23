#include "TeamsKeeper.h"
#include <windows.h>

#define WM_TRAYICON (WM_USER + 1)

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static TeamsKeeper* keeper = nullptr;

    switch (uMsg) {
        case WM_CREATE:
            keeper = reinterpret_cast<TeamsKeeper*>(
                reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams
            );
            return 0;

        case WM_TRAYICON:
            if (keeper) {
                return keeper->HandleTrayMessage(wParam, lParam);
            }
            return 0;

        case WM_COMMAND:
            if (keeper) {
                return keeper->HandleCommand(wParam);
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    const wchar_t* className = L"TeamsKeeperClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        return 1;
    }

    // Initialize TeamsKeeper
    TeamsKeeper keeper;

    // Create hidden window for message handling
    HWND hwnd = CreateWindow(
        className, L"TeamsKeeper",
        0, 0, 0, 0, 0,
        nullptr, nullptr, hInstance, &keeper
    );

    if (!hwnd) {
        return 1;
    }
    
    if (!keeper.Initialize(hwnd)) {
        return 1;
    }

    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    keeper.Shutdown();
    return static_cast<int>(msg.wParam);
}