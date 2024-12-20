# HelloCurl

HelloCurl is a simple C project that demonstrates how to use and statically link the `libcurl` library on Microsoft Windows x64

# Prerequisites
- **CMake** Version 3.19 or higher
- **vcpkg** (bootstraped and integrated)
- **MSVC C Compiler**

# Working on the Project
## Using Visual Studio Code
1. Lanuch Visual Studio Code via `x64 Native Tools Command Prompt`
2. Open the Command Palette (`Ctrl+Shift+P`) and Select `CMake: Configure`.
3. Open the Command Palette (`Ctrl+Shift+P`) and Select `CMake: Select Configure Preset` and choose `windows-debug-static`
4. To debug, open the Command Palette (`Ctril+Shift+P`) and select `CMake: Debug`. 

# Building the Project

1. Clone the repository
2. Lanuch: `x64 Native Tools Command Prompt`
3. Configure the project:
    ```
    cmake --preset windows-release-static
    ```
3. Configure the project:
    ```
    cmake --build --preset windows-release-static
    ```
5. Running the Executable
    ```
    .\build\windows-release-static\HelloCurl.exe
    ```