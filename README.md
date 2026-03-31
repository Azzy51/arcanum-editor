# The Arcanum Editor

A multi-column text editor for manuscript formatting, built with pure C++ and WinAPI.

## Features

- Multi-column page layout with automatic word wrapping
- Spell checking using a 176K word dictionary (trie-based)
- Text search with highlighting
- Auto-save with delta tracking
- Multiple document tabs (up to 10 documents)
- Cursor management and text selection
- Clipboard operations (copy/paste/cut)
- Right-click context menu
- Text alignment (left, right, center, justified)
- Statistics calculation (word count, character count, reading time)
- Table of contents generation

## Building

Compile with MinGW/g++:

```bash
g++ -std=c++11 -DUNICODE -D_UNICODE -mwindows Q7.cpp -o Q7.exe -lgdi32 -luser32 -lcomdlg32
```

## Requirements

- Windows operating system
- MinGW or MSYS2 with g++ compiler

## Usage

1. Run `Q7.exe`
2. Configure your manuscript layout:
   - Columns per page (default: 2)
   - Lines per column (default: 20)
   - Characters per line (default: 80)
3. Click "Start Editing" to begin

## Project Structure

- `Q7.h` - Header file with all declarations
- `Q7.cpp` - Implementation file with all functions
- `OPTED-Dictionary.csv` - Spell check dictionary (not included in repo)

## License

This project was created for educational purposes.
