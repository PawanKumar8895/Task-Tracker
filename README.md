# Study Task Tracker

This repo documents, step-by-step, how a bare-bones console app becomes a dependable study-task tracker. Think of it like a miniature dev blog: each section walks through the reasoning behind a part of the project so you can follow along or adapt it for your own workflow.

## Step 1: Clarify the problem
Busy semesters mean sticky notes and half-remembered due dates. The tracker keeps everything in one `tasks.txt` file so that even when the CLI is closed, you can peek at your list from any text editor. Every task needs a title, an optional due hint, and a tiny flag for whether it is complete.

## Step 2: Define the data contract
We chose a pipe-delimited format because it is human-editable and easy to parse:

```
title|due_note|status
Algorithms HW|2024-09-10|0
```

`status` is `1` when done, `0` otherwise. The file lives under `data/tasks.txt`, and the parser/serializer logic resides in `TaskManager`.

## Step 3: Build the core TaskManager
`include/TaskManager.hpp` + `src/TaskManager.cpp` implement the in-memory list plus persistence helpers. The class:
- Loads every line of the file into `Task` structs.
- Adds new tasks through `addTask`.
- Flips the completion state via `markTaskComplete`.
- Saves the entire list back to disk with `saveToDisk`.

This core stays free of I/O prompts, which keeps it reusable if you later bolt on a GUI or a web API.

## Step 4: Craft the CLI loop
`src/main.cpp` supplies the experience:
1. Ensure the `data/` folder exists and attempt to load existing tasks.
2. Present a simple menu (`list`, `add`, `complete`, `save`, `exit`).
3. Call the appropriate `TaskManager` method based on user input.
4. Auto-save on exit so progress never disappears.

Because the menu is minimal, students can run it between classes without digging through documentation.

## Step 5: Run it yourself
```bash
# from the project root
make            # builds study_tracker
./study_tracker # or run: make run
```
Open `data/tasks.txt` afterward to verify the saved entries. Back the file up with git or a sync service if you hop between machines.

## Step 6: Keep iterating
Ideas once the basics feel solid:
1. Add priority/course fields and filter in the listing view.
2. Export to CSV/JSON for calendar imports.
3. Swap the CLI front end with Qt, ImGui, or even a web dashboard.

Stick to the same data contract and the rest of the app keeps working. Happy tracking!
