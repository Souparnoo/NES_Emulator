# NES Emulator

A Nintendo Entertainment System (NES) emulator written in C++ that recreates the core hardware of the original console. The project implements the 6502 CPU, Picture Processing Unit (PPU), Audio Processing Unit (APU), memory bus, cartridge loading, and multiple cartridge mappers to execute NES ROMs.


## Project Structure

```text
Bus.*                System bus and hardware communication
Cartridge.*          ROM loading and cartridge interface
Mapper*.*            Cartridge mapper implementations
6502.*               MOS 6502 CPU emulation
2C02.*               Picture Processing Unit
2A03.*               Audio Processing Unit
PixelGameEngine      Rendering, windowing, and input
```

## Building

### Linux

Install dependencies:

```bash
sudo apt install build-essential libx11-dev libgl1-mesa-dev \
libglu1-mesa-dev libpng-dev libasound2-dev
```

Compile:

```bash
g++ *.cpp -std=c++17 -O2 \
-o vnes \
-lX11 -lGL -lpthread -lpng -lasound
```

Run:

```bash
./vnes
```

## Controls

| NES Button | Keyboard |
| ---------- | -------- |
| Up         | ↑        |
| Down       | ↓        |
| Left       | ←        |
| Right      | →        |
| A          | X        |
| B          | Z        |
| Start      | A        |
| Select     | S        |

## Technical Highlights

* Emulated the complete NES hardware pipeline, including CPU, PPU, APU, and memory bus.
* Implemented instruction decoding, memory mapping, and cartridge handling for multiple mapper types.
* Parsed and executed iNES ROMs while reproducing console memory behavior.
* Built visualization tools for graphics debugging, including pattern tables, palettes, and nametables.
* Used modern C++ to organize hardware components into modular, maintainable classes.

