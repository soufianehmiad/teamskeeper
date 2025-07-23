cmake_minimum_required(VERSION 3.20)
project(TeamsKeeper VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-specific configuration
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE TRUE)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/TeamsKeeper.cpp
    src/SystemTray.cpp
    src/ActivitySimulator.cpp
    src/PowerManager.cpp
)

set(HEADERS
    src/TeamsKeeper.h
    src/SystemTray.h
    src/ActivitySimulator.h
    src/PowerManager.h
)

# Create executable
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

# Windows-specific libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} 
        user32
        kernel32
        shell32
        comctl32
        gdi32
        ole32
        uuid
    )
    
    
    # Set subsystem to Windows (GUI app)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()