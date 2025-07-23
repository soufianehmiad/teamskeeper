# TeamsKeeper

A lightweight Windows 11 system tray application that keeps your system awake and maintains your Microsoft Teams status as "Available" (green).

## Features

- **Keep System Awake**: Prevents Windows from going to sleep or turning off the display
- **Keep Teams Green**: Simulates subtle user activity every 4 minutes to maintain Teams availability status
- **System Tray Integration**: Runs quietly in the system tray with visual status indicators
- **Toggle Controls**: Easy right-click menu to enable/disable features independently
- **Minimal Resource Usage**: Lightweight C++ application with minimal CPU and memory footprint

## System Tray Icons

- **Green Icon**: One or both features are active
- **Gray Icon**: Both features are disabled

## Right-Click Menu Options

- **Keep System Awake**: Toggle system sleep prevention
- **Keep Teams Green**: Toggle Teams activity simulation
- **About**: Show application information
- **Exit**: Close the application

## Building

### Prerequisites

- Visual Studio 2022 with C++ development tools
- CMake 3.20 or later
- Windows 11 SDK

### Build Instructions

1. Open a Command Prompt or PowerShell in the project directory
2. Run the build script:
   ```batch
   build.bat
   ```
3. The executable will be created at: `build\Release\TeamsKeeper.exe`

### Manual Build

```batch
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## Usage

1. Run `TeamsKeeper.exe`
2. The application will start in the system tray (both features enabled by default)
3. Right-click the tray icon to access the menu
4. Toggle features as needed
5. The application will continue running until you choose "Exit"

## How It Works

### Keep System Awake
Uses Windows `SetThreadExecutionState` API to prevent the system from entering sleep mode or turning off the display.

### Keep Teams Green
Alternates between two subtle activities every 4 minutes:
- **Mouse Movement**: Moves cursor 1-2 pixels and immediately returns it
- **Key Press**: Sends F15 key (rarely used, won't interfere with applications)

These activities are designed to be completely unnoticeable during normal computer use while keeping Teams status active.

## Technical Details

- **Language**: C++17
- **Framework**: Win32 API
- **Architecture**: x64
- **Target OS**: Windows 11 (compatible with Windows 10)
- **Dependencies**: Windows system libraries only (no external dependencies)

## Security & Privacy

- All activity simulation happens locally on your machine
- No network connections or data transmission
- No logging or data collection
- Uses only standard Windows APIs
- Source code is fully available for review

## License

This project is provided as-is for educational and personal use.