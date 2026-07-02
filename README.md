# Tetris 🧱

A simple Tetris game written in C for the Windows console.

## Features

- Classic falling-block gameplay
- Seven block types: O, J, L, I, S, Z, T
- Block rotation
- Hard drop
- Score counting
- Drop guide preview by " . "

## Requirements

- Windows
- MinGW GCC, or another C compiler that supports `windows.h` and `conio.h`

## Controls
Arrow left/right: move the block

Arrow down: move the block down faster

Arrow up: rotate the block

Enter: hard drop

q: quit

## Build

```powershell
gcc tetris.c -o tetris.exe -luser32
