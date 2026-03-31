# The Arcanum Editor

A multi-column text editor for manuscript formatting, built with pure C++ and WinAPI.

## About

This project was developed as **Question 7 of Assignment 2** for our **second semester** course. The task was to create a Windows GUI text editor for the fictional publishing house "Blackwood & Hargrove" using pure C++ and WinAPI calls.



![dba2fed4-8128-42bf-9d87-130e400c8950](file:///C:/Users/PC/Pictures/Typedown/dba2fed4-8128-42bf-9d87-130e400c8950.png)



![912f987d-96df-4c24-8e35-8872278b41c8](file:///C:/Users/PC/Pictures/Typedown/912f987d-96df-4c24-8e35-8872278b41c8.png)







## Features

- Multi-column page layout with automatic word wrapping
- Spell checking using a 176K word dictionary (trie-based)
- Text search with highlighting and history
- Auto-save with delta tracking (maintains last 10 saves)
- Multiple document tabs (up to 10 documents)
- Cursor management and text selection
- Clipboard operations (copy/paste/cut)
- Right-click context menu
- Text alignment (left, right, center, justified)
- Statistics calculation (word count, character count, reading time)
- Automatic Table of Contents generation
- Mouse support (click to position, drag to select)
- Auto-numbering page footers

## Building

Compile with MinGW/g++:

```bash
g++ -std=c++11 -DUNICODE -D_UNICODE -mwindows editor.cpp -o arcanum_editor.exe -lgdi32 -luser32 -lcomdlg32
```

## Requirements

- Windows operating system
- MinGW or MSYS2 with g++ compiler

## Usage

1. Run `arcanum_editor.exe`
2. Configure your manuscript layout:
   - Columns per page (default: 2)
   - Lines per column (default: 20)
   - Characters per line (default: 80)
3. Click "Start Editing" to begin

## Project Structure

- `editor.h` - Header file with all declarations
- `editor.cpp` - Implementation file with all functions
- `ASSIGNMENT.md` - The original assignment question

## Keyboard Shortcuts

| Shortcut       | Action                   |
| -------------- | ------------------------ |
| Ctrl+Tab       | Next document tab        |
| Ctrl+Shift+Tab | Previous document tab    |
| Ctrl+S         | Save document            |
| Ctrl+F         | Search                   |
| Ctrl+X         | Cut                      |
| Ctrl+C         | Copy                     |
| Ctrl+V         | Paste                    |
| Ctrl+L         | Align Left               |
| Ctrl+R         | Align Right              |
| Ctrl+E         | Center Align             |
| Ctrl+J         | Justify                  |
| Ctrl+T         | Toggle Table of Contents |
| Ctrl+H         | Search History           |

## License

This project was created for educational purposes.
