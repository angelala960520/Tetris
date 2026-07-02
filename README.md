# Console Tetris

A small Tetris game written in C for the Windows console.

## Build

This project uses Windows-specific headers such as `windows.h` and `conio.h`.
Build it with MinGW on Windows:

```powershell
gcc tetris.c -o tetris.exe -luser32
```

## Run

```powershell
.\tetris.exe
```

## Controls

- Arrow left/right: move the block
- Arrow down: move the block down faster
- Arrow up: rotate the block
- Enter: hard drop
- `q`: quit

