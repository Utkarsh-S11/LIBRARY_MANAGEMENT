# 🐧 Library Management System — Linux Native C Application

This project is a Linux-native C port of the Library Management System, compiled with **GCC** and preserving 100% binary compatibility with the original binary database files (`Record.dat` and `password.dat`).

---

## 📋 Requirements

- **Linux Distribution**: Ubuntu / Debian / Fedora / Arch / RHEL / Alpine (or WSL2 on Windows)
- **Compiler**: GCC (GNU Compiler Collection, version 4.8 or newer supporting `-std=c11`)
- **Terminal**: Any standard POSIX VT100-compatible terminal emulator (xterm, gnome-terminal, konsole, etc.)

To install GCC build dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential
```

---

## 🔨 Building the Linux Application

### Method 1: Using the Build Script
```bash
chmod +x build_linux.sh
./build_linux.sh
```

### Method 2: Manual GCC Compilation
```bash
gcc -Wall -Wextra -std=c11 Library_Management.c -o Library_Management
chmod +x Library_Management
```

---

## 🚀 Running the Application

Execute the compiled binary from the project directory:
```bash
./Library_Management
```
Or use the launcher script:
```bash
chmod +x run_linux.sh
./run_linux.sh
```

---

## 🔐 Administrator Authentication

- **Default Admin Password**: `admin`
- Password storage is persisted in 10-byte binary format in `password.dat`.
- Initial password setup triggers automatically if `password.dat` is not present.

---

## 💾 Binary Data Format & Compatibility

- **Books Database**: `Record.dat` (Array of 60-byte binary records matching `struct BOOK`).
- **Binary Struct Layout (60 Bytes)**:
  - `id`: offset 0 (4 bytes, `int32_t`)
  - `name`: offset 4 (20 bytes, `char[20]`)
  - `Author`: offset 24 (20 bytes, `char[20]`)
  - `quantity`: offset 44 (4 bytes, `int32_t`)
  - `Price`: offset 48 (4 bytes, `float`)
  - `rackno`: offset 52 (4 bytes, `int32_t`)
  - `cat_ptr`: offset 56 (4 bytes, `uint32_t` VMA category pointer)

### Backup Files
Initial backup copies are stored in:
- `Record.dat.backup-linux`
- `password.dat.backup-linux`

---

## 🛠️ Key Linux Compatibility Enhancements

1. **POSIX Non-Canonical Input**: Replaced Windows `conio.h` and `getch()` with `<termios.h>` raw character input handling that restores terminal attributes automatically upon exit.
2. **ANSI Terminal Formatting**: Replaced `windows.h` and `SetConsoleCursorPosition()` with standard ANSI escape sequences (`\033[y;xH` and `\033[2J\033[H`).
3. **POSIX Microsecond Timing**: Replaced Windows `Sleep(ms)` with POSIX `usleep(microseconds)`.
4. **Input Buffer Safety**: Replaced undefined Windows `fflush(stdin)` with POSIX `tcflush(STDIN_FILENO, TCIFLUSH)`.
5. **Cross-Platform Struct Packing**: Configured `#pragma pack(push, 1)` and explicit fixed-width integer types (`int32_t`, `uint32_t`) to ensure `sizeof(struct BOOK)` remains exactly 60 bytes on both 32-bit and 64-bit Linux architectures.
