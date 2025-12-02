# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Name of your project
project(C4C_Plotter_Comp CXX)

# Specify the C++ standard to use (C++17 is modern and standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ==========================================================
# FIX: Use PKG_CONFIG to reliably find and link SDL libraries
# ==========================================================

# 1. Check if pkg-config is available
find_package(PkgConfig REQUIRED)

# 2. Use pkg-config to find the SDL linker flags
# This uses the common naming conventions for the installed libraries
# pkg_check_modules(SDL2 REQUIRED sdl2 sdl2_image sdl2_ttf)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_image SDL2_ttf)

# Add the executable target. 
add_executable(holiday_art main.cpp)

# 3. Link the executable to the found SDL libraries using PKG_CONFIG variables
target_link_libraries(holiday_art 
    ${SDL2_LDFLAGS} 
)

# 4. Include the SDL header files
target_include_directories(holiday_art PUBLIC
    ${SDL2_INCLUDE_DIRS}
)
# ==========================================================

# Optional: Set a property for easier debugging in VS Code
set_target_properties(holiday_art PROPERTIES CXX_EXTENSIONS ON)