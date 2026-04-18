# Nana C++ GUI Installation Guide (Windows)

This guide provides step-by-step instructions on how to install the [Nana C++ GUI library](https://github.com/cnjinhao/nana) on Windows using Microsoft's `vcpkg` package manager. This setup is optimized for seamless integration with Visual Studio.

## Prerequisites

Before you begin, ensure you have the following installed on your system:
* **Git** (available in your system PATH)
* **Visual Studio** (with the "Desktop development with C++" workload installed)

---

## Phase 1: Set up vcpkg

*Skip this phase if you already have vcpkg installed and configured on your machine.*

Open your command prompt (`cmd`) or PowerShell in the directory where you want to store your C++ libraries (e.g., `C:\dev\`), and execute the following steps:

### 1. Clone the vcpkg repository
```bat
git clone [https://github.com/microsoft/vcpkg.git](https://github.com/microsoft/vcpkg.git)
```
### 2. Build vcpkg
Navigate into the newly cloned directory and run the bootstrap script to build the package manager:
```
cd vcpkg
.\bootstrap-vcpkg.bat
```
### 3. Integrate vcpkg with Visual Studio
This crucial step links vcpkg to Visual Studio. It ensures Visual Studio will automatically find the headers and binaries for any library you install, eliminating the need to manually configure Include Directories or Linker paths.
```
.\vcpkg integrate install
```
## Phase 2: Install Nana
### 1. Install the 64-bit Windows version of Nana
Ensure your command line is still inside the vcpkg directory, then run:
```
.\vcpkg install nana:x64-windows
```
Note: This step may take a few minutes. vcpkg will automatically download the necessary source code, required build tools (like CMake), and compile Nana from scratch for your system.
