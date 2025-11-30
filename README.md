# Study Task Tracker

Simple console program for CS students to keep assignment and study todos organized in a lightweight text file.

## Project layout

- `src/main.cpp` – interactive CLI for viewing, adding, and completing tasks.
- `src/TaskManager.cpp` & `include/TaskManager.hpp` – persistence and in-memory task list.
- `data/tasks.txt` – sample task file; feel free to edit or delete when starting fresh.

## Build and run

```bash
# from the project root
make            # builds study_tracker
./study_tracker # or: make run
```

The program stores tasks in `data/tasks.txt`. You can back this file up with version control or sync services to keep progress across machines.

## Task file format

Each line is `title|due_note|status`, where status is `1` if the task is completed. You can edit this file manually if you like jotting tasks down in a text editor.

## Ideas for extension

- Add priorities or course names and filter by them.
- Export to CSV for spreadsheets.
- Wrap the same logic with a GUI toolkit (Qt, ImGui) for a friendlier interface.
# Task-Tracker
