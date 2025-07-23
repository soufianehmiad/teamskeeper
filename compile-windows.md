# Compiling TeamsKeeper on Windows

## Method 1: Using the Build Script (Recommended)

1. Open Command Prompt as Administrator
2. Navigate to the project directory
3. Run: `build.bat`

## Method 2: Manual Compilation

### Using Visual Studio 2022

1. Open Visual Studio 2022
2. File → Open → CMake → Select `CMakeLists.txt`
3. Visual Studio will configure the project automatically
4. Build → Build All
5. The executable will be in `out/build/x64-Release/TeamsKeeper.exe`

### Using Command Line

```batch
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

# Build the project
cmake --build . --config Release

# The executable will be at: build\Release\TeamsKeeper.exe
```

## Cross-Compilation from macOS/Linux

If you have MinGW-w64 installed:

```bash
mkdir build-windows
cd build-windows

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-toolchain.cmake
make
```

## Troubleshooting

- **CMake not found**: Install CMake from https://cmake.org/download/
- **Visual Studio not found**: Install Visual Studio 2022 Community (free)
- **Windows SDK missing**: Install Windows 11 SDK through Visual Studio Installer
- **Build errors**: Make sure you're using Visual Studio 2022 or later with C++17 support

## Running the Application

1. Navigate to the build output directory
2. Run `TeamsKeeper.exe`
3. Check your system tray for the green/gray icon
4. Right-click the icon to access the menu